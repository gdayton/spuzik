<h1>Send Alerts</h1>
<p>This function allows you to send a mass email to all the users in the debugging system.<br /><br />
<b style="border-top:2px solid red; border-bottom:2px solid red; padding:5px 0px;">For emergency purposes only.</b>
<form method="post" action="">
	<textarea name="message" style="width:100%; font-size:18px; height:75px;"><?php echo $_POST['message']; ?></textarea><br />
	<input type="submit" name="submit" value="Send Message" style="font-size:18px; margin-top:10px;"/>
</form>
<?php
if(isset($_POST['submit'])){
	if(strlen($_POST['message']) > 0){
		$stmt = $db->prepare("SELECT email, name FROM spuzik_bug_users;");
		$stmt->execute();
		$results = $stmt->fetchAll(PDO::FETCH_ASSOC);
		//print_r($results);
		echo "Emails were sent to the following recipients:<ul>";
		foreach($results as $r=>$c){
			echo "<li>".$c['name']." <i>&lt;".$c['email']."&gt;</i></li>";
			mail($c['email'],"Urgent Message From Spuzik Debugging Management System",$_POST['message']);
		}
		echo "</ul>";
	}else{
		echo "<div style='border-top:2px solid red; border-bottom:2px solid red; padding:5px 0px;'><b>ERROR</b> You must enter a message!</div>";
	}
}
?>