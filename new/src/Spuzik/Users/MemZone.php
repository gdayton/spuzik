<?php
/*
 * Copyright 2013 Glenn Dayton
 */
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

class MemZoneItem{
	public $aws;
	public $client;

	public $MemId;
	public $Text;
	public $Date;
	public $UserId;

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");
	}

	/*
		Inserts a FavQuote item into the database.
	*/
	public function add($data){
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			//insert fq into database
			$uniqueId = uniqid();
			$response = $this->client->batchWriteItem(array(
				"RequestItems" => array(
					"MemZone" => array(
						 array(
							"PutRequest" => array(
								"Item" => array(
									"MemId"		=> array(Type::STRING => $uniqueId),
									"UserId"	=> array(Type::NUMBER => $userId),
									"Text"		=> array(Type::STRING => htmlspecialchars($data["Text"])),
									"Date"		=> array(Type::STRING => htmlspecialchars($data["Date"]))
								)
							)
						)
					)
				)
			));
			$this->MemId = $uniqueId;
			$this->UserId = $userId;
			$this->Text = htmlspecialchars($data["Text"]);
			$this->Date = htmlspecialchars($data["Date"]);

			return $this;
		}else{
			return 0;
		}
	}

	/*
		Deletes a FavQuote according to its id.
	*/
	public function delete($id){
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$response = $this->client->deleteItem(array(
				'TableName' => 'MemZone',
				'Key' => array(
					'MemId' => array(
						Type::STRING => $id
					)
				)
			));
		}else{
			echo "error";
		}
	}

	/*
		Retrieves a FavQuote according to its id.
	*/
	public function get($id){
		//get fq from database.
		$response = $this->client->getItem(array(
			'TableName' => 'MemZone',
			'Key'       => array(
				'MemId' => array('S' => $id)
			)
		));

		$this->addSoft($response["Item"]);
		return $this;
	}

	public function __get($value){
		return $this->$value;
	}

	public function __set($key, $value){
		$this->$key = $value;
	}

	public function addSoft($attrs){
		$this->MemId	= $attrs["MemId"]["S"];
		$this->Text		= $attrs["Text"]["S"];
		$this->Date		= $attrs["Date"]["S"];
		$this->UserId	= $attrs["UserId"]["N"];
	}

	public function attrs(){
		return array(
			"MemId"		=> $this->MemId,
			"Text"		=> $this->Text,
			"Date"		=> $this->Date,
			"UserId"	=> $this->UserId
		);
	}

	public function toJSON(){
		echo json_encode($this->attrs());
	}
}

/*
	Serves a collection like interface, that also sorts database records via the UserId
*/
class MemZone{
	public $aws;
	public $client;

	public $UserId;
	public $MemIds;

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");

		$this->UserId = 0;
		$this->MemIds = array();
	}

	public function __get($key){
		return $this->$key;
	}

	public function __set($key,$value){
		$this->$key = $value;
	}

	/*
		Returns a list of all fq objects in the following format:
		[
			{UserId:"this"},
			...
		]
	*/
	public function attrs(){
		$data = array();

		foreach($this->MemIds as $memItem){
			array_push($data, $memItem->attrs());
		}

		return $data;
	}

	public function add($data){
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$memItem = new MemZoneItem();
			//item added to database.
			$item = $memItem->add($data);
			$uniqueId = $item->MemId;

			$responseLookup = $this->client->getItem(array(
				'TableName' => 'MemZoneIndex',
				'Key'       => array(
					'UserId' => array('N' => $userId)
				)
			));

			if(count($responseLookup["Item"]) == 0){ //you need to create an index, there are no items in the lineupindex
				$response = $this->client->batchWriteItem(array(
					"RequestItems" => array(
						"MemZoneIndex" => array(
							 array(
								"PutRequest" => array(
									"Item" => array(
										"UserId"	=> array(Type::NUMBER => $userId),
										"MemIds"	=> array(Type::STRING_SET => array($uniqueId))
									)
								)
							)
						)
					)
				));
			}else{							   //you need to update an index
				$prevIds = $responseLookup["Item"]["MemIds"]["SS"];
				array_push($prevIds, $uniqueId);
				$response = $this->client->updateItem(array(
					"TableName" => "MemZoneIndex",
						"Key" => array(
							"UserId" => array(
								Type::NUMBER => $userId
							)
						),
						"AttributeUpdates" => array(
							"MemIds" => array(
								"Action" => AttributeAction::PUT,
								"Value" => array(
									Type::STRING_SET => $prevIds
								)
							)
						)
				));
			}

			$memItem->toJSON();
		}else{
			echo "error";
		}
	}

	public function delete($id){
		$memZoneItem = new MemZoneItem();
		$memZoneItem->delete($id);
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$responseLookup = $this->client->getItem(array(
				'TableName' => 'MemZoneIndex',
				'Key'       => array(
					'UserId' => array('N' => (int)$userId)
				)
			));

			$prevIds = $responseLookup["Item"]["MemIds"]["SS"];
			$prevIds = array_diff($prevIds, array($id));

			$newIds = array();
			foreach($prevIds as $p){
				array_push($newIds, $p);
			}

			if(count($newIds) > 0){
				$response = $this->client->updateItem(array(
					"TableName" => "MemZoneIndex",
						"Key" => array(
							"UserId" => array(
								Type::NUMBER => (int)$userId
							)
						),
						"AttributeUpdates" => array(
							"MemIds" => array(
								"Action" => AttributeAction::PUT,
								"Value" => array(
									Type::STRING_SET => $newIds
								)
							)
						)
				));
			}else{ //just delete the entire index
				$response = $this->client->deleteItem(array(
					'TableName' => 'MemZoneIndex',
					'Key' => array(
						'UserId' => array(
							Type::NUMBER => (int)$userId
						)
					)
				));
			}
		}else{
			echo "error";
		}
	}

	public function get($id){
		$this->UserId = $id;
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$responseLookup = $this->client->getItem(array(
				'TableName' => 'MemZoneIndex',
				'Key'       => array(
					'UserId' => array('N' => $id)
				)
			));

			$prevIds = $responseLookup["Item"]["MemIds"]["SS"];

			if(count($prevIds) > 0){
				foreach($prevIds as $memIndv){
					$newMem = new MemZoneItem();
					$newMem->get($memIndv);
					array_push($this->MemIds, $newMem);
				}
			}else{
				return $this;
			}
		}

		return $this;
	}

	public function toJSON(){
		echo json_encode($this->attrs());
	}
}
?>