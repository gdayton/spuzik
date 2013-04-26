<?php

	require_once 'tinysong.php';

	$api_key = 'YOUR-TINYSONG-API-KEY';

	$query = $_GET['query'];

	$tinysong = new Tinysong($api_key);

	$result = $tinysong
	            ->single_tinysong_metadata($query)
	            ->execute();

	echo $_GET['callback'] . "(" . json_encode($result) . ");";

?>