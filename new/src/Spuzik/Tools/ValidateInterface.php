<?php
namespace Spuzik\Tools;

interface ValidateInterface{
	public function stringValidate($string,$max_length);
	public function numberValidate($number);
}
?>