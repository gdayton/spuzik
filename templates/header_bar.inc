<style type="text/css">
.header-line{
        background-color:#ffff27; /* FFD500 #ffff00 */
        margin-bottom:10px;
        /*padding:10px 10px 5px 10px;*/
        position:absolute;
		width:100%;
		height:65px;
		left:0px;
		top: 0px;
		position:fixed;
		z-index:15000;
		/* http://i47.tinypic.com/23k9bgn.png O8q9 http://i.imm.io/O8qQ.png O8rH O8wQ http://i50.tinypic.com/3a0zp.png O8z9 08zu 08BU O8Ce OlIn 08CG OlJc OlKx OlKZ OlLG OlOU OlRY OlVX OlXA OlYj OlZT Om0Q Om1C Om20 Om3v Om42 OHoi OHpc http://i47.tinypic.com/f27ome.png OHx4 OIon OIoS OIwN OIx6 OIAb OIAs OIEi OIJ3 OIJx OIJU OILr OILK OIMi OIMW OINc P8Ym http://i50.tinypic.com/v7d40i.gif http://i.imm.io/RtVp.png http://i.imm.io/SMyU.png*/
		background-image:url('http://i.imm.io/1flQs.png');
		background-repeat:no-repeat;
		background-size:250px 60px;
		background-position:15px 3px;
		/*background-size:85px 53px;
		background-position:175px 5px;*/
}.name-drop{
		position:relative;
        float:right;
        right:10px;
        padding:5px;
        cursor:pointer;
}.name-drop .targeted{
        float:right;
        padding:5px;
        -moz-border-radius:5px;
        -webkit-border-radius:5px;
        border-radius:5px;
        border:0px solid #000;
		background-color:#ffff00;
}.name-drop .targeted:hover{
	background-color:#e5c004;
}.name-drop .notif{
        float:left;
        padding:5px;
        -moz-border-radius:5px;
        -webkit-border-radius:5px;
        border-radius:5px;
        border:0px solid #000;
		background-color:#ffff00;
}.name-drop .notif:hover{
	background-color:#e5c004;
}.tab-header{
        -moz-border-top-right-radius:5px;
        -webkit-border-top-right-radius:5px;
        border-top-right-radius:5px;
        -moz-border-top-left-radius:5px;
        -webkit-border-top-left-radius:5px;
        border-top-left-radius:5px;
        border:0px solid #000;
        background-color:#003F87;
        margin-top:-10px;
        margin-right:-10px;
        margin-left:-10px;
        padding-top:10px;
        padding-left:10px;
        padding-right:10px;
}.tab-header a{
        color:black;
}.logo b{
	font-family: 'Port Lligat Slab', serif;
	position:relative;
	left:20px;
	bottom:2px;
	color:#125eb1;
	font-size:55px;
}.btncustom2{
	background-image: -webkit-linear-gradient(top,#ff0000,#b10000);
	background-image: -o-linear-gradient(top,#ff0000,#b10000);
	background-image: -moz-linear-gradient(top,#ff0000,#b10000);
}.btncustom2:hover{
	background-image: -webkit-linear-gradient(top,#b10000,#ff0000);
	background-image: -o-linear-gradient(top,#b10000,#ff0000);
	background-image: -moz-linear-gradient(top,#b10000,#ff0000);
}.search-res{
	float:left;
	position:absolute;
	top:30px;
	margin-left:40px;
	padding:5px;
	background-color:yellow;
	-moz-border-bottom-right-radius:5px;
	-webkit-border-bottom-right-radius:5px;
	border-bottom-right-radius:5px;
	-moz-border-bottom-left-radius:5px;
	-webkit-border-bottom-left-radius:5px;
	border-bottom-left-radius:5px;
	border:0px solid #000;
}
</style>
<script>
	$(document).ready(function(){
		$.ajax({
			url: "actions.php?type=headerBar",
			success: function(data){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.fname != undefined && parseJSON.lname != undefined){
					$(".u_name").html(parseJSON.fname+" "+parseJSON.lname);
					$(".profile-pic").attr("src","/usr_content/pics/"+parseJSON.profile_pic+"_t.jpg");
				}else if(parseJSON.tname != undefined){
					$(".u_name").html(parseJSON.tname);
					$(".profile-pic").attr("src","/usr_content/pics/"+parseJSON.profile_pic+"_t.jpg");
				}else if(parseJSON.bname != undefined){
					$(".u_name").html(parseJSON.bname);
					$(".profile-pic").attr("src","/usr_content/pics/"+parseJSON.profile_pic+"_t.jpg");
				}
			}
		});
	});

	function playSong(songID) {
		$.ajax({
			url: "actions/songGetter.php",
			type: "POST",
			data: {
				song: songID
			},
			success: function(response) {
				var responseData = $.parseJSON(response);
				window.player.playStreamKey(responseData.StreamKey, responseData.StreamServerHostname, responseData.StreamServerID);
				window.player.setErrorCallback("onPlayerError");
				window.player.setStatusCallback("onPlayerStateChange");
				displayPause();
			}
		});
	}

	$.post('actions.php?type=keepAlive');

	function getUrlVars() {
		var vars = {};
		var parts = window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function(m,key,value) {
			vars[key] = value;
		});
		return vars;
	}
</script>
<table border="0" class="header-line">
	<tr>
		<td style="min-width:245px;">
			<a href="javascript:void(0);" onclick="switchPage('profile');"><div style="width:245px; height:65px;"></div></a>
		</td>
		<td width="40%" style="padding-left:20px;">
			<script>
			  	// Update a particular HTML element with a new value
				function updateHTML(elmId, value) {
					document.getElementById(elmId).innerHTML = value;
				}

				// This function is called when an error is thrown by the player
				function onPlayerError(errorCode) {
					setTimeout(function(){
						$(".music-error").html("ERROR [#"+errorCode+"]");
						$(".music-error").show();
					},2000);
					$(".music-error").hide();
				}

				// This function is called when the player changes state
				function onPlayerStateChange(newState) {
					//alert(newState);
					if(newState == "playing"){ //playing
						displayPause();
					}else if(newState == "paused"){ //paused
						displayPlay();
					}else if(newState == "loading"){ //buffering
						displayPause();
						displayLoading();
					}else if(newState == "failed"){ //failed music
						//alert("failed to load");
					}
				}

				/*
				// Allow the user to set the volume from 0-100
				function volumeUp(){
					if(ytplayer){
						if(ytplayer.getVolume() <= 100){
							ytplayer.setVolume(ytplayer.getVolume()+5);
							//displayVolume(true);
						}
					}
				}

				function volumeDown(){
					if(ytplayer){
						if(ytplayer.getVolume() >= 0){
							ytplayer.setVolume(ytplayer.getVolume()-5);
							//displayVolume(false);
						}
					}
				}
				*/

				$(document).ready(function(){
					$(".playlist-container").css("width",$(".music-player").width());
					//window.onresize = function() { $(".playlist-container").css("width",$(".music-player").width()); };
				});

				function pauseVideo() {
					window.player.pauseStream();
					displayPlay();
				}

				function playVideo() {
					window.player.resumeStream();
					displayPause();
				}

				function changeID(musicArray){
					initScriptSpot(musicArray);
					playVideo();
				}

				//custom player functions

				var videoID = 36502170;

				$(document).ready(function() {
					if(getUrlVars()["p"] == "notifications"){
						setTimeout(function(){

							//loadMyMusic(); //initialize the player correctly
							var songNew = getSongsAll(profileSongID); //pass the profile song id into here
							changeID(songNew); //pass the user's profile song into these parameters
							playlistStats(songNew);
						},3000);
					}else if(getUrlVars()["p"] == "profile"){ //load the profiles user's music
						setTimeout(function(){
							var tAr = getSongsAll(profileSongID); //pass the profile song id into here
							changeID(tAr[0]); //pass the user's profile song into these parameters
							playlistStats(tAr);
						},3000);
					}
				});

				swfobject.embedSWF("http://grooveshark.com/APIPlayer.swf", "player", "0", "0", "9.0.0", "", {}, {allowScriptAccess: "always"}, {id:"groovesharkPlayer", name:"groovesharkPlayer"}, function(e) {
					var element = e.ref;
					if(element) {
						setTimeout(function() {
							window.player = element;
							window.player.setVolume(99);
						}, 1500);
					} else {
						// Couldn't load player
						alert("Could'nt load the player.");
					}
				});

				function populateInfo(data){
					$(document).ready(function(){
						if(data != undefined){
							$(".song-name").html(data[1]+" - "+data[2]);
						}
					});
				}

				function displayPlay(){
					$(".play").attr("onclick","playVideo();");
					$(".play-icon").attr("class","icon-play play-icon");
					$(".loading").hide();
				}

				function displayPause(){
					$(".play").attr("onclick","pauseVideo();");
					$(".play-icon").attr("class","icon-pause play-icon");
					$(".loading").hide();
				}

				function displayLoading(){
					$(".loading").show();
				}

				function calculateTimes(current, total){
					return Math.floor(current/total*100);
				}

				function displayVolume(color){
					if(ytplayer){
						$(".volume-alert").html(ytplayer.getVolume());
						if(color){ //green
							$(".volume-alert").css("color","green");
						}else{
							$(".volume-alert").css("color","red");
						}
					}
				}

				function initScriptSpot(musicArray){ //searchTerm, AKA music terms
					populateInfo(musicArray);
					if(musicArray != undefined){
						videoID = musicArray[0];
						playSong(videoID);
					}
				}

				$(".playlist-container").css("width",$(".music-player").width());
				window.onresize = function() { $(".playlist-container").css("width",$(".music-player").width()); };

				function expandPlaylistView(){
					$(".playlist-container").slideToggle();
					headerGrabPlaylists();
				}

				function headerGrabPlaylists(){
					$.ajax({
						url: "actions.php?type=grabPlaylist&u_id="+logId,
						success: function(data){
							var parseJSON = $.parseJSON(data);
							if(parseJSON != undefined){
								$(".playlist-container table").empty();
								$(".playlist-container table").html("<tr><td colspan='3'></td></tr>");
								if(parseJSON.data.length > 0){
									for(var i = 0;i < parseJSON.data.length;i++){
										$(".playlist-container tr:last").after("<tr>\
										<td width='45px;'><button class='btn btn-mini btn-success' onclick='loadPlaylist("+parseJSON.data[i].id+");'>PLAY</button></td>\
										<td><b style='font-size:14px; color:black;'>"+parseJSON.data[i].title+"</b></td>\
										<td style='font-size:13px; color:black;' width='75px;'>"+parseJSON.data[i].amt+" songs</td>\
										</tr>");
									}
								}else{
									$(".playlist-list").append("<tr><td colspan='3' style='color:black;'>No playlists have been created.</td></tr>");
								}
							}
						}
					});
				}

				var songsAll;
				songsAll = [];

				function loadPlaylist(plst_id){
					songsAll = [];
					$.ajax({
						url: "actions.php?type=getPlaylistMusic&p_id="+plst_id,
						success: function(data){
							var parseJSON = $.parseJSON(data);
							if(parseJSON != undefined){
								if(parseJSON.data.songs.length > 0){
									for(var i = 0;i < parseJSON.data.songs.length;i++){
										songsAll.push([parseJSON.data.songs[i].y_id,parseJSON.data.songs[i].name,parseJSON.data.songs[i].album,parseJSON.data.songs[i].artist]);
									}
								}
							}
							$(".playlist-name").html(parseJSON.data.title);
							$(".controls").attr("songID",0);
							changeID(songsAll[0]);
							playlistStats(songsAll);
						}
					});
				}

				function loadMyMusic(){
					songsAll = [];
					$.ajax({
						url: "actions.php?type=getMusic&id="+logId,
						success: function(data){
							var parseJSON = $.parseJSON(data);
							if(parseJSON != undefined){
								if(parseJSON.data.length > 0){
									for(var i = 0;i < parseJSON.data.length;i++){
										songsAll.push([parseJSON.data[i].y_id,parseJSON.data[i].name,parseJSON.data[i].album,parseJSON.data[i].artist]);
									}
								}
							}
							$(".playlist-name").html("All Music");
							$(".controls").attr("songID",0);
							changeID(songsAll[0]); 			//place this as current id for song to play
							playlistStats(songsAll); 	//update the text that goes along w/ it
						},
					});
				}

				function getSongsAll(s_id){ //pass song id and get array with info returned from DB., returns the array w/ info
					var songsAllArray = [];
					$.ajax({
						url: "actions.php?type=getSongsAll&s_id="+s_id,
						success: function(data){
							var parseJSON = $.parseJSON(data);
							if(parseJSON != undefined){
								songsAllArray.push([parseJSON.data.y_id,parseJSON.data.name,parseJSON.data.album,parseJSON.data.artist]);
							}
						},
					});
					return songsAllArray;
				}

				function nextSong(){
					if($(".controls").attr("songID") != (songsAll.length-1)){ //reached end
						var newIndex = parseInt($(".controls").attr("songID"))+1;
						changeID(songsAll[newIndex]); //pass the small array
						$(".controls").attr("songID",parseInt($(".controls").attr("songID"))+1);
						playlistStats(songsAll);
					}
				}

				function previousSong(){
					if($(".controls").attr("songID") != 0){ 		//reached end
						var newIndex = parseInt($(".controls").attr("songID")) - 1;
						changeID(songsAll[newIndex]);
						$(".controls").attr("songID",parseInt($(".controls").attr("songID"))-1);
						playlistStats(songsAll);
					}
				}
			</script>
			<div id="player"></div>
			<div class="signup" style="background-color:#ffff00; margin-left:50px;">
				<div style="width:0px; height:0px; overflow:hidden;">
					<div id="videoDiv"></div>
				</div>
				<table border="0" width="100%" class='music-player'>
					<tr>
						<td colspan="3">
							<marquee><b style="color:#2727ff;" class="song-name">--</b></marquee><img src="data/img/14s30k.gif" class="loading" width="16px;" height="16px;" style="float:right; display:none;"/><br />
						</td>
					</tr>
					<tr>
						<td width="64px;">
							<div class="controls">
								<a href="javascript:void(0);" onclick="javascript:previousSong();"><i class="icon-chevron-left"></i></a>
								<a class="play" href="javascript:void(0);" onclick="playVideo();"><i class="icon-play play-icon"></i></a>
								<a onclick="nextSong();" href="javascript:void(0);"><i class="icon-chevron-right"></i></a>
							</div>
						</td>
						<td>
							<!-- BLACK BAR -->
							<div style="width:100%; height:5px; background-color:black; position:relative;">
								<div style="width:0%; height:5px; background-color:grey;" class="loading-bar"></div>
								<div style="width:0%; height:5px; background-color:red; position:relative; bottom:5px;" class="play-bar"></div>
							</div>
							<!-- GREY BAR -->
						</td>
						<td width="32px;">
							<a onmousedown="volumeDown();" href="javascript:void(0);"><i class="icon-volume-down"></i></a><a onmousedown="volumeUp();" href="javascript:void(0);"><i class="icon-volume-up"></i></a>
							<span style="color:black; font-size:13px;" class="volume-alert"></span>
							<!--<div style="position:absolute; margin-left:13px;"><span class='music-error' style='color:red; display:none; font-size:12px; font-weight:bold;'>ERROR</span></div>-->
						</td>
					</tr>
					<tr>
						<td></td>
						<td>
							<div style='position:absolute; bottom:3px;'>
								<a href='javascript:expandPlaylistView();' style='font-size:12px; float:right; color:black; margin-left:5px; font-weight:bold;'><i class='icon-music'></i> Switch <span class='music-error' style='color:red; display:none; font-size:12px; font-weight:bold;'>ERROR</span></a> <span style='font-size:13px; color:black;'>Current playlist: <b style='color:green;' class='playlist-name'>--</b> - <span style='color:red;'>Song <span class='playlist-current'>0</span> of <span class='playlist-total'>0</span></span></style></span>
							</div>
						</td>
						<td></td>
					</tr>
				</table>
				<style type='text/css'>
				.playlist-container{
					position:absolute;
					top:67px;
					background-color:yellow;
					display:none;
					-moz-border-radius:0 0 5px 5px;
					border-radius:0 0 5px 5px;
					-webkit-border-radius:0 0 5px 5px;
					padding:5px;
				}
				</style>
				<div class='playlist-container'>
					<button class='btn btn-mini btn-inverse' onclick='loadMyMusic()' style='color:white; float:right;'>&laquo; All Music</button>
					<b style='color:black;'>My Playlists</b>

					<table border='0' width='100%;'>
						<tr>
							<td>No Playlists were found</td>
						</tr>
					</table>
				</div>
			</div>
		</td>
		<td width="25%">
			<style type="text/css">
			.search-head{
				color:black;
				font-weight:bold;
				border-bottom:1px solid #999;
			}.search-cont{
				color:black;
			}.search-cont img{
				width:30px;
				height:30px;
			}.search-cont:hover{
				background-color:white;
			}.resource{
				margin-left:10px;
			}
			</style>
			<script>
			function playlistStats(songsAll){
				$(".playlistInfo").show();
				$(".playlist-current").html( parseInt($(".controls").attr("songID")) + 1 );

				if( (parseInt($(".controls").attr("songID")) + 1) > songsAll.length){
					$(".playlist-current").html(songsAll.length);
				}

				$(".playlist-total").html(songsAll.length);
			}

			function search(){
				$(document).ready(function(){
					$(".search-area").empty();
					$.ajaxSetup({async:false});
					var actionUrl = "actions.php?type=search";
					$.post(
						actionUrl,
						{
							query: $(".search-bar").val()
						},
						function(data,status){
							$(".search-res").show();
							var parseJSON = $.parseJSON(data);
							var searchArea = $(".search-area");
							var noShow = 0;

							if($(".search-bar").val() != ""){
								if(parseJSON.results.standard.length > 0){
									searchArea.append('<tr><td><img src="http://i.imm.io/12P7L.png" style="width:16px; height:16px; float:right;" /><b style="color:black;">People</b></td></tr>');
									for(var i = 0;i < parseJSON.results.standard.length;i++){
										searchArea.append('<tr><td class="search-cont"><a style="color:#173aff;" href="?p=profile&id='+parseJSON.results.standard[i].u_id+'"><div><img class="img-rounded" src="/usr_content/pics/'+parseJSON.results.standard[i].profile_pic+'_t.jpg" width="50px;" height="50px;"/><span class="resource">'+parseJSON.results.standard[i].fname+' '+parseJSON.results.standard[i].lname+'</span><span style="color:black; font-size:13px; margin-left:5px;">'+parseJSON.results.standard[i].hmtown+'</span></div></a></td></tr>');
									}
								}else{
									noShow++;
								}
								if(parseJSON.results.athelete.length > 0){
									searchArea.append('<tr><td><img src="http://i.imm.io/XaEd.png" style="width:16px; height:16px; float:right;" /><b style="color:orange;">Athletes</b></td></tr>');
									for(var i = 0;i < parseJSON.results.athelete.length;i++){
										//searchArea.append('<tr><td class="search-cont"><a style="color:yellow;" href="?p=profile&id='+parseJSON.results.athelete[i].u_id+'"><div><img class="img-rounded" src="/usr_content/pics/'+parseJSON.results.athelete[i].profile_pic+'_t.jpg" width="50px;" height="50px;"/><span class="resource">'+parseJSON.results.athelete[i].fname+' '+parseJSON.results.athelete[i].lname+'</span></div></a></td></tr>');
									}
								}else{
									noShow++;
								}
								if(parseJSON.results.musician.length > 0){
									searchArea.append('<tr><td><img src="http://i.imm.io/OON3.png" style="width:16px; height:16px; float:right;" /><b style="color:orange;">Musicians</b></td></tr>');
									for(var i = 0;i < parseJSON.results.musician.length;i++){
										//searchArea.append('<tr><td class="search-cont"><a style="color:yellow;" href="?p=profile&id='+parseJSON.results.musician[i].u_id+'"><div><img class="img-rounded" src="/usr_content/pics/'+parseJSON.results.musician[i].profile_pic+'_t.jpg" width="50px;" height="50px;"/><span class="resource">'+parseJSON.results.musician[i].fname+' '+parseJSON.results.musician[i].lname+'</span></div></a></td></tr>');
									}
								}else{
									noShow++;
								}
								if(parseJSON.results.agent.length > 0){
									searchArea.append('<tr><td><img src="http://i.imm.io/X5OY.png" style="width:16px; height:16px; float:right;" /><b style="color:orange;">Agents</b></td></tr>');
									for(var i = 0;i < parseJSON.results.agent.length;i++){
										//searchArea.append('<tr><td class="search-cont"><a style="color:yellow;" href="?p=profile&id='+parseJSON.results.agent[i].u_id+'"><div><img class="img-rounded" src="/usr_content/pics/'+parseJSON.results.agent[i].profile_pic+'_t.jpg" width="50px;" height="50px;"/><span class="resource">'+parseJSON.results.agent[i].fname+' '+parseJSON.results.agent[i].lname+'</span><span style="color:white; font-size:13px; margin-left:5px;">'+parseJSON.results.agent[i].hmtown+'</span></div></a></td></tr>');
									}
								}else{
									noShow++;
								}

								if(parseJSON.results.band.length > 0){
									searchArea.append('<tr><td><img src="http://i.imm.io/OONt.png" style="width:16px; height:16px; float:right;" /><b style="color:orange;">Bands</b></td></tr>');
									for(var i = 0;i < parseJSON.results.band.length;i++){
										//searchArea.append('<tr><td class="search-cont"><a style="color:yellow;" href="?p=profile&id='+parseJSON.results.band[i].u_id+'"><div><img class="img-rounded" src="/usr_content/pics/'+parseJSON.results.band[i].profile_pic+'_t.jpg" width="50px;" height="50px;"/><span class="resource">'+parseJSON.results.band[i].bname+'</span></div></a></td></tr>');
									}
								}else{
									noShow++;
								}

								if(parseJSON.results.team.length > 0){
									searchArea.append('<tr><td><img src="http://i.imm.io/XcH8.png" style="width:16px; height:16px; float:right;" /><b style="color:orange;">Teams</b></td></tr>');
									for(var i = 0;i < parseJSON.results.team.length;i++){
										//searchArea.append('<tr><td class="search-cont"><a style="color:yellow;" href="?p=profile&id='+parseJSON.results.team[i].u_id+'"><div><img class="img-rounded" src="/usr_content/pics/'+parseJSON.results.team[i].profile_pic+'_t.jpg" width="50px;" height="50px;"/><span class="resource">'+parseJSON.results.team[i].tname+'</span></div></a></td></tr>');
									}
								}else{
									noShow++;
								}
							}else{
								noShow+=6;
							}
							//add agent profile to search

							if(noShow >= 6){
								$(".search-res").hide();
							}
						}
					);
				});
			}
			$(document).ready(function(){
				$(".search-bar").keydown(function(e){
					var keycode =  e.keyCode ? e.keyCode : e.which;
					if(keycode == 8)
						search();
					if(keycode == 46)
						search();
					search();
				});
				/*setInterval(function(){
					checkNotifications();
				}, 1000);*/
			});

			function checkNotifications(){
				$.ajax({
					url: "actions.php?type=pendingNotifications",
					success: function(data){
						var parseJSON = $.parseJSON(data);

						if(parseInt(parseJSON.data) > 0){
							$(".notif-badge").show();
							$(".notif-badge").html("<span style='color:white; text-decoration:blink;'>"+parseJSON.data+"</span>");
						}
					}
				});
			}

			</script>
			<form class="form-search" style='position:relative; left:45px;'>
				<div style="float:left; width:100%;" class="input-prepend">
					<button type="submit" class="btn btn-primary btncustom2" style="width:40px; height:30px; background-color:red;"><i class="icon-search icon-white"></i></button>
					<input type="text" placeholder="Explore..." style="width:90%; height:30px; font-size:16px;" class="span2 search-bar">
				</div>
				<div class="search-res" style="display:none;">
					<table border="0" class="search-area">
					</table>
				</div>
        	</form>
		</td>
		<td>
			<a href="?p=unite" ><img src="http://i.imm.io/1dzW8.png" width="45px;" style="margin-left:135px;"/></a><!-- onclick="switchPage('unite');" -->
		</td>
		<td style="min-width:280px;">
			<div class="name-drop">
				<script>
				function toggleMenu(){
					$(document).ready(function(){
						$(".user-menu").slideToggle('fast');
					});
				}
				</script>
				<style type="text/css">
				.user-menu{
					top:45px;
					background-color:yellow;
					padding:3px;
					position:absolute;
					border:0px solid #000;
					-moz-border-radius:3px;
					-webkit-border-radius:3px;
					border-radius:3px;
				}
				</style>
				<div class="targeted" style="margin-left:25px; margin-top:5px;">
					<a href='javascript:void(0);' onclick='switchPage("profile");'><img src="" width="30" height="30" style="margin-right:5px;" class="img-rounded profile-pic"/><span style="color:black; font-size:13px;" class="u_name"></span></a><i class="icon-chevron-down" onclick="toggleMenu()"></i>
					<div class="user-menu" style="display:none;">
						<a href="actions.php?type=logout" style="color:black; font-size:13px;">Sign out</a>
						<a href="#" style="color:black; font-size:13px;"><img src="https://cdn2.iconfinder.com/data/icons/flat-ui-icons-24-px/24/settings-24-128.png" width="16" height="16" style="margin-right:2px;"/>Settings</a>
					</div>
				</div>
			</div>
		</td>
	</tr>
</table>
</div>
