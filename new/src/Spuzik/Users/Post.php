<?php
//6XDG645 Mercedes S-Class 550 - Seen East Dunne Ave Morgan Hill
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


/*
	Database Schema
	Post ---------------------------
		-PostId		STRING		HASH
		-UserId		NUMBER
		-Date		NUMBER
		-Post		STRING_SET
		-Claps		NUMBER_SET
		-Context	STRING_SET
		-Category	STRING
	--------------------------------

	PostIndex ----------------------
		-UserId		NUMBER		HASH
		-PostId 	STRING
	--------------------------------

	PostProfileIndex ---------------
		-UserId		NUMBER		HASH
		-PosterIds	NUMBER_SET
	--------------------------------
*/


class Post{
	public $aws;
	public $client;

	public $PostId;
	public $UserId;
	public $Date;
	public $Post;
	public $Claps;
	public $Context;
	public $Category;

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");
	}

	public function attrs(){
		return array(
			"PostId" 	 => $this->PostId,
			"UserId" 	 => $this->UserId,
			"Date"	 	 => $this->Date,
			"Post"	 	 => $this->Post,
			"Claps"	 	 => $this->Claps,
			"Context"	 => $this->Context,
			"Category"	 => $this->Category
		);
	}

	public function create($attrs){
		/*
			What attrs must contain:
			Post_Text				Text/Content of the posting. Can be left blank.
			Post_Secondary_Type		Image, Link, or Music
			Post_Secondary			Id of Image, Link, or Music
		*/
		$validateResponse = $this->validateParsePost();
		//put if statement here, checking to see if validateParsePost
		//returned any errors that need to be displayed.
		if($validateResponse->status = "success"){
			$uniqueId = uniqid();
			$session = new Session();
			$userId = $session->currentId();
			if($userId != false){
				$response = $this->client->batchWriteItem(array(
					"RequestItems" => array(
						"Post" => array(
							 array(
								"PutRequest" => array(
									"Item" => array(
										"PostId"	=> array(Type::STRING => $uniqueId),
										"UserId"	=> array(Type::NUMBER => $userId),
										"Date"		=> array(Type::NUMBER => strtotime("now")),
										"Post"		=> array(Type::STRING_SET => $this->formatPost()),
										"Claps"		=> array(Type::NUMBER_SET => array()),
										"Context"	=> array(Type::STRING_SET => $this->formatContext()),
										"Category"	=> array(Type::STRING => $this->Category)
									)
								)
							)
						)
					)
				));
			else{ //you must be logged in to make a post.
				echo "error";
			}
		}else{
			echo $validateResponse;
		}
	}

	/*
		Takes the current variables for this object and verifies that they comply, and
		then they format it.

		Example attrs:

		$this->validateParsePost(array(
			"PostText" => "This is a post that is really cool.",
			"PostType" => "image",
			"PostSecondary" => "image-id-here"
		));
	*/
	public function validateParsePost($attrs){
		$jsonEncode = array("status"=>"error");

		if(strlen($attrs["PostText"]) > 5000)
			$jsonEncode['Post'] = "Your post exceeds the maximum allowed length.";
		else{
			if(isset($attrs["PostType"))
				$this->Post = array($attrs["PostText"]);
				switch($attrs["PostType"]){
					case "text":
						$this->Post = array(htmlspecialchars(trim($attrs["PostText"])));
						break;
					case "image":
						if(isset($attrs["PostSecondary"]))
							$this->Post = array(
								htmlspecialchars(trim($attrs["PostText"])),
								array(
									"image",
									$attrs["PostSecondary"]	//this is the image id
								)
							);
						else
							$jsonEncode["Post"] = "Declaration of image requires that image id be present.";
						break;
					case "link":
						$this->Post = array(htmlspecialchars(trim($attrs["PostText"])));
						if(isset($attrs["PostSecondary"]))
							$this->Post = array(
								htmlspecialchars(trim($attrs["PostText")),
								array(
									"link",
									$attrs["PostSecondary"] //this is the link id
								);
							);
						else
							$jsonEncode["Post"] = "Declaration of link requires that link id be present.";
						break;
					case "tune":
						$this->Post = array(htmlspecialchars(trim($attrs["PostText"])));
						if(isset($attrs["PostSecondary"]))
							$this->Post = array(
								htmlspecialchars(trim($attrs["PostText"])),
								array(
									"tune",
									$attrs["PostSecondary"] //this is the tune id
								);
							);
						else
							$jsonEncode["Post"] = "Declaration of tune requires that the id be present.";
						break;
				}
			else //assume that it is just a regular text posting.
				$this->Post = array(htmlspecialchars(trim($attrs["PostText"])));
		}

		if(count($jsonEncode) == 0)
			$jsonEncode["status"] = "success";
		return json_encode($jsonEncode);
	}

	public function toJSON(){
		echo json_encode($this->attrs());
	}

	public function __get($key){
		return $this->$key;
	}

	public function __set($key, $value){
		$this->$key = $value;
	}
}
?>