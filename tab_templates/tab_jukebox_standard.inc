<style type="text/css">
.add-music{
	padding:10px;
	/*background-color:rgba(255,255,255,.4);*/
	background-color:yellow; /* #fc5a1e */
	/*-moz-border-radius:5px;
	-webkit-border-radius:5px;
	border-radius:5px;
	border:0px solid #000;*/
}.playlist-area{
	background-color:yellow;
	padding:10px;
}.music-area{

}.popupadd{
	width:150px;
	display:none;
	background-color:#156ed4;
	border:1px solid yellow;
	position:absolute;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
	padding:10px;
}
</style>
<script>
$(document).ready(function(){
	$(".music-search").focus();
	showMusic();

	if(logId != user_id){
		$(".delete-tune").hide();
		$(".add-tune").hide();
	}
});

Array.prototype.move = function (old_index, new_index) {
	if (new_index >= this.length) {
		var k = new_index - this.length;
		while ((k--) + 1) {
			this.push(undefined);
		}
	}
	this.splice(new_index, 0, this.splice(old_index, 1)[0]);
	return this; // for testing purposes
};

function addMusic(id,m_name,p_duration, artist_p, album_p){
	//if((id != "") && (m_name != "")){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addTune";
		$.post(
			actionUrl,
			{
				y_id : id,
				name : m_name,
				artist: artist_p,
				album: album_p,
				duration: p_duration
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					alert("Added tune.");
				}
			}
		);
	//}
}

function searchMusic(){
	if($(".music-search").val() != ""){
		/*
			Check restriction:
			http://gdata.youtube.com/feeds/api/videos/1G4isv_Fylg?fields=media:group/media:restriction&alt=json
			https://gdata.youtube.com/feeds/api/videos?q=coldplay&max-results=20&v=2&alt=json&format=5&restriction=DE
		*/
		$.ajax({
			//url: "http://gdata.youtube.com/feeds/api/videos?q="+$(".music-search").val()+"&start-index=1&max-results=20&v=2&format=5&alt=json&restriction=DE",
			url: "actions.php?type=searchMusic&s="+$(".music-search").val()+"&a=15",
			success: function(data){
				var parseJSON = $.parseJSON(data);
				$(".search-title").html($(".music-search").val().replace('"', '&quot;'));
				$(".search-title").show();

				$(".song-list > tbody").html("");
				if(parseJSON != undefined){
					for(var i = 0;i < parseJSON.length;i++){
						$(".song-list > tbody").append("<tr><td><button class='btn btn-success btn-mini' type='button' onclick='javascript:addMusic(\""+parseJSON[i].SongID+"\",\""+parseJSON[i].SongName+"\",\""+0+"\",\""+parseJSON[i].ArtistName+"\",\""+parseJSON[i].AlbumName+"\");' style='color:black;'><i class='icon-plus-sign icon-white'></i></button></td><td style='color:black;'><img style='margin-right:20px;' src='http://images.gs-cdn.net/static/albums/30_"+parseJSON[i].AlbumID+".png' />"+parseJSON[i].SongName+" <i style='font-size:13px; color:grey; margin-left:5px;'>"+parseJSON[i].ArtistName+"</i></td></tr>");
					}
				}else{
					alert("We could not retrieve music corresponding to that search.");
				}
			}
  		});
  	}else{
  		alert("You must enter a search term.");
  	}
}

var musicArray = [];

function showMusic(){
	musicArray = [];
	$(".all-m").hide();
	$(".playlist-name").html("All Music");
	$.ajax({
		url: "actions.php?type=getMusic&id="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);

			$(".music-list").empty();
			$(".music-list").append("\
				<tr>\
					<td width='100%;'>\
						<ul class='music-list-pop' width='100%;'></ul>\
					</td>\
				</tr>");
			for(var i = 0;i < parseJSON.data.length;i++){
				musicArray.push(parseJSON.data[i].id);
				$(".music-list-pop").append("<li class='ui-state-default' width='100%;'>\
												<table border='0' style='width:100%;'>\
													<tr>\
														<td width='60px;'>\
															<button class='btn btn-mini btncustom22' style='color:black; margin-left:10px; background-color:#fc5a1e;' onclick='javascript:changeID([\""+parseJSON.data[i].y_id+"\",\""+parseJSON.data[i].name+"\",\""+parseJSON.data[i].album+"\",\""+parseJSON.data[i].artist+"\"]);'>PLAY</button>\
														</td>\
														<td>\
															"+parseJSON.data[i].name+"\
														</td>\
														<td width='50px;'>\
															<div class='popup"+parseJSON.data[i].id+" popupadd'></div><button class='btn btn-mini btncustom22 add-tune'  style='background-color:#fc5a1e;' onclick='addTo("+parseJSON.data[i].id+");'><i class='icon-plus'></i></button><i class='icon-trash icon-white delete-tune' onclick='removeTune("+parseJSON.data[i].id+");' title='Delete tune' style='position:relative; top:2px; left:3px; cursor:pointer;'></i></table>\
														</td>\
													</tr>\
												</table>\
											</li>");
			}

			//alert(musicArray);
			var tempArray = musicArray;

			var old_pos = 1;
			$(".music-list-pop").sortable({
				start: function(event, ui){
					old_pos = ui.item.index();
				},
				stop: function(event, ui) {
					tempArray.move(old_pos,ui.item.index());

					moveMusicUp(tempArray);
				}
			});
			$(".music-list-pop").disableSelection();
		}
	});
}

function moveMusicUp(music_list){
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=changeTunePosition";
	$.post(
		actionUrl,
		{
			tune_list: music_list
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
			}
		}
	);
}

function movePlaylistUp(playlist_list, pos){
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=changePlaylistPosition";
	$.post(
		actionUrl,
		{
			playlist_list: playlist_list,
			pos: pos_p
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				//Music was moved to the position.
				//showMusic();
			}
		}
	);
}

function movePlaylistMusicUp(playlist_music_list, pos){

}

function removeTune(t_id){
	$.post("actions.php?type=removeTune&t_id="+t_id);
	showMusic();
}

function removePlaylist(p_id){
	$.post("actions.php?type=removePlaylist&p_id="+p_id);
	grabPlaylist();
}

// This is something that needs to be done in order to get these other things setup.

$(document).ready(function(){
	$(".music-search").keyup(function(event){
		if(event.keyCode == 13){
			searchMusic();
		}
	});
});

function showNewPlaylist(){
	$(".new-playlist").slideToggle();
}

function createPlaylist(){
	if($(".playlist-title").val() != ""){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=createPlaylist";
		$.post(
			actionUrl,
			{
				title: $(".playlist-title").val(),
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					//Chatroom was created.
					$(".playlist-title").val("");
					showNewPlaylist();
					grabPlaylist(); //update playlist area to reflect addition
				}
			}
		);
	}
}

function addTo(id){
	$(".popup"+id).show();
	var list = "";
	$.ajax({
		url: "actions.php?type=grabPlaylist&u_id="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON != undefined){
				if(parseJSON.data.length > 0){
					for(var i = 0;i < parseJSON.data.length;i++){
						list += "<option value='"+parseJSON.data[i].id+"'>"+parseJSON.data[i].title+"</option>";
					}
				}
			}
		}
	});
	$(".popup"+id).html("<table border='0' width='100%;'>\
							<tr>\
								<td align='left'><b style='color:white;'>Add To</b><i class='icon-remove icon-white' onclick='$(this).parent().parent().parent().parent().parent().hide();' style='margin-bottom:5px; cursor:pointer; float:right;'></i></td>\
							</tr>\
							<tr>\
								<td>\
									<select style='width:150px;' class='popup-playlist"+id+"'>\
										"+list+"\
									</select>\
								</td>\
							</tr>\
							<tr>\
								<td align='left'><button class='btn btn-small btn-warning' style='color:black;' onclick='addSongPlaylist("+id+");'>Save</button></td>\
							</tr>\
						</table>");
}

function addSongPlaylist(id){
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=addSongPlaylist";
	$.post(
		actionUrl,
		{
			p_id: $(".popup-playlist"+id).val(),
			t_id: id
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				$(".popup"+id).html("<div style='border:1px solid white;'>Added song to playlist!</div>");

				//wait 2 secs before taking it down
				setTimeout($(".popup"+id).hide(),2000);
			}
		}
	);
}

function grabPlaylist(){
	$.ajax({
		url: "actions.php?type=grabPlaylist&u_id="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON != undefined){
				$(".playlist-list").empty();
				$(".playlist-list").html("<tr>\
								<th style='border-bottom:1px dashed #156ed4; width:45px;'></th><th style='color:white; border-bottom:1px dashed #156ed4; color:black;' align='left'></th><th style='border-bottom:1px dashed #156ed4; color:black;' width='80px;'></th>\
							</tr>");
				if(parseJSON.data.length > 0){
					for(var i = 0;i < parseJSON.data.length;i++){
						$(".playlist-list tr:last").after("<tr>\
									<td width='30px;'><button class='btn btn-mini btn-primary' onclick='listPlaylistSongs("+parseJSON.data[i].id+");'><b><span style='color:yellow;'>VIEW</span></b></button></td><td style='color:#156ed4;'>"+parseJSON.data[i].title+"</td><td width='35px;'><i class='icon-trash' onclick='removePlaylist("+parseJSON.data[i].id+");'></i></td>\
								</tr>");

					}
				}else{
					$(".playlist-list").append("<tr><td colspan='3' style='color:black;'>No playlists have been created.</td></tr>");
				}
			}
		}
	});
}
grabPlaylist();

var old_pos = 0;

function listPlaylistSongs(playlist_id){
	$(".all-m").show();
	$.ajax({
		url: "actions.php?type=getPlaylistMusic&p_id="+playlist_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);

			$(".music-list").empty();
			$(".music-list").append("\
				<tr>\
					<td width='100%;'>\
						<ul class='music-list-pop' width='100%;'></ul>\
					</td>\
				</tr>");
			for(var i = 0;i < parseJSON.data.songs.length;i++){
				$(".music-list-pop").append("<li class='ui-state-default' width='100%;'>\
												<table border='0' style='width:100%;'>\
													<tr>\
														<td width='60px;'>\
															<button class='btn btn-mini btncustom22' style='color:black; margin-left:10px; background-color:#fc5a1e;' onclick='javascript:changeID([\""+parseJSON.data.songs[i].y_id+"\",\""+parseJSON.data.songs[i].name+"\",\""+parseJSON.data.songs[i].album+"\",\""+parseJSON.data.songs[i].artist+"\"])'>PLAY</button>\
														</td>\
														<td>\
															"+parseJSON.data.songs[i].name+"\
														</td>\
														<td width='50px;'>\
															<div class='popup"+parseJSON.data.songs[i].id+" popupadd'></div><button class='btn btn-mini btncustom22' style='background-color:#fc5a1e;' onclick='addTo("+parseJSON.data.songs[i].id+");'><i class='icon-plus'></i></button><i class='icon-eject icon-white' title='Remove from playlist' style='position:relative; top:2px; left:3px;'></i></table>\
														</td>\
													</tr>\
												</table>\
											</li>");
			}
			$(".playlist-name").html(parseJSON.data.title);
			$(".music-list-pop").sortable({
				start: function(event, ui){
					old_pos = ui.item.index();
				},
				stop: function(event, ui) {
					movePlaylistMusicUp(old_pos,ui.item.index());
				}
			});
			$(".music-list-pop").disableSelection();
		}
		//$(".playlist-name").html(parseJSON.data.title);
	});
	//also change the text on top to the playlist name.
}

</script>
<style type="text/css">
.playlist-manage{
	background-color:yellow;
}.music-list-pop li:hover{
	background-color:#5a5aff;
	cursor:pointer;
}
</style>

<div class="add-music">
	<table border="0" cellpadding="10px;" width="100%;">
		<tr>
			<td><img src="http://i.imm.io/YggK.png" /></td><!-- http://i49.tinypic.com/23r3bq0.png http://i.imm.io/W34m.png http://i49.tinypic.com/23r3bq0.png -->
			<td align='left'>
				<b style="color:#156ed4;">Search for your favorite music.</b><br />
				<input type="text" style="height:28px; width:250px;" class="music-search" placeholder="Artists, Albums, Songs ..." />
				<button class="btn btn-primary" type="button" style="color:black; position:relative; bottom:5px;" onclick="javascript:searchMusic();"><span style='color:yellow;'>Search</span></button><br />
				<b style="color:#156ed4; position:relative; bottom:6px;">Create a unique playlist.</b>
			</td>
			<td>
				<div style='position:relative; bottom:4px;'>
					<b style='color:black; font-size:13px;'>Powered by</b><br />
					<img src='http://www.grooveshark.com/webincludes/logo/Grooveshark_Logo_Horizontal.png' width='100px;' />
				</div>
			</td>
		</tr>
	</table>
	<div class="music-results">
		<i style="margin-left:75px; display:none; color:black;" class="search-title">Results for: --</i>
		<table border="0" width="80%" style="margin-left:75px;" cellpadding="8" class="song-list"><tr></tr></table>
	</div>
</div>

<div class='playlist-manage'>
	<center><button class='btn btn-small btn-primary' style='color:yellow;' onclick='showNewPlaylist();'>New playlist</button></center>

	<div class='new-playlist' style='display:none;'>
		<table border='0' style='margin-left:20px;'>
			<tr>
				<td align='right' style='color:black; padding-right:15px;' valign='middle'>Playlist Title</td>
				<td><input type='text' class='playlist-title' style='height:30px; position:relative; top:3px;' placeholder='Playlist title...' /></td>
			</tr>
			<tr>
				<td align='right' style='color:black;'></td>
				<td><button class='btn btn-small btn-primary' style='color:yellow;' onclick='createPlaylist();'>Create Playlist</button></td>
			</tr>
		</table>
	</div>
</div>

<div class="playlist-area">
	<button class="btn btn-mini btn-inverse all-m" style="position:absolute; margin-top:8px; margin-left:6px;" type="button" onclick="showMusic();"><span style='color:white; font-size:18px;'>&laquo;</span> All Music</button>
	<center>
		<span style="font-size:25px; color:black; /*text-shadow: 2 2 5 yellow;*/ border-bottom:2px solid #156ed4; font-weight:bold;">Playlists</span>
	</center>
	<table border="0" width="100%;">
		<tr>
			<!--<td valign="center" width="85px">

			</td>-->
			<td>
				<table border="0" class="playlist-list" cellpadding="5" width="100%;" style='margin-bottom:15px;'></table>
			</td>
		</tr>
	</table>
</div>


<style type='text/css'>
.music-list-pop{
	list-style:none;
	width:100%;
	display:table;
	margin-left:0px;
}
</style>
<div class="music-area">
	<div style="margin-top:-30px;">
		<div style="text-align:center; position:relative; bottom:3px; padding-left:10px; padding-right:10px;">
			<span class='playlist-name' style="font-size:25px; color:black; border-bottom:2px solid #156ed4; font-weight:bold;">Music</span>
		</div>
		<table border="0" width="100%" style="background-color:yellow;">
			<tr>
				<td width="100px;" align="left"><!--<button class="btn btn-mini btn-inverse" style="margin-left:10px;"><span style='color:white; font-size:18px;'>&laquo;</span> All Music</button>--></td>
			</tr>
		</table>
		<table border="0" class="music-list" cellpadding="5" width="100%;"></table>
	</div>
</div>