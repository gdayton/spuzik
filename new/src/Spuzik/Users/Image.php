<?php
require "/var/www/new/packages/amazon-php-sdk/autoload.php";
require_once "Session.php";

use Aws\Common\Aws;
use Aws\Common\Enum\Region;

use Aws\S3\Enum\CannedAcl;
use Aws\S3\Exception\S3Exception;

use Aws\DynamoDb\DynamoDbClient;
use Aws\DynamoDb\Enum\ComparisonOperator;
use Aws\DynamoDb\Enum\KeyType;
use Aws\DynamoDb\Enum\Type;
use Aws\DynamoDb\Enum\AttributeAction;

use Guzzle\Http\EntityBody;

class Image{
	public $aws;
	public $client;
	public $awsS3;
	public $s3;

	public $PhotoId;
	public $Date;
	public $Description;
	public $UserId;
	public $Extension;

	public function __construct(){
		//For Database connection
		$this->aws 		= Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client 	= $this->aws->get("dynamodb");

		//For S3 connection
		$this->awsS3 	= Aws::factory("/var/www/new/packages/amazon-php-sdk/config_s3.php");
		$this->s3		= $this->awsS3->get("s3");
	}

	public function get($id, $returnJSON = false){
		//Using the getItem operation, you can grab more of the items from the database using less amount of operations.
		$response = $this->client->getItem(array(
			"TableName"	=> "Image",
			"Key"		=> array(
				"ImageId" => array( Type::STRING => $id)
			)
		));

		if($response != null){
			$this->ImageId = $response["Item"]["ImageId"]["S"];
			$this->UserId = $response["Item"]["UserId"]["N"];
			$this->Date	= $response["Item"]["Date"]["N"];
			$this->Description = $response["Item"]["Description"]["S"];
			$this->Extension = $response["Item"]["Extension"]["S"];
		}else{
			echo "null";
		}

		if($returnJSON)
			$this->toJSON();
	}

	/*
		Add image id, and add a description, the image id will have been made from the UploadHandler class.
	*/
	public function create($fileId){
		$session = new \Spuzik\Users\Session();
		$userId = $session->currentId();
		if($userId != false){
			$id = explode(".",$fileId);

			$this->transferToS3($fileId);

			$response = $this->client->putItem(array(
				"TableName" => "Image",
				"Item"		=> $this->client->formatAttributes(array(
					"ImageId"		=> $id[0],
					"Date"			=> strtotime("now"),
					"Description"	=> "-",
					"UserId"		=> (int)$userId,
					"Extension"		=> $id[1]
					)
				)
			));

			//You gotta update the photo index now.
			$responseIndex = $this->client->getItem(array(
				"TableName"	=> "ImageIndex",
				"Key"		=> array(
					"UserId" => array(Type::NUMBER => $userId)
				)
			));

			$imageIds = $responseIndex["Item"]["ImageIds"]["SS"];

			if(count($imageIds) > 0){
				array_push($imageIds, (string)$id[0]);

				$response = $this->client->updateItem(array(
					"TableName"	=> "ImageIndex",
					"Key"	    => array(
						"UserId" => array(
							Type::NUMBER => $userId
						)
					),
					"AttributeUpdates"	=> array(
						"ImageIds" => array(
							"Action" => AttributeAction::PUT,
							"Value"  => array(
								Type::STRING_SET => $imageIds
							)
						)
					)
				));
			}else{
				$response = $this->client->putItem(array(
					"TableName"	=> "ImageIndex",
					"Item"		=> $this->client->formatAttributes(array(
						"UserId" 	=> $userId,
						"ImageIds"	=> array($id[0])
					))
				));
			}
		}else{
			echo "null";
		}
	}

	public function update($attrs){
		$session = new \Spuzik\Users\Session();
		$userId = $session->currentId();
		if($userId != false){
			$imgID = trim($attrs['ImageId']);
			$response = $this->client->updateItem(array(
				"TableName"	=> "Image",
				"Key"	    => array(
					"ImageId" => array(
						Type::STRING => $imgID
					)
				),
				"AttributeUpdates"	=> array(
					"Description" => array(
						"Action" => AttributeAction::PUT,
						"Value"  => array(
							Type::STRING => htmlspecialchars(trim($attrs['Description']))
						)
					)
				)
			));
		}
	}
	/*

	*/

	/*
		Given the id of the image it transfers all 5 images over to the S3 instance.
	*/
	public function transferToS3($idURL){
		//REGULAR				Original File
		$result = $this->s3->putObject(array(
			'Bucket' => "spuzik",
			'Key'    => "/o/".$idURL,
			'Body'   => Guzzle\Http\EntityBody::factory(fopen("/var/www/new/files/o/".$idURL, 'rb')),
			'ACL'	 => "public-read"
		));

		//THUMBNAIL				80 x 80
		$result = $this->s3->putObject(array(
			'Bucket' => "spuzik",
			'Key'    => "/t/".$idURL,
			'Body'   => Guzzle\Http\EntityBody::factory(fopen("/var/www/new/files/t/".$idURL, 'rb')),
			'ACL'	 => "public-read"
		));

		//FEED + SLIDESHOW		520 x 325
		$result = $this->s3->putObject(array(
			'Bucket' => "spuzik",
			'Key'    => "/fs/".$idURL,
			'Body'   => Guzzle\Http\EntityBody::factory(fopen("/var/www/new/files/fs/".$idURL, 'rb')),
			'ACL'	 => "public-read"
		));
	}

	/*
		Gets all 5 links to the Amazon S3 instance, including the thumbnail, feed, regular image, and the zone out image sizes.
	*/
	public function getS3($id){
		$responseIndex = $this->client->getItem(array(
			"TableName"	=> "ImageIndex",
			"Key"		=> array(
				"UserId" => array(Type::NUMBER => $userId)
			)
		));
	}

	public function getImages($user_id){
		$responseIndex = $this->client->getItem(array(
			"TableName"	=> "ImageIndex",
			"Key"		=> array(
				"UserId" => array(Type::NUMBER => (int)$user_id)
			)
		));

		$finalReturn = array();
		$responseIndex = $responseIndex["Item"]["ImageIds"]["SS"];

		foreach($responseIndex as $s){
			$img = new Image();
			$img->get((string)$s);
			array_push($finalReturn, $img->attrs());
			$img = null;
		}

		echo json_encode($finalReturn);
	}

	public function __get($key){
		return $this->$key;
	}

	public function __set($key, $value){
		$this->$key = $value;
	}

	public function attrs(){
		return array(
			"ImageId"		=> $this->ImageId,
			"Date"			=> $this->Date,
			"Description"	=> $this->Description,
			"UserId"		=> $this->UserId,
			"Extension"		=> $this->Extension
		);
	}

	public function toJSON(){
		echo json_encode($this->attrs());
	}
}
?>