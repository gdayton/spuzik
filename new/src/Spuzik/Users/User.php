<?php
/*
 * Copyright 2013 Glenn Dayton
 */
namespace Spuzik\Users;

require "/var/www/new/packages/amazon-php-sdk/autoload.php";

use Aws\Common\Aws;
use Aws\Common\Enum\Region;
use Aws\DynamoDb\DynamoDbClient;
use Aws\DynamoDb\Enum\ComparisonOperator;
use Aws\DynamoDb\Enum\KeyType;
use Aws\DynamoDb\Enum\Type;

class User{

	public $aws;
	public $client;

	public $UserId;
	public $FirstName;
	public $LastName;
	public $LastOn;
	public $Email;
	public $Password;
	public $ProfileMusicId;
	public $ProfilePicture;
	public $RegistrationDate;
	public $AccountType;
	public $Location;

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");
		return $this;
	}

	public function __get($item){
		return $this->$item;
	}

	public function __set($item, $value){
		$this->$item = $value;
	}

	/*
		Sets all variables to what's in passed array.
	*/
	public function withJSON($postArr){
		$this->UserId 				= $postArr['UserId']['N'];
		$this->FirstName			= $postArr['FirstName']['S'];
		$this->LastName				= $postArr['LastName']['S'];
		$this->LastOn				= $postArr['LastOn']['N'];
		$this->Email				= $postArr['Email']['S'];
		$this->Password				= $postArr['Password']['S'];
		$this->ProfileMusicId		= $postArr['ProfileMusicId']['N'];
		$this->ProfilePicture		= $postArr['ProfilePicture']['S'];
		$this->RegistrationDate		= $postArr['RegistrationDate']['N'];
		$this->AccountType			= $postArr['AccountType']['SS'];
		$this->Location				= $postArr['Location']['S'];
	}

	/*
		Only return the important things that matter.
	*/
	public function attrs(){
		return array(
			"UserId" 			=> $this->UserId,
			"FirstName" 		=> $this->FirstName,
			"LastName" 			=> $this->LastName,
			"LastOn" 			=> $this->LastOn,
			"Email" 			=> $this->Email,
			"ProfileMusicId" 	=> $this->ProfileMusicId,
			"ProfilePicture" 	=> $this->ProfilePicture,
			"RegistrationDate"	=> $this->RegistrationDate,
			"AccountType" 		=> $this->AccountType,
			"Location" 			=> $this->Location
		);
	}

	/*
		Grabs user object from DynamoDB according to passed user id.
		Returns null if no user is found with the passed parameter.
		- UserId int User Id in accordance to table's hash.
	*/
	public function fetchWithId($UserId){

		$response = $this->client->getItem(array(
			'TableName' => 'Users',
			'Key'       => array(
				'UserId' => array('N' => $UserId)
			)
		));

		if(count($response["Item"]) > 0){
			$this->withJSON($response["Item"]);
			return $this;
		}else{
			return null;
		}
	}

	/*
		Grabs user object from DynamoDB according to passed email
		- email String Formatted email.
	*/
	public function fetchWithEmail($Email){

		$response = $this->client->getItem(array(
			'TableName' => 'UsersEmail',
			'Key'       => array(
				'Email' => array('S' => $Email)
			)
		));

		return $this->fetchWithId(intval($response["Item"]["UserId"]["N"]));
	}

	/*
		Checks if password matches database password.
		- email String Formatted email.
		- password String In non-md5 format.
	*/
	public function checkCredentials($Email, $Password){
		$user = $this->fetchWithEmail($Email);

		return ($user->Password == md5($Password));
	}

	public function __destruct(){
		$this->aws = null;
		$this->client = null;
	}

	/*
		Call this function once you've populated its contents with data for a new user.
		- type String REG, FBK, GOO, TWI

		Example Usage:
		print_r($ref->createUser("REG"));
		// output is a json file wih newley created file, or an error
	*/
	public function createUser($type){
		switch($type){
			case "REG":
				$this->validateAndParseUser();
				$response = $this->client->batchWriteItem(array(
					"RequestItems" => array(
						"User" => array(
							 array(
								"PutRequest" => array(
									"Item" => array(
										"UserId"			=> array(Type::NUMBER 		=> $this->getUniqueId()),
										"FirstName"			=> array(Type::STRING 		=> $this->FirstName),
										"LastName"			=> array(Type::STRING 		=> $this->LastName),
										"LastOn"			=> array(Type::NUMBER 		=> $this->LastOn),
										"Email"				=> array(Type::STRING 		=> $this->Email),
										"ProfileMusicId"	=> array(Type::STRING 		=> $this->ProfileMusicId),
										"RegistrationDate"	=> array(Type::NUMBER 		=> $this->RegistrationDate),
										"AccountType"		=> array(Type::STRING_SET 	=> array()), //send blank array, nothin more.
										"Location"			=> array(Type::STRING		=> $this->Location)
									)
								)
							)
						)
					)
				));
				$this->toJSON();
				break;
			case "FBK":
				break;
			case "GOO":
				break;
			case "TWI":
				break;
		}
	}

	/*
		Gets a unique integer id that no other user has.
		As website gets more users this method is bound to have more
		collisions that what one would desire for an optimal solution.
	*/
	public function getUniqueID(){
		/* Options
		 * 1 Look up in the database for last written id number.
		 * 2 Generate random 10 digit number.
		 */
		 do{
		 	$randInt = rand(2, 999999999); //Max of 9 numbers in length, this function will be rewritten if we get more than 1 billion users.
			$response = $this->$client->getItem(array(
		 		"TableName" => "User",
		 		"Key"		=> array(
		 			"UserId" => array("N", $randInt)
		 		)
		 	));

		 	if($response != null){ //There must be an id already under that random number
		 		return $randInt;
		 	}
		 }while(true);
	}

	public function getFacebookID(){
		//Add code here to login to facebook and get information about it.
	}

	public function getGooglePlusId(){}
	public function getTwitterId(){}

	/*
		Passes over the data finding errors, and parses entered data into cleaner versions.
		- usage String "update" denotes that fields not requested upon signup be validated and parsed for updates.

		Returns:
			JSON error response with the names of the fields as the error accessor headers.
			{"FirstName": "First name is too long."}
	*/
	public function validateAndParseUser(){
		$jsonEncode = array();

		/*
			FIRST NAME
		*/
		if(!isset($this->FirstName))
			if(strlen(trim($this->FirstName)) <= 1)
				$jsonEncode["FirstName"] = "First name must contain more than 1 character.";
			else if(strlen(trim($this->FirstName)) > 25)
				$jsonEncode["FirstName"] = "First name is too long.";
			else	//First name is good, now clean it up
				$this->FirstName = htmlspecialchars(trim($this->FirstName));
		else
			$jsonEncode["FirstName"] = "You must enter a first name.";

		/*
			LAST NAME
		*/
		if(!isset($this->LastName))
			if(strlen(trim($this->LastName)) <= 1)
				$jsonEncode["LastName"] = "Last name must contain more than 1 character.";
			else if(strlen(trim($this->LastName)) > 25)
				$jsonEncode["LastName"] = "Last name is too long.";
			else	//Last name is good, now clean it up
				$this->LastName = htmlspecialchars(trim($this->LastName));
		else
			$jsonEncode["LastName"] = "You must enter a last name.";

		/*
			Email
		*/
		if(!isset($this->Email))
			if(strlen(trim($this->Email)) <= 1)
				$jsonEncode["Email"] = "Email must contain more than 3 characters.";
			else if(strlen(trim($this->Email)) > 100)
				$jsonEncode["Email"] = "Email is too long.";
			else
				$this->Email = htmlspecialchars(trim($this->Email));	//No reason to check if it's valid, used for account activiation
		else
			$jsonEncode["Email"] = "You must enter an email.";

		echo json_encode($jsonEncode);
	}
}

?>