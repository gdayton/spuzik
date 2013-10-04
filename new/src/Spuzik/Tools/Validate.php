<?php
namespace Spuzik\Tools;

class Validate{

	public function __construct(){
		return $this;
	}

	public function stringValidate($string,$max_length){
		$string = trim($string);
		return strlen($string) > 0 && strlen($string) <= $max_length;
	}

	public function numberValidate($number){
		return is_numeric($number);
	}
}
?>