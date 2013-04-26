<!--<div id="player"></div>

<script>
  var tag = document.createElement('script');

  tag.src = "//www.youtube.com/iframe_api";
  var firstScriptTag = document.getElementsByTagName('script')[0];
  firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

  var player;
  function onYouTubeIframeAPIReady() {
	player = new YT.Player('player', {
	  height: '390',
	  width: '640',
	  videoId: 'qJwPEPRbkyk',
	  events: {
		'onReady': onPlayerReady,
		'onStateChange': onPlayerStateChange
	  }
	});
  }

  function onPlayerReady(event) {
	event.target.playVideo();
  }

  function onPlayerStateChange(){

  }

  function stopVideo() {
	player.stopVideo();
  }
</script>-->
<?php
//echo strtotime('01/19/2014 01:23 AM');
?>
<!--<iframe width='100%' height='100%' src='http://www.youtube.com/embed/qrO4YZeyl0I?version=3&border=0&autohide=1&showinfo=0&rel=0&theme=light&color=white&iv_load_policy=3&autoplay=1' frameborder='0'></iframe>-->

<?php

/*
searchMusic($_GET['s'],$_GET['a']);

function searchMusic($searchTerm, $limit = 5){
	$searchTerm = urlencode($searchTerm);
	$json = file_get_contents("http://tinysong.com/s/".$searchTerm."?format=json&limit=".$limit."&key=e645c4270980103b19215d1bf7439438");

	$json_decode = json_decode($json, true);
	//print_r($json_decode);
	foreach($json_decode as $jd){
		echo "<hr />";
		echo "<b>".$jd['SongName']."</b><br />";
		echo "<i>".$jd['ArtistName']."</i><br />";
		echo $jd['Url']."<br />";
	}
}
*/

?>
<html>
	<head>
	  <script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
	  <script src="//ajax.googleapis.com/ajax/libs/jqueryui/1.9.2/jquery-ui.min.js"></script>
	  <script src="/actions/swfobject.js"></script>
	  <script src="/actions/grooveshark.js"></script>
	</head>

	<body>
		<script>
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
			  }
			});
		}
		</script>
		<script>
			swfobject.embedSWF("http://grooveshark.com/APIPlayer.swf", "player", "300", "300", "9.0.0", "", {}, {allowScriptAccess: "always"}, {id:"groovesharkPlayer", name:"groovesharkPlayer"}, function(e) {

			var element = e.ref;

			if (element) {

				setTimeout(function() {
					window.player = element;
					window.player.setVolume(99);
				}, 1500);

			} else {

				// Couldn't load player
				alert("Could'nt load the player.");
			}

			});
		</script>

	  	<div id="player"></div>
	  	<style type='text/css'>
			#groovesharkPlayer {
				position: absolute;
				top: -9999px;
				left: -9999px;
			}
	  	</style>
		<a href='javascript:void();' onclick='playSong(10466);'>Play Bob Dylan</a>
	</body>
</html>
<h1>1</h1><img src='http://i41.tinypic.com/35bhv2e.png' />
<h1>2</h1><img src='http://i40.tinypic.com/2wqex04.png' />
<h1>3</h1><img src='http://i40.tinypic.com/35bf8l0.png' />
<h1>4</h1><img src='http://i41.tinypic.com/66yq2x.png' />
<h1>5</h1><img src='http://i42.tinypic.com/34gt28n.png' />