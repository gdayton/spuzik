<?php
class dbcon{
	public function __construct(){
		return new PDO("mysql:dbname=spk;host=localhost","spk_handler","qaw3ufRa");
	}
}
?>
