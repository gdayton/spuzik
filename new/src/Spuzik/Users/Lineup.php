<?php
namespace Spuzik\Users;

require "/var/www/new/packages/amazon-php-sdk/autoload.php";
require_once "Session.php";

use Aws\Common\Aws;
use Aws\Common\Enum\Region;
use Aws\DynamoDb\DynamoDbClient;
use Aws\DynamoDb\Enum\ComparisonOperator;
use Aws\DynamoDb\Enum\KeyType;
use Aws\DynamoDb\Enum\Type;
use Aws\DynamoDb\Enum\AttributeAction;

class LineupItem{
	public $aws;
	public $client;

	public $LineupId;
	public $UserId;
	public $Text;
	public $PhotoURL;
	public $Position;

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");
	}

	public function __get($name){
		return $this->$get;
	}

	public function __set($name, $vale){
		$this->$name = $value;
	}

	/*
		Loads lineup items from the database.
	*/
	public function load($LineupId){
		$response = $this->client->getItem(array(
			'TableName' => 'Lineup',
			'Key'       => array(
				'LineupId' => array('S' => $LineupId)
			)
		));

		$this->withJSON($response["Item"]);
		return $this;
	}

	public function withJSON($json){
		$this->LineupId		= $json["LineupId"]["S"];
		$this->UserId		= $json["UserId"]["N"];
		$this->Text			= $json["Text"]["S"];
		$this->PhotoURL		= $json["PhotoURL"]["S"];
		$this->Position		= $json["Position"]["N"];
	}

	public function attrs(){
		if(isset($this->LineupId)){
			return array(
				"LineupId" 	=> $this->LineupId,
				"UserId"	=> $this->UserId,
				"Text"		=> $this->Text,
				"PhotoURL"	=> $this->PhotoURL,
				"Position"	=> $this->Position
			);
		}else{
			return "null";
		}
	}
}

class Lineup{
	public $aws;
	public $client;

	public $LineupItems;

	public function __construct(){
		$this->LineupItems = array();
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");

		return $this;
	}

	/*
		Put item into Lineup
	*/
	public function add($LineupItem){
		array_push($this->LineupItems,$LineupItem);
	}

	/*
		TODO Consider ordering these items by Position
	*/
	public function toJSON(){
		$jsonEncode = array();

		if(count($this->LineupItems) > 0){
			foreach($this->LineupItems as $li){
				array_push($jsonEncode, $li->attrs());
			}

			$jsonEncode = array_reverse($jsonEncode);
			echo json_encode($jsonEncode);
		}else{
			echo "error";
		}
	}

	public function load($UserId){
		$response = $this->client->getItem(array(
			'TableName' => 'LineupIndex',
			'Key'       => array(
				'UserId' => array('N' => $UserId)
			)
		));

		if(count($response["Item"]["LineupItemIds"]["SS"]) > 0){
			foreach($response["Item"]["LineupItemIds"]["SS"] as $LineupItemId){
				$LineupItem = new LineupItem();
				$LineupItem->load($LineupItemId);
				$this->add($LineupItem);
			}
		}
		return $this;
	}

	public function addLineup($text){
		//Write to the databox
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$uniqueId = uniqid();
			$response = $this->client->batchWriteItem(array(
				"RequestItems" => array(
					"Lineup" => array(
						 array(
							"PutRequest" => array(
								"Item" => array(
									"LineupId"	=> array(Type::STRING => $uniqueId),
									"UserId"	=> array(Type::NUMBER => $userId),
									"PhotoURL"	=> array(Type::STRING => "-"),
									"Position"	=> array(Type::NUMBER => 1),
									"Text"		=> array(Type::STRING => $text)
								)
							)
						)
					)
				)
			));

			$responseLookup = $this->client->getItem(array(
				'TableName' => 'LineupIndex',
				'Key'       => array(
					'UserId' => array('N' => $userId)
				)
			));

			if(count($responseLookup["Item"]) == 0){ //you need to create an index, there are no items in the lineupindex
				$response = $this->client->batchWriteItem(array(
					"RequestItems" => array(
						"LineupIndex" => array(
							 array(
								"PutRequest" => array(
									"Item" => array(
										"UserId"	=> array(Type::NUMBER => $userId),
										"LineupItemIds"	=> array(Type::STRING_SET => array($uniqueId))
									)
								)
							)
						)
					)
				));
			}else{							   //you need to update an index
				$prevIds = $responseLookup["Item"]["LineupItemIds"]["SS"];
				array_push($prevIds, $uniqueId);
				$response = $this->client->updateItem(array(
					"TableName" => "LineupIndex",
						"Key" => array(
							"UserId" => array(
								Type::NUMBER => $userId
							)
						),
						"AttributeUpdates" => array(
							"LineupItemIds" => array(
								"Action" => AttributeAction::PUT,
								"Value" => array(
									Type::STRING_SET => $prevIds
								)
							)
						)
				));
			}
		}else{
			echo "Not logged in";
		}
	}

	public function removeLineup($id){
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			//remove item from the data table
			$response = $this->client->deleteItem(array(
				'TableName' => 'Lineup',
				'Key' => array(
					'LineupId' => array(
						Type::STRING => $id
					)
				)
			));

			//remove the item from the lineup index next
			$responseLookup = $this->client->getItem(array(
				'TableName' => 'LineupIndex',
				'Key'       => array(
					'UserId' => array('N' => $userId)
				)
			));

			$prevIds = $responseLookup["Item"]["LineupItemIds"]["SS"];
			$prevIds = array_diff($prevIds, array($id));

			$newIds = array();
			foreach($prevIds as $p)
				array_push($newIds, $p);

			if(count($newIds) > 0){
				$response = $this->client->updateItem(array(
					"TableName" => "LineupIndex",
						"Key" => array(
							"UserId" => array(
								Type::NUMBER => (int)$userId
							)
						),
						"AttributeUpdates" => array(
							"LineupItemIds" => array(
								"Action" => AttributeAction::PUT,
								"Value" => array(
									Type::STRING_SET => $newIds
								)
							)
						)
				));
			}else{ //just delete the entire index
				$response = $this->client->deleteItem(array(
					'TableName' => 'LineupIndex',
					'Key' => array(
						'UserId' => array(
							Type::NUMBER => (int)$userId
						)
					)
				));
			}
		}
	}
}
?>