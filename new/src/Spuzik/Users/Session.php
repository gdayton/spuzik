<?php
namespace Spuzik\Users;

require "/var/www/new/packages/amazon-php-sdk/autoload.php";
require_once "/var/www/new/packages/facebook/facebook.php";

use Aws\Common\Aws;
use Aws\Common\Enum\Region;
use Aws\DynamoDb\DynamoDbClient;
use Aws\DynamoDb\Enum\ComparisonOperator;
use Aws\DynamoDb\Enum\KeyType;
use Aws\DynamoDb\Enum\Type;

class Session{
	public $aws;
	public $client;
	public $sessionHandler;
	public $facebook;

	const NONE	   = 0;
	const SPUZIK   = 1;
	const FACEBOOK = 2;

	/*
		Constructs the session everytime the page is loaded.
	*/
	public function __construct(){
		/* SPUZIK INIT */
		$this->aws = Aws::factory("/var/www/new/packages/amazon-php-sdk/config.php");
		$this->client = $this->aws->get("dynamodb");

		/* FACEBOOK INIT */
		$this->facebook = new \Facebook(array(
			'appId'  => '194694247368490',
			'secret' => 'b4a7c130729347f94f14f64322865126',
		));

		$this->sessionHandler = $this->client->registerSessionHandler(array(
			'table_name' 	   => 'Sessions',
			'session_lifetime' => 604800
		));

		return $this;
	}

	/*
		Pass a user's who credentials were verified and correct, and retreive id and name info.
		TODO Make it return a validation object with info about what needs to be done to fix
		     service type sections.
	*/
	public function registerSession($user, $method){
		//check if they are logged in from another account type
		if($this->serviceType() == self::NONE){
			switch($method){
				case self::SPUZIK: //spuzik
					//$this->write("spuzik",true);
					//$this->write("spuzik_uid",$user->UserId);
					session_destroy();
					session_start();

					$_SESSION['spuzik'] = true;
					$_SESSION['spuzik_uid'] = $user->UserId;

					session_write_close();
					break;
				case self::FACEBOOK: //facebook
					//if facebook hasn't been linked
					$this->facebook->destroySession();
					break;
			}
		}else{
			return false;
		}
	}

	/*
		Returns which session is the active session.
	*/
	public function serviceType(){
		if($this->facebook->getUser()){
			return self::FACEBOOK;
		}else if(isset($_SESSION['spuzik'])){
			return self::SPUZIK;
		}else{
			return "NONE";
		}
	}

	/*
		Logs the current session out.
	*/
	public function logOut(){
		switch($this->serviceType()){
			case self::SPUZIK:
				$_SESSION = array();
				session_destroy();
				//session_regenerate_id();
				break;
			case self::FACEBOOK:
				//https://developers.facebook.com/docs/reference/php/facebook-getLogoutUrl/
				// HANDLED BY HAVING USER CLICK THEIR LINK
				break;
		}
	}

	/*
		Returns link for login or logout function.
		- type String Login type such as LOGIN or something else is passed indicating action.
	*/
	public function facebookLink($type){
		if($type == "LOGIN")
			return $this->facebook->getLoginUrl();
		else
			return $this->facebook->getLogoutUrl();
	}

	/*
		Writes a session variable with the passed parameter and the data for it.
		- data  String Data that is pushed into the array item.
		- param String Param of Session to write the data to.
	*/
	public function write($param, $data){
		$_SESSION[$param] = $data;
	}

	/*
		Extracts data from session with the passed parameter.
		- param String Name of param for session that you want to retrieve.
	*/
	public function read($param){
		if(isset($_SESSION[$param])){
			return $_SESSION[$param];
		}
		return false;
	}

	/*
		Returns the id of the currently logged in user.
	*/
	public function currentId(){
		if($this->serviceType() == self::SPUZIK){ //if the service is Spuzik, then give information about user away.
			return $_SESSION['spuzik_uid'];
		}else{
			return false;
		}
	}
}
?>