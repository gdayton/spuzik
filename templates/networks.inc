<?php include("header_bar.inc") ?>
<style type="text/css">
.chat{
	margin-left:10px;
	float:left;
	position:relative;
	width:200px;
	background-color:white;
}
.chat .people .person{
	border-bottom:1px solid #CCC;
	padding:5px;
}.chat .people .person img{
	float:left;
	margin-right:3px;
	width:20px;
	height:20px;
}.chat .people{
}.chat .dialog{
}.chat .dialog .chat-item{
	font-size:13px;
}.chat .chat-header{
	padding:3px;
}.chat .dialog .chat-container{
	overflow:auto;
	padding:5px;
}.chat .dialog .chat-container i{
	margin-left:15px;
	font-size:12px;
	color:#CCC;
}.notif-i{
	border-bottom:1px solid #EEE;
	padding-top:3px;
	padding-bottom:3px;
	cursor:pointer;
	/*border-bottom:1px solid #CCC;*/
}.notif-i .icon-chevron-right{
    float:right;
}.notif-main-area{
	/*position:relative;
	left:50px;
	top:15px;*/
}.musicp{
	position:absolute;
	bottom:5px;
	left:10px;
}.sL-image{
	width:100%;
	margin:0 0 -30% 0;
}.sL-i-cont{
	overflow:hidden;
}.sL-main{
	height:100%;
	z-index:1000000;
}.net-area .net-link{
	padding:3px;
}.net-area .net-link{
	padding-bottom:2px;
	border-bottom:1px solid #EEE;
}.net-area a:hover{
	color:black;
	text-decoration:none;
}.net-area .net-link:hover{
	background-color:#FFD700;
}.tab-area .tab{
	border:0px solid #000;
	-moz-border-top-right-radius:5px;
	-webkit-border-top-right-radius:5px;
	border-top-right-radius:5px;
	-moz-border-top-left-radius:5px;
	-webkit-border-top-left-radius:5px;
	border-top-left-radius:5px;
	padding:3px;
	font-weight:bold;
}.tab-area a{
	text-decoration:none;
	color:black;
}.tab-area .tab:hover{
	background-color:#EEE;
	color:black;
}.btncustom{
	background-image: -webkit-linear-gradient(top,#fcdc3c,#fbd515);
	background-image: -moz-linear-gradient(top,#fcdc3c,#fbd515);
	background-image: -o-linear-gradient(top,#fcdc3c,#fbd515)
}.btncustom:hover{
	background-color:#fbd515;
}.btncustom2{
	background-image: -webkit-linear-gradient(top,#ff0000,#b10000);
	background-image: -o-linear-gradient(top,#ff0000,#b10000);
	background-image: -moz-linear-gradient(top,#ff0000,#b10000);
}.btncustom2:hover{
	background-color:#b10000;
}
</style>
<table border="0" width="100%;" height="100%">
	<tr>
		<td colspan="3" height="65px;"></td>
	</tr>
	<tr>
		<td valign="top">
			<table border="0" width="100%;" height="100%;" cellspacing="0" cellpadding="0">
				<tr>
					<td width="15%;" valign="top">
						<div style="height:100%; padding:10px;">
							<img src="http://i47.tinypic.com/21dj0c3.png" width="16px;" height="16px;" style="float:right;"/><b>Networks</b>
							<table width="100%" border="0" class="net-area" style="margin-top:10px;">
								<tr>
									<td><a href="#"><div class="net-link">Family</div></a></td>
								</tr>
								<tr>
									<td><a href="#"><div class="net-link">Calabasas Soccer</div></a></td>
								</tr>
								<tr>
									<td><a href="#"><div class="net-link">Ollie, Jake, Glenn</div></a></td>
								</tr>
								<tr>
									<td><a href="#"><div class="net-link">Spurs Fans</div></a></td>
								</tr>
								<tr>
									<td><a href="#"><div class="net-link">Laker Fans</div></a></td>
								</tr>
								<tr>
									<td><a href="#"><div class="net-link">Pink Floyd Nation</div></a></td>
								</tr>
								<tr>
									<td><a href="#"><div class="net-link">My Band</div></a></td>
								</tr>
							</table>
							<script>
							function dropCreateNetwork(){
								$(".create-network").slideDown("fast");
							}
							</script>
							<table border="0" width="100%;" cellpadding="5" style="margin-top:10px;">
								<tr>
									<td><button class="btn btn-warning" onclick="dropCreateNetwork()"><span style="color:black;">Create a Network<i class="icon-plus" style="position:relative; left:5px; top:0px;"></i></span></button>
									<div class="create-network" style="display:none;">
										<form class="form-horizontal" style="margin-top:20px;">
											<input type="text" id="inputEmail" style="height:30px; width:180px;" placeholder="Name"/>
											<select div="privacy" style="margin-top:3px; width:180px;">
												<option value="public">Public</option>
												<option value="private">Private</option>
											</select>
											<button type="submit" class="btn btn-primary" style="margin-top:5px;">Create</button>
										</form>
									</div>
									</td>
									<!--Create a Network<i class="icon-plus" style="position:relative; left:5px; top:0px;"></i></td>-->
								</tr>
								<tr>
									<td><button class="btn btn-warning"><span style="color:black;">Send Invitations<i class="icon-envelope" style="position:relative; left:5px; top:1px;"></i></span></button></td>
									<!--Send Invitations<i class="icon-envelope" style="position:relative; left:5px; top:1px;"></i></td>-->
								</tr>
							</table>
						</div>
					</td>
					<td width="85%;" valign="top">
						<table border="0" height="100%;" width="100%;" cellspacing="0" cellpadding="0">
							<tr align="center" valign="top">
								<td height="25%;">
									<div>
									<table border="0" width="100%;">
										<tr>
											<td width="25%;" valign="top" style="padding-left:10px;">
												<table border="0" width="100%">
													<tr>
														<td colspan="5" align="center"><h3><span style="border-bottom:1px solid black;">The Google Guys</span></h3></td>
													</tr>
													<tr>
														<td><img class="img-rounded" src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRFDiQ0tf6dinUHJ0aLWARyd4zpScBZoc3xhAlnm7ay0VvGsbQz_Q" width="45px;" height="45px;" />
														<img class="img-rounded" src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRFDiQ0tf6dinUHJ0aLWARyd4zpScBZoc3xhAlnm7ay0VvGsbQz_Q" width="45px;" height="45px;" />
														<img class="img-rounded" src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRFDiQ0tf6dinUHJ0aLWARyd4zpScBZoc3xhAlnm7ay0VvGsbQz_Q" width="45px;" height="45px;" />
														<img class="img-rounded" src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRFDiQ0tf6dinUHJ0aLWARyd4zpScBZoc3xhAlnm7ay0VvGsbQz_Q" width="45px;" height="45px;" />
														<img class="img-rounded" src="https://encrypted-tbn3.gstatic.com/images?q=tbn:ANd9GcRGIS--tz2H8Syud648WotwLLqtJma8QTzKPByRGIc9Eq_6-fKj" width="45px;" height="45px;" /></td>
													</tr>
												</table>
											</td>
											<td width="50%;" valign="bottom">
												<div class="sL-i-cont">
													<img class="sL-image" src="http://www.metromodemedia.com/images/Features/Issue%2056/Google-Group-520.jpg" />
												</div>
											</td>
											<td width="25%;" valign="top">
												<div style="padding:20px;">
													<h3 style="position:relative; bottom:25px;">Info</h3><br />
													<div style="position:relative; bottom:45px;">
														Private <img src="http://i.imm.io/NjOP.png" style="position:relative; bottom:3px; right:3px;" width="14px;" height="14px;"/><br />
														5 members<br />
														Created November 5, 2012<br />
														Administrator: <a href="#">Bob Tomson</a>
													</div>
												</div>
											</td>
										</tr>
									</table></div>
								</td>
							</tr>
							<tr align="center" valign="top">
								<td height="75%;">
									<div class="sL-main" style="padding:10px;">
										<table border="0" width="100%;" style="margin-top:-15px;">
											<tr>
												<td align="center">
													<div style="background-color:#ffff00; padding-top:5px; position:relative; left:2px; width:100%;">
														<table border="0" width="100%;" class="tab-area">
															<tr>
																<td align="center" width="20%">
																	<a href="#">
																		<div class="tab">
																			Feed
																		</div>
																	</a>
																</td>
																<td align="center" width="20%">
																	<a href="#">
																		<div class="tab">
																			Photos
																		</div>
																	</a>
																</td>
																<!--
																<td align="center" width="30%">
																	<a href="#">
																		<div class="tab">
																			Memory Zone
																		</div>
																	</a>
																</td>
																<td align="center" width="30%">
																	<a href="#">
																		<div class="tab">
																			Prediction Zone
																		</div>
																	</a>
																</td-->
															</tr>
														</table>
													</div>
												</td>
											</tr>
											<tr align="center">
												<td style="padding-top:5px; padding-bottom:5px;">
													<div style="width:30%;">
														<textarea style="width:100%;" placeholder="Express yourself..."></textarea><br />
														<button class="btn btn-primary" style="float:right;"><b style="color:#FCDC3B;">Vent</b></button><a href="#" style="margin-left:10px;"><i class="icon-picture icon-white"></i></a><a href="#" style="margin-left:10px;"><i class="icon-film icon-white"></i></a><a href="#" style="margin-left:10px;"><i class="icon-edit icon-white"></i></a>
													</div>
												</td>
											</tr>
											<tr>
												<td style="padding-top:15px;">
													<table border="0" width="100%;" height="100%;">
														<tr>

															<td>
																<div class="notif-i">
																	<table border="0">
																		<tr>
																			<td valign="top"><img src="https://encrypted-tbn2.gstatic.com/images?q=tbn:ANd9GcTeCQ1hFcjHfVnqQi89a3kgIqKDS9VetMe7jWDYRmM9p9aj9oTBog" class="img-rounded" width="45" height="64"></img></td>
																			<td style="padding-left:10px; font-size:12px; color:white;" valign="top"><b>Samantha Lee</b><br />&nbsp;&nbsp;&nbsp; I'm really excited about the new football season! I'm really excited about the new football season! I'm really excited about the new football season!I'm really excited about the new football season! I'm really excited about the new football season! I'm really excited about the new football season!</b>
																			<br /><br />
																			<table border="0" width="100%">
																				<tr>
																					<td valign="top">
																						<span style="font-size:12px;"><b>Bob Tom</b>&nbsp;Really cool!<br /><b>Tom Brown</b>&nbsp;Nice nice post!<br /><a href="#">3 comments</a><br /><input type="text" placeholder="Comment..." style="height:20px; font-size:12px; margin-left:20px;" /></span>
																					</td>
																					<td valign="top">
																						<div class="btn-group">
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Clap" data-placement="top" data-trigger="hover"><img src="http://i50.tinypic.com/2el9i7c.gif" width="15px" height="15px" style="position:relative; bottom:2px;"/><span style="color:black"> 2</span></button>
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Respond" data-placement="top" data-trigger="hover"><i class="icon-share-alt"></i><span style="color:black"> 5</span></button>
																						</div>
																						<span style="font-size:12px;">3hrs ago</span>
																					</td>
																				</tr>
																			</table>
																			</td>
																		</tr>
																	</table>
																</div>
																<div class="notif-i">
																	<table border="0">
																		<tr>
																			<td valign="top"><img src="https://encrypted-tbn2.gstatic.com/images?q=tbn:ANd9GcTeCQ1hFcjHfVnqQi89a3kgIqKDS9VetMe7jWDYRmM9p9aj9oTBog" class="img-rounded" width="45" height="64"></img></td>
																			<td style="padding-left:10px; font-size:12px; color:white;" valign="top"><b>Samantha Lee</b><br />&nbsp;&nbsp;&nbsp; This is a shot that I took of Johnny Boy playing soccer today! He is doing really well this season.</b><br />
																			<img width="200px;" style="margin-left:80px;" src="http://s7d2.scene7.com/is/image/Fathead/lgo_nfl_pittsburgh_steelers?layer=comp&fit=constrain&hei=350&wid=350&fmt=png-alpha&qlt=75,0&op_sharpen=1&resMode=bicub&op_usm=0.0,0.0,0,0&iccEmbed=0" />
																			<br /><br />
																			<table border="0" width="100%">
																				<tr>
																					<td valign="top">
																						<span style="font-size:12px;"><a href="#">3 comments</a><br /><input type="text" placeholder="Comment..." style="height:20px; font-size:12px; margin-left:20px;" /></span>
																					</td>
																					<td valign="top">
																						<div class="btn-group">
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Clap" data-placement="top" data-trigger="hover"><img src="http://i50.tinypic.com/2el9i7c.gif" width="15px" height="15px" style="position:relative; bottom:2px;"/><span style="color:black"> 2</span></button>
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Respond" data-placement="top" data-trigger="hover"><i class="icon-share-alt"></i><span style="color:black"> 5</span></button>
																						</div>
																						<span style="font-size:12px;">3hrs ago</span>
																					</td>
																				</tr>
																			</table>
																			</td>
																		</tr>
																	</table>
																</div>
																<div class="notif-i">
																	<table border="0">
																		<tr>
																			<td valign="top"><img src="https://encrypted-tbn2.gstatic.com/images?q=tbn:ANd9GcTeCQ1hFcjHfVnqQi89a3kgIqKDS9VetMe7jWDYRmM9p9aj9oTBog" class="img-rounded" width="45" height="64"></img></td>
																			<td style="padding-left:10px; font-size:12px; color:white;" valign="top"><b>Samantha Lee</b><br />&nbsp;&nbsp;&nbsp; This is a shot that I took of Johnny Boy playing soccer today! He is doing really well this season.</b><br />
																			<iframe width="300" height="169" src="http://www.youtube.com/embed/xRRtOJqB8PU" frameborder="0" allowfullscreen></iframe>
																			<br /><br />
																			<table border="0" width="100%">
																				<tr>
																					<td valign="top">
																						<span style="font-size:12px;"><a href="#">3 comments</a><br /><input type="text" placeholder="Comment..." style="height:20px; font-size:12px; margin-left:20px;" /></span>
																					</td>
																					<td valign="top">
																						<div class="btn-group">
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Clap" data-placement="top" data-trigger="hover"><img src="http://i50.tinypic.com/2el9i7c.gif" width="15px" height="15px" style="position:relative; bottom:2px;"/><span style="color:black"> 2</span></button>
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Respond" data-placement="top" data-trigger="hover"><i class="icon-share-alt"></i><span style="color:black"> 5</span></button>
																						</div>
																						<span style="font-size:12px;">3hrs ago</span>
																					</td>
																				</tr>
																			</table>
																			</td>
																		</tr>
																	</table>
																</div>
															</td>

															<!-- CENTER -->
															<td width="20px;" align="center">
																<div style="background-color:#FCDC3B; height:100%; width:2px;"></div>
															</td>


															<td>
																<div class="notif-i">
																	<table border="0">
																		<tr>
																			<td valign="top"><img src="https://encrypted-tbn2.gstatic.com/images?q=tbn:ANd9GcTeCQ1hFcjHfVnqQi89a3kgIqKDS9VetMe7jWDYRmM9p9aj9oTBog" class="img-rounded" width="45" height="64"></img></td>
																			<td style="padding-left:10px; font-size:12px; color:white;" valign="top"><b>Samantha Lee</b><br />&nbsp;&nbsp;&nbsp; I'm really excited about the new football season! I'm really excited about the new football season! I'm really excited about the new football season!I'm really excited about the new football season! I'm really excited about the new football season! I'm really excited about the new football season!</b>
																			<br /><br />
																			<table border="0" width="100%">
																				<tr>
																					<td valign="top">
																						<span style="font-size:12px;"><b>Bob Tom</b>&nbsp;Really cool!<br /><b>Tom Brown</b>&nbsp;Nice nice post!<br /><a href="#">3 comments</a><br /><input type="text" placeholder="Comment..." style="height:20px; font-size:12px; margin-left:20px;" /></span>
																					</td>
																					<td valign="top">
																						<div class="btn-group">
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Clap" data-placement="top" data-trigger="hover"><img src="http://i50.tinypic.com/2el9i7c.gif" width="15px" height="15px" style="position:relative; bottom:2px;"/><span style="color:black"> 2</span></button>
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Respond" data-placement="top" data-trigger="hover"><i class="icon-share-alt"></i><span style="color:black"> 5</span></button>
																						</div>
																						<span style="font-size:12px;">3hrs ago</span>
																					</td>
																				</tr>
																			</table>
																			</td>
																		</tr>
																	</table>
																</div>
																<div class="notif-i">
																	<table border="0">
																		<tr>
																			<td valign="top"><img src="https://encrypted-tbn2.gstatic.com/images?q=tbn:ANd9GcTeCQ1hFcjHfVnqQi89a3kgIqKDS9VetMe7jWDYRmM9p9aj9oTBog" class="img-rounded" width="45" height="64"></img></td>
																			<td style="padding-left:10px; font-size:12px; color:white;" valign="top"><b>Samantha Lee</b><br />&nbsp;&nbsp;&nbsp; This is a shot that I took of Johnny Boy playing soccer today! He is doing really well this season.</b><br />
																			<img width="200px;" style="margin-left:80px;" src="http://i47.tinypic.com/qoi0yx.jpg" />
																			<br /><br />
																			<table border="0" width="100%">
																				<tr>
																					<td valign="top">
																						<span style="font-size:12px;"><a href="#">3 comments</a><br /><input type="text" placeholder="Comment..." style="height:20px; font-size:12px; margin-left:20px;" /></span>
																					</td>
																					<td valign="top">
																						<div class="btn-group">
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Clap" data-placement="top" data-trigger="hover"><img src="http://i50.tinypic.com/2el9i7c.gif" width="15px" height="15px" style="position:relative; bottom:2px;"/><span style="color:black"> 2</span></button>
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Respond" data-placement="top" data-trigger="hover"><i class="icon-share-alt"></i><span style="color:black"> 5</span></button>
																						</div>
																						<span style="font-size:12px;">3hrs ago</span>
																					</td>
																				</tr>
																			</table>
																			</td>
																		</tr>
																	</table>
																</div>
																<div class="notif-i">
																	<table border="0">
																		<tr>
																			<td valign="top"><img src="https://encrypted-tbn2.gstatic.com/images?q=tbn:ANd9GcTeCQ1hFcjHfVnqQi89a3kgIqKDS9VetMe7jWDYRmM9p9aj9oTBog" class="img-rounded" width="45" height="64"></img></td>
																			<td style="padding-left:10px; font-size:12px; color:white;" valign="top"><b>Samantha Lee</b><br />&nbsp;&nbsp;&nbsp; This is a shot that I took of Johnny Boy playing soccer today! He is doing really well this season.</b><br />
																			<iframe width="300" height="169" src="http://www.youtube.com/embed/xRRtOJqB8PU" frameborder="0" allowfullscreen></iframe>
																			<br /><br />
																			<table border="0" width="100%">
																				<tr>
																					<td valign="top">
																						<span style="font-size:12px;"><a href="#">3 comments</a><br /><input type="text" placeholder="Comment..." style="height:20px; font-size:12px; margin-left:20px;" /></span>
																					</td>
																					<td valign="top">
																						<div class="btn-group">
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Clap" data-placement="top" data-trigger="hover"><img src="http://i50.tinypic.com/2el9i7c.gif" width="15px" height="15px" style="position:relative; bottom:2px;"/><span style="color:black"> 2</span></button>
																							<button class="btn btn-small user_type btn-warning" rel="tooltip" title="Respond" data-placement="top" data-trigger="hover"><i class="icon-share-alt"></i><span style="color:black"> 5</span></button>
																						</div>
																						<span style="font-size:12px;">3hrs ago</span>
																					</td>
																				</tr>
																			</table>
																			</td>
																		</tr>
																	</table>
																</div>
															</td>
														</tr>
													</table>
												</td>
											</tr>
										</table>
									</div>
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>