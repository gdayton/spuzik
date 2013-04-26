<style type="text/css">
.signup-grad{
	background-image: linear-gradient(right bottom, #FCDC3B 15%, #FFEC8B 41%, #FFFFFF 82%);
	background-image: -o-linear-gradient(right bottom, #FCDC3B 15%, #FFEC8B 41%, #FFFFFF 82%);
	background-image: -moz-linear-gradient(right bottom, #FCDC3B 15%, #FFEC8B 41%, #FFFFFF 82%);
	background-image: -webkit-linear-gradient(right bottom, #FCDC3B 15%, #FFEC8B 41%, #FFFFFF 82%);
	background-image: -ms-linear-gradient(right bottom, #FCDC3B 15%, #FFEC8B 41%, #FFFFFF 82%);

	background-image: -webkit-gradient(
		linear,
		right bottom,
		left top,
		color-stop(0.15, #FCDC3B),
		color-stop(0.41, #FFEC8B),
		color-stop(0.82, #FFFFFF)
	)
}.signup{
	background-color:yellow;
}.favsul li{
	color:black;
}.coming-soon{
	font-size:20px;
	color:yellow;
	position:absolute;
	margin-left:80px;
	margin-top:8px;
	background-color:rgba(255,255,255,.3);
	padding:5px;
	width:400px;
	-moz-border-radius:5px;
	-webkit-border-radius:5px;
	border-radius:5px;
}
</style>
			<table border="0" width="100%;">
				<tr>
					<td align="left">
						<table border="0" width="100%;">
							<tr>
								<td align="left">
									<h1 style="text-align:center; font-size:45px; position:relative; right:80px;"><b style="color:#fc5a1e;">Welcome.</b></h1><br />
									<!--<div style='margin-left:75px;'><button type='button' class='btn btn-mini btn-primary' onclick='start();'>Start</button>
						 			 <button type='button' class='btn btn-mini btn-primary' onclick='favs();'>Favorites</button></div>-->
								</td>
								<td align="right">
									<div style="margin-top:10px; margin-right:10px;">
										<form>
											<input style="height:30px; width:190px;" type="text" id="emailSignin" placeholder="Email" />
											<input style="height:30px; width:190px;" type="password" id="passwordSignin" placeholder="Password" /><br />
											<a style="font-size:13px; position:relative; bottom:3px; right:3px;" href="?p=forgot_password">Forgot Password?</a>
											<button class="btn btn-warning" onclick="signIn();" style="margin-top:-5px;"><span style="color:black;">Sign In</span></button>
										</form>
									</div>
								</td>
							</tr>
						</table>
					</td>
				</tr>
				<tr>
					<td align="left" style="padding-top:5px;">
						<table border="0" cellpadding="5" style="margin-top:10px; margin-left:14%;">
							<tr>
								<td valign="top" style="padding-top:130px;">
									<div style='width:200px;'></div>
								</td>
								<td style="padding-top:5px; color:black;">
									<!-- Pwf0 PwFj PwHx PwI0 PwIo PwIA PwKy PwLd PwLq http://i46.tinypic.com/10ofsbl.png http://i50.tinypic.com/v7d40i.gif SMDt SMEP SMFh SMEP SMFQ-->
									<img src="http://i.imm.io/10Nfk.png" width="397px;" height="88px;" style="margin-left:55px; position:relative; bottom:60px;"/><br />
									<!-- ffde0f -->
									<span style="color:white; font-size:20px; position:relative; bottom:10px; right:10px;"><i class='icon-film icon-white' onmouseover="switchAct(6);" style='position:relative; right:10px; top:90px;'></i><b>The new social network for <span style="color:yellow;">Music</span> and <span style="color:yellow;">Sports</span> fans.</b></span>
									<div>
									<!--<span class='coming-soon'><center>Coming soon...</center></span>-->
									<table border='0' style='width:100%; margin-bottom:10px;'>
									 <tr>
									 	<td align='center'><img onclick="switchAct(0);" class='u0' rel="tooltip" title="Standard" data-placement="top" data-trigger="hover" src="http://i.imm.io/XYAY.png" width="40px;" height="40px;" style='cursor:pointer;' /></td><!-- ZEeP -->
									 	<td align='center'><img class='u1' rel="tooltip" title="Coming Soon..." data-placement="top" data-trigger="hover" src="http://i.imm.io/ZEgO.png" width="40px;" height="40px;" /></td><!-- XYzJ onclick="switchAct(1);" -->
									 	<td align='center'><img class='u2' rel="tooltip" title="Coming Soon..." data-placement="top" data-trigger="hover" src="http://i.imm.io/ZEgm.png" width="40px;" height="40px;" /></td><!-- XYDA onclick="switchAct(2);" -->
										<td align='center'><img class='u3' rel="tooltip" title="Coming Soon..." data-placement="top" data-trigger="hover" src="http://i.imm.io/ZEh3.png" width="40px;" height="40px;" /></td><!-- XYER onclick="switchAct(3);" -->
									 	<td align='center'><img class='u4' rel="tooltip" title="Coming Soon..." data-placement="top" data-trigger="hover" src="http://i.imm.io/ZEhg.png" width="40px;" height="40px;" /></td><!-- XYFt onclick="switchAct(4);" -->
									 	<td align='center'><img class='u5' rel="tooltip" title="Coming Soon..." data-placement="top" data-trigger="hover" src="http://i.imm.io/ZEhr.png" width="40px;" height="40px;" /></td><!-- XYFi onclick="switchAct(5);" -->
									</table>
									</div>
									<form class="form-horizontal" id="act-form" style="width:500px;" method="POST">
						  <div class='act-icon-holder'>
						  <img src="http://i50.tinypic.com/2lic02p.gif" style="float:right; margin-top:15px; margin-right:15px; display:none;" class="ban-icon" width="50px" height="50px"/>
						  <img src="http://i47.tinypic.com/2cqifj7.png" style="float:right; margin-top:15px; margin-right:15px; display:none;" class="mus-icon" width="40px" height="40px"/>
						  <img src="http://i.imm.io/W2yT.png" style="float:right; margin-top:15px; margin-right:15px; display:none;"  class="tea-icon" width="40px" height="40px"/>
						  <img src="http://i49.tinypic.com/30bh02h.png" style="float:right; margin-top:15px; margin-right:15px;" class="gen-icon" width="40px" height="40px"/>
						  <img src="http://i.imm.io/W2Cn.png" style="float:right; margin-top:15px; margin-right:15px; display:none;" class="ath-icon" width="50px" height="50px"/>
						  <img src="http://i50.tinypic.com/1pbdzr.gif" style="float:right; margin-top:15px; margin-right:15px; display:none;" class="age-icon" width="50px" height="50px"/>
						  </div>
						 <script>
						 var sports = ["Aquatics",
									"Archery",
									"Automobile Racing",
									"Badminton",
									"Base Jumping",
									"Baseball",
									"Basketball",
									"Beach Volleyball",
									"Biathlon",
									"Bobsleigh",
									"Body Building",
									"Bowling",
									"Boxing",
									"Camping",
									"Canoeing",
									"Cheerleading",
									"Chess",
									"Classical Dance",
									"Cricket",
									"Cross Country Running",
									"Cross Country Skiing",
									"Curling",
									"Cycling",
									"Darts",
									"Decathlon",
									"Diving",
									"Dog Training",
									"Down Hill Skiing",
									"Equestrianism",
									"Fencing",
									"Figure Skating",
									"Fishing",
									"Flag Football",
									"Football",
									"Golf",
									"Gymnastics",
									"Hang Gliding",
									"High Jump",
									"Hiking",
									"Hockey",
									"Hunting",
									"Ice Skating",
									"Inline Skating",
									"Judo",
									"Karate",
									"Kayaking",
									"Lacrosse",
									"Land Sailing",
									"Long Jump",
									"Luge",
									"Modern Dance",
									"Modern Pentathlon",
									"Motorcycle Racing",
									"Mountain Biking",
									"Mountaineering",
									"Netball",
									"Paint Ball",
									"Para Gliding",
									"Parachuting",
									"Pool Playing",
									"Quad Biking",
									"Racquetball",
									"River Rafting",
									"Rock Climbing",
									"Rodeo Riding",
									"Roller Skating",
									"Rowing",
									"Rugby",
									"Sailing",
									"Scuba Diving",
									"Shooting",
									"Shot Put",
									"Shuffleboard",
									"Skateboarding",
									"Skeet Shooting",
									"Snow Biking",
									"Snow Boarding",
									"Snow Sledding",
									"Soccer",
									"Speed Skating",
									"Sport Fishing",
									"Sprint Running",
									"Squash",
									"Stunt Plane Flying",
									"Sumo Wrestling",
									"Surfing",
									"Swimming",
									"Synchronized Swimming",
									"Table Tennis",
									"Taekwondo",
									"Tennis",
									"Track and Field",
									"Triathlon",
									"Volleyball",
									"Water Polo",
									"Water Skiing",
									"Weight Lifting",
									"Wheelchair Basketball",
									"White Water Rafting",
									"Wind Surfing",
									"Wrestling",
									"Yachting",
									"Yoga"];

						 var musics = ["Alternative",
									"Blues",
									"Children's Music",
									"Christian & Gospel",
									"Classic Hits",
									"Classical",
									"Comedy",
									"Country",
									"Dance",
									"Electronic",
									"Fitness & Workout",
									"Hip-Hop/Rap",
									"Jazz",
									"Latino",
									"Live Music",
									"Metal",
									"Pop",
									"R&B/Soul",
									"Reggae",
									"Rock",
									"Singer/Songwriter",
									"Soundtrack",
									"World"];
						 function dispVideo(){
						 	$(".cont-video").hide();
						 	$(".spuzik-video").show();
						 }

						 function start(){
						 	$(".act-icon-holder").hide();
						 	$(".signup .second").hide();
						 	$(".signup .third").hide();
						 	$(".signup .first").html("<span class='label label-info' style='color:yellow; background-color:#0000d9;'>Step 1</span> <b style='color:black;'><center>Select an account from above to sign up.</b></center>\
						 	<img onclick='dispVideo();' class='cont-video' src='http://i.imm.io/10Ngt.png' style='width:100%; margin-top:10px; cursor:pointer;'/>\
						 	<object width='640' height='360' class='spuzik-video' style='display:none;'>\
							  <param name='movie' value='https://www.youtube.com/v/2ryYDvE6UKg?controls=0&showinfo=0&version=3&autoplay=1'></param>\
							  <param name='allowFullScreen' value='true'></param>\
							  <param name='allowScriptAccess' value='always'></param>\
							  <embed src='https://www.youtube.com/v/2ryYDvE6UKg?controls=0&showinfo=0&version=3&autoplay=1' type='application/x-shockwave-flash' allowfullscreen='true' allowScriptAccess='always' width='480' height='280'></embed>\
							</object>\
						 	").show();
						 }

						 $(document).ready(function(){
						 	start();
						 });

						 function favs(){
						 	$(".act-icon-holder").hide();
						 	$(".signup .second").hide();
						 	$(".signup .third").hide();
							var sport = "";
						 	for(var i = 0;i < sports.length;i++){
						 		sport += "<li><label><input type='checkbox' style='position:relative; bottom:3px; right:2px;' />"+sports[i]+"</label></li>";
						 	}
						 	var music = "";
						 	for(var i = 0;i < musics.length;i++){
						 		music += "<li><label>"+musics[i]+"<input type='checkbox' style='position:relative; bottom:3px; left:2px;' /></label></li>";
						 	}
						 	$(".signup .first").html("<span class='label label-success' style='color:yellow; background-color:#0000d9;'>Step 3</span><b style='color:black;'><center>Compatibility Check.</b><br /><span style='font-size:13px;'>This information will be used for recommendations.</span></center>\
						 	<table border='0' width='100%;'>\
						 		<tr>\
						 			<th align='left' style='color:#156ed4;'>Sports</th>\
						 			<th align='right' style='color:#156ed4;'>Genres</th>\
						 		</tr>\
						 		<tr>\
						 			<td width='50%;' valign='top' align='left'>\
						 				<ul class='favsul sport-ul' style='list-style:none; margin-left:3px;'>"+sport+"</ul>\
						 			</td>\
						 			<td width='50%;' valign='top' align='right'>\
						 				<ul class='favsul music-ul' style='list-style:none;'>"+music+"</ul>\
						 			</td>\
						 		</tr>\
						 	</table>\
						 	").show();
						 }

						 $(".u0").tooltip('toggle');
						 $(".u0").tooltip('hide');
					  /* $(".u1").tooltip('toggle');
						 $(".u1").tooltip('hide');
						 $(".u2").tooltip('toggle');
						 $(".u2").tooltip('hide');
						 $(".u3").tooltip('toggle');
						 $(".u3").tooltip('hide');
						 $(".u4").tooltip('toggle');
						 $(".u4").tooltip('hide');
						 $(".u5").tooltip('toggle');
						 $(".u5").tooltip('hide'); */
						 </script>
						 <div class="signup">
						  <div class='first'></div>
						  <div class='second'>
						  <span class='label label-info' style='background-color:#0000d9; color:yellow;'>Step 2</span><br />
						  <h4 id="act-display-type" style="color:black;">Standard</h4>
									  <div class="alert alert-info loading-act" style="display:none;">
											<button type="button" class="close" data-dismiss="alert">×</button>
											<img src="/data/img/loader.gif" /> <b>Loading...</b> We're verifying that your information is valid.
									  </div>
									  <div class="alert alert-success signup-success2" style="display:none;">
											<button type="button" class="close" data-dismiss="alert">×</button>
											 <h4 style="color:green;">Success!</h4>
											 An email has been sent to <b class="signup-success-email" style="color:green;"></b>. Please click on the verification link contained within the email.
									  </div>
									  <div class="alert alert-error signup-error" style="display:none;">
											<button type="button" class="close" data-dismiss="alert">×</button>
											<h4 style="color:rgb(185,74,72);">Uh, oh...</h4>
											There were <b class="signup-error-b" style="color:rgb(185,74,72);">2</b> errors while trying to create your account.<br />
											<ul class="signup-error-ul" style="color:rgb(185,74,72);"></ul>
									  </div>
									  <div class="form-control">
			<div id="fnamed" class="control-group">
										<label class="control-label" for="fname">First name</label>
										<div class="controls">
										  <input style="height:30px;" type="text" id="fname" placeholder="First name">
										</div>
									  </div>
									  <input type="hidden" name="type" id="type" value="0" />
									  <div id="lnamed" class="control-group">
										<label class="control-label" for="lname">Last name</label>
										<div class="controls">
										  <input style="height:30px;" type="text" id="lname" placeholder="Last name">
										</div>
									  </div>
									  <div id="anamed" class="control-group" style="display:none;">
										<label class="control-label" for="aname">Group name</label>
										<div class="controls">
										  <input style="height:30px;" type="text" id="aname" placeholder="Group name">
										</div>
									  </div>
									  <div class="control-group">
										<label class="control-label" for="inputEmail">Email</label>
										<div class="controls">
										  <div class="input-prepend">
										  <span class="add-on"><i class="icon-envelope"></i></span>
										  <input style="height:30px; width:220px;" class="span2" type="text" id="email" placeholder="Email">
										  </div>
										</div>
									  </div>
									  <div class="control-group">
										<label class="control-label" for="password">Password</label>
										<div class="controls">
										  <input style="height:30px;" type="password" id="password" placeholder="Password">
										</div>
									  </div>
									  <div class="control-group">
										<label class="control-label" for="passwordv">Verify password</label>
										<div class="controls">
										  <input style="height:30px;" type="password" id="passwordv" placeholder="Verify password">
										</div>
									  </div>
									  <div id="dobd" class="control-group">
										<label class="control-label" for="dob">Date of birth</label>
										<div class="controls">
										  <select class="month" id="month" style="width:80px;">
											<option value="1">Jan</option>
											<option value="2">Feb</option>
											<option value="3">Mar</option>
											<option value="4">Apr</option>
											<option value="5">May</option>
											<option value="6">Jun</option>
											<option value="7">Jul</option>
											<option value="8">Aug</option>
											<option value="9">Sep</option>
											<option value="10">Oct</option>
											<option value="11">Nov</option>
											<option value="12">Dec</option>
										  </select>
										  <script>
											$(".month").change(function(){
													if(jQuery.inArray(parseInt($(".month").val()),[9,4,6,11]) != -1){ //has 30 days
															displayDays(30);
													}else if(jQuery.inArray(parseInt($(".month").val()),[1,3,5,7,8,10,12]) != -1){ //has 31 days
															displayDays(31);
													}else{ //has 28 days
															displayDays(29);
													}
											});
											$(".ind-act").hover(function(){
													$(this).find(".arrow").show();
											},function(){
													$(this).find(".arrow").hide();
											});

											function displayDays(amt){
													var s = "";
													for(var i = 1;i <= amt;i++){
															s+="<option>"+String(i)+"</option>";
													}
													$(".days").html(s);
											}
											//$(".act-tooltop").popover('hide');

											$(".act-tooltip").popover('show');
											$(".expand-act-button").click(function(){
													$(".expand-act").slideDown(300);
											});

											function switchAct(act){
												$(".act-icon-holder").show();
												$(".second").show();
												$(".first").hide();
												$(".third").hide();
												switch(act){
														case 0: //general
														case 1: //athelete
														case 3: //musician
													    case 5: //agent
																$("#fnamed").show();
																$("#lnamed").show();
																$("#dobd").show();
																$("#anamed").hide();
																switch(act){
																	case 0:
																		$(".gen-icon").show();
																		$(".ath-icon").hide();
																		$(".tea-icon").hide();
																		$(".ban-icon").hide();
																		$(".mus-icon").hide();
																		$(".age-icon").hide();
																		break;
																	case 1:
																		$(".ath-icon").show();
																		$(".tea-icon").hide();
																		$(".ban-icon").hide();
																		$(".mus-icon").hide();
																		$(".gen-icon").hide();
																		$(".age-icon").hide();
																		break;
																	case 3:
																		$(".mus-icon").show();
																		$(".gen-icon").hide();
																		$(".ath-icon").hide();
																		$(".tea-icon").hide();
																		$(".ban-icon").hide();
																		$(".age-icon").hide();
																		break;
																	case 5:
																		$(".mus-icon").hide();
																		$(".gen-icon").hide();
																		$(".ath-icon").hide();
																		$(".tea-icon").hide();
																		$(".ban-icon").hide();
																		$(".age-icon").show();
																		break;
																}
															break;
														case 2: //team
															$(".tea-icon").show();
															$(".mus-icon").hide();
															$(".gen-icon").hide();
															$(".ath-icon").hide();
															$(".ban-icon").hide();
															$(".age-icon").hide();
															break;
														case 4: //band
															$("#anamed").show();
															$("#fnamed").hide();
															$("#lnamed").hide();
															$("#dobd").hide();
															$(".tea-icon").hide();
															$(".mus-icon").hide();
															$(".gen-icon").hide();
															$(".ath-icon").hide();
															$(".ban-icon").show();
															$(".age-icon").hide();
															break;
														case 6: //show start menu
															start();
															break;
										switch(act){
											case 2:
												$(".tea-icon").show();
												$(".mus-icon").hide();
												$(".gen-icon").hide();
												$(".ath-icon").hide();
												$(".ban-icon").hide();
												$(".age-icon").hide();
												break;
											case 4:
												$(".tea-icon").hide();
												$(".mus-icon").hide();
												$(".gen-icon").hide();
												$(".ath-icon").hide();
												$(".ban-icon").show();
												$(".age-icon").hide();
												break;
										}
																	break;
													}
													var type = ['Standard','Athlete','Team','Musician','Band','Agent'];
													$("#act-display-type").html(type[act]);
													$("#type").attr("value",act);
											}

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

											function signUp(){
													$.ajaxSetup({async:false});
													var actionUrl = "actions.php?type=addUser";
													$.post(
															actionUrl,
															{
																	fname: $("#fname").val(),
																	lname:  $("#lname").val(),
																	email: $("#email").val(),
																	password: $("#password").val(),
																	passwordv: $("#passwordv").val(),
																	month: $("#month").val(),
																	day: $("#day").val(),
																	gender: $("#gender:checked").val(),
																	zip: $("#zip").val(),
																	year: $("#year").val(),
																	aname: $("#aname").val(),
																	type: $("#type").val()
															},
															function(data,status){
																	var parseJSON = $.parseJSON(data);
																	if(parseJSON.status_type == "internal"){
																		alert(parseJSON.status_msg);
																		$(".signup-error").html("There was a database issue.");
																		$(".signup-error").show();
																	}

																	if(parseJSON.status == "error"){
																			var error = new Array();
																			if(typeof parseJSON.status_itr.fname != "undefined"){
																					$("#fname").parent().parent().addClass("error");
																					error.push(parseJSON.status_itr.fname);
																			}else{
																					$("#fname").parent().parent().removeClass("error");
																			}
																			if(typeof parseJSON.status_itr.aname != "undefined"){
																					$("#aname").parent().parent().addClass("error");
																					error.push(parseJSON.status_itr.aname);
																			}else{
																					$("#aname").parent().parent().removeClass("error");
																			}
																			if(typeof parseJSON.status_itr.lname != "undefined"){
																					$("#lname").parent().parent().addClass("error");
																					error.push(parseJSON.status_itr.lname);
																			}else{
																					$("#lname").parent().parent().removeClass("error");
																			}
																			if(typeof parseJSON.status_itr.email != "undefined"){
																					$("#email").parent().parent().parent().addClass("error");
																					error.push(parseJSON.status_itr.email);
																			}else{
																					$("#email").parent().parent().parent().removeClass("error");
																			}
																			if(typeof parseJSON.status_itr.password != "undefined"){
																					$("#password").parent().parent().addClass("error");
																					$("#passwordv").parent().parent().addClass("error");
																					error.push(parseJSON.status_itr.password);
																			}else{
																					$("#password").parent().parent().removeClass("error");
																					$("#passwordv").parent().parent().removeClass("error");
																			}

																			// ----------------
																			if(typeof parseJSON.status_itr.gender != "undefined"){
																					$("#genderd").addClass("error");
																					error.push(parseJSON.status_itr.gender);
																			}else{
																					$("#genderd").removeClass("error");
																			}
																			if(typeof parseJSON.status_itr.zip != "undefined"){
																					$("#zipd").addClass("error");
																					error.push(parseJSON.status_itr.zip);
																			}else{
																					$("#zipd").removeClass("error");
																			}
																			// ----------------

																			if(typeof parseJSON.status_itr.dob != "undefined"){
																					$("#dob").parent().parent().addClass("error");
																					error.push(parseJSON.status_itr.dob);
																			}else{
																					$("#dob").parent().parent().removeClass("error");
																			}
																			//alert(error.length);
																			$(".signup-error-b").html(error.length.toString());
																			var alertText = "";
																			for(var i = 0;i < error.length;i++){
																					alertText+="<li style='color:#b94a48;'>"+error[i]+"</li>";
																			}
																			$(".signup-error-ul").html(alertText);
																			$(".signup-error").show();
																	}else{
																			//favs();
																			$(".signup-error").hide();
																			$("#act-display-type").hide();
																			$(".signup-success-email").html($("#email").val());
																			$(".signup-success2").show();

																			window.setTimeout(function(){
																					window.location.replace("/");
																			},15000);

																	}
															}
													);
													$.ajaxSetup({async:true});
											}
											function hideIt(){
													$(".form-control").slideToggle("slow",function(){
															$(".loading-act").show();
													});
											}
										  </script>
										  <select class="days" id="day" style="width:60px;">
							  			  <?php
											foreach(range(1,31) as $i){
													echo "<option value=\"".$i."\">".$i."</option>";
											}
										  ?>
										  </select>
										  <select style="width:90px;" id="year">
											<?php
											 $goto = date('Y')-13; //users must be 13 and older
											 foreach(range($goto,($goto-100)) as $year){
													echo "<option value=\"".$year."\">".$year."</option>";
											 }
											?>
										  </select>
										</div>
									  </div>
									  <div id="genderd" class="control-group">
									  	<label class="control-label" for="gender">Gender</label>
									  	<div class="controls">
									  		<table border='0' width='100%; position:relative; top:15px;'>
									  			<tr>
									  				<td style='color:black;' width='20%;'><label><input type='radio' id='gender' name='gender' value='m' style='position:relative; bottom:3px;' /> Male</label></td>
									  				<td style='color:black;' width='80%;'><label><input type='radio' id='gender' name='gender' value='f' style='position:relative; bottom:3px;' /> Female</label></td>
									  			</tr>
									  		</table>
									  	</div>
									  </div>
									  <div id="zipd" class="control-group">
									  	<label class="control-label" for="zip">Zip Code / Post Code</label>
									  	<div class="controls">
									  		<input type='text' id='zip' maxlength='8' style='height:30px; width:200px;' placeholder='Zip code / Post code...'/>
									  	</div>
									  </div>
												<div class="control-group">
												  <div class="controls">
													By clicking the &quot;Next&quot; button you agree to the <a style="color:#156ed4;" href="/?p=tos">Terms of Service</a>
																 </div>
												</div>
												<div class="control-group">
													<div class="controls">
														<button type="button" onclick="signUp();" name="submit" class="btn btn-primary signup-btn" style='color:yellow;'>Next</button>
													</div>
												</div>
											</div>
										</form>
									</div>
									</div>
								</td>
								<!--<td valign="top">
									<iframe width="480" height="360" src="http://www.youtube.com/embed/HXKOsajNZY4" frameborder="0" allowfullscreen style="margin-top:50px;"></iframe>
								</td>-->
							</tr>
							<tr>
								<td></td>
								<td align="right">
									<div style="position:relative; bottom:25px; font-size:13px;">
										<a href="#" style="color:white;">Privacy</a> &middot; <a href="#" style="color:white;">Contact</a> &middot; <a href="#" style="color:white;">Terms</a> &middot; <a href="#" style="color:white;">Cookies</a></span>
									</div>
								</td>
								<td></td>
							</tr>
						</table>
					</td>
				</tr>
			</table>