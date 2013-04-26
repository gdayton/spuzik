<style>
.ybox{
	background-color:yellow;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
	border:0px solid #000;
	padding:10px;
	margin-top:300px;
	width:80%;
}.error{
	background-color:red;
	color:white;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
	border:0px solid #000;
	padding:5px;
	font-weight:bold;
}.success{
	background-color:green;
	color:white;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
	border:0px solid #000;
	padding:5px;
	font-weight:bold;
}
</style>
<center>
	<div class='ybox'>
		<h3 style='color:black;'>
		<?php
			if(isset($_GET['token'])){
				$res = $u->verif($_GET['token']);
				echo "<span class='success'>Success!</span> Your account has now been verified.<br /><center><b style='font-size:18px; color:black;'>Redirecting in 3 seconds...</b></center>";
			}else{
				echo "<span class='error'>ERROR</span> There was an error in processing this token.<br /><center><b style='font-size:18px; color:black;'>Redirecting in 3 seconds...</b></center>";
			}
		?>
		</h3>
	</div>
</center>
<script>
setTimeout(function(){
	window.location = "/";
},3000);
</script>