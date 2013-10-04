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

class LinkItem{
	public $aws;
	public $client;

	public $LinkId;
	public $Text;
	public $Url;
	public $UserId;

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");
	}

	/*
		Inserts a Link item into the database.
	*/
	public function add($data){
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			//insert fq into database
			$uniqueId = uniqid();
			$response = $this->client->batchWriteItem(array(
				"RequestItems" => array(
					"Links" => array(
						 array(
							"PutRequest" => array(
								"Item" => array(
									"LinkId"	=> array(Type::STRING => $uniqueId),
									"UserId"	=> array(Type::NUMBER => $userId),
									"Text"		=> array(Type::STRING => htmlspecialchars($data["Text"])),
									"Url"		=> array(Type::STRING => htmlspecialchars($data["Url"]))
								)
							)
						)
					)
				)
			));
			$this->LinkId = $uniqueId;
			$this->UserId = $userId;
			$this->Text = htmlspecialchars($data["Text"]);
			$this->Url = htmlspecialchars($data["Url"]);

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
				'TableName' => 'Links',
				'Key' => array(
					'LinkId' => array(
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
			'TableName' => 'Links',
			'Key'       => array(
				'LinkId' => array('S' => $id)
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
		$this->LinkId	= $attrs["LinkId"]["S"];
		$this->Text		= $attrs["Text"]["S"];
		$this->Url		= $attrs["Url"]["S"];
		$this->UserId	= $attrs["UserId"]["N"];
	}

	public function attrs(){
		return array(
			"LinkId"	=> $this->LinkId,
			"Text"		=> $this->Text,
			"Url"		=> $this->Url,
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
class Links{
	public $aws;
	public $client;

	public $UserId;
	public $LinkIds;

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");

		$this->UserId = 0;
		$this->LinkIds = array();
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

		foreach($this->LinkIds as $linkItem){
			array_push($data, $linkItem->attrs());
		}

		return $data;
	}

	public function add($data){
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$linkItem = new LinkItem();
			//item added to database.
			$item = $linkItem->add($data);
			$uniqueId = $item->LinkId;

			$responseLookup = $this->client->getItem(array(
				'TableName' => 'LinkIndex',
				'Key'       => array(
					'UserId' => array('N' => $userId)
				)
			));

			if(count($responseLookup["Item"]) == 0){ //you need to create an index, there are no items in the lineupindex
				$response = $this->client->batchWriteItem(array(
					"RequestItems" => array(
						"LinkIndex" => array(
							 array(
								"PutRequest" => array(
									"Item" => array(
										"UserId"	=> array(Type::NUMBER => $userId),
										"LinkIds"	=> array(Type::STRING_SET => array($uniqueId))
									)
								)
							)
						)
					)
				));
			}else{							   //you need to update an index
				$prevIds = $responseLookup["Item"]["LinkIds"]["SS"];
				array_push($prevIds, $uniqueId);
				$response = $this->client->updateItem(array(
					"TableName" => "LinkIndex",
						"Key" => array(
							"UserId" => array(
								Type::NUMBER => $userId
							)
						),
						"AttributeUpdates" => array(
							"LinkIds" => array(
								"Action" => AttributeAction::PUT,
								"Value" => array(
									Type::STRING_SET => $prevIds
								)
							)
						)
				));
			}

			$linkItem->toJSON();
		}else{
			echo "error";
		}
	}

	public function delete($id){
		$linkItem = new LinkItem();
		$linkItem->delete($id);
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$responseLookup = $this->client->getItem(array(
				'TableName' => 'LinkIndex',
				'Key'       => array(
					'UserId' => array('N' => (int)$userId)
				)
			));

			$prevIds = $responseLookup["Item"]["LinkIds"]["SS"];
			$prevIds = array_diff($prevIds, array($id));

			$newIds = array();
			foreach($prevIds as $p){
				array_push($newIds, $p);
			}

			if(count($newIds) > 0){
				$response = $this->client->updateItem(array(
					"TableName" => "LinkIndex",
						"Key" => array(
							"UserId" => array(
								Type::NUMBER => (int)$userId
							)
						),
						"AttributeUpdates" => array(
							"LinkIds" => array(
								"Action" => AttributeAction::PUT,
								"Value" => array(
									Type::STRING_SET => $newIds
								)
							)
						)
				));
			}else{ //just delete the entire index
				$response = $this->client->deleteItem(array(
					'TableName' => 'LinkIndex',
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
				'TableName' => 'LinkIndex',
				'Key'       => array(
					'UserId' => array('N' => (int)$id)
				)
			));

			$prevIds = $responseLookup["Item"]["LinkIds"]["SS"];

			if(count($prevIds) > 0){
				foreach($prevIds as $linkIndv){
					$newLink = new LinkItem();
					$newLink->get($linkIndv);
					array_push($this->LinkIds, $newLink);
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