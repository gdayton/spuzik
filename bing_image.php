<?php
/*$acctKey = 'xQ3zpMJqqEwPytwDFS/n6CMVsN+dgJYWC5KZW3h6aFI';
$rootUri = 'https://api.datamarket.azure.com/Bing/Search/Image?$format=json&Query=glenn';

$auth = base64_encode("$acctKey:$acctKey");
$data = array(
	'http' => array(
	'request_fulluri' => true,
	'ignore_errors' => true,
	'header' => "Authorization: Basic $auth")
);

$context = stream_context_create($data);

$response = file_get_contents($rootUri, 0, $context);

$jsonObj = json_decode($response);
$resultStr = '';
// Parse each result according to its metadata type.
foreach($jsonObj->d->results as $value) {
	$resultStr .= "<h4>{$value->Title} ({$value->Width}x{$value->Height}) " . "{$value->FileSize} bytes)</h4>" . "<a href=\"{$value->MediaUrl}\">" . "<img src=\"{$value->Thumbnail->MediaUrl}\"></a><br />";
}

echo $resultStr;*/
?>
<head>

<head>
<style type="text/css">
body{
	background-image:url('http://images.wikia.com/uncyclopedia/images/7/76/Strobe.gif');
	width:100%;
	height:100%;
	background-size:100% 100%;
}
</style>
<body>
	<p>content</p>
</body>