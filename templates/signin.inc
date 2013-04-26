<div class="row posmid">
                        <div class="span3 offset1">
                         <div>
                                <h1 style="color:#FCDC3B;">Spuzik</h1>
                        </div>
			<div class="signup">
                                <button class="btn btn-primary" onclick="window.location.replace('/?p=main');">Create Account</button>
                        </div>
			<div style="text-align:right;">
                        <h4 style="color:white;">Bringing people<br /><span> together through sports and music.</span></h4>
                        </div>

                        </div>
                        <div class="span6">
				<div class="signup">
					<legend><h2 style="color:black;">Sign In</h2></legend>
<?php
if(isset($_GET['s']) && $_GET['s'] == 1){
	echo "<div class='alert alert-error'>
		<a href='#' class='close' data-dismiss='alert'>×</a>
		<b style='color:#B94A48'>Error</b> You are using an incorrect password and username combination.
	</div>";
}
?>
<form class="form-horizontal">
  <div class="control-group">
    <label class="control-label" for="inputEmail">Email</label>
    <div class="controls">
      <input style="height:30px;" type="text" id="emailSignin" placeholder="Email">
    </div>
  </div>
  <div class="control-group">
    <label class="control-label" for="inputPassword">Password</label>
    <div class="controls">
      <input style="height:30px;" type="password" id="passwordSignin" placeholder="Password">
    </div>
  </div>
  <div class="control-group">
    <div class="controls">
     	<button class="btn btn-primary" onclick="signIn();" style="margin-top:-5px;">Sign In</button>
    </div>
  </div>
</form>
<script>
function signIn(){
                                        $.ajaxSetup({async:false});
                                        var actionUrl = "actions.php?type=signIn";
                                        $.post(
                                                actionUrl,
                                                {
                                                        email: $("#emailSignin").val(),
                                                        password: $("#passwordSignin").val()
                                                },
                                                function(data,status){
                                                        var parseJSON = $.parseJSON(data);
                                                        if(parseJSON.status == "error"){
                                                                window.location.replace("/?p=signin&s=1")
                                                        }else{
                                                                window.location.replace("/?p=notifications")
                                                        }
                                                }
                                        );
                                }
</script>
<a href="javascript:void(0);" onclick="window.location.replace('/?p=forgot');" style="color:blue;">Forgot Password?</a>
				<div style="position:relative; top:35px; text-align:right; color:white; font-size:13px;">
                    <a href="#" style="color:white;">Privacy</a> &middot; <a href="#" style="color:white;">Contact</a> &middot; <a href="#" style="color:white;">Terms</a> &middot; <a href="#" style="color:white;">Cookies</a>
                  </div>
				</div>
			</div>
		</div>
	</div>
