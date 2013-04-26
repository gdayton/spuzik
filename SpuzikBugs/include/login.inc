<h1>Login</h1>
<?php
if($_SESSION['logged'])
	header("Location: ?p=main");
if(isset($_POST['submit'])){
	$stmt = $db->prepare("SELECT COUNT(id) FROM spuzik_bug_users WHERE email = :email AND password = :password AND ok = 1;");
	$stmt->bindParam("email",$_POST['email']);
	$stmt->bindParam("password",md5($_POST['password']));
	$stmt->execute();
	$results = $stmt->fetch(PDO::FETCH_ASSOC); // if it's 1 then its ok

	if($results['COUNT(id)'] > 0){
		if($_SESSION['logged'])
			header("Location: ?p=viewbugs");
		else{
			$stmt = $db->prepare("SELECT name FROM spuzik_bug_users WHERE email = :email AND password = :password AND ok = 1;");
			$stmt->bindParam("email",$_POST['email']);
			$stmt->bindParam("password",md5($_POST['password']));
			$stmt->execute();
			$results = $stmt->fetch(PDO::FETCH_ASSOC); // if it's 1 then its ok

			$_SESSION['logged'] = true;
			$_SESSION['name'] = $results['name'];

			header("Location: ?p=viewbugs");
		}
	}else{
		echo "<div style='border-top:2px solid red; border-bottom:2px solid red; padding:5px 0px;'>User authentication failed.</div>";
	}
}
?>
<form method="post" action="">
	<table border="0">
		<tr>
			<td style="font-size:18px;" align="right">Email</td>
			<td><input type="text" name="email" style="font-size:18px;" /></td>
		</tr>
		<tr>
			<td style="font-size:18px;">Password</td>
			<td><input type="password" name="password" style="font-size:18px;"/></td>
		</tr>
		<tr>
			<td></td>
			<td><input type="submit" name="submit" value="Login" style="font-size:20px;"/></td>
		</tr>
	</table>
</form>