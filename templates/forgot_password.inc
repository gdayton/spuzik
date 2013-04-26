<style type='text/css'>
.main{
	margin-top:50px;
	margin-left:20%;
	padding:10px;
	border:0px solid #000;
	width:600px;
}.main-color{
	background-color:yellow;
	padding:10px;
	-webkit-border-radius:5px;
	-moz-border-radius:5px;
	border-radius:5px;
}
</style>
<?php
	$type = $_GET['type']; // 0 - regular enter email, 1 - reset password screen
	if(!isset($type))
		$type = 0;
?>
<div class='main'>
	<img src="http://i.imm.io/Tzes.png" width="250px;" height="60px;"/>
	<div class='main-color'>
		<?php
		if($type == 0){
			echo "<div class='forgot'>
				<div style='border-bottom:1px dashed #cccc00; padding-bottom:10px; margin-bottom:10px;'><span style='color:black; font-size:25px;'>Forgot Password</span></div>
				Please enter the email that you used to create your Spuzik account below.
				<div class='alert alert-success' style='display:none;'>
					An email containing a reset link has been sent to <b style='color:#468847;'>glenn.dayton24@gmail.com</b>.
				</div>
				<div class='alert alert-error' style='display:none;'>
					We were not able to send an email to <b style='color:#b94a48;'>glenn.dayton24@gmail.com</b>.
				</div>
				<table border='0' width='100%' style='margin-top:15px; margin-bottom:30px;'>
					<tr>
						<td align='right' style='font-size:14px; padding-right:20px; color:black;'>
							Email
						</td>
						<td>
							<input type='text' class='newpword' style='height:30px; position:relative; top:4px;' />
						</td>
					</tr>
					<tr>
						<td></td>
						<td>
							<button class='btn btn-primary' style='color:white;'>Confirm Email</button>
						</td>
					</tr>
				</table>
			</div>";
		}else if($type == 1){
			echo "<div class='forgot-enter'>
				<div style='border-bottom:1px dashed #cccc00; padding-bottom:10px; margin-bottom:10px;'><span style='color:black; font-size:25px;'>Forgot Password</span></div>
				Please enter a new password for your Spuzik account below.
				<div class='alert alert-success' style='display:none;'>
					Your password was successfully changed.
				</div>
				<div class='alert alert-error' style='display:none;'>
					We were not able to change your password.
				</div>
				<table border='0' style='margin-top:15px; margin-bottom:30px;'>
					<tr>
						<td align='right' style='font-size:14px; padding-right:20px; color:black;'>
							New Password
						</td>
						<td>
							<input type='password' class='newpword' style='height:30px;' />
						</td>
					</tr>
					<tr>
						<td align='right' style='font-size:14px; padding-right:20px; color:black;'>
							New Password Confirmation
						</td>
						<td>
							<input type='password' class='newpword-conf' style='height:30px;' />
						</td>
					</tr>
					<tr>
						<td></td>
						<td align='left'>
							<button type='submit' class='btn btn-primary submit' >Reset Password</button>
						</td>
					</tr>
				</table>
			</div>";
		}
		?>
	</div>
</div>