<script type="text/javascript">

var fileId = 0;
$(document).ready(function(){
	$(function() {
		var data = {"fileType":['image/png','image/jpg','image/jpeg','image/gif']};
		$('#file_upload').uploadifive({
			'auto'         : true,
			'fileType'	   : data.fileType,
			'queueID'      : 'queue',
			'uploadScript' : 'uploadifive.php',
			'onUploadComplete' : function(file, data) {
				var parseJSON = $.parseJSON(data);

				if(parseJSON.status == "success"){
					$("#uploadifive-file_upload-file-"+fileId).attr("photo-id",parseJSON.photo_id);
					$("#uploadifive-file_upload-file-"+fileId).append("<img src='usr_content/pics/"+parseJSON.photo_id+"_t.jpg' width='100%;' height='100%;'/>");
					$("#uploadifive-file_upload-file-"+fileId).append("<div style='margin:5px;'><textarea placeholder='Description...' style='width:100%;' class='"+parseJSON.photo_id+"-textbox'></textarea><span class='"+parseJSON.photo_id+"-saved label label-success' style='display:none;'>Saved</span><button type='button' class='btn btn-small btncustom' style='float:right;' onclick=\"addDescription('"+parseJSON.photo_id+"');\">Save</button></div>");
				}
				//grab photo and credentials associated w/ photo
				fileId++;
			}
		});
	});

	if(user_id == logId){
		$(".edit-res").show();
	}
});

function managePhotos(){
	$(".manage-photos").slideToggle();
	$(".manage-videos").slideUp();
	$(".manage-albums").slideUp();
}

function manageVideos(){
	$(".manage-photos").slideUp();
	$(".manage-videos").slideToggle();
	$(".manage-albums").slideUp();
}

function manageAlbums(){
	$(".manage-photos").slideUp();
	$(".manage-albums").slideToggle();
	$(".manage-videos").slideUp();
}

//function populateVideoInfo(data){
//	$(document).ready(function(){
//		$(".video-info .video-name").html(data.entry.title.$t);
//		$(".video-info .video-thmb").attr("src",data.entry.media$thumbnial[1].url);
//	});
//}
function youtube_parser(url){
    var regExp = /.*(?:youtu.be\/|v\/|u\/\w\/|embed\/|watch\?v=)([^#\&\?]*).*/;
    var match = url.match(regExp);
    if (match&&match[1].length==11){
        return match[1];
    }else{
        alert("URL is incorrect.");
    }
}

function addVideo(){
	if($(".youtubeID").val() != ""){

		$.ajax({
			url: "http://gdata.youtube.com/feeds/api/videos/"+youtube_parser($(".youtubeID").val())+"?v=2&alt=json",
			success: function(data){
				if(data.entry.title.$t != undefined){
					$(".video-name").html(data.entry.title.$t);
					$(".video-thmb").attr("src","http://i.ytimg.com/vi/"+youtube_parser($(".youtubeID").val())+"/mqdefault.jpg");
					setVideo(youtube_parser($(".youtubeID").val()),data.entry.title.$t);
				}else{
					$(".video-name").html("Video does not exist with that ID.");
					$(".video-info").attr("style","border:1px solid red;");
				}
			}
  		});
  	}else{
  		alert("You must enter a Youtube ID.");
  	}
}

$(document).ready(function(){
  //Photos
  $.ajax({
		url: "actions.php?type=getPhotos&uid="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					for(var i = 0;i < parseJSON.data.length;i++){
						$(".photos-holder").append("<a href='javascript:launchModal(0,\""+parseJSON.data[i]+"\");'><img style='margin:2px; margin-top:5px;' src='/usr_content/pics/"+parseJSON.data[i]+"_t.jpg' width='155px;' height='155px;' /></a>");
					}
					$(".photo-ctr").html(parseJSON.data.length);
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
  });

  //Videos
  $.ajax({
		url: "actions.php?type=getVideos&uid="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					for(var i = 0;i < parseJSON.data.length;i++){
						$(".videos-holder").append("<a href='javascript:launchModal(1,\""+parseJSON.data[i]+"\");'><img style='margin:2px; margin-top:5px;' src='http://i.ytimg.com/vi/"+parseJSON.data[i]+"/2.jpg' width='155px;' height='155px;' /></a>");
					}
					$(".video-ctr").html(parseJSON.data.length);
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
  });
});

function addDescription(pid){
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=addDescription";
	$.post(
		actionUrl,
		{
			id: pid,
			text: $("."+pid+"-textbox").val()
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				$("."+pid+"-saved").show();
			}
		}
	);
}

function launchModal(type,id){
	if(type == 0){ 							//photo
		$(".modal-img").show();
		$(".imgvid-content").hide();
		$(".modal-img").attr("src","/usr_content/pics/"+id+"_w.jpg");
		$(".modal-img").attr("img-id",id);
		$(".manage-btn").attr("r-id",id);
		$("#myModal").modal("toggle");

		$(".comment-item").remove();

		switchManage(0);
		getPhotoData(id);
		grabComments(id);
	}
	if(type == 1){							//video
		$(".modal-img").hide();
		$(".imgvid-content").show();
		$(".imgvid-content").html("<iframe class='modal-video' type='text/html' width='100%' height='100%' src='http://www.youtube.com/embed/"+id+"' frameborder='0' allowfullscreen></iframe>");
		$("#myModal").modal("toggle");

		$(".manage-btn").attr("r-id",id);
		$(".description").remove();
		$(".comment-item").remove();

		switchManage(1);
		grabComments(id);
		getVideoData(id);
		$(".modal-backdrop").live("click", function (e) {
   			removeModal();
		});
	}
}

function switchManage(type){
	if(type == 0){ 	//photo
		$(".manage-btn").html("<li><a href='javascript:showDescription();' class='drop-a'><i class='icon-pencil'></i> Edit Description</a></li>\
		<li><a href='javascript:showPerms();' class='drop-a'><i class='icon-edit'></i> Edit Permissions</a></li>\
		<li><a href='javascript:setHomePic();' class='drop-a'><i class='icon-home'></i> Set as home image</a></li>\
		<li><a href='javascript:setProfilePic();' class='drop-a'><i class='icon-user'></i> Set as profile picture</a></li>\
		<li class='divider'></li>\
		<li class='warning'><a href='javascript:removePhoto();' class='drop-a'><i class='icon-ban-circle'></i> Remove</a></li>");
	}else{			//video
		$(".manage-btn").html("<li><a href='javascript:showPerms();' class='drop-a'><i class='icon-edit'></i> Edit Permissions</a></li>\
		<li class='divider'></lis>\
		<li class='warning'><a href='javascript:removeVideo();' class='drop-a'><i class='icon-ban-circle'></i> Remove</a></li>");
	}
}

function getPhotoData(id){
	$.ajax({
		url: "actions.php?type=getPhotoData&id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					$(".resource-content .date").html(parseJSON.data.date);
					$(".resource-content .user-name").html(parseJSON.data.name);
					$(".resource-content .description").attr("r_id",id);
					$(".resource-content .profile-pic").attr("src","/usr_content/pics/"+parseJSON.data.profile_pic+"_t.jpg");
					$(".resource-content .description").html("&quot; "+parseJSON.data.description+" &quot;");
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
  });
}

function getVideoData(id){
	$.ajax({
		url: "actions.php?type=getVideoData&id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					$(".resource-content .date").html(parseJSON.data.date);
					$(".resource-content .user-name").html(parseJSON.data.name);
					$(".resource-content .profile-pic").attr("src","/usr_content/pics/"+parseJSON.data.profile_pic+"_t.jpg");
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
  });
}

$(".comment-tbox").elastic();

function setVideo(id,title){
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=addVideo";
	$.post(
		actionUrl,
		{
			y_id: id,
			name: title,
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				$(".youtubeID").val("");
				$(".youtubeID").select();
			}
		}
	);
}

function editDescription(){
	if($(".description-tbox").val() != ""){
		var description = $(".description-tbox").val();
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=editImageDescription";
		$.post(
			actionUrl,
			{
				r_id: $(".resource-content .description").attr("r_id"),
				description: $(".description-tbox").val()
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					$(".resource-content .description").html("&quot; "+description+" &quot;");
					$(".description-tbox").val("");
					$(".modal-edit-des").hide();
				}
			}
		);
	}
}

function removePhoto(){
	var sure = confirm("Are you sure you want to permanently remove this photo?");
	if(sure){
		$.post("actions.php?type=removePhoto&r_id="+$(".resource-content .description").attr("r_id"));
		$(".close").click();
		loadTab("tab_photovideo_agent.inc");
	}
}

function removeVideo(){
	var sure = confirm("Are you sure you want to permanently remove this video?");
	if(sure){
		$.post("actions.php?type=removeVideo&r_id="+$(".manage-btn").attr("r-id"));
		$(".close").click();
		loadTab("tab_photovideo_agent.inc");
	}
}

function showPerms(){
	$(".modal-edit-perms").slideToggle();
	$(".modal-edit-des").hide();
}

function showDescription(){
	$(".modal-edit-des").slideToggle();
	$(".modal-edit-perms").hide();
}

function setProfilePic(){
	var img_id = $(".modal-img").attr("img-id");
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=editProfilePic";
	$.post(
		actionUrl,
		{
			pic_id: img_id
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				alert("Profile picture changed.");
			}
		}
	);
}

function setHomePic(){
	var img_id = $(".modal-img").attr("img-id");
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=editHomePic";
	$.post(
		actionUrl,
		{
			pic_id: img_id
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				alert("Home picture changed.");
			}
		}
	);
}

function makeComment(){
	if($(".comment-tbox").val() != ""){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addComment";
		$.post(
			actionUrl,
			{
				comment: $(".comment-tbox").val(),
				type: 1,
				r_id: $(".manage-btn").attr("r-id")
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					$(".comment-tbox").val("");
					$(".comment-tbox").select();
					grabComments($(".manage-btn").attr("r-id"));
				}
			}
		);
	}else
		alert("You must enter text into comment area.");
}

function grabComments(resource_id){
	$.ajax({
		url: "actions.php?type=grabComments&r_id="+resource_id+"&c_type=1",
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.data != undefined){
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".comment-holder").append("<div class='comment-item'>\
						<span class='namec'>"+parseJSON.data[i].name+"</span><span class='comment'>"+parseJSON.data[i].comment+"</span><span class='date-comment'>"+parseJSON.data[i].date+"</span></div>\
					</div>");
				}
			}
		}
  });
}

</script>
<style>
.edit-res{
	display:none;
	text-align:center;
	width:100%;
}.edit-res-wrap{
	background-color:#063d78;
	padding-top:10px;
	padding-bottom:10px;
}
</style>
	<div class="edit-res-wrap">
		<div class="edit-res">
			<button class="btn btn-primary btn-small btn-primary" style="color:black;" onclick="javascript:managePhotos();"><span style="color:#ffff00;">Manage Photos</span></button>
			<button class="btn btn-primary btn-small btn-primary" style="color:black;" onclick="javascript:manageVideos();"><span style="color:#ffff00;">Manage Videos</span></button>
			<button class="btn btn-primary btn-small btn-primary" style="color:black;" onclick="javascript:manageAlbums();"><span style="color:#ffff00;">Manage Albums</span></button>
		</div>

		<form class="manage-photos" style="display:none; margin:10px;">
			<div id="queue"></div>
			<input id="file_upload" name="file_upload" type="file" multiple="true">
		</form>

		<form class="manage-videos" style="display:none; margin:10px;">
			<input type="text" style="height:25px; position:relative; top:5px;" placeholder="Paste Youtube video ID..." class="youtubeID" />
			<button class="btn btn-primary btn-small btncustom" type="button" onclick="javascript:addVideo();"><span style="color:black;">Add Video</span></button><img src="http://i50.tinypic.com/33m6cy1.png" style="margin-left:8px;" />
			<div class="video-info">
				<b class="video-name"></b><br />
				<img class="video-thmb" src="" width="100%;"/>
			</div>
		</form>

		<script>
		function get0Album(){
			$.ajax({
				url: "actions.php?type=grabNonAlbumPhotos&uid="+logId,
				success: function(data){
					var parseJSON = $.parseJSON(data);
					if(parseJSON.status != "error"){
						if(parseJSON.data != undefined){
							$(".album-photo").empty();
							for(var i = 0;i < parseJSON.data.length;i++){
								$(".album-photo").append("<a class='min"+parseJSON.data[i]+"' onmouseover=\"displayBig(\'"+parseJSON.data[i]+"\');\" href='javascript:addAlbumQueue(\""+parseJSON.data[i]+"\");'><img src='/usr_content/pics/"+parseJSON.data[i]+"_t.jpg' width='50px' /></a>");
							}
							//$(".photo").append("<br /><button href='?p=profile='"+logId+"'#tab_photosvideo_standard' class='btn btn-small btncustom'>Add Photo</button>");
						}
					}else{
						alert("There was an error obtaining your photos.");
					}
				}
		  });
		}

		function displayBig(id){
			$(".big-img").attr("src","/usr_content/pics/"+id+"_s.jpg");
		}

		Array.prototype.remove = function(from, to) {
		  var rest = this.slice((to || from) + 1 || this.length);
		  this.length = from < 0 ? this.length + from : from;
		  return this.push.apply(this, rest);
		};

		var albumQueue = [];
		function addAlbumQueue(id){
			$.post("actions.php?type=addAlbumItem&a_id="+$(".album-list").val()+"&p_id="+id);
			$(".min"+id).remove();
			albumQueue.push(id);
			repaintAlbumQueue();
		}

		function repaintAlbumQueue(){
			$(".album-holding").empty();
			for(var i = 0;i < albumQueue.length;i++){
				$(".album-holding").append("<a onmouseover=\"displayBig(\'"+albumQueue[i]+"\');\" href='javascript:removeAlbumQueue(\""+albumQueue[i]+"\");'><img src='/usr_content/pics/"+albumQueue[i]+"_t.jpg' width='50px' /></a>");
			}
		}

		function removeAlbumQueue(id){
			$.post("actions.php?type=removeAlbumItem&p_id="+id);
			var indexi = albumQueue.indexOf(id);
			albumQueue.remove(indexi);
			$(".album-photo").append("<a class='min"+id+"' onmouseover=\"displayBig(\'"+id+"\');\" href='javascript:addAlbumQueue(\""+id+"\");'><img src='/usr_content/pics/"+id+"_t.jpg' width='50px' /></a>");
			repaintAlbumQueue();
		}

		function selectAlbum(){
			var a_id = $(".album-list").val();
			$(".remove-album").attr("onclick","removeAlbum("+a_id+");");
			$(".remove-album").show();
			if(a_id == "mn"){
		    	$(".new-album").show();
		    	$(".remove-album").hide();
		    	$(".album-holding").empty();
		    }else{
		    	$(".album-holding").empty();
		    	$(".new-album").hide();
				if(a_id != "!!"){
					$.ajax({
						url: "actions.php?type=grabAlbumPhotos&a_id="+a_id,
						success: function(data){
							var parseJSON = $.parseJSON(data);
							if(parseJSON.status != "error"){
								if(parseJSON.data != undefined){
									//$(".album-holding").empty();
									albumQueue = [];
									for(var i = 0;i < parseJSON.data.length;i++){
										albumQueue.push(parseJSON.data[i].photo_path);
										//$(".album-holding").append("<a href='javascript:removeAlbumQueue(\""+parseJSON.data[i].photo_path+"\");'><img src='/usr_content/pics/"+parseJSON.data[i].photo_path+"_t.jpg' width='50px' /></a>");
									}
									repaintAlbumQueue();
								}
							}else{
								alert("There was an error obtaining your photos.");
							}
						}
					});
				}
			}
		}

		function removeAlbum(id){
			var yesno = confirm("Are you sure you want to permanently remove this album?");
			if(yesno){
				$.post("actions.php?type=removeAlbum&a_id="+id);
				albumQueue = [];
				repaintAlbumQueue();
				selectAlbumText();
				$(".album-holding").empty();
				$(".remove-album").hide();
			}
		}

		function selectAlbumText(){
			$.ajax({
				url: "actions.php?type=selectAlbumText",
				success: function(data){
					var parseJSON = $.parseJSON(data);
					if(parseJSON.status != "error"){
						if(parseJSON.data != undefined){
							$(".album-list").empty();
							$(".album-list").append("<option value='!!'>Select...</option>");
							for(var i = 0;i < parseJSON.data.length;i++){
								$(".album-list").append("<option value='"+parseJSON.data[i].id+"'>"+parseJSON.data[i].title+"</option>");
							}
							$(".album-list").append("<option value='mn'>New album</option>");
						}else{
							$(".album-list").append("<option value='!!'>Select...</option>");
							$(".album-list").append("<option value='mn'>New album</option>");
						}
					}else{
						alert("There was an error obtaining your photos.");
					}
				}
		    });
		}

		function createAlbum(){
			var text = $(".album-desc").val();
			var title = $(".album-title").val();

			if(title.length > 0){
				$.ajaxSetup({async:false});
				var actionUrl = "actions.php?type=createAlbum";
				$.post(
					actionUrl,
					{
						title: title,
						description: text
					},
					function(data,status){
						var parseJSON = $.parseJSON(data);
						if(parseJSON.status == "error"){
							alert(parseJSON.status_msg);
						}else{
							$(".new-album").hide();
							$(".album-holding").html("<span style='font-size:13px; color:white;'><i class='icon-chevron-up icon-white'></i> Select newly created playlist.</span>");
							selectAlbumText();
						}
					}
				);
			}
		}

		function removeModal(){ //removes the video
			$(".modal-video").remove();
		}

		selectAlbumText();
		get0Album();
		</script>

		<style type="text/css">
		.album-photo img{
			margin:4px;
		}.album-photo img:hover{
			margin:2px;
			border:2px solid green;
		}.album-holding{
			height:100%;
		}.album-holding img{
			margin:4px;
		}.album-holding img:hover{
			margin:2px;
			border:2px solid red;
		}
		</style>
		<form class="manage-albums" style="display:none; margin:10px;">
			<table border="0" width="100%;">
				<tr>
					<td width="40%;" valign="top"><b style="color:white;">Choose Photo</b><div class="album-photo"></div></td>
					<td valign="top"><b style="color:white;">Choose Album</b>
					<button class="btn btn-mini btncustom remove-album" type='button' style='float:right; display:none;'>Remove Album</button>
					<div class="album-text">
						<select onChange="selectAlbum()" class="album-list">
						</select>
						<div class="new-album" style="display:none;">
							<input type="text" placeholder="Album title..." class="album-title" style="height:23px; margin-right:3px;"/>
							<textarea class="album-desc" style="width:100%; resize:none;" placeholder="Description..."></textarea>
							<button class="btn btn-mini btncustom" onclick="createAlbum();" type="button" style="position:relative; bottom:4px;">Create</button>
						</div>
					</div>
					<div class="album-holding"></div>
					<img class="big-img" src="" width="100%" style="margin-top:10px;"/>
					</td>
					<!--<td align="right" valign="top"><button class="btn btn-primary btn-small btncustom" style="color:black;" onclick="javascript:manageAlbums();">Save</button></td>-->
				</td>
			</table>
		</form>
	</div>

<div class="view" style="margin-top:10px;">
	<div style='border-bottom:1px solid yellow; margin-top:10px;'>
		<b style='color:yellow;'><i class="icon-th icon-white" style="position:relative; right:3px; bottom:2px; margin-left:5px;"></i>Albums</b>
	</div>
	<table border="0" width="100%;">
		<td align="center">
			<div class="album-holder"></div>
		</td>
	</table>
	<div style='border-bottom:1px solid yellow;'>
		<b style='color:yellow;'><i class="icon-picture icon-white" style="position:relative; right:3px; bottom:2px; margin-left:5px;"></i>Photos</b><span style='font-size:13px;'> &middot; <span class='photo-ctr'>0</span> photos</span>
	</div>
	<table border="0" width="100%;">
		<td align="center">
			<div class="photos-holder"></div>
		</td>
	</table>
	<div style='border-bottom:1px solid yellow; margin-top:10px;'>
		<b style='color:yellow;'><i class="icon-film icon-white" style="position:relative; right:3px; bottom:2px; margin-left:5px;"></i>Videos</b><span style='font-size:13px;'> &middot; <span class='video-ctr'>0</span> videos</span>
	</div>
	<table border="0" width="100%;">
		<td align="center">
			<div class="videos-holder"></div>
		</td>
	</table>
</div>

<div class="upload">
	<style type="text/css">
	#queue {
		overflow: auto;
		padding:10px;
		width:95%;
		margin-bottom:10px;
	}.error{
		background-color:red;
		padding:5px;
		border:0px solid #000;
		-moz-border-radius:3px;
		-webkit-border-radius:3px;
		border-radius:3px;
		margin-bottom:3px;
	}
	</style>
</div>
















<!-- Modal -->
<div id="myModal" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" style="height:80%; width:93%; margin-left:-47%;">
    <style type="text/css">
    .resource-content{
    	margin-left:20px;
    }
    </style>
    <table border="0" width="100%" height="100%">
    	<tr>
    		<td style="background-color:black;" align="center" valign="center">
    		<div class="imgvid-content" style='width:100%; height:100%;'></div>
    		<img class="modal-img" style="display:none;" src="" style="height:100%;" img-id=""/>
    		</td>
    		<td align="right" valign="top" width="300px;"><button type="button" class="close" data-dismiss="modal" aria-hidden="true" onclick="removeModal()">×</button>
    			<div class="resource-content" style="color:black;">
    			<table border="0" style="margin:10px;" width="100%">
    				<tr>
    					<td rowspan="2" align="right" valign="top" width="50px;"><img class="profile-pic img-rounded" src="" width="30px;" height="30px;" style="margin-right:5px;"/></td>
    					<td class="manage-btn-edit" style="display:none;">
    						<div class="btn-group" style="float:right;">
							  <button class="btn btn-small btn-primary"><span style="color:yellow;">Manage</span></button>
							  <button class="btn btn-small dropdown-toggle btn-primary" style="height:26px;" data-toggle="dropdown">
								<span class="caret"></span>
							  </button>
							  <ul class="dropdown-menu pull-right manage-btn"></ul>
							</div>
    						<a href="#" style="color:blue;" class="user-name">--</a>
    					</td>
    				</tr>
    				<tr>
    					<td style="color:black; font-size:12px;">Uploaded <span class="date"></span></td>
    				</tr>
    				<tr>
    					<td colspan="2" style="color:black; padding:10px;"><span class="description"></span></td>
    				</tr>
    				<script>
					if(user_id == logId){
						$(".manage-btn-edit").show();
					}
    				</script>
    				<style type="text/css">
    				.drop-a{
    					color:black;
    				}.drop-a:hover{
    					color:white;
    				}
    				</style>
    				<tr>
    					<td colspan="2" class="edit-photo">
							<div class="modal-edit-des" style="display:none;">
								<table border="0" style="margin:10px;">
									<tr>
										<td width="150px;">
											<textarea class="description-tbox" placeholder="Edit description..." width="100%;"></textarea><br />
										</td>
										<td valign="top" align="left">
											<button class="btn btn-small btncustom" style="color:black;" onclick="editDescription();">Save</button>
										</td>
									</tr>
								</table>
							</div>

							<div class="modal-edit-perms" style="display:none;">
								<table border="0" style="margin:10px;">
									<tr>
										<td width="150px;">
											<select style="width:206px;">
												<option value="priv">Public</option>
												<option value="fans">Fans</option>
											</select>
										</td>
										<td valign="top" align="left">
											<button class="btn btn-small btncustom" style="color:black;" onclick="editPerms();" >Save</button>
										</td>
									</tr>
								</table>
							</div>

							<style type="text/css">
							.image-comments{
								margin-top:10px;
							}.namec{
								font-weight:bold;
								color:blue;
								margin-right:5px;
								font-size:13px;
							}.comment{
								color:black;
								font-size:13px;
							}.date-comment{
								font-size:12px;
								float:right;
								color:grey;
							}
							</style>
							<div class="image-comments">
								<div class="comment-holder"></div>
								<textarea placeholder="Comment..." style="width:100%; resize:none; font-size:13px; margin-top:10px;" class="comment-tbox"></textarea><button class="btn btn-mini btn-primary" style="float:right;" onclick="makeComment();"><span style="color:yellow;">Comment</span></button>
							</div>
    					</td>
    				</tr>
    			</table>
    			</div>
    		</td>
    	</tr>
    </table>
</div>