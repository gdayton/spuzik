<!doctype html>
<html itemscope="itemscope" itemtype="http://schema.org/WebPage">
	<head>
		<title>Spuzik | The Social Network for Music and Sports</title>

		<!-- CSS -->
		<link rel="shortcut icon" href="/data/img/spuzik_icon.ico" type="image/x-icon" />
		<link rel="stylesheet" type="text/css" href="data/css/bootstrap.min.css" />
		<link rel="stylesheet" type="text/css" href="data/css/css/bootstrap-glyphicons.css" />
		<link rel="stylesheet" type="text/css" href="main.css" />
	</head>
	<body>

		<script id="feedTemplate" type="text/template">
			<div class="info">
				<span class="glyphicon glyphicon-remove remove-feed-item"></span>
				<span class="glyphicon glyphicon-flag flag-feed-item"></span>
				<img class="img-rounded" src="<%= profile_pic %>" />
				<a href="#"><%= name %></a>
			</div>
			<div class="content">
				<%= content %>
			</div>
			<div class="actions">
				<table border='0' cellpadding='0' cellspacing='0' width='100%;'>
					<tr>
						<td valign="top">
							<textarea class="form-control comment-enter" rows="3" placeholder="Make a comment..." style="display:none;"></textarea>
							<div class="expand-comments">
								<span class="glyphicon glyphicon-eye-open"></span> <%= comment_amount %> Comments
							</div>
							<div class="comments"></div>
						</td>
						<td valign="top" width="100px;">
							<div class="comment-controls">
								<span class="date"><%= date %></span><br />
								<table border="0" cellpadding="0" cellspacing="0">
									<tr>
										<td width="100%;"><button type="button" class="btn btn-mini custom-yellow" style="width:95%;"><img src="http://i.imm.io/14rOO.png" /><span class="clap-amount"><%= claps %></span></button></td>
										<td width="30px;"><button type="button" class="btn btn-mini custom-yellow"><span class="glyphicon glyphicon-comment comment-toggle" style="color:blue;"></span></td>
									</tr>
								</table>
								<!--<button type="button" class="btn btn-mini btn-primary post-comment">Comment</button>-->
							</div>
						</td>
					</tr>
				</table>
			</div>
		</script>

		<script id="commentTemplate" type="text/template">
			<div class="comment">
				<a href="#"><%= name %></a> <%= comment %>
			</div>
		</script>

		<script id="profileinfoTemplate" type="text/template">
			<table border="0" cellpadding="0" cellspacing="0" width="170px">
				<tr>
					<td>
						<div class="profile-pic">
							<img class="img-rounded" src="<%= profile_pic %>" />
						</div>
					</td>
					<td valign="top" align="right">
						<div class="stats">
							<table border="0" cellpadding="0" cellspacing="0" style="border-color:white;">
								<tr>
									<td colspan="2" align="left">
										<div class="name">
											<b><%= name %></b>
										</div>
									</td>
								</tr>
								<tr>
									<td align="left"><span class="fans-header">Fans</span></td>
									<td align="left"><b class="fans-content"><%= fans %></b></td>
								</tr>
								<tr>
									<td align="left"><span class="supporting-header">Supporting</span></td>
									<td align="left"><b class="supporting-content"><%= supporting %></b></td>
								</tr>
							</table>
						</div>
					</td>
				</tr>
			</table>
		</script>

		<script id="meTemplate" type="text/template">
			<div class="user-info">
				<table border="0" cellpadding="0" cellspacing="0" width="100%;">
					<tr>
						<th>Nickname</th>
						<th>Hometown</th>
						<th>Gender</th>
						<th>Birthdate</th>
					</tr>
					<tr>
						<td><%= nickname %></td>
						<td><%= location %></td>
						<td><%= gender %></td>
						<td><%= age_date %> (<%= age %>)</td>
					</tr>
					<tr>
						<td colspan="4"><p class="about-me">Donec eget diam nec mauris suscipit placerat. Proin tempor est id dolor tincidunt vehicula. Nam id ante dapibus, iaculis magna in, porttitor ligula. Mauris sit amet accumsan nisi. Ut at risus et erat vehicula tristique eget ac eros. Fusce sed semper tortor, et fringilla odio. Donec accumsan elementum lorem et rutrum. Sed malesuada eu tortor congue tincidunt.
Sed lacinia arcu sodales massa egestas tristique. Vestibulum in ornare neque. Maecenas suscipit facilisis lectus non pretium. Mauris suscipit, tortor in feugiat auctor, metus elit rhoncus nisl, in suscipit mi neque nec orci. Donec porta neque a purus molestie mattis. Vivamus erat neque, suscipit eget varius a, venenatis ac tortor. Aenean fringilla laoreet nunc id eleifend. Donec sed tellus nibh. Sed facilisis tortor ac quam mattis dictum. Ut nec est purus. Nunc sit amet tortor at leo luctus sollicitudin vitae vel enim. Donec dapibus, ligula ut viverra scelerisque, nunc purus sagittis ante, commodo malesuada quam ipsum non tellus. Duis sed dapibus neque. Phasellus at pretium risus. Sed non dolor sagittis, tempus nibh in, pulvinar ligula. Duis vitae ligula sem.
Integer consectetur est neque, non molestie urna tempor non. Phasellus feugiat risus sit amet felis tristique vulputate. Quisque commodo a risus a aliquet. In orci metus, iaculis vel sodales a, rhoncus ac ligula. Duis sit amet massa velit. Donec lobortis metus eu ullamcorper mattis. Suspendisse mollis aliquam facilisis. Phasellus vel accumsan lacus, vitae feugiat mauris. Sed sit amet est eget quam auctor hendrerit vitae eget dolor. Duis consequat luctus nisl. Vivamus ac feugiat nisi.
In in nulla dui. Sed euismod lacus nec ante pharetra, ac tristique libero condimentum. In convallis rutrum ante in ullamcorper. Phasellus eleifend nibh sit amet mollis scelerisque. Mauris sodales nec quam quis consequat. Vestibulum vitae dictum nibh. Sed suscipit pharetra nisl. Aliquam interdum est ut diam ornare, in placerat sapien placerat. Nulla commodo interdum ligula, a pulvinar erat sodales ac. Cras consequat elementum adipiscing. Fusce accumsan, ipsum condimentum volutpat tempor, lorem orci ullamcorper tortor, id pretium turpis leo non turpis. Nunc hendrerit tellus quis nisi viverra ultrices. Ut eu risus magna. Integer quis augue ac elit posuere porta. Proin et turpis tellus.
Praesent sem risus, ornare sit amet mollis vitae, ornare convallis ligula. Morbi justo ipsum, sollicitudin quis sagittis nec, laoreet in urna. Morbi id sapien leo. Donec vestibulum diam sed sapien tempus consequat. Curabitur accumsan nunc quam, ac scelerisque lectus consectetur vel. Etiam feugiat elit et nunc dignissim, quis consectetur dolor porttitor. Morbi molestie ipsum quis ipsum iaculis, eu eleifend metus ullamcorper. Vestibulum ac orci orci.</p></td>
					</td>
				</table>
			</div>
			<div class="user-quotes">
				<div class="user-quotes-icon"><span class="glyphicon glyphicon-align-center"></span> Favorite Quotes & Lyrics</div>
				<ul class="user-quotes-ul"></ul>
			</div>
			<div class="user-memory">
				<div class="user-memory-icon"><span class="glyphicon glyphicon-dashboard"></span> Memory Zone</div>
				<table class="memory-table" border="0" cellpadding="0" cellspacing="0" width="100%"></table>
			</div>
		</script>

		<script id="quoteTemplate" type="text/template">
			<%= quote %><span class="quote-auth"> <%= author %></span>
		</script>

		<script id="lineupitemTemplate" type="text/template">
			<span style="color:#179bff;"><%= lineup %></span><span class="glyphicon glyphicon-trash lineup-trash"></span>
		</script>

		<script id="memoryTemplate" type="text/template">
			<th valign="top"><%= year %></th>
			<td valign="top"><%= memory %></td>
		</script>

		<!-- SCRIPTS -->
		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
		<script src="//ajax.googleapis.com/ajax/libs/jqueryui/1.9.2/jquery-ui.min.js"></script>
		<script src="/data/bootstrap/js/bootstrap.min.js"></script>
		<script src="http://underscorejs.org/underscore-min.js"></script>
		<script src="http://documentcloud.github.io/backbone/backbone-min.js"></script>
		<script src="main.js"></script>
		<script src="data/js/bootstrap.min.js"></script>
		<script type="text/javascript" src="http://malsup.github.com/jquery.cycle.all.js"></script>
		<script src="http://blog.guilhemmarty.com/flippy/jquery.flippy.min.js"></script>

		<!--<div class="fadeSec"></div>-->
		<!--<div class="contentPop">
			<div class="photo-holder">
				<table border="0" cellpadding="0" cellspacing="0" width="100%;" height="100%;">
					<tr>
						<td width="75%;">
							<img src="http://www.city-data.com/forum/members/rd5050-202436-albums-san-diego-pic21128-pacific-beach-jan-16-2009.jpg" width="100%;"/>
						</td>
					</tr>
					<tr>
						<td width="25%" valign="top">
							<div class="sidebar">
								<table border="0" cellpadding="0" cellspacing="0" width="100%;">
									<tr>
										<td align="right">
											<span class="glyphicon glyphicon-remove close-modal"></span>
										</td>
									</tr>
									<tr>
										<td valign="top" style="background-color:white;">
											content
										</td>
									</tr>
								</table>
							</div>
						</td>
					</tr>
				</table>
			</div>
		</div>-->
		<!--<div class="settingsPop">
			<script>
			function tabSettings(settext){
				if(settext == "user"){ $(".settings-user").show(); }else{ $(".settings-user").hide(); }
				if(settext == "security"){ $(".settings-security").show(); }else{ $(".settings-security").hide(); }
				if(settext == "comp"){ $(".settings-comp").show(); }else{ $(".settings-comp").hide(); }
			}
			</script>
			<span class="glyphicon glyphicon-remove settings-close"></span>
			<span class="header"><span class="glyphicon glyphicon-cog"></span> Settings</span>
			<table class="settings-content" border="0" cellpadding="0" cellspacing="0" width="100%;">
				<tr>
					<td width="30%;" valign="top">
						<table class="settings-nav" border="0" cellpadding="0" cellspacing="0" width="100%;">
							<tr onclick="tabSettings('user');">
								<td style="background-color:#ededed; padding-left:10px;"><span class="glyphicon glyphicon-user"></span> User management</td>
								<td align="left"><div class="right-tri"></div></td>
							</tr>
							<tr onclick="tabSettings('security');">
								<td style="padding-left:10px;"><span class="glyphicon glyphicon-lock"></span> Security</td>
								<td></td>
							</tr>
							<tr onclick="tabSettings('comp');">
								<td style="padding-left:10px;"><span class="glyphicon glyphicon-screenshot"></span> Compatibility</td>
								<td></td>
							</tr>
						</table>
					</td>
					<td>
						<div class="settings-area">
							<div class="settings-user">
								<form>
									<table class="settings-table" border="0" cellpadding="3" cellspacing="0">
										<tr>
											<td colspan="2" align="left"><span style="font-size:20px; font-weight:500;">Change Name</span></td>
										</tr>
										<tr>
											<td><input type="text" class="form-control" value="Glenn Dayton" /></td>
											<td><button class="btn btn-success name-change">Change Name</button></td>
										</tr>
										<tr>
											<td colspan="2">
												<b>Account registered:</b> July 12, 2013 3:50pm
											</td>
										</tr>
										<tr>
											<td>
												<button class="btn btn-danger">Deactivate Account</button>
											</td>
											<td>
												You will not be able to reverse the deactivation of your account.
											</td>
										</tr>
									</table>
								</form>
							</div>
							<div class="settings-security" style="display:none;">
								<form>
									<table class="settings-table" border="0" cellpadding="3" cellspacing="0">
										<tr>
											<td colspan="2" align="left"><span style="font-size:20px; font-weight:500;">Change Password</span></td>
										</tr>
										<tr>
											<td align="right">Password</td>
											<td><input type="password" class="form-control" /></td>
										</tr>
										<tr>
											<td align="right">Retype Password</td>
											<td><input type="password" class="form-control" /></td>
										</tr>
										<tr>
											<td></td>
											<td><button class="btn btn-success name-change" style="width:100%; margin-left:0px;">Change Password</button></td>
										</tr>
									</table>
								</form>
							</div>
							<div class="settings-comp" style="display:none;">
								<form>
									<table class="settings-table" border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td><input type="text" class="form-control" value="Glenn Dayton"/></td>
											<td><button class="btn btn-success name-change">Change Name</button></td>
										</tr>
										<tr>
											<td></td>
											<td></td>
										</tr>
									</table>
								</form>
							</div>
						</div>
					</td>
				</tr>
			</table>
		</div>-->
		<script type="text/javascript">
		$(document).ready(function() {
			$('.slideshow1').cycle({
				fx: 'fade'
			});
			$('.slideshow2').cycle({
				fx: 'fade'
			});
			$('.slideshow3').cycle({
				fx: 'fade'
			});
			$('.slideshow4').cycle({
				fx: 'fade'
			});
			$('.slideshow5').cycle({
				fx: 'fade'
			});
			$('.slideshow6').cycle({
				fx: 'fade'
			});
			$(".songs-load").click(function(){
				$(".songs-list-1").slideToggle();
			});
		});
		</script>
		<div id="zone-out">
			<span class="glyphicon glyphicon-chevron-right" style="color:white; font-size:40px; position:absolute; right:5px; top:50%;"></span>
			<table border="0" cellspacing="0" cellpadding="0" width="100%;" style="margin-top:63px; height:100%;">
				<tr>
					<td align="center" class="zone-out-item">
						<table border="0" cellpadding="0" cellspacing="0">
							<tr>
								<td align="center">
									<span class="album-head">The Beatles</span>
								</td>
							</tr>
							<tr>
								<td>
									<div class="album-border">
										<div class="album-cover slideshow1">
											<img src="http://i.telegraph.co.uk/multimedia/archive/02252/beatles_PA2_2252757b.jpg" />
											<img src="https://d26houopdteji.cloudfront.net/images/q/thumb/x598%3E/quality/85/interlace/true/src/http%3A%2F%2Fjux-user-files-prod.s3.amazonaws.com%2F2012%2F10%2F12%2F06%2F38%2F08%2F360%2FThe_Beatles__by_naicak.jpg" />
										</div>
									</div>
								</td>
							</tr>
							<tr>
								<td>
									<table border="0" cellpadding="0" cellspacing="0" width="100%;">
										<tr>
											<td>
												<span class="album-foot">Day Tripper</span>
											</td>
											<td rowspan="2" align="right">
												<span style="color:yellow; margin-left:5px; font-size:18px;" class="glyphicon glyphicon-chevron-down songs-load"></span>
											</td>
										</tr>
										<tr>
											<td>
												<span class="album-auth">The Beatles</span>
												<div class="songs-list songs-list-1" style="display:none;">
													<table class="songs-list-holder" border="0" cellpadding="0" cellspacing="0" width="100%;">
														<tr>
															<td>
																<table border="0" cellpadding="0" cellspacing="0" width="100%;">
																	<tr>
																		<td>Can't Get Enough of Your Love</td>
																	</tr>
																	<tr>
																		<td class="artist">Barry White</td>
																	</tr>
																</table>
															</td>
														</tr>
														<tr>
															<td>
																<table border="0" cellpadding="0" cellspacing="0">
																	<tr>
																		<td>Let the Music Play</td>
																	</tr>
																	<tr>
																		<td class="artist">Barry White</td>
																	</tr>
																</table>
															</td>
														</tr>
														<tr>
															<td>
																<table border="0" cellpadding="0" cellspacing="0">
																	<tr>
																		<td>Just the Way You Are</td>
																	</tr>
																	<tr>
																		<td class="artist">Barry White</td>
																	</tr>
																</table>
															</td>
														</tr>
														<tr>
															<td>
																<table border="0" cellpadding="0" cellspacing="0">
																	<tr>
																		<td>You</td>
																	</tr>
																	<tr>
																		<td class="artist">Barry White</td>
																	</tr>
																</table>
															</td>
														</tr>
														<tr>
															<td>
																<table border="0" cellpadding="0" cellspacing="0">
																	<tr>
																		<td>The Secret Garden</td>
																	</tr>
																	<tr>
																		<td class="artist">Barry White</td>
																	</tr>
																</table>
															</td>
														</tr>
														<tr>
															<td>
																<table border="0" cellpadding="0" cellspacing="0">
																	<tr>
																		<td>You're the One I Need</td>
																	</tr>
																	<tr>
																		<td class="artist">Barry White</td>
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
					<td align="center" class="zone-out-item">
						<table border="0" cellpadding="0" cellspacing="0">
							<tr>
								<td align="center">
									<span class="album-head">Spurs vs Chelsea</span>
								</td>
							</tr>
							<tr>
								<td>
									<div class="album-border">
										<div class="album-cover slideshow2">
											<img src="http://sevencolourgossips.files.wordpress.com/2012/10/tottenham-vs-chelsea.jpg" />
											<img src="http://cdn.bleacherreport.net/images_root/slides/photos/002/134/072/142943992_crop_650x440.jpg" />
										</div>
									</div>
								</td>
							</tr>
							<tr>
								<td>
									<table border="0" cellpadding="0" cellspacing="0" width="100%;">
										<tr>
											<td>
												<span class="album-foot">Can't Stop</span>
											</td>
											<td rowspan="2" align="right">
												<span style="color:yellow; margin-left:5px; font-size:18px;" class="glyphicon glyphicon-chevron-down songs-load"></span>
											</td>
										</tr>
										<tr>
											<td>
												<span class="album-auth">Red Hot Chili Peppers</span>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
					<td align="center" class="zone-out-item">
						<table border="0" cellpadding="0" cellspacing="0">
							<tr>
								<td align="center">
									<span class="album-head">MTC 2012- Coombe Hill</span>
								</td>
							</tr>
							<tr>
								<td>
									<div class="album-border">
										<div class="album-cover slideshow3">
											<img src="http://www.thejc.com/files/imagecache/body_landscape/%252Fimages/260810-jc_int_golf_usa_uk67.jpg" />
											<img src="http://www.thejc.com/files/imagecache/simchach_galleria/images/jc_int_golf_usa_uk68.jpg" />
										</div>
									</div>
								</td>
							</tr>
							<tr>
								<td>
									<table border="0" cellpadding="0" cellspacing="0" width="100%;">
										<tr>
											<td>
												<span class="album-foot">London Calling</span>
											</td>
											<td rowspan="2" align="right">
												<span style="color:yellow; margin-left:5px; font-size:18px;" class="glyphicon glyphicon-chevron-down songs-load"></span>
											</td>
										</tr>
										<tr>
											<td>
												<span class="album-auth">The Clash</span>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
				</tr>
				<tr>
					<td align="center" class="zone-out-item">
						<table border="0" cellpadding="0" cellspacing="0">
							<tr>
								<td align="center">
									<span class="album-head">Pink Floyd</span>
								</td>
							</tr>
							<tr>
								<td>
									<div class="album-border">
										<div class="album-cover slideshow4">
											<img src="http://topnews.in/light/files/Pink-Floyd44.jpg" />
											<img src="http://userserve-ak.last.fm/serve/500/88225/Pink+Floyd.jpg" />
										</div>
									</div>
								</td>
							</tr>
							<tr>
								<td>
									<table border="0" cellpadding="0" cellspacing="0" width="100%;">
										<tr>
											<td>
												<span class="album-foot">Another Brick In the Wall</span>
											</td>
											<td rowspan="2" align="right">
												<span style="color:yellow; margin-left:5px; font-size:18px;" class="glyphicon glyphicon-chevron-down songs-load"></span>
											</td>
										</tr>
										<tr>
											<td>
												<span class="album-auth">Pink Floyd</span>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
					<td align="center" class="zone-out-item">
						<table border="0" cellpadding="0" cellspacing="0">
							<tr>
								<td align="center">
									<span class="album-head">Tottenham Hotspur FC</span>
								</td>
							</tr>
							<tr>
								<td>
									<div class="album-border">
										<div class="album-cover slideshow5">
											<img src="http://cowperhill.com/wp-content/uploads/2013/05/Tottenham-Hotspur-F.C-Wallpaper-HD29.jpg" />
											<img src="http://i42.tinypic.com/28m3fgz.jpg" />
										</div>
									</div>
								</td>
							</tr>
							<tr>
								<td>
									<table border="0" cellpadding="0" cellspacing="0" width="100%;">
										<tr>
											<td>
												<span class="album-foot">The Masterplan</span>
											</td>
											<td rowspan="2" align="right">
												<span style="color:yellow; margin-left:5px; font-size:18px;" class="glyphicon glyphicon-chevron-down songs-load"></span>
											</td>
										</tr>
										<tr>
											<td>
												<span class="album-auth">Oasis</span>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
					<td align="center" class="zone-out-item">
						<table border="0" cellpadding="0" cellspacing="0">
							<tr>
								<td align="center">
									<span class="album-head">Kobe Bryant</span>
								</td>
							</tr>
							<tr>
								<td>
									<div class="album-border">
										<div class="album-cover slideshow6">
											<img src="http://www.empowernetwork.com/againstallodds/files/2013/03/Kobe-Bryant-Lakers-Wallpaper.jpg" />
											<img src="http://i42.tinypic.com/ivfrjd.jpg" />
										</div>
									</div>
								</td>
							</tr>
							<tr>
								<td>
									<table border="0" cellpadding="0" cellspacing="0" width="100%;">
										<tr>
											<td>
												<span class="album-foot">Lose yourself</span>
											</td>
											<td rowspan="2" align="right">
												<span style="color:yellow; margin-left:5px; font-size:18px;" class="glyphicon glyphicon-chevron-down songs-load"></span>
											</td>
										</tr>
										<tr>
											<td>
												<span class="album-auth">Eminem</span>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</div>

		<div id="header">
			<table border="0" cellpadding="0" cellspacing="0" width="100%;" height="63px;" style="max-height:63px;">
				<tr>
					<td width="262px;">
						<!-- LOGO PLACEHOLDER -->
						<div style="width:262px;"></div>
					</td>
					<td width="38%;" valign="center">
						<div class="search">
							<button type="button" class="btn btncustomred"><span class="glyphicon glyphicon-search"></span></button>
							<div class="input-holder">
								<input type="text" class="form-control" placeholder="Search..." />
							</div>
						</div>
					</td>
					<td valign="center" width="355px;" align="right">
						<div class="music-player">
							<div class="bg-player">
								<table border="0" cellpadding="0" cellspacing="0">
									<tr>
										<td>
											<button type="button" class="btn btncustomblue playlist-control"><span class="glyphicon glyphicon-list"></span> Classic Rock</button>
										</td>
										<td>
											<button type="button" class="btn btncustomred main-control"><span class="glyphicon glyphicon-play"></span></button>
										</td>
										<!--<td>
											<div class="action-panel">
												<button class="btn btn-mini btn-primary"><span class="glyphicon glyphicon-backward"></span></button>
											</div>
										</td>-->
										<td>
											<img src="http://images.gs-cdn.net/static/albums/80_134218.png" width="38px;" height="38px;" />
										</td>
										<td>
											<span class="song">Gimme Shelter</span><br />
											<span class="artist">The Rolling Stones</span>
										</td>
										<!--<td>
											<div class="action-panel">
												<button class="btn btn-mini btn-primary"><span class="glyphicon glyphicon-forward"></span></button>
											</div>
										</td>-->
									</tr>
								</table>
							</div>
						</div>
					</td>
					<td width="200px;" valign="center">
						<div class="login-info">
							<button type="button" class="btn btn-link profile-button" style="position:relative; bottom:5px;"><span class="glyphicon glyphicon-arrow-left" style="color:black; font-size:25px;"></span></button>
							<div class="placecard">
								<table border="0" cellpadding="0" cellspacing="0" width="100%;">
									<tr>
										<td rowspan="2"><!--<b>Glenn Dayton</b>--></td>
										<td><button type="button" class="btn btn-mini btncustomblue"><span class="glyphicon glyphicon-cog"></span> Settings</button></td>
									</tr>
									<tr>
										<td><button type="button" class="btn btn-mini btn-danger">Sign out</button></td>
									</tr>
								</table>
							</div>
						</div>
					</td>
				</tr>
			</table>
		</div>

		<div id="info">
			settings
		</div>

		<div id="columns">
			<table border="0" cellpadding="0" cellspacing="0" width="100%;" height="100%;">
				<tr>
					<td width="38%;" valign="top">
						<!--<img src="http://i40.tinypic.com/2qdzke9.png" width="100%;" />-->
						<div id="feed-create">
							<textarea class="form-control" rows="3" placeholder="Vent about music and/or sports..."></textarea>
							<!--<div class="vent-button">
								<span class="glyphicon glyphicon-picture icons"></span><span class="glyphicon glyphicon-share icons"></span>
								<button type="button" class="btn btncustomred" style="/*border-color:#cccccc; background-color:#ffffff;*/">
									<span style="color:white;">Vent</span>
								</button>
							</div>
							<table class="tabstop" border="0" cellpadding="0" cellspacing="0" width="100%;">
								<tr>
									<td width="20px;"><span class="glyphicon glyphicon-refresh"></span></td>
									<td class="tab" align="center"><img src="http://i.imm.io/1dkAY.png" width="20px" height="20px" /></td>
									<td class="tab" align="center"><img src="http://i.imm.io/1dkAN.png" width="20px" height="20px" /></td>
									<td class="tab" align="center"><img src="http://i.imm.io/1dkzn.png" width="20px" height="20px" /></td>
								</tr>
							</table>-->
							<table border="0" cellpadding="0" cellspacing="0" width="100%;">
								<tr>
									<td>
										<table class="tabstop" border="0" cellpadding="0" cellspacing="0" width="100%;" style="margin-top:8px;">
											<tr>
												<td width="20px;"><span class="glyphicon glyphicon-refresh"></span></td>
												<td class="tab" align="center"><img src="http://i.imm.io/1dkAY.png" width="20px" height="20px" /></td>
												<td class="tab" align="center"><img src="http://i.imm.io/1dkAN.png" width="20px" height="20px" /></td>
												<td class="tab" align="center"><img src="http://i.imm.io/1dkzn.png" width="20px" height="20px" /></td>
											</tr>
										</table>
									</td>
									<td width="120px;">
										<div class="vent-button">
											<span class="glyphicon glyphicon-picture icons"></span><span class="glyphicon glyphicon-share icons"></span>
											<button type="button" class="btn btncustomred" style="/*border-color:#cccccc; background-color:#ffffff;*/">
												<span style="color:white;">Vent</span>
											</button>
										</div>
									</td>
								</tr>
							</table>
						</div>
						<div id="feed-area">

						</div>
					</td>
					<td width="48%;" valign="top">
						<table border="0" cellpadding="0" cellspacing="0" width="100%;">
							<tr>
								<td>
									<!--<div style="height:100px; width:100%; background-color:gray;"></div>-->
									<!--<script>
										$(document).ready(function() {
											$('.slideshow').cycle({
												fx: 'fade'
											});
										});
									</script>-->
									<div class="slideshow">
										<img src="http://oi43.tinypic.com/2yuhkeq.jpg" />
										<!--<img src="http://l1.yimg.com/bt/api/res/1.2/69koZrff8XAsVqLRUcTRZA--/YXBwaWQ9eW5ld3M7cT04NTt3PTYzMA--/http://media.zenfs.com/en-GB/blogs/rankings-uk/GunnersTeam.jpg" />
										<img src="http://2.bp.blogspot.com/-tIpQJGClDsk/UD-AmFbI1nI/AAAAAAAAFzo/k3uCWWX9_uQ/s1600/Capture.PNG" />
										<img src="http://www.australia.com/contentimages/about-australias-landscapes-coastal-australian-beaches.jpg"/>
										<img src="http://www.jayblessed.com/new/wp-content/uploads/2012/07/Cayman-Islands.jpg"/>-->
									</div>
								</td>
							</tr>
							<tr>
								<td style="z-index:1000;">
									<table class="tabs" border="0" cellpadding="0" cellspacing="0" width="100%;">
										<tr>
											<td align="center" class="tabb">
												<div class="tab">
													My Links
												</div>
											</td>
											<td align="center" class="tabb tabb-active">
												<div class="tab">
													Me
												</div>
											</td>
											<td align="center" class="tabb">
												<div class="tab">
													Media
												</div>
											</td>
											<td align="center" class="tabb">
												<div class="tab">
													My Tunes
												</div>
											</td>
											<td align="center" class="tabb">
												<div class="tab">
													Live
												</div>
											</td>
											<td align="center" class="tabb">
												<div class="tab">
													Zone Out
												</div>
											</td>
										</tr>
									</table>
								</td>
							</tr>
						</table>
						<div id="tab-content">
							<!--
								MY TUNES
							-->
							<!--
							<div class="music-content">
								<div class="actions-header">
									<div class="power-header">
										<b>Powered by </b><img src="http://www.grooveshark.com/webincludes/logo/Grooveshark_Logo_Horizontal.png" width="90px;" />
									</div>
									<script>
									function tabToggle(script){
										if(script == "search"){ $(".tab-search-content").show(); }else{ $(".tab-search-content").hide(); }
										if(script == "import"){ $(".tab-import-content").show(); }else{ $(".tab-import-content").hide(); }
										if(script == "manage"){ $(".tab-manage-content").show(); }else{ $(".tab-manage-content").hide(); }
									}
									</script>
									<table class="tabs2" border="0" cellpadding="0" cellspacing="0" width="50%;">
										<tr>
											<td onclick="tabToggle('search');"><span class="glyphicon glyphicon-search"></span> Search</td>
											<td onclick="tabToggle('manage');"><span class="glyphicon glyphicon-briefcase"></span> Manage Playlists</td>
											<td onclick="tabToggle('import');"><span class="glyphicon glyphicon-collapse"></span> Import</td>
										</tr>
									</table>
									<div class="actions-header-main">
										<div class="tab-search-content">
											<table border="0" cellpadding="0" cellspacing="0" width="100%;">
												<tr>
													<td><input type="text" class="form-control" placeholder="Artists, Albums, Songs..." /></td>
													<td><button type="button" class="btn btncustomred"><span class="glyphicon glyphicon-search"></span></button></td>
												</tr>
											</table>
										</div>
										<div class="tab-manage-content" style="display:none;">
											<form>
												<table border="0" cellpadding="0" cellspacing="0" width="100%;">
													<tr>
														<td><input type="text" class="form-control" placeholder="Playlist..." /></td>
														<td width="130px;"><button type="button" class="btn btn-success">Create Playlist</button></td>
													</tr>
												</table>
											</form>
											<table border="0" cellpadding="0" cellspacing="0" width="100%;">
												<tr>
													<td>Rock</td>
													<td align="right">
														<button type="button" class="btn btn-mini btn-primary remove-playlist"><span class="glyphicon glyphicon-edit"></span></button>
														<button type="button" class="btn btn-mini btn-danger remove-playlist"><span class="glyphicon glyphicon-trash"></span></button>
													</td>
												</tr>
											</table>
										</div>
										<div class="tab-import-content" style="display:none;">
											<form>
												<table border="0" cellpadding="0" cellspacing="0">
													<tr>
														<td>
															Import tunes into
															<label class="radio-inline"><input name="loc" type="radio">all tunes</label>
															<label class="radio-inline"><input name="loc" type="radio">playlist</label>
														</td>
													</tr>
													<tr>
														<td>
															Select iTunes XML file to import <input type="file" />
														</td>
													</tr>
												</table>
											</form>
										</div>

										<tab class="tab-playlist-content" style="display:none;">
											<form>
												<table border="0" cellpadding="0" cellspacing="0">
													<tr>
														<td><input type="text" class="form-control" placeholder="Playlist..." /></td>
														<td><button type="button" class="btn btn-success">Create Playlist</button></td>
													</tr>
												</table>
											</form>
										</div>
									</div>
								</div>
								<div class="music-list-holder">
									<div class="music-list">
										<table class="music-table" border="0" cellspacing="0" cellpadding="0">
											<tr>
												<th></th>
												<th align="left">Title & Artist</th>
												<th align="left">Duration</th>
												<th align="left">Genre</th>
												<th></th>
												<th></th>
											</tr>
											<tr>
												<td></td>
												<td>Gimme Shelter - <span class="artist">The Rolling Stones</span></td>
												<td>3:45</td>
												<td>Rock</td>
												<td class="stripes-container">-->
													<!--<table class="stripes" border="0" cellpadding="0" cellspacing="0">
														<tr>
															<td><div style="height:20px; width:2px; background-color:#e69500;"></div></td>
														</tr>
													</table>-->
												<!--</td>
												<td class="actions"><img src="https://cdn2.iconfinder.com/data/icons/ios-7-icons/50/down4-16.png" width="12px;" height="12px;"/></td>
											</tr>
											<tr>
												<td></td>
												<td>Jazz Tempo - <span class="artist">Jack Bu</span></td>
												<td>1:45</td>
												<td>Jazz</td>
												<td class="stripes-container"></td>
												<td class="actions"><img src="https://cdn2.iconfinder.com/data/icons/ios-7-icons/50/down4-16.png" width="12px;" height="12px;"/></td>
											</tr>
											<tr>
												<td></td>
												<td>The Finer Things - <span class="artist">Steve Winwood</span></td>
												<td>4:45</td>
												<td>Rock</td>
												<td class="stripes-container"></td>
												<td class="actions"><img src="https://cdn2.iconfinder.com/data/icons/ios-7-icons/50/down4-16.png" width="12px;" height="12px;"/></td>
											</tr>
											<tr>
												<td><i class="icon-star"></i></td>
												<td>Can't Find My Way Home - <span class="artist">Steve Winwood</span></td>
												<td>4:34</td>
												<td>Rock</td>
												<td class="stripes-container">-->
													<!--<table class="stripes" border="0" cellpadding="0" cellspacing="0">
														<tr>
															<td><div style="height:20px; width:2px; background-color:#e69500;"></div></td>
															<td><div style="height:20px; width:2px; background-color:green;"></div></td>
															<td><div style="height:20px; width:2px; background-color:red;"></div></td>
															<td><div style="height:20px; width:2px; background-color:purple;"></div></td>
															<td><div style="height:20px; width:2px; background-color:gray;"></div></td>
														</tr>
													</table>-->
												<!--</td>
												<td class="actions"><img src="https://cdn2.iconfinder.com/data/icons/ios-7-icons/50/down4-16.png" width="12px;" height="12px;"/></td>
											</tr>
										</table>
									</div>
								</div>
							</div>
							-->

							<!--
								MEDIA TAB
							-->
							<!--<div class="media-content">
								<img src="http://54.243.129.126/usr_content/pics/50ff4334ca885_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff4359c6ec3_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff45a163bc2_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff45e3e6ed8_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff461cd9e91_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff46368d839_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff464d82a39_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff467f23097_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff469a53f8d_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff46c771906_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff47d09a6e3_t.jpg" />
								<img src="http://54.243.129.126/usr_content/pics/50ff481210576_t.jpg" />

								<hr />

								<div class="alb-holder">
									<span>Summer 2013</span><br />
									<img src="http://54.243.129.126/usr_content/pics/50ff481210576_t.jpg" />
								</div>
								<div class="alb-holder">
									<span>Ferrari Headphones</span><br />
									<img src="http://www.drdreheadphoneonsale.com/22-105-home/beats-by-dr-dre-ferrari-limited-edition.jpg" width="159px;" height="159px;" />
								</div>
								<div class="alb-holder-expanded">
									<span>Fat Sals</span><br />
									<table border="0" cellpadding="0" cellspacing="0">
										<tr>
											<td width="50%;">
												<script>
													setTimeout(function(){
														$(".scroll-photos").css("height",$(".preview-photo").height());

														$(".scroll-photos img").hover(function(){
															$(".preview-photo").attr("src",$(this).attr("src"));
														});
													},200);
												</script>
												<div class="scroll-photos" style="overflow:scroll;">
													<img src="http://54.243.129.126/usr_content/pics/5121def746ed2_t.jpg" />
													<img src="http://54.243.129.126/usr_content/pics/511f3a7063843_t.jpg" />
													<img src="http://54.243.129.126/usr_content/pics/511f3a48c9233_t.jpg" />
													<img src="http://54.243.129.126/usr_content/pics/5100a907005a1_t.jpg" />
													<img src="http://54.243.129.126/usr_content/pics/50ff59cdcd7b7_t.jpg" />
													<img src="http://redbullrant.files.wordpress.com/2012/12/cropped-logo-31.png" />
													<img src="http://www.ramanmedianetwork.com/wp-content/uploads/2013/04/redbull-155x155.jpg" />
												</div>
											</td>
											<td width="50%;">
												<img class="preview-photo" src="http://54.243.129.126/usr_content/pics/511f3a48c9233_t.jpg" style="width:100%;"/>
											</td>
										</tr>
									</table>
								</div>
								<div class="alb-holder">
									<span>Nickelodeon</span><br />
									<img src="http://gheriarnold.com/worksm/nickeld.jpg" width="159px;" height="159px;" />
								</div>
							</div>-->

							<!--
								ME TAB
							-->

						</div>
					</td>
					<td width="200px;" valign="top" style="background-color:#179bff;">
						<div class="profile-info">
							<div class="profile-info-holder">
							</div>
							<div class="lineup">
								<form class="add-lineup">
									<!--<span class="glyphicon glyphicon-refresh shuffle"></span>-->
									<input type="text" class="form-control lineup-add-text" placeholder="Music and Sports favorites..." />
								</form>
								<!--<ol></ol>-->
							<div>
						</div>
						<script>
						$(document).ready(function(){
							/*$(".img-control").mouseenter(function(){
								//$(this).css({
								//	"background-color":"rgba(0,0,0.4)"
								//});
								//$(this).append($(this).attr("data-info"));
								$(this).find(".desc-bar").show();

							}).mouseleave(function(){
								$(this).find(".desc-bar").hide();
							});*/

							$(".img-control .desc-bar span.lineup-settings").click(function(){
								var selectEle = $(this).parent().parent();
								$(selectEle).flippy({
									color_target: "#179bff",
									duration: "250",
									direction: "bottom",
									verso: "<div class='settings-area'>\
										<b style='color:white;'>Settings</b><span class='glyphicon glyphicon-remove' onclick='$(this).parent().parent().flippyReverse();' style='float:right; color:white; cursor:pointer;'></span>\
									</div>"
								});
							});

							$(".img-control").mouseenter(function(){
								$(this).flippy({
									color_target: "#179bff",
									duration: "250",
									direction: "bottom",
									verso: "<div class='img-control'>\
										<b style='color:white;'>Settings</b><span class='glyphicon glyphicon-remove' onclick='$(this).parent().parent().flippyReverse();' style='float:right; color:white; cursor:pointer;'></span>\
									</div>"
								});
							}).mouseleave(function(){
								$(this).flippyReverse();
							});
						});
						</script>
						<div class="flipbox-container">
						<div class="lineup-img">
							<div class="img-control">
								<div class="img-wrapper" data-info="Words 1">
									<img src="http://api.ning.com/files/*vTqq5fDgY5pKQr7rNgIRXLhYBTXG8K68pUvHACsHVGN5VGZmVUao6v9L1C2SYufoYHICn8ztn9PiP1lvOJcWeRvi06WmNTT/LedZeppelin1973_Gruen.jpg" />
								</div>
								<div class="desc-bar">
									<span>Led Zeppelin</span>
									<span class="glyphicon glyphicon-cog lineup-settings"></span>
								</div>
							</div>
							<div class="img-control">
								<div class="img-wrapper" data-info="Words 1">
									<img src="http://www.armyproperty.com/Equipment-Info/Pictures/MOLLE-Rucksack-3.jpg" />
								</div>
								<div class="desc-bar">
									<span>300 pound rucksack</span>
									<span class="glyphicon glyphicon-cog lineup-settings"></span>
								</div>
							</div>
							<div class="img-control">
								<div class="img-wrapper" data-info="Words 1">
									<img src="http://i2.mirror.co.uk/incoming/article97241.ece/ALTERNATES/s615/lee-westwood-pic-action-324643072-97241.jpg" />
								</div>
								<div class="desc-bar">
									<span>Lee Westwood</span>
									<span class="glyphicon glyphicon-cog lineup-settings"></span>
								</div>
							</div>
							<div class="img-control">
								<div class="img-wrapper" data-info="Words 1">
									<img src="http://static.tvtropes.org/pmwiki/pub/images/genesis_gallery_2.jpg" />
								</div>
								<div class="desc-bar">
									<span>Genesis</span>
									<span class="glyphicon glyphicon-cog lineup-settings"></span>
								</div>
							</div>
							<div class="img-control">
								<div class="img-wrapper" data-info="Words 1">
									<img src="http://s1.ibtimes.com/sites/www.ibtimes.com/files/styles/v2_article_large/public/2012/05/13/273318-roger-federer.jpg" />
								</div>
								<div class="desc-bar">
									<span>Roger Federer</span>
									<span class="glyphicon glyphicon-cog lineup-settings"></span>
								</div>
							</div>
							<div class="img-control">
								<div class="img-wrapper" data-info="Words 1">
									<img src="http://www.hacknsmack.org/img/logo-caballero.jpg" />
								</div>
								<div class="desc-bar">
									<span>El Caballero</span>
									<span class="glyphicon glyphicon-cog lineup-settings"></span>
								</div>
							</div>
							<div class="img-control">
								<div class="img-wrapper" data-info="Words 1">
									<img src="http://www.bbl.org.uk/typo3temp/pics/94d57ff654.png" />
								</div>
								<div class="desc-bar">
									<span>Sky Sports</span>
									<span class="glyphicon glyphicon-cog lineup-settings"></span>
								</div>
							</div>
							<div class="img-control">
								<div class="img-wrapper" data-info="Words 1">
									<img src="http://www.iafrica.tv/wp-content/uploads/2013/07/Barclays-Premier-League-2013-iafrica.tv_.png" />
								</div>
								<div class="desc-bar">
									<span>Barclays</span>
									<span class="glyphicon glyphicon-cog lineup-settings"></span>
								</div>
							</div>

							<!--<div class="img-wrapper" data-info="Words 2"><div class="img-wrapper-inside"><img src="http://classicrockreview.files.wordpress.com/2013/04/led-zeppelin-b89e2e3a4b67c923.jpg" /></div></div>
							<div class="img-wrapper" data-info="Words 3"><div class="img-wrapper-inside"><img src="http://www.regentsprep.org/Regents/math/geometry/GG2/soccerball.jpg" /></div></div>
							<div class="img-wrapper" data-info="Words 4"><div class="img-wrapper-inside"><img src="http://www.peterguy.merseyblogs.co.uk/Beatles,%20Liverpool,%20Getintothis%20GIT%20Award.jpg" /></div></div>
							<div class="img-wrapper" data-info="Words 5"><div class="img-wrapper-inside"><img src="http://us.123rf.com/400wm/400/400/2nix/2nix1205/2nix120500152/14512934-soccer-ball-on-the-stadium.jpg" /></div></div>
							<div class="img-wrapper" data-info="Words 6"><div class="img-wrapper-inside"><img src="http://tekstovi-pesama.com/g_img2/0/i/18862/inxs-2.jpg" /></div></div>
							<div class="img-wrapper" data-info="Words 7"><div class="img-wrapper-inside"><img src="http://liverockprods.com/wp-content/uploads/2013/04/the-beatles-0.jpg" /></div></div>
							<div class="img-wrapper" data-info="Words 8"><div class="img-wrapper-inside"><img src="http://www.armyproperty.com/Equipment-Info/Pictures/MOLLE-Rucksack-3.jpg" /></div></div>
							<div class="img-wrapper" data-info="Words 9"><div class="img-wrapper-inside"><img src="http://www.soccerforum.com/photopost/data/500/tottenham-hotspur-lo_48038.jpg" /></div></div>
							<div class="img-wrapper" data-info="Words 10"><div class="img-wrapper-inside"><img src="http://i2.mirror.co.uk/incoming/article97241.ece/ALTERNATES/s615/lee-westwood-pic-action-324643072-97241.jpg" /></div></div>
							<div class="img-wrapper" data-info="Words 11"><div class="img-wrapper-inside"><img src="http://static.tvtropes.org/pmwiki/pub/images/genesis_gallery_2.jpg" /></div></div>
							<div class="img-wrapper" data-info="Words 12"><div class="img-wrapper-inside"><img src="http://www.troika.tv/wp-content/uploads/lakers_hero1.jpg"/></div></div>-->
						</div>
						</div>
					</td>
				</tr>
			</table>
		</div>

		<!--<div id="feed">
			<div class="info">
				<span class="glyphicon glyphicon-remove remove-feed-item"></span>
				<span class="glyphicon glyphicon-flag flag-feed-item"></span>
				<img class="img-rounded" src="http://flickholdr.com/400/150/forest" />
				<a href="#">Glenn Dayton</a>
			</div>
			<div class="content">
				REGULAR POSTING
				<p>This is a lot of verbiage to fill up this small little space that needs something on it to make it look good.</p>
				LINK POSTING
				<p><span class="glyphicon glyphicon-link"></span><a href="#">ESPN Sport Center</a></p>
				PHOTO POSTING
				<img src="http://54.243.129.126/usr_content/pics/51eb37bc9ee25_w.jpg" />
			</div>
			<div class="actions">
				<table border='0' cellpadding='0' cellspacing='0' width='100%;'>
					<tr>
						<td valign="top">
							<textarea class="form-control" rows="3" placeholder="Make a comment..."></textarea>
							<div class="expand-comments">
								<span class="glyphicon glyphicon-eye-open"></span> 34 Comments
							</div>
						</td>
						<td valign="top" width="100px;">
							<div class="comment-controls">
								<span class="date">3 days ago</span><br />
								<table border="0" cellpadding="0" cellspacing="0">
									<tr>
										<td width="100%;"><button type="button" class="btn btn-mini custom-yellow" style="width:95%;"><img src="http://i.imm.io/14rOO.png" /><span class="clap-amount">42</span></button></td>
										<td width="30px;"><button type="button" class="btn btn-mini custom-yellow"><span class="glyphicon glyphicon-comment" style="color:blue;"></span></td>
									</tr>
								</table>
								<button type="button" class="btn btn-mini btn-primary">Comment</button>
							</div>
						</td>
					</tr>
				</table>
			</div>
		</div>-->
	</body>
</html>