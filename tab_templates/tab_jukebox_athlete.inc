<style type="text/css">
.add-music{
	padding:10px;
	/*background-color:rgba(255,255,255,.4);*/
	background-color:#fc5a1e;
	/*-moz-border-radius:5px;
	-webkit-border-radius:5px;
	border-radius:5px;
	border:0px solid #000;*/
}.playlist-area{
	background-color:#fc5a1e;
	padding:10px;
}.music-area{

}
</style>
<script>
$(document).ready(function(){
	$(".music-search").focus();
	showMusic();
});

function addMusic(id,m_name,p_duration){
	//if((id != "") && (m_name != "")){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addTune";
		$.post(
			actionUrl,
			{
				y_id : id,
				name : m_name,
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
			url: "http://gdata.youtube.com/feeds/api/videos?q="+$(".music-search").val()+"&start-index=1&max-results=20&v=2&format=5&alt=json&restriction=DE",
			success: function(data){
				$(".song-list > tbody").html("");
				$(".search-title").html(data.feed.title.$t.replace('"', '&quot;'));
				$(".search-title").show();
				if(data.feed.title.$t != undefined){
					for(var i = 0;i < data.feed.entry.length;i++){
						$(".song-list > tbody").append("<tr><td><button class='btn btn-success btn-mini' type='button' onclick='javascript:addMusic(\""+data.feed.entry[i].media$group.yt$videoid.$t+"\",\""+data.feed.entry[i].title.$t+"\",\""+data.feed.entry[i].media$group.yt$duration.seconds+"\");' style='color:white;'><i class='icon-plus-sign icon-white'></i></button></td><td style='color:black;'>"+data.feed.entry[i].title.$t+"</td><td>"+data.feed.entry[i].media$group.yt$duration.seconds.toHHMMSS()+"</td></tr>");
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

function playSong(id){
	changeID(id);
	loadPlayer();
}

function showMusic(){
	$.ajax({
		url: "actions.php?type=getMusic&id="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.length > 0){
				var edit = "";
				for(var i = 0;i < parseJSON.length;i++){
					$(".music-list tr:last").after("<tr><td><button class='btn btn-mini btn-warning' style='color:black; margin-left:10px;' onclick='javascript:changeID(\""+parseJSON[i].y_id+"\")'>PLAY</button></td><td>"+parseJSON[i].name+"</td><td align='center'>"+parseJSON[i].duration.toHHMMSS()+"</td><td align='center'><button class='btn btn-mini btn-warning'><i class='icon-plus'></i></button></td></tr>");
				}
			}else{
				$(".music-list").append("<tr><td colspan='2'>No music has been added.</td></tr>");
			}
		}
	});
}

$(document).ready(function(){
	$(".music-search").keyup(function(event){
		if(event.keyCode == 13){
			searchMusic();
		}
	});
});

</script>
<!--<table border="0" width="100%;" cellpadding="0" cellspacing="0">
	<tr>
		<td>-->
			<div class="add-music">
				<table border="0" cellpadding="10px;">
					<tr>
						<td><img src="http://i.imm.io/YFwt.png" /></td><!-- http://i49.tinypic.com/23r3bq0.png http://i.imm.io/W34m.png http://i49.tinypic.com/23r3bq0.png -->
						<td>
							<b style="color:black;">Search for your favorite music.</b><br />
							<input type="text" style="height:28px; width:250px;" class="music-search" placeholder="Artists, Albums, Songs, Playlists..." />
							<button class="btn btn-primary" type="button" style="color:black;" onclick="javascript:searchMusic();"><span style='color:yellow;'>Search</span></button><br />
							<b style="color:black;">Create a unique playlist.</b>
						</td>
					</tr>
				</table>
				<div class="music-results">
					<i style="margin-left:75px; display:none; color:black;" class="search-title">Results for: The Police</i>
					<table border="0" width="80%" style="margin-left:75px;" cellpadding="8" class="song-list"><tr></tr></table>
				</div>
			</div>
		<!--</td>
	</tr>
	<tr style="background-color:#063d78;">
		<td>-->
		<div class="playlist-area">
			<center>
				<span style="font-size:25px; color:black; /*text-shadow: 2 2 5 yellow;*/ border-bottom:2px solid blue; font-weight:bold;">Playlists</span>
			</center>
			<table border="0" width="100%;">
				<tr>
					<td valign="center" width="85px">
						<button class="btn btn-mini btncustom" style="margin-left:10px; color:#156ed4;" type="button"><span style='color:#156ed4; font-size:18px;'>&laquo;</span> All Music</button>
					</td>
					<td>
						<table border="0" class="playlist-list" cellpadding="5" width="100%;">
							<tr>
								<th style='border-bottom:1px dashed blue; width:45px;'></th><th style="color:white; border-bottom:1px dashed blue; color:black;" align="left">Name</th><th style="border-bottom:1px dashed black; color:yellow;"></th>
							</tr>
							<tr>
								<td><button class="btn btn-mini btn-primary"><b><span style="color:yellow;">VIEW</span></b></butotn></td><td style='color:blue;'>Rock Music</td><td> </td>
							</tr>
							<tr>
								<td><button class="btn btn-mini btn-primary"><b><span style="color:yellow;">VIEW</span></b></butotn></td><td style='color:blue;'>Jazz Music</td><td> </td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
		</div>
		<!--</td>
	</tr>
	<tr>
		<td>-->
		<div class="music-area" style='margin-top:-15px;'>
			<div>
				<div style="text-align:center; /*position:relative; top:5px;*/ padding-left:10px; padding-right:10px; background-color:#fc5a1e;">
					<span style="font-size:25px; color:black; border-bottom:2px solid blue; font-weight:bold;">Jazz Music</span>
				</div>
				<table border="0" width="100%" style="background-color:#fc5a1e;">
					<tr>
						<td width="100px;" align="left"><!--<button class="btn btn-mini btn-inverse" style="margin-left:10px;"><span style='color:white; font-size:18px;'>&laquo;</span> All Music</button>--></td>
					</tr>
				</table>
				<table border="0" class="music-list" cellpadding="5" width="100%;">
					<tr style="background-color:#fc5a1e;">
						<th style='border-bottom:1px dashed black; width:45px;'></th><th style="border-bottom:1px dashed black; color:blue;" align="left">Title</th><th style='border-bottom:1px dashed black; color:blue;'>Duration</th><th style='width:75px; border-bottom:1px dashed black; color:blue;'>Add to</th>
					</tr>
				</table>
			</div>
		</div>
		<!--</td>
	</tr>
</table>-->