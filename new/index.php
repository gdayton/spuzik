<?php session_start(); ?><html>
	<head>
		<title>Spuzik</title>
		<link rel="shortcut icon" href="/data/img/spuzik_icon.ico" type="image/x-icon" />
		<link rel="stylesheet" type="text/css" href="data/css/bootstrap.min.css" />
		<link rel="stylesheet" type="text/css" href="data/css/css/bootstrap-glyphicons.css" />
		<link rel="stylesheet" type="text/css" href="main2.css" />
		<link href='http://fonts.googleapis.com/css?family=Roboto+Condensed|Fugaz+One' rel='stylesheet' type='text/css'>

		<script type="text/javascript" src="//ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
		<script type="text/javascript" src="//ajax.googleapis.com/ajax/libs/jqueryui/1.9.2/jquery-ui.min.js"></script>
		<script type="text/javascript" src="data/js/underscore-min.js"></script>
		<script type="text/javascript" src="data/js/backbone-min.js"></script>
		<script type="text/javascript" src="data/js/bootstrap.min.js"></script>
		<script type="text/javascript" src="data/js/jquery.cycle.all.js"></script>
		<script type="text/javascript" src="data/js/jquery.flippy.min.js"></script>
		<script type="text/javascript" src="data/js/jquery.ui.widget.js"></script>
		<script type="text/javascript" src="data/js/jquery.iframe-transport.js"></script>
		<script type="text/javascript" src="data/js/jquery.fileupload.js"></script>

		<script type="text/javascript" src="models/spuzik_user.js"></script>
		<script type="text/javascript" src="models/spuzik_lineup.js"></script>
		<script type="text/javascript" src="models/spuzik_tab.js"></script>
		<script type="text/javascript" src="models/spuzik_fq.js"></script>
		<script type="text/javascript" src="models/spuzik_mz.js"></script>
		<script type="text/javascript" src="models/spuzik_link.js"></script>
		<script type="text/javascript" src="models/spuzik_image.js"></script>
		<script type="text/javascript" src="models/spuzik_jukebox.js"></script>
		<script type="text/javascript" src="views/spuzik_index.js"></script>
		<script type="text/javascript" src="views/spuzik_profile.js"></script>
		<script type="text/javascript" src="views/spuzik_header.js"></script>
		<script type="text/javascript" src="views/spuzik_lineup.js"></script>
		<script type="text/javascript" src="views/spuzik_top.js"></script>
		<script type="text/javascript" src="views/spuzik_tab.js"></script>
		<script type="text/javascript" src="views/spuzik_jukebox.js"></script>
		<script type="text/javascript" src="spuzik_router.js"></script>

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

		<script id="indexTemplate" type="text/template">
			<div id="index">
				<table class="main" border="0" cellpadding="0" cellspacing="0" style="border-color:white;">
					<tr>
						<td colspan="2" height="20%;"></td>
					</tr>
					<tr>
						<td colspan="2" height="33%;">
							<table class="signup" border="0" cellpadding="0" cellspacing="0" style="border-color:white;">
								<tr>
									<td width="40%;" align="right">
										<img src="http://i.imm.io/19S6Z.png" />
									</td>
									<td width="60%;" valign="center">
										<div class="signup-middle">
											<table class="actions-bar" border="0" cellpadding="0" cellspacing="0">
												<tr>
													<!--<td align="right"><button type="button" class="btn btn-primary">Create Account</button></td>
													<td align="left"><button type="button" class="btn btn-danger" style="margin-left:10px;">Sign In</button></td>-->
													<td align="right"><div class="create-account">Create Account</div></td>
													<td align="left"><div class="sign-in">Sign in</div></td>
												</tr>
											</table>
											<div class="headline">Sports & Music<br />Social Network</div>
										</div>
										<div class="signup-middle-enter">
											<table border="0" cellpadding="0" cellspacing="0">
												<tr>
													<td><div class="fbook">Connect with Facebook</div></td>
													<td rowspan="2" valign="center"><span style="color:white;">OR</span></td>
													<td><input type="text" class="form-control" placeholder="First name..." /></td>
													<td><input type="text" class="form-control" placeholder="Last name..." /></td>
													<td></td>
												</tr>
												<tr>
													<td><div class="twitter">Connect with Twitter</div></td>
													<td colspan="2"><input type="text" class="form-control" placeholder="Email..." /></td>
													<td><button class="btn btn-warning">Sign Up</button></td>
												</tr>
											</table>
										</div>
										<div class="sign-in-enter"></div>
									</td>
								</tr>
							</table>
						</td>
					</tr>
					<tr>
						<td height="48%;"></td>
						<td width="60%;" valign="top">
							<div class="info-box">
								<span class="header">Sports & Music Social Network</span>
								<img src="http://i43.tinypic.com/29pytzt.png" />
								<ul>
									<li>Manage a music library that you can listen to anywhere.</li>
									<li>Keep up with your favorite sports amongst your friends.</li>
									<li>Customize your profile to represent the person you are.</li>
								</ul>
								<p>Carry Spuzik with you, we're going mobile soon.</p>
								<!--<table class="phone" border="0" cellpadding="0" cellspacing="0">
									<tr>
										<td colspan="3"><span class="header-footer">Download Spuzik onto your phone!</span></td>
									</tr>
									<tr>
										<td><img src="http://mydayplus.com/img/appStoreLogoTransparentBKG.gif" /></td>
										<td><img src="http://developer.android.com/images/brand/Android_Robot_100.png" /></td>
										<td><img src="https://developer.blackberry.com/webroot/img/blackberryworld/logo_blackberryworld.png" /></td>
									</tr>
									<tr>
										<td>iPhone</td>
										<td>Android</td>
										<td>Blackberry</td>
									</tr>
								</table>-->
							</div>
						</td>
					</tr>
				</table>
			</div>
		</script>

		<script id="jukeboxItem" type="text/template">
			<td><%= Title %> - <span class="artist"><%= Artist %></span></td>
			<td><span class="duration"><%= Length %></span></td>
			<td><%= Genre %></td>
			<td>
				<table border="0" cellpadding="0" cellspacing="0">
					<tr>
						<td><span class="glyphicon glyphicon-chevron-left song-actions"></span></td>
						<td>
							<div class="song-actions-view">
								<table border="0">
									<tr>
										<td><span class="glyphicon glyphicon-user"></span></td>
										<td><span class="glyphicon glyphicon-trash"></span></td>
									</tr>
								</table>
							</div>
						</td>
					</tr>
				</table>
			</td>
		</script>

		<script id="loginTemplate" type="text/template">
			<table border="0" cellpadding="0" cellspacing="0">
				<tr>
					<td><div class="fbook">Connect with Facebook</div></td>
					<td rowspan="2" valign="center"><span style="color:white;">OR</span></td>
					<td><input type="text" class="form-control email-signin" placeholder="Email..." style="width:200px;"/></td>
					<td></td>
					<td rowspan="2" valign="top">
						<!--<div class="error">
						<span class="glyphicon glyphicon-warning-sign" style="margin-right:3px; position:relative; top:2px;"></span>Your email and password are incorrect.
						</div>-->
					</td>
				</tr>
				<tr>
					<td><div class="twitter">Connect with Twitter</div></td>
					<td><input type="password" class="form-control password-signin" placeholder="Password..." style="width:200px;"/></td>
					<td><button class="btn btn-warning login-button">Sign In</button></td>
				</tr>
			</table>
		</script>

		<script id="userInfoTemplate" type="text/template">
			<img src="<%= ProfilePicture %>" />
			<!-- http://i42.tinypic.com/2v7tlif.png -->
			<div class="info">
				<p class="name"><%= FirstName %> <%= LastName %></p>
				<span class="live"><%= Location %></span>
			</div>
		</script>

		<script id="lineupItemTemplate" type="text/template">
			<div id="draggable<%= Position %>" class="lineup-item" data-img="<%= PhotoURL %>">
				<div class="lineup-item-align" >
					<div class="lineup-floater">
						<span class="glyphicon glyphicon-remove delete-lineup"></span>
					</div>
					<span class="order-number"><%= Position %></span><span class="lineup-text"><%= Text %></span>
				</div>
			</div>
		</script>

		<script id="lineupErrorTemplate" type="text/template">
			<div class="lineupError">
				Add Lineup items!
			</div>
		</script>

		<script id="lineupLoadingTemplate" type="text/template">
			<div class="lineupLoading">
				<img src="https://s3-us-west-1.amazonaws.com/spuzik/images/ajax-loader+(3).gif" /> Loading
			</div>
		</script>

		<script id="lineupAddItemTemplate" type="text/template">
			<div class="lineupAdd">
				<input type="text" class="form-control" placeholder="Add your favorites..."/>
			</div>
		</script>

		<script id="profileTemplate" type="text/template">
			<div id="main">
				<div class="row">
					<div class="col-lg-3 whiter">
						<div id="profile"></div>
						<div class="lineup">
							<div class="lineup-container"></div>
						</div>
					</div>
					<div class="col-lg-9 whiter">
						<div id="sli-tab"></div>
						<div class="feed-head-top">
							<ul>
								<li><span class="glyphicon glyphicon-bullhorn"></span> Sports</li>
								<li><span class="glyphicon glyphicon-music"></span> Music</li>
								<li><span class="glyphicon glyphicon-random"></span> Recommendations</li>
							</ul>
							<div class="feed-ind">
								<div class="arrow-up" style="margin-left:6px;"></div>
							</div>
						</div>
						<div id="feed-area">
							<div id="feed">
								<div class="info">
									<span class="glyphicon glyphicon-remove remove-feed-item"></span>
									<span class="glyphicon glyphicon-flag flag-feed-item"></span>
									<img class="img-rounded" src="http://54.243.129.126/usr_content/pics/514bd1c5ba8c6_t.jpg" />
									<a href="#">Jake Cohen</a>
								</div>
								<div class="content">
									I'm sure this will be the permanent change for the website!
									<img src="http://s23.postimg.org/4v78zztfv/Green_Forest_Wallpaper_green_20036604_1280_1024.jpg" />
								</div>
								<div class="actions">
									<table border='0' cellpadding='0' cellspacing='0' width='100%;'>
										<tr>
											<td valign="top">
												<textarea class="form-control comment-enter" rows="3" placeholder="Make a comment..." style="display:none;"></textarea>
												<div class="expand-comments">
													<span class="glyphicon glyphicon-eye-open"></span> 3 Comments
												</div>
												<div class="comments"></div>
											</td>
											<td valign="top" width="100px;">
												<div class="comment-controls">
													<span class="date">3 days ago</span><br />
													<table border="0" cellpadding="0" cellspacing="0">
														<tr>
															<td width="100%;"><button type="button" class="btn btn-mini custom-yellow" style="width:95%;"><img src="http://i.imm.io/14rOO.png" /><span class="clap-amount">5</span></button></td>
															<td width="30px;"><button type="button" class="btn btn-mini custom-yellow"><span class="glyphicon glyphicon-comment comment-toggle" style="color:blue;"></span></td>
														</tr>
													</table>
													<!--<button type="button" class="btn btn-mini btn-primary post-comment">Comment</button>-->
												</div>
											</td>
										</tr>
									</table>
								</div>
							</div>
						</div>
					</div>
				</div>
			</div>
		</script>

		<script id="headerTemplate" type="text/template">
			<div id="header">
				<div class="inner-header">
					<table border="0" cellpadding="0" cellspacing="0" width="100%;" style="height:63px;">
						<tr>
							<td width="256px;">
								<img src="http://i.imm.io/1flQs.png" style="height:63px; margin-bottom:9px;"/>
							</td>
							<td>
								<table class="header-functions" border="0" cellpadding="0" cellspacing="0" width="100%;">
									<tr>
										<td align="right" class="left">
											<span class="glyphicon glyphicon-search" style="float:right;"></span>
											<div class="show-expanded">
												<input type="text" class="form-control search-bar" placeholder="Search for users..." />
											</div>
										</td>
										<td width="1px;" valign="center">
											<div class="seperate"></div>
										</td>
										<td align="left" class="right" valign="center">
											<div class="show-expanded">
												<div class="music-player">
													<table border="0" cellpadding="0" cellspacing="0">
														<tr>
															<td>
																<span class="glyphicon glyphicon-play play-button"></span>
															</td>
															<td>
																<span class="song-name">Smooth Operator</span><br />
																<span class="artist-name">Sade</span>
															</td>
															<td>
																<!--<img src="http://images.coolchaser.com/themes/t/1039374-i36.photobucket.com-albums-e5-hannahbanana105-equalizer.gif" />-->
															</td>
														</tr>
													</table>
												</div>
											</div>
											<span class="glyphicon glyphicon-music" style="float:left; clear:left;"></span>
										</td>
									</tr>
								</table>
							</td>
							<td width="50px;">
								<div class="user-login">
									<table class="userfloater activate-user-menu" border="0" cellpadding="0" cellspacing="0" width="30px;">
										<tr>
											<td align="center"><span class="glyphicon glyphicon-user usericon"></span></td>
										</tr>
									</table>
									<div class="user-menu-big">
										<div class="user-menu activate-user-menu">
											<div class="arrow-up-top"></div>
											<ul>
												<li><span class="glyphicon glyphicon-cog"></span> Settings</li>
												<li><span class="glyphicon glyphicon-"></span> Sign Out</li>
											</ul>
										</div>
									</div>
								</div>
							</td>
						</tr>
					</table>
				</div>
			</div>
		</script>

		<script id="topTemplate" type="text/template">
			<table border="0" cellpadding="0" cellspacing="0" width="100%;">
				<tr>
					<td>
						<div class="img-cons"></div>
					</td>
					<td valign="top" width="30%;">
						<div class="navigation">
							<ul>
								<a href="#/p/<%= UserId %>/me"><li class="me"><span class="glyphicon glyphicon-user"></span> Me</li></a>
								<a href="#/p/<%= UserId %>/media"><li class="media"><span class="glyphicon glyphicon-picture"></span> Media</li></a>
								<a href="#/p/<%= UserId %>/myTunes"><li class="myTunes"><span class="glyphicon glyphicon-music"></span> Jukebox</li></a>
								<a href="#/p/<%= UserId %>/links"><li class="links"><span class="glyphicon glyphicon-list"></span> Links</li></a>
								<a href="#/p/<%= UserId %>/live"><li class="live"><span class="glyphicon glyphicon-comment"></span> Live <span class="glyphicon glyphicon-exclamation-sign app-alert"></span></li></a>
								<a href="#/p/<%= UserId %>/zoneOut"><li class="zoneOut"><span class="glyphicon glyphicon-fullscreen"></span> Zone Out</li></a>
							</ul>
						</div>
					</td>
				</tr>
			</table>
		</script>

		<script id="tabSlideshowTemplate" type="text/template">
			<img class="slideshow-img" src="http://s10.postimg.org/w981usqyd/tumblr_m01gumpvf21qlcoefo1_500.jpg?noCache=1377558264" />
		</script>

		<script id="tabAboutMeInfoTemplate" type="text/template">
			<table border="0" cellpadding="5" cellspacing="0" width="100%;">
				<tr>
					<td colspan="2" align="center" style="padding:30px 5px 10px 5px;">
						<%= Bio %>
					</td>
				</tr>
				<!-- remove this element if the currently logged in user is not the profile that is being viewed. -->
				<tr>
					<td colspan="2" align="center">
						<div class="edit-aboutme">
							<button type="button" class="btn btn-small btn-success"><span class="glyphicon glyphicon-pencil"></span> Edit</button>
						</div>
					</td>
				</tr>
				<tr>
					<td width="50%;" align="right"><span class="header">Nickname</span></td>
					<td width="50%;" align="left"><%= Nickname %></td>
				</tr>
				<tr>
					<td width="50%;" align="right"><span class="header">Age</span></td>
					<td width="50%;" align="left"><%= Age %></td>
				</tr>
				<tr>
					<td width="50%;" align="right"><span class="header">Location</span></td>
					<td width="50%;" align="left"><%= Location %></td>
				</tr>
			</table>
		</script>

		<script id="tabAboutMeEditTemplate" type="text/template">
			<div class="aboutme-edit">
				<table border="0" cellpadding="5" cellspacing="0" width="100%;">
					<tr>
						<td colspan="2" align="center" style="padding:30px 5px 10px 5px;">
							<textarea class="form-control aboutme-bio"><%= Bio %></textarea>
						</td>
					</tr>
					<tr>
						<td colspan="2" align="center">
							<div class="edit-aboutme">
								<button type="button" class="btn btn-small btn-primary edit-save"><span class="glyphicon glyphicon-check"></span> Save</button>
							</div>
						</td>
					</tr>
					<tr>
						<td width="50%;" align="right"><span class="header">Nickname</span></td>
						<td width="50%;" align="left"><input type="text" class="form-control aboutme-nickname" value="<%= Nickname %>" /></td>
					</tr>
					<tr>
						<td width="50%;" align="right"><span class="header">Age</span></td>
						<td width="50%;" align="left"><input type="text" class="form-control aboutme-age" value="<%= Age %>" /></td>
					</tr>
					<tr>
						<td width="50%;" align="right"><span class="header">Location</span></td>
						<td width="50%;" align="left"><input type="text" class="form-control aboutme-location" value="<%= Location %>" /></td>
					</tr>
				</table>
			</div>
		</script>

		<script id="tabFavQuoteTemplate" type="text/template">
			<span class="header">Favorite Quotes & Lyrics</span>
			<div></div>
			<ul class="favQuoteHolder"></ul>
			<div class="edit">
				<button type="button" class="btn btn-small btn-warning add-fq">Add Quote or Lyric</button>
				<div class="add-fq-hidden" style="display:none;">
					<table border="0" cellpadding="5" cellspacing="0" width="100%;">
						<tr>
							<td width="70%;"><input type="text" class="fq-text form-control" placeholder="Favorite Quote or Lyrics..." /></td>
							<td width="30%;"><input type="text" class="fq-author form-control" placeholder="Author..." /></td>
						</tr>
						<tr>
							<td colspan="2"><button class="btn btn-small btn-primary fq-save">Save</button><button class="btn btn-small btn-warning collapse-fq-cancel" style="margin-left:5px;">Cancel</button></td>
						</tr>
					</table>
				</div>
			</div>
		</script>

		<script id="tabFavQuoteIndvTemplate" type="text/template">
			<%= Text %> - <b><%= Author %></b><span class="glyphicon glyphicon-remove fq-remove"></span>
		</script>

		<script id="tabMemZoneTemplate" type="text/template">
			<span class="header">Memory Zone</span>
			<div></div>
			<table class="memZoneHolder" border="0" cellpadding="3" cellspacing="0" width="100%;"></table>
			<div class="edit">
				<button type="button" class="btn btn-small btn-warning add-mem">Add Memory</button>
				<div class="add-mem-hidden" style="display:none;">
					<table border="0" cellpadding="5" cellspacing="0" width="100%;">
						<tr>
							<td width="20%;" valign="top"><input type="text" class="form-control mem-date" placeholder="Year..." /></td>
							<td width="80%;"><textarea class="form-control mem-text" placeholder="Memory..." style="height:75px; resize:none;"></textarea></td>
						</tr>
						<tr>
							<td colspan="2"><button class="btn btn-small btn-primary mem-save">Save</button><button class="btn btn-small btn-warning collapse-mem-cancel" style="margin-left:5px;">Cancel</button></td>
						</tr>
					</table>
				</div>
			</div>
		</script>

		<script id="tabMemZoneIndvTemplate" type="text/template">
			<td valign="top" width="50px;"><b><%= Date %></b></td>
			<td><%= Text %></td>
			<td valign="top"><span class="glyphicon glyphicon-remove mem-remove"></span></td>
		</script>

		<script id="tabAboutMeTemplate" type="text/template">
			<div class="aboutmewrapper">
				<table class="aboutme" border="0" cellpadding="0" cellspacing="0" width="100%;">
					<tr>
						<td width="50%;">
							<table border="0" cellpadding="0" cellspacing="0" width="100%;">
								<tr>
									<td align="center"><span class="topheader">24</span></td>
								</tr>
								<tr>
									<td align="center"><span class="header">Fans</span></td>
								</tr>
							</table>
						</td>
						<td width="50%;">
							<table border="0" cellpadding="0" cellspacing="0" width="100%;">
								<tr>
									<td align="center"><span class="topheader">123</span></td>
								</tr>
								<tr>
									<td align="center"><span class="header">Following</span></td>
								</tr>
							</table>
						</td>
					</tr>
					<tr>
						<td colspan="2">
							<div class="aboutmeholder"></div>
						</td>
					</tr>
					<tr> <!-- Favorite Quotes & Lyrics -->
						<td colspan="2">
							<div class="favquote"></div>
						</td>
					</tr>
					<tr> <!-- Memory Zone -->
						<td colspan="2">
							<div class="memzone"></div>
						</td>
					</tr>
				</table>
			</div>
		</script>

		<script id="tabMediaTemplate" type="text/template">
			<div class="megaimg-holder">
				<div class="media-header"><button class="btn btn-small btn-warning add-photo-btn"><span class="glyphicon glyphicon-plus"></span> Add Photo</button></div>
				<div class="add-photo-small">
					<table border="0" cellspacing="0" cellpadding="5" width="100%;">
						<tr>
							<td valign="top">
								<b>Upload a photo</b>
								<div style="margin-top:10px;">
									<input id="fileupload" class="form-control" type="file" name="files[]" data-url="endpt.php/imageUpload" multiple>
								</div>
								<div class="results"></div>
							</td>
							<!--<td width="5%" valign="middle">
								<b>OR</b>
							</td>
							<td width="47%" valign="top">
								<b>Grab a photo</b><br />
								<table border="0" cellpadding="0" cellspacing="0" width="100%;">
									<tr>
										<td>
											<input type="text" class="form-control" placeholder="Paste photo URL..."/>
										</td>
										<td width="64px;">
											<button class="btn btn-warning" style="margin-left:5px;">Grab</button>
										</td>
									</tr>
								</table>
							</td>-->
						</tr>
					</table>
				</div>
				<div class="desc-add"></div>
				<div class="img-holder"></div>
			</div>
		</script>

		<script id="tabMediaDescription" type="text/template">
			<table border="0" cellpadding="0" cellspacing="0" width="100%;">
				<tr>
					<td colspan="3" align="center">
						<div class="content-holder">
							<img src="files/fs/<%= PhotoURL %>" style="width:300px; margin:5px;"/>
						</div>
						<div class="content-update">
							<textarea placeholder="Description... " class="form-control desc-textarea" style="resize:none;" img-id="<%= ID %>" ></textarea>
							<button class="btn btn-small btn-primary desc-add-button" style="float:right; margin-top:5px;">Add Description</button>
							<button class="btn btn-small btn-warning desc-skip" style="float:right; margin-top:5px; margin-right:5px;">Skip</button>
						</div>
					</td>
				</tr>
			</table>
		</script>

		<script id="tabPhotoPopup" type="text/template">
			<div id="img-popup">
				Description and a photo.
			</div>
		</script>

		<script id="tabMediaThumb" type="text/template">
			<img src="https://s3-us-west-1.amazonaws.com/spuzik/t/<%= ImageId %>.<%= Extension %>" />
		</script>

		<script id="tabProspectJukeboxIndv" type="text/template">
			<td><span class="glyphicon glyphicon-plus add-tune"></span></td><td><%= Title %> - <span class="artist"><%= Artist %></span></td><td><%= Album %></td>
		</script>

		<script id="tabMyTunesTemplate" type="text/template">
			<!--<input type="text" class="form-control music-search" placeholder="Search..." style="width:200px;" /><button type="button" class="btn btn-small btn-warning">Search</button>-->
			<div class="music-search">
				<table border="0" cellpadding="0" cellspacing="0">
					<tr>
						<td><input type="text" class="form-control music-search" placeholder="Search for music..." style="width:200px;" /></td>
						<td><button type="button" class="btn btn-small btn-warning">Search</button></td>
					</tr>
				</table>
				<div class="search-results">
					<table border="1"></table>
				</div>
			</div>
			<div class="music-tabs">
			</div>
			<div class="music-list">
				<table border="0" cellpadding="5" cellspacing="0" width="100%;"></table>
			</div>
		</script>

		<script id="tabLinkTemplate" type="text/template">
			<td><a href="<%= Url %>"><%= Text %></a></td>
			<td align="right"><span class="glyphicon glyphicon-remove tab-link-remove"></span></td>
		</script>

		<script id="tabLinkHolderTemplate" type="text/template">
			<div class="linkswrapper">
				<table class="link-table" border="0" cellpadding="5" cellspacing="0" width="100%;"></table>
				<div class="no-links"><span class="glyphicon glyphicon-exclamation-sign"></span> No Links have been added.</div>
				<button class="btn btn-warning btn-small add-link-btn">Add Link</button>
				<div class="add-link">
					<table border="0" cellpadding="5" cellspacing="0" width="100%;">
						<tr>
							<td width="40%;"><input type="text" class="form-control link-title" placeholder="Title..." /></td>
							<td width="60%;"><input type="text" class="form-control link-content" placeholder="Link... " /></td>
						</tr>
						<tr>
							<td colspan="2"><button class="btn btn-small btn-primary link-save-btn">Save</button><button class="btn btn-small btn-warning cancel-link-btn" style="margin-left:5px;">Cancel</button></td>
						</tr>
					</table>
				</div>
			</div>
		</script>

		<script id="tabLiveTemplate" type="text/template">
			<h2>Live Area</h2>
		</script>

		<script id="tabZoneOutTemplate" type="text/template">
			<h2>Zone Out Area</h2>
		</script>

		<div id="mega-holder"></div>
		<script type="text/javascript">
		var router = new App.Routers.SpuzikRouter();
		Backbone.history.start();
		</script>
	</body>
</html>