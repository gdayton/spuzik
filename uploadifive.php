<?php
include("actions/actions.class.php");
sec_session_start();

$jsonArray = array("status"=>"success");

$uploadDir = '/usr_content/tmp_pics/';
$finalDir = '/usr_content/pics/';

$db = new PDO("mysql:dbname=spk;host=localhost","spk_handler","qaw3ufRa");
$u = new User();

if (!empty($_FILES)) {
	$tempFile   = $_FILES['Filedata']['tmp_name'];
	$uploadDir  = $_SERVER['DOCUMENT_ROOT'] . $uploadDir;
	$finalDir 	= $_SERVER['DOCUMENT_ROOT'] . $finalDir;
	$targetFile_0 = uniqid(); //Original

	//Change to 2 when you set the rest of the code up
	$jsonArray['photo_id'] = $targetFile_0;

	//check via mime types for an error free experience
	$fileTypes = array(IMAGETYPE_JPEG, IMG_JPG, IMAGETYPE_GIF, IMG_GIF, IMAGETYPE_PNG, IMG_PNG);
	if(is_uploaded_file($_FILES['Filedata']['tmp_name']))
		$tempFile = move_uploaded_file($tempFile,$uploadDir.$_FILES['Filedata']['name']);
	else
		$tempFile = false;

	$fileParts = exif_imagetype($uploadDir.$_FILES['Filedata']['name']);

	if (in_array($fileParts, $fileTypes)) {
		$srcFile = null;
		switch($fileParts){
			case IMAGETYPE_JPEG :
				$srcFile = imagecreatefromjpeg($uploadDir.$_FILES['Filedata']['name']);
				break;
			case IMAGETYPE_PNG :
				$srcFile = imagecreatefrompng($uploadDir.$_FILES['Filedata']['name']);
				break;
			case IMAGETYPE_GIF :
				$srcFile = imagecreatefromgif($uploadDir.$_FILES['Filedata']['name']);
				break;
		}

		///>>> CODE FOR CREATE PERMISSIONS
			$queryIn = "INSERT INTO permissions (type,u_id) VALUES (:type,:u_id);";
			$stmt = $db->prepare($queryIn);
			//convert to number not string
			$zero = 0;
			$stmt->bindParam("type",$zero); //default public
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->execute();
			//get the last inserted item with user id, since other items likely are not going to change quickly.
			$query2 = "SELECT id FROM permissions WHERE u_id = :u_id ORDER BY id DESC LIMIT 1;";
			$stmt = $db->prepare($query2);
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->execute();
			$results = $stmt->fetch(PDO::FETCH_ASSOC);

			$perm_id = $results['id'];
		///>>>

		///////
		//
		// Save original version of the image
		//
		///////
		$insert = "INSERT INTO photo (photo_path,a_id,p_id,u_id,ss_incl,date) VALUES (:photo_path,:a_id,:p_id,:u_id,:ss_incl,:date);";
		$stmt = $db->prepare($insert);
		$stmt->bindParam("photo_path",$targetFile_0);
		$zero = 0;
		$stmt->bindParam("a_id",$zero);
		$stmt->bindParam("p_id",$perm_id);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->bindParam("ss_incl",$zero); //0 = yes include, 1 = no dont include
		$time = strtotime("now");
		$stmt->bindParam("date",$time);
		$res = $stmt->execute();

		if($res){
			//Change the file type for the original image
			imagejpeg($srcFile, $finalDir.$targetFile_0.".jpg", 100); //Original

			list($image_w, $image_h) = getimagesize($uploadDir.$_FILES['Filedata']['name']);

			//Keep em constant
			$w = 155;
			$h = 155;

			$source_aspect_ratio = $image_w / $image_h;
			$desired_aspect_ratio = $w / $h;

			if ($source_aspect_ratio > $desired_aspect_ratio) {
				/*
				 * Triggered when source image is wider
				 */
				$temp_height = $h;
				$temp_width = floor($h * $source_aspect_ratio);
			} else {
				/*
				 * Triggered otherwise (i.e. source image is similar or taller)
				 */
				$temp_width = $w;
				$temp_height = floor($w / $source_aspect_ratio);
			}

			/*
			 * Resize the image into a temporary GD image
			 */

			$temp_gdim = imagecreatetruecolor($temp_width, $temp_height);
			imagecopyresampled($temp_gdim,$srcFile,0, 0,0, 0,$temp_width, $temp_height,$image_w, $image_h);

			/*
			 * Copy cropped region from temporary image into the desired GD image
			 */

			$x0 = ($temp_width - $w) / 2;
			$y0 = ($temp_height - $h) / 2;
			$thumbnail = imagecreatetruecolor($w, $h);
			imagecopy($thumbnail,$temp_gdim,0, 0,$x0, $y0,$w, $h);

			imagejpeg($thumbnail, $finalDir.$targetFile_0."_t.jpg",50); //Thumbnail

			imagedestroy($thumbnail);
			imagedestroy($temp_gdim);

			//Keep em constant
			$w = 500;
			$h = 500;

			$source_aspect_ratio = $image_w / $image_h;
			$desired_aspect_ratio = $w / $h;

			if ($source_aspect_ratio > $desired_aspect_ratio) {
				/*
				 * Triggered when source image is wider
				 */
				$temp_height = $h;
				$temp_width = floor($h * $source_aspect_ratio);
			} else {
				/*
				 * Triggered otherwise (i.e. source image is similar or taller)
				 */
				$temp_width = $w;
				$temp_height = floor($w / $source_aspect_ratio);
			}

			/*
			 * Resize the image into a temporary GD image
			 */

			$temp_gdim = imagecreatetruecolor($temp_width, $temp_height);
			imagecopyresampled($temp_gdim,$srcFile,0, 0,0, 0,$temp_width, $temp_height,$image_w, $image_h);

			/*
			 * Copy cropped region from temporary image into the desired GD image
			 */

			$x0 = ($temp_width - $w) / 2;
			$y0 = ($temp_height - $h) / 2;
			$thumbnail = imagecreatetruecolor($w, $h);
			imagecopy($thumbnail,$temp_gdim,0, 0,$x0, $y0,$w, $h);

			imagejpeg($thumbnail, $finalDir.$targetFile_0."_s.jpg",75); //Thumbnail

			imagedestroy($thumbnail);
			imagedestroy($temp_gdim);

			$maxW = 550;
			$maxH = 400;

			$source_aspect_ratio = $image_w / $image_h;
			$thumbnail_aspect_ratio = $maxW / $maxH;
			if ($image_w <= $maxW && $image_h <= $maxH) {
				$thumbnail_image_width = $image_w;
				$thumbnail_image_height = $image_h;
			} elseif ($thumbnail_aspect_ratio > $source_aspect_ratio) {
				$thumbnail_image_width = floor($maxH * $source_aspect_ratio);
				$thumbnail_image_height = $maxH;
			} else {
				$thumbnail_image_width = $maxW;
				$thumbnail_image_height = floor($maxW / $source_aspect_ratio);
			}
			$thumbnail_gd_image = imagecreatetruecolor($thumbnail_image_width, $thumbnail_image_height);
			imagecopyresampled($thumbnail_gd_image, $srcFile, 0, 0, 0, 0, $thumbnail_image_width, $thumbnail_image_height, $image_w, $image_h);

			imagejpeg($thumbnail_gd_image, $finalDir.$targetFile_0."_w.jpg", 75);

			imagedestroy($thumbnail_gd_image);


		}else{
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "There was a fatal error with the database.";
		}

		echo json_encode($jsonArray);
	} else {
		echo 'Invalid file type.';
	}
}else if(!empty($_GET['url'])){  //put the URL to the photo here.
	$array_response = array("status"=>"success");

	$image_url = trim($_GET['url']);

	if($image_url != ""){

		$targetFile_0 = uniqid(); //Original
		$content = file_get_contents($image_url);
		$uploadDir = '/var/www/usr_content/tmp_pics/'.basename($image_url);
		$finalDir 	= $_SERVER['DOCUMENT_ROOT'] . $finalDir;
		file_put_contents($uploadDir, $content);
		chmod($uploadDir,0777);

		$jsonArray['data'] = $targetFile_0;

		//
		//    - - - - - - - - - - - - - - - -
		//
		//
		//Image is now inside the tmp photos, ready for further parsing
		$fileTypes = array(IMAGETYPE_JPEG, IMG_JPG, IMAGETYPE_GIF, IMG_GIF, IMAGETYPE_PNG, IMG_PNG);

		$fileParts = exif_imagetype($uploadDir);

		if (in_array($fileParts, $fileTypes)) {
			$srcFile = null;
			switch($fileParts){
				case IMAGETYPE_JPEG :
					$srcFile = imagecreatefromjpeg($uploadDir);
					break;
				case IMAGETYPE_PNG :
					$srcFile = imagecreatefrompng($uploadDir);
					break;
				case IMAGETYPE_GIF :
					$srcFile = imagecreatefromgif($uploadDir);
					break;
			}

			///>>> CODE FOR CREATE PERMISSIONS
			$queryIn = "INSERT INTO permissions (type,u_id) VALUES (:type,:u_id);";
			$stmt = $db->prepare($queryIn);
			//convert to number not string
			$zero = 0;
			$stmt->bindParam("type",$zero); //default public
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->execute();
			//get the last inserted item with user id, since other items likely are not going to change quickly.
			$query2 = "SELECT id FROM permissions WHERE u_id = :u_id ORDER BY id DESC LIMIT 1;";
			$stmt = $db->prepare($query2);
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->execute();
			$results = $stmt->fetch(PDO::FETCH_ASSOC);

			$perm_id = $results['id'];
			///>>>

			///////
			//
			// Save original version of the image
			//
			///////
			$insert = "INSERT INTO photo (photo_path,a_id,p_id,u_id,ss_incl,date) VALUES (:photo_path,:a_id,:p_id,:u_id,:ss_incl,:date);";
			$stmt = $db->prepare($insert);
			$stmt->bindParam("photo_path",$targetFile_0);
			$zero = 0;
			$stmt->bindParam("a_id",$zero);
			$stmt->bindParam("p_id",$perm_id);
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->bindParam("ss_incl",$zero); //0 = yes include, 1 = no dont include
			$time = strtotime("now");
			$stmt->bindParam("date",$time);
			$res = $stmt->execute();

			if($res){
				//Change the file type for the original image
				imagejpeg($srcFile, $finalDir.$targetFile_0.".jpg", 100); //Original

				list($image_w, $image_h) = getimagesize($uploadDir);

				//Keep em constant
				$w = 155;
				$h = 155;

				$source_aspect_ratio = $image_w / $image_h;
				$desired_aspect_ratio = $w / $h;

				if ($source_aspect_ratio > $desired_aspect_ratio) {
					/*
					 * Triggered when source image is wider
					 */
					$temp_height = $h;
					$temp_width = floor($h * $source_aspect_ratio);
				} else {
					/*
					 * Triggered otherwise (i.e. source image is similar or taller)
					 */
					$temp_width = $w;
					$temp_height = floor($w / $source_aspect_ratio);
				}

				/*
				 * Resize the image into a temporary GD image
				 */

				$temp_gdim = imagecreatetruecolor($temp_width, $temp_height);
				imagecopyresampled($temp_gdim,$srcFile,0, 0,0, 0,$temp_width, $temp_height,$image_w, $image_h);

				/*
				 * Copy cropped region from temporary image into the desired GD image
				 */

				$x0 = ($temp_width - $w) / 2;
				$y0 = ($temp_height - $h) / 2;
				$thumbnail = imagecreatetruecolor($w, $h);
				imagecopy($thumbnail,$temp_gdim,0, 0,$x0, $y0,$w, $h);

				imagejpeg($thumbnail, $finalDir.$targetFile_0."_t.jpg",50); //Thumbnail

				imagedestroy($thumbnail);
				imagedestroy($temp_gdim);

				//Keep em constant
				$w = 500;
				$h = 500;

				$source_aspect_ratio = $image_w / $image_h;
				$desired_aspect_ratio = $w / $h;

				if ($source_aspect_ratio > $desired_aspect_ratio) {
					/*
					 * Triggered when source image is wider
					 */
					$temp_height = $h;
					$temp_width = floor($h * $source_aspect_ratio);
				} else {
					/*
					 * Triggered otherwise (i.e. source image is similar or taller)
					 */
					$temp_width = $w;
					$temp_height = floor($w / $source_aspect_ratio);
				}

				/*
				 * Resize the image into a temporary GD image
				 */

				$temp_gdim = imagecreatetruecolor($temp_width, $temp_height);
				imagecopyresampled($temp_gdim,$srcFile,0, 0,0, 0,$temp_width, $temp_height,$image_w, $image_h);

				/*
				 * Copy cropped region from temporary image into the desired GD image
				 */

				$x0 = ($temp_width - $w) / 2;
				$y0 = ($temp_height - $h) / 2;
				$thumbnail = imagecreatetruecolor($w, $h);
				imagecopy($thumbnail,$temp_gdim,0, 0,$x0, $y0,$w, $h);

				imagejpeg($thumbnail, $finalDir.$targetFile_0."_s.jpg",75); //Thumbnail

				imagedestroy($thumbnail);
				imagedestroy($temp_gdim);

				$maxW = 550;
				$maxH = 400;

				$source_aspect_ratio = $image_w / $image_h;
				$thumbnail_aspect_ratio = $maxW / $maxH;
				if ($image_w <= $maxW && $image_h <= $maxH) {
					$thumbnail_image_width = $image_w;
					$thumbnail_image_height = $image_h;
				} elseif ($thumbnail_aspect_ratio > $source_aspect_ratio) {
					$thumbnail_image_width = floor($maxH * $source_aspect_ratio);
					$thumbnail_image_height = $maxH;
				} else {
					$thumbnail_image_width = $maxW;
					$thumbnail_image_height = floor($maxW / $source_aspect_ratio);
				}
				$thumbnail_gd_image = imagecreatetruecolor($thumbnail_image_width, $thumbnail_image_height);
				imagecopyresampled($thumbnail_gd_image, $srcFile, 0, 0, 0, 0, $thumbnail_image_width, $thumbnail_image_height, $image_w, $image_h);

				imagejpeg($thumbnail_gd_image, $finalDir.$targetFile_0."_w.jpg", 75);

				imagedestroy($thumbnail_gd_image);


			}else{
				$jsonArray['status'] = "error";
				$jsonArray['status_msg'] = "There was a fatal error with the database.";
			}

			echo json_encode($jsonArray);
		} else {
			echo 'Invalid file type.';
		}
	}
}else{
	echo $_SESSION['user_id'];
}





?>