<?php
namespace Spuzik\Tools;

require "/var/www/new/packages/amazon-php-sdk/autoload.php";
require "../helpers.php";

class Logger{

	public $aws;
	public $client;

	public $Id;
	public $UserId;
	public $ActionTime;
	public $IPAddress;
	public $Browser;
	public $Platform;
	public $Action;
	public $Report;

	const LOGIN  		= 1;  	 //Logged In
	const LOGOUT 		= 2;	 //Logged Out
	const LOGIN_ATTEMPT = 3;	 //Login Attempted, but unsuccessful
	const SETTINGS		= 4;	 //Settings Modified
	const FORGOT_P		= 5;	 //Forgot Password

	public function __construct(){
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");

		return $this;
	}

	public function __set($item){
		return $this->item;
	}

	public function __get($item, $value){
		$this->$item = $value;
	}

	public function write($action, $report){
		$userAgentInfo = parse_user_agent();

		$response = $client->batchWriteItem(array(
			"RequestItems" => array(
				"Watchdog" => array(
					 array(
						"PutRequest" => array(
							"Item" => array(
								"Id"         => array(Type::NUMBER => 1),															// x
								"UserId"     => array(Type::NUMBER => 1),															// x
								"ActionTime" => array(Type::INT    => strtotime("now")),		   									// /
								"IPAddress"  => array(Type::STRING => $_SERVER['REMOTE_ADDR']),										// /
								"Browser"    => array(Type::STRING => $userAgentInfo['platform']), 									// /
								"Platform"   => array(Type::STRING => $userAgentInfo['browser']." | ".$userAgentInfo['version']]),	// /
								"Action"	 => array(Type::NUMBER => $action),														// /
								"Report"  	 => array(Type::STRING => $report)														// /
							)
						)
					)
				)
			)
		));

		return true;
	}
}
?>