<script src="http://www.google.com/jsapi" type="text/javascript"></script>
<script type="text/javascript">
  google.load("swfobject", "2.1");
</script>
<script type="text/javascript">
  /*
   * Chromeless player has no controls.
   */

  // Update a particular HTML element with a new value
  function updateHTML(elmId, value) {
	document.getElementById(elmId).innerHTML = value;
  }

  // This function is called when an error is thrown by the player
  function onPlayerError(errorCode) {
	alert("An error occured of type:" + errorCode);
  }

  // This function is called when the player changes state
  function onPlayerStateChange(newState) {
	/*updateHTML("playerState", newState);*/
	if(newState == 1){ //playing
		displayPlay();
	}else if(newState == 2){ //paused
		displayPause();
	}else if(newState == 3){ //buffering
		displayPlay();
		displayLoading();
	}
  }

  // Display information about the current state of the player
  function updatePlayerInfo() {
	// Also check that at least one function exists since when IE unloads the
	// page, it will destroy the SWF before clearing the interval.
	if(ytplayer && ytplayer.getDuration) {
	  /*updateHTML("videoDuration", ytplayer.getDuration());
	  updateHTML("videoCurrentTime", ytplayer.getCurrentTime());
	  updateHTML("bytesTotal", ytplayer.getVideoBytesTotal());
	  updateHTML("startBytes", ytplayer.getVideoStartBytes());
	  updateHTML("bytesLoaded", ytplayer.getVideoBytesLoaded());
	  updateHTML("volume", ytplayer.getVolume());*/
	}
  }

  // Allow the user to set the volume from 0-100
  function setVideoVolume() {
	var volume = parseInt(document.getElementById("volumeSetting").value);
	if(isNaN(volume) || volume < 0 || volume > 100) {
	  alert("Please enter a valid volume between 0 and 100.");
	}
	else if(ytplayer){
	  ytplayer.setVolume(volume);
	}
  }

  function playVideo() {
	if (ytplayer) {
	  ytplayer.playVideo();
	}
  }

  function pauseVideo() {
	if (ytplayer) {
	  ytplayer.pauseVideo();
	}
  }

  function muteVideo() {
	if(ytplayer) {
	  ytplayer.mute();
	}
  }

  function unMuteVideo() {
	if(ytplayer) {
	  ytplayer.unMute();
	}
  }


  // This function is automatically called by the player once it loads
  function onYouTubePlayerReady(playerId) {
	ytplayer = document.getElementById("ytPlayer");
	// This causes the updatePlayerInfo function to be called every 250ms to
	// get fresh data from the player
	setInterval(updatePlayerInfo, 250);
	updatePlayerInfo();
	ytplayer.addEventListener("onStateChange", "onPlayerStateChange");
	ytplayer.addEventListener("onError", "onPlayerError");
	//Load an initial video into the player
	ytplayer.cueVideoById("BiJcDP6hoZU");
	//auto-play the video
	playVideo();
  }

  // The "main method" of this sample. Called when someone clicks "Run".
  function loadPlayer() {
	// Lets Flash from another domain call JavaScript
	var params = { allowScriptAccess: "always" };
	// The element id of the Flash embed
	var atts = { id: "ytPlayer" };
	// All of the magic handled by SWFObject (http://code.google.com/p/swfobject/)
	swfobject.embedSWF("http://www.youtube.com/apiplayer?" +
					   "version=3&enablejsapi=1&playerapiid=player1",
					   "videoDiv", "0", "0", "9", null, null, params, atts);
  }
  function _run() {
	loadPlayer();
  }
  google.setOnLoadCallback(_run);

  //custom player functions

  function populateInfo(data){
  	$("b.song-name").html(data.entry.title.$t);
  }

  function displayPlay(){
  	$(".controls a").attr("onclick","pauseVideo();");
  	$(".controls i").attr("class","icon-pause");
  	$(".loading").hide();
  }

  function displayPause(){
  	$(".controls a").attr("onclick","playVideo();");
  	$(".controls i").attr("class","icon-play");
  	$(".loading").hide();
  }

  function displayLoading(){
  	$(".loading").show();
  }
</script>
<script type="text/javascript" src="http://gdata.youtube.com/feeds/api/videos/BiJcDP6hoZU?v=2&alt=json&callback=populateInfo"></script>
<div class="signup" style="background-color:#ffff00; margin-left:50px;">
	<div id="videoDiv"></div>
	<b style="color:black;" class="song-name">Pink Floyd - Wish you were here</b><img src="data/img/14s30k.gif" class="loading" width="16px;" height="16px;" style="display:none;"/><br />
	<div style="float:right;">
		<i class="icon-volume-down"></i><i class="icon-volume-up"></i>
	</div>
	<div style="width:100%px; margin-left:20px; height:5px; background-color:black; position:relative; top:6px;"></div>
	<div class="controls">
		<a onclick="playVideo();"><i class="icon-play" style="position:relative; bottom:5px;"></i></a>
	</div>
</div>