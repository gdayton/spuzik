<?php
require "packages/amazon-php-sdk/autoload.php";
use Aws\Common\Aws;
use Aws\Common\Enum\Region;
use Aws\S3\Enum\CannedAcl;
use Aws\S3\Exception\S3Exception;
use Guzzle\Http\EntityBody;

$aws = Aws::factory("packages/amazon-php-sdk/config_s3.php");

$s3 = $aws->get('s3');

/*echo "ListBuckets with SDK Version 1:\n";
echo "------------------------\n";
$response = $s3v1->listBuckets();
if ($response->isOK()) {
    foreach ($response->body->Buckets->Bucket as $bucket) {
        echo "- {$bucket->Name}\n";
    }
} else {
    echo "Request failed.\n";
}
echo "\n";*/

try {
    /*$result = $s3->listBuckets();
    foreach ($result['Buckets'] as $bucket) {
        echo "- {$bucket['Name']}\n";
    }*/

	/*
		This is how you upload an item to the s3 instance.
	*/
	$result = $s3->putObject(array(
		'Bucket' => "spuzik",
		'Key'    => "/user_images/test_upload.txt",
		'Body'   => Guzzle\Http\EntityBody::factory(fopen("test_upload.txt", 'r')),
		'ACL'	 => "public-read"
	));
	echo $response["ObjectURL"];

	/*
		Getting url for item in s3 instance.
	*/
	$resultUrl = $s3->getObjectUrl("spuzik","/user_images/test_upload.txt");
	echo $resultUrl;

	echo "Did it!";

} catch (Aws\S3\Exception\Exception $e) {
    echo "Redirect Issue.\n";
}
echo "\n";