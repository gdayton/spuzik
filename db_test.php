<?php
namespace Spuzik;

require "new/src/Spuzik/Users/Session.php";
require "new/src/Spuzik/Users/User.php";
require "new/src/Spuzik/Users/Lineup.php";

/*$user = new Users\User();
$sesh = new Users\Session();

$user->fetchWithId(1);
echo $user->FirstName;
echo "<br />";
echo $sesh->serviceType();
echo "<br />";*/

$lineup = new Users\Lineup(1);
$lineup->toJSON();
/*
$sesh->logOut();
echo $sesh->serviceType();
*/
/*
$sesh->registerSession($user,Users\Session::SPUZIK);
echo $sesh->serviceType();

print_r($_SESSION);*/
/*
echo "<br />";
$sesh->registerSession($user,Users\Session);
*/
/*
require "new/packages/amazon-php-sdk/autoload.php";

use Aws\Common\Aws;
use Aws\Common\Enum\Region;
use Aws\DynamoDb\DynamoDbClient;
use Aws\DynamoDb\Enum\ComparisonOperator;
use Aws\DynamoDb\Enum\KeyType;
use Aws\DynamoDb\Enum\Type;

$credentials = array(
	'key'    => 'AKIAIKXP42LVZCFE5SQQ',
	'secret' => '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',
	'region' => Region::US_WEST_2
);

$aws = Aws::factory($credentials);

$client = $aws->get("dynamodb");

$tableName = "Watchdog";


echo "# Creating table $tableName..." . PHP_EOL;

$result = $client->createTable(array(
    "TableName" => $tableName,
    "AttributeDefinitions" => array(
        array(
            "AttributeName" => "Id",
            "AttributeType" => Type::NUMBER
        )
    ),
    "KeySchema" => array(
        array(
            "AttributeName" => "Id",
            "KeyType" => KeyType::HASH
        )
    ),"ProvisionedThroughput" => array(
        "ReadCapacityUnits"		=> 1,
        "WriteCapacityUnits"	=> 1
    )
));

print_r($result->getPath('TableDescription'));


echo "Batch writing data to the table...";

$response = $client->batchWriteItem(array(
	"RequestItems" => array(
        $tableName => array(
             array(
                "PutRequest" => array(
                    "Item" => array(
                        "Id"         => array(Type::NUMBER => 3),
                        "UserId"     => array(Type::NUMBER => 1),
                        "ActionTime" => array(Type::STRING => 1234567890),
                        "IPAddress"  => array(Type::STRING => "192.168.1.0"),
                        "Browser"    => array(Type::STRING => "Chrome"),
                        "Platform"   => array(Type::STRING => "MacOS"),
                        "Action"	 => array(Type::NUMBER => 1),
                        "Report"  	 => array(Type::STRING => "Logged In.")
                    )
                )
            )
        )
    )
));

print_r($response);


$response = $client->query(array(
			"TableName" => $tableName,
			"IndexName" => "LoginIndex",
			"KeyConditions" => array(
				"UserId" => array(
					"ComparisonOperator" => ComparisonOperator::EQ,
					"AttributeValueList" => array(
						array(Type::NUMBER => 1)
					)
				),"Email" => array(
					"ComparisonOperator" => ComparisonOperator::EQ,
					"AttributeValueList" => array(
						array(Type::STRING => "glenn.dayton24@gmail.com")
					)
				)
			),
			"Select" => "ALL_ATTRIBUTES"
		));

print_r($response['Items']);

*/
?>