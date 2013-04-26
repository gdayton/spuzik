<?php
ob_start();
session_start();

// CHANGE TO SPUZIK REGULAR DB CONNECT VIA AMAZON
$db = new PDO("mysql:dbname=spuzik_bugs;host=localhost;","spk_handler","qaw3ufRa");
?>
<html>
	<head>
		<title>Bug Management</title>
		<meta http-equiv="content-type" content="text/html; charset=utf-8" />
		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.1/jquery.min.js"></script>
	</head>
	<body>
		<table border="0" style="margin:0 auto; width:1000px;">
			<tr>
				<td colspan="2" style="padding:5px;">
					<div style="float:right;">
						<?php
							if($_SESSION['logged'])
								echo "<a href='?p=logout' style='float:right;'>Log out</a><br />".$_SESSION['name'];
						?>
					</div>
					<h1>Spuzik Debugging</h1>
				</td>
			</tr>
			<tr>
				<style type="text/css">
					.nav{
						margin-top:10px;
						list-style:none;
						display:block;
						margin-right:10px;
					}.nav li{
						width:100%;
						padding:5px 0px;
						background-color:white;
						color:blue;
					}.nav li:hover{
						background-color:#ccc;
						color:white;
					}.nav a{
						text-decoration:none;
					}body{
						font-family:courier;
					}
				</style>
				<td width="150px" style="border-right:2px dashed #000;" valign="top">
					<ul class="nav">
						<a href="?p=main"><li>Home</li></a>
						<a href="?p=newbug"><li>Create Bug</li></a>
						<a href="?p=viewbugs"><li>View Bugs</li></a>
						<a href="?p=alert"><li>Send Alerts</li></a>
					</ul>
				</td>
				<td style="padding-left:20px;" valign="top">
					<p>
						<?php
							$p = $_GET['p'];
							if(file_exists("include/".$p.".inc")){
								if($_SESSION['logged'] || $_GET['p'] == "login"){
									include("include/".$p.".inc");
								}else{
									header("Location: ?p=login");
								}
							}else{
								echo "<span style='color:red'>Page does not exist</span>";
							}
						?>
					</p>
				</td>
			</tr>
		</table>
	</body>
</html>
<?php
ob_end_flush();
?>