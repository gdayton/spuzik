<?php
$tmpname  = "PRN10-UNDER-ARMOUR-TOTTENHAM-PLAYERS-1yHigh-1.jpg";

list($image_w, $image_h) = getimagesize($tmpname);

//
//  Keeping things in line
//
if($w > $image_w){
	$w = $image_w;
	$x = 0;
}if($h > $image_h){
	$h = $image_h;
	$y = 0;
}

if($x > ($image_w-$w)){
	$x = ($image_w-$w);
}if($y > ($image_h-$h)){
	$y = ($image_h-$h);
}

/*
	To select a portion of the image use this width and height
*/
$thumbnail = imagecreatetruecolor($w,$h);

$img = imagecreatefromjpeg($tmpname);

imagecopyresampled($thumbnail,$img,0,0,abs($x),abs($y),$image_w,$image_h,$image_w,$image_h);

header("Content-Type: image/png");

//return low quality image for faster processing
imagejpeg($thumbnail,null,10);

imagedestroy($thumbnail);
?>