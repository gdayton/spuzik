<?php
/***********************
 TO RUN UNCOMMENT LINE 7
***********************/

$db = new PDO("mysql:dbname=spk;host=localhost;","spk_handler","qaw3ufRa");
$stmt = $db->prepare("SELECT photo_path FROM photo;");
//$stmt->execute();
$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
print_r($data);

foreach($data as $d){
	$srcFile = imagecreatefromjpeg("/var/www/usr_content/pics/".$d['photo_path'].".jpg");
	list($image_w, $image_h) = getimagesize("/var/www/usr_content/pics/".$d['photo_path'].".jpg");
	//Keep em constant
	$w = 500;
	$h = 500;

	$source_aspect_ratio = $image_w / $image_h;
	$desired_aspect_ratio = $w / $h;

	if ($source_aspect_ratio > $desired_aspect_ratio) {
		$temp_height = $h;
		$temp_width = floor($h * $source_aspect_ratio);
	} else {
		$temp_width = $w;
		$temp_height = floor($w / $source_aspect_ratio);
	}

	$temp_gdim = imagecreatetruecolor($temp_width, $temp_height);
	imagecopyresampled($temp_gdim,$srcFile,0, 0,0, 0,$temp_width, $temp_height,$image_w, $image_h);


	$x0 = ($temp_width - $w) / 2;
	$y0 = ($temp_height - $h) / 2;
	$thumbnail = imagecreatetruecolor($w, $h);
	imagecopy($thumbnail,$temp_gdim,0, 0,$x0, $y0,$w, $h);

	imagejpeg($thumbnail, "/var/www/usr_content/pics/".$d['photo_path']."_s.jpg",75); //Thumbnail
}
?>