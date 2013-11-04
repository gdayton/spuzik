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

class AboutMe{
	public $aws;
	public $client;

	public $UserId;
	public $Age;
	public $Location;
	public $Bio;
	public $Nickname;

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");
		return $this;
	}

	/*
		Converts the AboutMe object into something that backbone can use.
	*/
	public function attrs(){
		return array(
			"UserId"	=>	$this->UserId,
			"Age"		=>	$this->Age,
			"Location"	=>	$this->Location,
			"Bio"		=>	$this->Bio,
			"Nickname"	=>	$this->Nickname
		);
	}

	/*
		Updates the about me information with an associative array.
	*/
	public function update($Info){
		$session = new Session();
		$userId = $session->currentId();
		if($userId != false){
			$response = $this->client->updateItem(array(
				"TableName" => "AboutMe",
					"Key" => array(
						"UserId" => array(
							Type::NUMBER => $userId
						)
					),
					"AttributeUpdates" => array(
						"Age" => array(
							"Action" => AttributeAction::PUT,
							"Value" => array(
								Type::STRING => htmlspecialchars(trim($Info["Age"]))
							)
						),
						"Location" => array(
							"Action" => AttributeAction::PUT,
							"Value" => array(
								Type::STRING => htmlspecialchars(trim($Info["Location"]))
							)
						),
						"Bio" => array(
							"Action" => AttributeAction::PUT,
							"Value" => array(
								Type::STRING => htmlspecialchars(trim($Info["Bio"]))
							)
						),
						"Nickname" => array(
							"Action" => AttributeAction::PUT,
							"Value" => array(
								Type::STRING => htmlspecialchars(trim($Info["Nickname"]))
							)
						)
					)
			));
		}else{
			echo "error";
		}
	}

	/*
		Create an AboutMe object with passed attributes
	*/
	public function withJSON($attr){
		$this->UserId	= $attr["UserId"]["N"];
		$this->Age		= $attr["Age"]["S"];
		$this->Location	= $attr["Location"]["S"];
		$this->Bio		= $attr["Bio"]["S"];
		$this->Nickname = $attr["Nickname"]["S"];
	}

	/*
		Returns a AboutMe object with accessable info fields.
	*/
	public function get($id){
		$response = $this->client->getItem(array(
			'TableName' => 'AboutMe',
			'Key'       => array(
				'UserId' => array('N' => $id)
			)
		));

		$this->withJSON($response["Item"]);
		return $this;
	}

	public function __get($key){
		return $this->$key;
	}

	public function __set($key, $value){
		$this->$key = $value;
	}

	public function toJSON(){
		echo json_encode($this->attrs());
	}
}
?>