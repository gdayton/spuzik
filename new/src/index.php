<?php
session_start();

require "/var/www/new/packages/amazon-php-sdk/autoload.php";

use Aws\Common\Aws;
use Aws\Common\Enum\Region;
use Aws\DynamoDb\DynamoDbClient;
use Aws\DynamoDb\Enum\ComparisonOperator;
use Aws\DynamoDb\Enum\KeyType;
use Aws\DynamoDb\Enum\Type;

$aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
$client = $aws->get("dynamodb");

$sessionHandler = $client->registerSessionHandler(array(
    'table_name' => 'Sessions'
));

//$sessionHandler->createSessionsTable(1, 1);

// Alter the session data
$_SESSION['spuzik'] = true;
$_SESSION['spuzik_uid'] = 1;

echo $_SESSION['spuzik']." with user id of: ".$_SESSION['spuzik_uid'];

// Close the session (optional, but recommended)
session_write_close();

/*
namespace Spuzik;

require "Spuzik/Users/User.php";
require "Spuzik/Tools/Validate.php";

$user = new Users\User();
$user->UserId = 1;
$user->FirstName = "Glenn";
$user->LastName = "Dayton";
$user->LastOn = 1234567890;

echo $user->UserId."<br />";
echo $user->FirstName;

$validate = new Tools\Validate();
echo $validate->stringValidate("glenn",6);

echo "<br />---- FETCH WITH ID ----<br />";

$user2 = new Users\User();
$user2 = $user2->fetchWithId(2);
echo $user2->UserId." ".$user2->FirstName;

echo "<br />---- FETCH WITH EMAIL ----<br />";

$user2 = new Users\User();
$user2 = $user2->fetchWithEmail("glenn.dayton24@gmail.com");
echo $user2->UserId." ".$user2->FirstName;

echo "<br />---- CHECKING WITH NO RESULTS ----<br />";

$user3 = new Users\User();
$user3 = $user3->fetchWithId(3);

echo "<br />---- LOGIN CHECKER ----<br />";

$user4 = new Users\User();
$result = $user4->checkCredentials("glenn.dayton24@gmail.com","this");
if($result){ echo "LOGGED IN"; }else{ echo "NOT GOOD"; }
*/
?>