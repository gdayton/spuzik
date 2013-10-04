<?php
require "packages/amazon-php-sdk/autoload.php";

use Aws\Common\Aws;
use Aws\Common\Enum\Region;
use Aws\DynamoDb\DynamoDbClient;
use Aws\DynamoDb\Enum\ComparisonOperator;
use Aws\DynamoDb\Enum\KeyType;
use Aws\DynamoDb\Enum\Type;

// Instantiate the client with your AWS access keys
$aws = Aws::factory("packages/amazon-php-sdk/config.php");
$client = $aws->get("dynamodb");

/*$response = $client->query(array(
    "TableName" => "Users",
	"UserId" => array( Type::NUMBER => 1 )
));*/

$response = $client->getItem(array(
    'TableName' => 'Users',
    'Key'       => array(
        'UserId' => array('N' => 1),
    )
));

 /*

 "KeyConditions" => array(
        "UserId" => array(
            "ComparisonOperator" => ComparisonOperator::EQ,
            "AttributeValueList" => array(
                array(Type::NUMBER => 1)
            )
        )
	),
	$response = $dynamodb->query(array(
                  'TableName' => “Websites”,

    "UserId" => array( TYPE::NUMBER => 1 ),
	"AttributesToGet" => array( "FirstName", "LastName"),
    "ConsistentRead" => true

*/
echo "<h2>Awesome!</h2>";
echo "The database works!<br />";
echo $response["Item"]["FirstName"]["S"]." ".$response["Item"]["LastName"]["S"];
?>