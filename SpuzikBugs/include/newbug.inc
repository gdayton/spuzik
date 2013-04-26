<style type="text/css">
	.prompt{
		border-top:2px solid #000;
		border-bottom:2px solid #000;
		padding:5px 0px;
		float:right;
		width:300px;
	}
</style>
<?php
// INSTANTIATE VARIABLES
$errors = 0;
$tf = true;
?>
<form method="post" action="" enctype="multipart/form-data">
<h1>Create Bug</h1>
<table border="0" cellpadding="10px;" width="100%;">
	<tr>
		<td>
		<?php
			// ERROR TEXT
			if(isset($_POST['submit'])){
				if(!isset($_POST['name']) || strlen($_POST['name']) == 0 || strlen($_POST['name']) > 150){
					$errors++;
					echo " <span style='color:red; padding-left:5px;'>✖</span>";
				}
			}
		?>
		<span style="color:red;">*</span>Name</td>
		<td>
			<p style="font-size:13px;" class="prompt"><i style="font-size:16px; color:blue;">i</i></b> Please use short descriptive name for bug</p>
			<input type="text" name="name" style="font-size:20px; margin-top:25px; width:270px;" <?php echo "value='".$_POST['name']."'"; ?> />
		</td>
	</tr>
	<tr>
		<td>
		<?php
			// ERROR TEXT
			if(isset($_POST['submit'])){
				if(!isset($_POST['desc']) || strlen($_POST['desc']) == 0){
					$errors++;
					echo " <span style='color:red; padding-left:5px;'>✖</span>";
				}
			}
		?>
		<span style="color:red;">*</span>Description</td>
		<td>
			<p style="font-size:13px;" class="prompt"><b><i style="font-size:16px; color:blue;">i</i></b> Please describe what you did to make the bug occur (e.g. clicked on the "Home" link).</p>
			<textarea name="desc" style="width:270px; margin-right:10px; height:75px; margin-top:6px;"><?php echo $_POST['desc']; ?></textarea>
		</td>
	</tr>
	<tr>
		<td>
		<?php
			// ERROR TEXT
			if(isset($_POST['submit'])){
				if(!isset($_POST['browser']) || strlen($_POST['browser']) == 0){
					$errors++;
					echo " <span style='color:red; padding-left:5px;'>✖</span>";
				}
			}
		?>
		<span style="color:red;">*</span>Browser</td>
		<td>
			<p style="font-size:13px;" class="prompt"><b><i style="font-size:16px; color:blue;">i</i></b> What browser are you using? Chrome, Safari, IE, Firefox, etc... </p>
			<input type="text" name="browser" style="font-size:20px; margin-top:25px; width:270px;" <?php echo "value='".$_POST['browser']."'"; ?> />
		</td>
	</tr>
	<tr>
		<td>
		<?php
			// ERROR TEXT - this error text will only be used when the picture is in the wrong type

		?>
		Screenshot</td>
		<td>
			<p style="font-size:13px;" class="prompt"><i style="font-size:16px; color:blue;">i</i></b> Please provide a screenshot of the bug if possible. How to take a screenshot:
				<br /><b>Mac OS</b><br />
				&nbsp;&nbsp;&nbsp; &raquo;⌘+Shift+4
				<br /><b>Windows</b><br />
				&nbsp;&nbsp;&nbsp; &raquo;Start &gt; Snipping Tool <b>OR</b> PrtScrn
			</p>
			<input type="file" name="screenshot" style="margin-top:70px;"/>
		</td>
	</tr>
	<tr>
		<td>
		<?php
			// ERROR TEXT
			if(isset($_POST['submit'])){
				if(!isset($_POST['importance']) || $_POST['importance'] == "!!"){
					$errors++;
					$tf = false;
					echo " <span style='color:red; padding-left:5px;'>✖</span>";
				}
			}
		?>
		<span style="color:red;">*</span>Timeline</td>
		<td>
			Fix bug within
			<select name="importance">
				<?php
				echo "<option value='!!'>---</option>";
				$options = array(
					'1 day',
					'2 days',
					'3 days',
					'4 days',
					'5 days',
					'2 weeks',
					'3 weeks',
					'1 month',
					'2 months',
					'6 months'
				);

				foreach($options as $key=>$val){
					if(isset($_POST['importance']) && $_POST['importance'] != "!!"){
						if($_POST['importance'] == $key){
							echo "<option value='".$key."' selected='selected'>".$val."</option>";
						}else{
							echo "<option value='".$key."'>".$val."</option>";
						}
					}else{
						echo "<option value='".$key."'>".$val."</option>";
					}
				}
				?>
			</select>
		</td>
	</tr>
	<tr>
		<td colspan="2">
			<input type="submit" name="submit" value="Submit Bug" style="font-size:25px;"/><span style="margin-left:50px; color:red;">* = Required Fields</span>
		</td>
	</tr>
</table>
</form>
<?php
function getExtension($str) {
	 switch($str['type']){
	 	case "image/jpeg":
	 	case "image/jpg":
	 		return "jpeg";
	 		break;
	 	case "image/gif":
	 		return "gif";
	 		break;
	 	case "image/png":
	 		return "png";
	 		break;
	 	default:
	 		return "";
	 		break;
	 }
}

function randString($length) {
	$chars = "abcdefghijklmnopqrstuvwxyz";

	$size = strlen($chars);
	$str = "";
	for($i = 0;$i < $length; $i++){
		$str .= $chars[rand(0,$size-1)];
	}
	return $str;
}

if(isset($_POST['submit'])){
	if($errors > 0){ //sumethin is bad
		echo "<div style='border-top:2px solid red; border-bottom:2px solid red; padding:5px;'>There was ".$errors." error(s) attempting to submit this bug.</div>";
	}else{ //everything is good
		$scrsht = "";
		//first verify that the image is ok
		if(isset($_FILES['screenshot'])){
			 $filename 	= stripslashes($_FILES['screenshot']['name']);
			  $tmpname  = $_FILES['screenshot']['tmp_name'];
				  $ext 	= getExtension($_FILES['screenshot']);

			 $filesize  = $_FILES['image']['size'];
			if(strlen($ext)>0){
				if($filesize <= 5242880){
					$img = "";
					switch($ext){
						case "gif":
							$img = imagecreatefromgif($tmpname);
							break;
						case "png":
							$img = imagecreatefrompng($tmpname);
							break;
						case "jpeg":
						case "jpg":
							$img = imagecreatefromjpeg($tmpname);
							break;
					}
					$storeloc_sm = randString(5);

					$scrsht = "images/".$storeloc_sm.".png";
					imagepng($img,$scrsht);
				}
			}
		}
		$stmt = $db->prepare("INSERT INTO spuzik_bug_bugs (name, descr, scrsht, urg, bdate, date_fut, browser) VALUES (:name, :descr, :scrsht, :urg, :bdate, :date_fut, :browser);");
		$stmt->bindParam("name",$_POST['name']);
		$stmt->bindParam("descr",$_POST['desc']);
		$stmt->bindParam("scrsht",$scrsht);
		$stmt->bindParam("browser",$_POST['browser']);
		$stmt->bindParam("urg",$_POST['importance']);
		$dateStr = strtotime("now");
		$stmt->bindParam("bdate",$dateStr);
		switch($_POST['importance']){
			case 0:
				$dateStrFut = $dateStr+86400;
				break;
			case 1:
				$dateStrFut = $dateStr+(86400*2);
				break;
			case 2:
				$dateStrFut = $dateStr+(86400*3);
				break;
			case 3:
				$dateStrFut = $dateStr+(86400*4);
				break;
			case 4:
				$dateStrFut = $dateStr+(86400*5);
				break;
			case 5:
				$dateStrFut = $dateStr+(86400*14);
				break;
			case 6:
				$dateStrFut = $dateStr+(86400*21);
				break;
			case 7:
				$dateStrFut = $dateStr+(86400*30);
				break;
			case 8:
				$dateStrFut = $dateStr+(86400*60);
				break;
			case 9:
				$dateStrFut = $dateStr+(86400*183);
				break;
		}
		$stmt->bindParam("date_fut",$dateStrFut);

		$status = $stmt->execute();
		if($status){
			header("Location: ?p=viewbugs");
		}else{
			echo "There was a fatal error with the database.";
		}
	}
}
?>