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

class FavQuoteItem{
	public $aws;
	public $client;

	public $FQLId;
	public $Text;
	public $Author;
	public $UserId;

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");
	}

	/*
		Inserts a FavQuote item into the database.
		- uniqueId String Id of item that was inserted into the database.
	*/
	public function add($data){
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			//insert fq into database
			$uniqueId = uniqid();
			$response = $this->client->batchWriteItem(array(
				"RequestItems" => array(
					"FavQuoteLyric" => array(
						 array(
							"PutRequest" => array(
								"Item" => array(
									"FQLId"		=> array(Type::STRING => $uniqueId),
									"UserId"	=> array(Type::NUMBER => $userId),
									"Text"		=> array(Type::STRING => htmlspecialchars($data["Text"])),
									"Author"	=> array(Type::STRING => htmlspecialchars($data["Author"]))
								)
							)
						)
					)
				)
			));
			$this->FQLId = $uniqueId;
			$this->UserId = $userId;
			$this->Text = htmlspecialchars($data["Text"]);
			$this->Author = htmlspecialchars($data["Author"]);

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
				'TableName' => 'FavQuoteLyric',
				'Key' => array(
					'FQLId' => array(
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
			'TableName' => 'FavQuoteLyric',
			'Key'       => array(
				'FQLId' => array('S' => $id)
			)
		));

		$this->addSoft($response["Item"]);
		return $this;
	}

	/*
		Populates object with their values, but without saving the object to the database.
	*/
	public function addSoft($attrs){
		$this->FQLId	= $attrs["FQLId"]["S"];
		$this->Text		= $attrs["Text"]["S"];
		$this->Author	= $attrs["Author"]["S"];
		$this->UserId	= $attrs["UserId"]["N"];
	}

	public function __get($value){
		return $this->$value;
	}

	public function __set($key, $value){
		$this->$key = $value;
	}

	public function attrs(){
		return array(
			"FQLId"		=> $this->FQLId,
			"Text"		=> $this->Text,
			"Author"	=> $this->Author,
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
class FavQuote{
	public $aws;
	public $client;

	public $UserId;
	public $FQLIds; //array of FavQuoteItem objects, not ids

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");

		$this->UserId = 0;
		$this->FQLIds = array();
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

		foreach($this->FQLIds as $fqItem){
			array_push($data, $fqItem->attrs());
		}

		return $data;
	}

	/*
		Adds a new fq object into its area, and then appends it's id onto the FQLIds list.
	*/
	public function add($data){
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$fqItem = new FavQuoteItem();
			//item added to database.
			$item = $fqItem->add($data);
			$uniqueId = $item->FQLId;

			$responseLookup = $this->client->getItem(array(
				'TableName' => 'FavQuoteLyricIndex',
				'Key'       => array(
					'UserId' => array('N' => $userId)
				)
			));

			if(count($responseLookup["Item"]) == 0){ //you need to create an index, there are no items in the lineupindex
				$response = $this->client->batchWriteItem(array(
					"RequestItems" => array(
						"FavQuoteLyricIndex" => array(
							 array(
								"PutRequest" => array(
									"Item" => array(
										"UserId"	=> array(Type::NUMBER => $userId),
										"FQLIds"	=> array(Type::STRING_SET => array($uniqueId))
									)
								)
							)
						)
					)
				));
			}else{							   //you need to update an index
				$prevIds = $responseLookup["Item"]["FQLIds"]["SS"];
				array_push($prevIds, $uniqueId);
				$response = $this->client->updateItem(array(
					"TableName" => "FavQuoteLyricIndex",
						"Key" => array(
							"UserId" => array(
								Type::NUMBER => $userId
							)
						),
						"AttributeUpdates" => array(
							"FQLIds" => array(
								"Action" => AttributeAction::PUT,
								"Value" => array(
									Type::STRING_SET => $prevIds
								)
							)
						)
				));
			}

			$fqItem->toJSON();
		}else{
			echo "error";
		}
	}

	/*
		Removes the FavQuoteItem object of of FavQuote object, and destroys it
	*/
	public function delete($id){
		$favQuoteItem = new FavQuoteItem();
		$favQuoteItem->delete($id);
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$responseLookup = $this->client->getItem(array(
				'TableName' => 'FavQuoteLyricIndex',
				'Key'       => array(
					'UserId' => array('N' => (int)$userId)
				)
			));

			$prevIds = $responseLookup["Item"]["FQLIds"]["SS"];
			$prevIds = array_diff($prevIds, array($id));

			$newIds = array();
			foreach($prevIds as $p){
				array_push($newIds, $p);
			}

			if(count($newIds) > 0){
				$response = $this->client->updateItem(array(
					"TableName" => "FavQuoteLyricIndex",
						"Key" => array(
							"UserId" => array(
								Type::NUMBER => (int)$userId
							)
						),
						"AttributeUpdates" => array(
							"FQLIds" => array(
								"Action" => AttributeAction::PUT,
								"Value" => array(
									Type::STRING_SET => $newIds
								)
							)
						)
				));
			}else{ //just delete the entire index
				$response = $this->client->deleteItem(array(
					'TableName' => 'FavQuoteLyricIndex',
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

	/*
		Push all of the fq item onto object according to the User's id
	*/
	public function get($id){
		$this->UserId = $id;
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$responseLookup = $this->client->getItem(array(
				'TableName' => 'FavQuoteLyricIndex',
				'Key'       => array(
					'UserId' => array('N' => $id)
				)
			));

			$prevIds = $responseLookup["Item"]["FQLIds"]["SS"];

			if(count($prevIds) > 0){
				foreach($prevIds as $fqIndv){
					$newFq = new FavQuoteItem();
					$newFq->get($fqIndv);
					array_push($this->FQLIds, $newFq);
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