<?php
if(isset($_GET['id'])){
	$u_id = $_GET['id'];
}else{
	$u_id = $_SESSION['user_id'];
}

$u = new User();
$userInfo = $u->userInfo($u_id);
?>
<script>
var ptype = 0; //default
function popDates(){
	$(".popDates").datepicker({ dateFormat: 'mm/dd/yy' });
}

/*
	Load this stuff on page load.
*/
$(window).ready(function(){
	setTimeout(function(){
		init();
		$(".tab-area a").css("color","#173aff");
	},10);
	//setTimeout(function(){ createUploader() },30);
});

/*var fileId = 0;
$(document).ready(function(){
	$(function() {
		var data = {"fileType":['image/png','image/jpg','image/jpeg','image/gif']};
		$('#file_upload').uploadifive({
			'auto'         : true,
			'fileType'	   : data.fileType,
			'queueID'      : 'post-queue',
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
});*/

$(document).ready(function(){
	$(function() {
		var data = {"fileType":['image/png','image/jpg','image/jpeg','image/gif']};
		$('#post-file-upload').uploadifive({
			'auto'         : true,
			'fileType'	   : data.fileType,
			'queueID'      : 'post-queue',
			'uploadScript' : 'uploadifive.php',
			'onUploadComplete' : function(file, data) {
				var parseJSON = $.parseJSON(data);

				if(parseJSON.status == "success"){
					$("#uploadifive-file_upload-file-"+fileId).attr("photo-id",parseJSON.photo_id);
					$("#uploadifive-file_upload-file-"+fileId).append("<img src='usr_content/pics/"+parseJSON.photo_id+"_t.jpg' width='100%;' height='100%;'/>");
				}
				//grab photo and credentials associated w/ photo
				fileId++;
			}
		});
	});
	//setTimeout(createUploader(), 500);
});

function changePType(pt){
	ptype = pt;
	repaintPostings(0);
}

function init(){
	var lineupArray = [];
	//INFINITE SCROLL
	if(user_id == logId){
		$(".lineup-enter").show();
		$(".manage-btn-edit").show();
	}else{
		$(".shufflebtn").hide();
	}

	$(".fav-text").keyup(function(event){
		if(event.keyCode == 13){
			addLineup();
			$(".shufflebtn").focus();
		}
	});

	$(".user_type").tooltip('toggle');
	$(".user_type").tooltip('hide');
	popDates();

	/*
		Get fans
	*/
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=getFans";
	$.post(
		actionUrl,
		{
			id: <?php echo $u_id; ?>
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				var user_fans = $(".user-fans");
				for(var item in parseJSON){
					if(parseJSON[item].type != undefined){
						if(parseJSON[item].type == 0 || parseJSON[item].type == 1 || parseJSON[item].type == 3){
							if(parseJSON[item].lname != undefined){
								user_fans.append("<a href='?p=profile&id="+parseJSON[item].u_id+"'><div style='width:45%; padding:3px; color:#ffff67; float:left;'><img class='img-rounded' style='margin-right:5px;' src='http://54.243.129.126/usr_content/pics/"+parseJSON[item].profile_pic+"_t.jpg' width='40px;' height='40px;'/>"+parseJSON[item].fname+" "+parseJSON[item].lname+"</div></a>");
							}
						}else if(parseJSON[item].type == 2){
							if(parseJSON[item].tname != undefined){
								user_fans.append("<a href='?p=profile&id="+parseJSON[item].u_id+"'><div style='width:45%; padding:3px; color:#ffff67; float:left;'><img class='img-rounded' style='margin-right:5px;' src='http://54.243.129.126/usr_content/pics/"+parseJSON[item].profile_pic+"_t.jpg' width='40px;' height='40px;'/>"+parseJSON[item].tname+"</div></a>");
							}
						}else{
							if(parseJSON[item].bname != undefined){
								user_fans.append("<a href='?p=profile&id="+parseJSON[item].u_id+"'><div style='width:45%; padding:3px; color:#ffff67; float:left;'><img class='img-rounded' style='margin-right:5px;' src='http://54.243.129.126/usr_content/pics/"+parseJSON[item].profile_pic+"_t.jpg' width='40px;' height='40px;'/>"+parseJSON[item].bname+"</div></a>");
							}
						}
					}
				}
			}else{
				alert("We were not able to retrieve the users.");
			}
		}
	);

	/*
		Get supporters
	*/
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=getSupporters";
	$.post(
		actionUrl,
		{
			id: <?php echo $u_id; ?>
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				for(var item in parseJSON){
					if(parseJSON[item].type != undefined){
						if(parseJSON[item].type == 0 || parseJSON[item].type == 1 || parseJSON[item].type == 3 || parseJSON[item].type == 5){
							$(".user-supporters").append("<a href='?p=profile&id="+parseJSON[item].u_id+"'><div style='width:45%; padding:3px; color:yellow; float:left;'><img class='img-rounded' style='margin-right:5px;' src='http://54.243.129.126/usr_content/pics/"+parseJSON[item].profile_pic+"_t.jpg' width='40px;' height='40px;'/>"
							+parseJSON[item].fname+" "+parseJSON[item].lname+"</div></a>");
						}else if(parseJSON[item].type == 2){
							$(".user-supporters").append("<a href='?p=profile&id="+parseJSON[item].u_id+"'><div style='width:45%; padding:3px; color:yellow; float:left;'><img class='img-rounded' style='margin-right:5px;' src='http://54.243.129.126/usr_content/pics/"+parseJSON[item].profile_pic+"_t.jpg' width='40px;' height='40px;'/>"
							+parseJSON[item].tname+"</div></a>");
						}else{
							$(".user-supporters").append("<a href='?p=profile&id="+parseJSON[item].u_id+"'><div style='width:45%; padding:3px; color:yellow; float:left;'><img class='img-rounded' style='margin-right:5px;' src='http://54.243.129.126/usr_content/pics/"+parseJSON[item].profile_pic+"_t.jpg' width='40px;' height='40px;'/>"
							+parseJSON[item].bname+"</div></a>");
						}
					}
				}
			}else{
				alert("We were not able to retrieve the users.");
			}
		}
	);

	$(".lineup-delete").click(function(){
		$(this).parent().remove();
	});
	//slideshow loader
	$(".post-textbox").elastic();
	$.ajax({
		url: "actions.php?type=getPhotos&uid="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.data != undefined){
				parseJSON.data.shuffle();
				$(".init-image").attr("src","/usr_content/pics/"+parseJSON.data[0]+"_s.jpg");
			}

			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					for(var i = 1;i < parseJSON.data.length;i++){
						$(".img-cont").append("<img class='fix-w-img' src='/usr_content/pics/"+parseJSON.data[i]+"_s.jpg' />");
					}
					$(".photo-ctr").html(parseJSON.data.length);

					$('.img-cont').cycle({
						fx: 'fade',
						//timeout: 2000,
						speed:   300
					});
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
	});

	var old_pos = 0;
	$(".lineup-list").sortable({
		start: function(event, ui){
			old_pos = ui.item.index();
		},
		stop: function(event, ui) {
			moveUp(old_pos,ui.item.index());
		}
	});
	$(".lineup-list").disableSelection();
	$(".tab-scroll").slideDown(2000);

	//load first tab as default
	<?php $fI = $tabContent[0]['tab_script']; ?>
	if(!window.location.hash){
		$(".content-area").load("tab_templates/tab_mylinks_standard.inc",function(){
			$(".loading-area-top").hide();
		});
	}else{
		$(".content-area").load("tab_templates/"+window.location.hash.substring(1),function(){
			$(".loading-area-top").hide();
			window.scroll(0,430);
		});
	}

	$(".comment-tbox").elastic();

	//RESTORE LATER
	/*setInterval(function(){
		chatAlerts();
	},1000);*/

	$(window).scroll(function(){
		if($(window).scrollTop() == $(document).height() - $(window).height()){
			loadMoreContent();
			//$(".link-view").css("background-color","yellow");
			$(".link-view a").css("color","#2727ff");
		}
	});

	//wait for the area to load
	setTimeout(function(){
		// --==(( RENABLE THE LOADING HERE  ))==--
		repaintPostings(0);
		drawLineup();
	},10);
}

/*
$(".site-content").ready(function() {
	drawLineup();
});*/

function support(){
	$(document).ready(function(){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=fan";
		$.post(
			actionUrl,
			{
				u_id: <?php echo $u_id; ?>
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					$(".support-yes").hide();
				}
			}
		);
	});
}

function chatAlerts(){
	$.ajax({
		url: "actions.php?type=getChatAlerts",
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.data.num_alerts > 0){ //if there are alerts than display them
				$(".chat-badge").show();
				$(".chat-badge").html(parseJSON.data.num_alerts);
			}else{
				$(".chat-badge").hide();
			}
		}
	});
}

/*
	Used for playing and pausing the slideshow
*/
function pause(){
	$('.img-cont').cycle('pause');
	$('.img-cont').attr('onclick','play()');
}

function play(){
	$('.img-cont').cycle('resume');
	$('.img-cont').attr('onclick','pause()');
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

function displayVideo(id){
	$(".video"+id).show();
	$(".vid-pic"+id).hide();
	$(".vid-pic-play"+id).hide();
}

function showComment(id){
	$(".comment-area-show"+id).slideToggle();
	$(".comment-area-show").elastic();
	$(".comment-area-show-button"+id).slideToggle();
}

function makeComment2(id){
	if($(".comment-area-show"+id).val() != ""){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addComment";
		$.post(
			actionUrl,
			{
				comment: $(".comment-area-show"+id).val(),
				type: 0,
				r_id: id
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					$(".comment-area-show"+id).val("");
					grabComments2(id);
				}
			}
		);
	}else
		alert("You must enter text into comment area.");
}

function grabComments2(id){
	$.ajax({
		url: "actions.php?type=grabComments&r_id="+id+"&c_type=0",
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					$(".comment"+id).empty();
					if(parseJSON.data.length < 3){
						for(var i = 0;i < parseJSON.data.length;i++){
							var trash = "";
							if(parseJSON.data[i].u_id == logId)
								trash = "<i onclick='deleteComment("+parseJSON.data[i].id+","+id+");' class='icon-trash icon-white'></i>";
							else
								trash = "";
							$(".comment"+id).append("<b style='margin-right:3px;'>"+parseJSON.data[i].name+"</b>&nbsp;"+parseJSON.data[i].comment+"<span style='color:white; padding-left:5px;'>"+parseJSON.data[i].date+" ago</span>"+trash+"<br />");
						}
					}else{
						$(".comment-load"+id).show();
						$(".comment-load"+id).html((parseJSON.data.length-3)+" more comments");
						for(var i = 0;i < 3;i++){
							var trash = "";
							if(parseJSON.data[i].u_id == logId)
								trash = "<i onclick='deleteComment("+parseJSON.data[i].id+","+id+");' class='icon-trash icon-white'></i>";
							else
								trash = "";
							$(".comment"+id).append("<b style='margin-right:3px;'>"+parseJSON.data[i].name+"</b>&nbsp;"+parseJSON.data[i].comment+"<span style='color:white; padding-left:5px;'>"+parseJSON.data[i].date+" ago</span>"+trash+"<br />");
						}
						for(var i = 3;i < parseJSON.data.length;i++){
							var trash = "";
							if(parseJSON.data[i].u_id == logId)
								trash = "<i onclick='deleteComment("+parseJSON.data[i].id+","+id+");' class='icon-trash icon-white'></i>";
							else
								trash = "";
							$(".comment-hidden"+id).append("<b style='margin-right:3px;'>"+parseJSON.data[i].name+"</b>&nbsp;"+parseJSON.data[i].comment+"<span style='color:white; padding-left:5px;'>"+parseJSON.data[i].date+" ago</span>"+trash+"<br />");
						}
					}
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
	});
}

function deleteComment(id, id2){
	var yn = confirm("Are you sure you want to remove this comment?");
	if(yn){
		$.post("actions.php?type=deleteComment&r_id="+id);
		grabComments2(id2);
	}
}

function clap(id){
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=clap";
	$.post(
		actionUrl,
		{
			type: 0,
			r_id: id
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				var valueBefore = $(".clap"+id).val();
				//$(".clap"+id).html((valueBefore+1));
				getClaps(id);
			}
		}
	);
}

function loadMore(id){
	$(".comment-hidden"+id).slideToggle();
}

function getClaps(id){
	$.ajax({
		url: "actions.php?type=grabClaps&r_id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					$(".clap"+id).html(parseJSON.data[0]);
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
	});
}

/*
	LINEUP FUNCTIONS BELOW
*/

function grabLineup(){
	  lineupArray = [];
	  $.ajax({
			url: "actions.php?type=getLineup&u_id="+user_id,
			success: function(data){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.data != undefined){
					for(var i = 0;i < parseJSON.data.length;i++){
						lineupArray.push(parseJSON.data[i]); //pushes array onto lineupArray array
					}
				}
			}
	  });
}

function addLineup(){
	if($(".fav-text").val() != ""){
		var text = $(".fav-text").val();
		var font = Math.floor(Math.random()*2);
		var color = Math.floor(Math.random()*7);
		$(".fav-text").val("");
		$(".fav-text").select();
		$(document).ready(function(){
			$.ajaxSetup({async:false});
			var actionUrl = "actions.php?type=addEditLineup";
			$.post(
				actionUrl,
				{
					action: "add",
					item: text,
					font_id: font,
					a_id: color,
					position_id: (lineupArray.length+1)
				},
				function(data,status){
					var parseJSON = $.parseJSON(data);
					if(parseJSON.status == "error"){
						alert(parseJSON.status_msg);
					}else{
						//$(".support-yes").hide();
						drawLineup();
					}
				}
			);
		});
	}else
		alert("You must enter a favorite.");
}

function randomFonts(){
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=randomFonts";
	$.post(
		actionUrl,{id:"i"},
		function(data,status){
			drawLineup();
		}
	);
}

function drawLineup(){
	//var fontArray = ["Molle","Diplomata SC"];
	var fontArray = ["Helvetica","Helvetica"];
	//var colorArray = ["white","#ff1a1a","#00ff00","yellow","orange","#cd00cd"];
	var colorArray = ["#72bcd4","orange","red","#cd00cd","#32cd32","yellow","white","#33ffff"];
	//fetches fresh lineup from DB
	grabLineup();
	var display = ((user_id == logId) ? "show" : "none" );

	$(".lineup-item").remove();
	for(var i = 0;i < lineupArray.length;i++){
		if(i != 0){
			$(".lineup-list").append("<li class='lineup-item ui-state-default' lid='"+i+"'>\
				<div style='float:right;'><a href='javascript:removeLineup("+i+");' style='display:"+display+";'><img style='display:none; margin-right:3px;' class='trash-icon' src='/data/img/trash.png'></img></a></div>\
				<div style='width:30px; float:left;'><span style='color:yellow; margin-right:15px; margin-left:10px;'>"+i+"</span></div>\
				<span style='color:"+colorArray[lineupArray[i].color_id]+"; font-family:"+fontArray[lineupArray[i].font_id]+", cursive;'>"+lineupArray[i].item+"</span>\
			</li>");
		}else{ //render with the cup
			$(".lineup-list").append("<li class='lineup-item ui-state-default' lid='"+i+"'>\
				<div style='float:right'><a href='javascript:removeLineup("+i+");' style='display:"+display+";'><img style='display:none; margin-right:3px;' class='trash-icon' src='/data/img/trash.png'></img></a></div>\
				<div style='width:30px; float:left;'><img style=' margin-right:15px; margin-left:10px;' src='http://i.imm.io/1dzsx.png' /></div><!-- -->\
				<span style='color:"+colorArray[lineupArray[i].color_id]+"; font-family:"+fontArray[lineupArray[i].font_id]+", cursive;'>"+lineupArray[i].item+"</span>\
			</li>");
		}
	}

	$(".lineup-item").mouseenter(function(){
		$(this).find(".trash-icon").show(); //$("this .trash-icon").show();
		$(this).css("background-color","#373737");
	}).mouseleave(function(){
		$(this).find(".trash-icon").hide();
		$(this).css("background-color","black");
	});
}

function removeLineup(pos){
	var yes = confirm("Are you sure you want to delete this?");
	if(yes){
		$(document).ready(function(){
			$.ajaxSetup({async:false});
			var actionUrl = "actions.php?type=addEditLineup";
			$.post(
				actionUrl,
				{
					action: "remove",
					id: lineupArray[pos].id
				},
				function(data,status){
					var parseJSON = $.parseJSON(data);
					if(parseJSON.status == "error"){
						alert(parseJSON.status_msg);
					}else{
						//$(".support-yes").hide();
						drawLineup();
					}
				}
			);
		});
	}
}

// edit, position_id_1, position_id_2, id1, id2
function moveUp(pos, move_pos){
	if(pos == 0)
		alert("This item is already #1.");
	else{
		lineupArray.move(pos,move_pos);

		var condensedLineupArray = [];
		for(var i = 0;i < lineupArray.length;i++){
			condensedLineupArray[i] = lineupArray[i].id;
		}

		$(document).ready(function(){
			$.ajaxSetup({async:false});
			var actionUrl = "actions.php?type=addEditLineup";
			$.post(
				actionUrl,
				{
					action: "edit",
					items_list: condensedLineupArray
				},
				function(data,status){
					var parseJSON = $.parseJSON(data);
					if(parseJSON.status == "error"){
						alert(parseJSON.status_msg);
					}else{
						drawLineup();
					}
				}
			);
		});
	}
}
/*
	END LINEUP
*/

function status(){
	$(".status-1").hide();
	$(".status-cancel").show();
	$(".status-save").show();
	$(".def-status").slideToggle('fast');
	$(".edit-status").slideToggle('fast');
	$(".status-enter").select();
}

function statusSubmit(){
	var statusVar = $(".status-enter").val();

	if(status.length <= 300){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=updateStatus";
		$.post(
			actionUrl,
			{
				status: statusVar
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					$(".def-status").html("<i style='color:yellow;'>"+statusVar.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;")+"</i>");
					$(".def-status").slideToggle('fast');
					$(".edit-status").slideToggle('fast');
					$(".status-cancel").hide();
					$(".status-save").hide();
					$(".status-1").show();
				}
			}
		);
	}else{
		alert("Your status exceeded the allowed 300 characters.");
	}
}

function statusCancel(){
	$(".def-status").slideToggle('fast');
	$(".edit-status").slideToggle('fast');
	$(".status-cancel").hide();
	$(".status-save").hide();
	$(".status-1").show();
}

function makePosting(){
	var postingText = $(".post-textbox").val();

	//Figure out type and extra info with it.
	var postingType = 0;
	var postingAdd = 0;

	$(document).ready(function(){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addPosting";

		$.post(
			actionUrl,
			{
				text: postingText,
				type: contType,
				text_add: contId,
				r_id: user_id,
				post_type: 0
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					$(".pick-cat").attr("post-id",parseJSON.data);
					//Add posting to post list
					$(".post-adder").hide("");
					$(".pick-cat").show();
				}
			}
		);
	});
}

function makePostingCats(category){
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=addPostingCategory";
	$.post(
		actionUrl,
		{
			post_id: $(".pick-cat").attr("post-id"),
			cat: category,
			cat_b: 0
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				$(".post-adder").show();
				$(".pick-cat").hide();
				$(".post-textbox").val("");
				repaintPostings(0);
				changePostExtra(-1);
				contId = "";
				contType = 0;
				$(".post-extra").slideUp("slow");
				$(".post-extra-remove").hide();
			}
		}
	);
}

function removePosting(p_id){
	var yesno = confirm("Are you sure the you would like to permanently remove this posting?");
	if(yesno){
		$.post("actions.php?type=removePosting&p_id="+p_id);
		repaintPostings(0);
	}
}

function repaintPostings(p_id){ //p_id is the page id/ infinite scroll page that we're on
	$.ajax({
		url: "actions.php?type=getProfilePostings&p_id="+p_id+"&u_id="+user_id+"&ptype="+ptype,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			pageMAX = parseJSON.amt;
			if(parseJSON.status != "error"){
				if(p_id == 0){
					$(".feed-area").fadeOut('fast');
					$(".feed-area").empty();
				}
				if(parseJSON.data != undefined){
					for(var i = 0;i < parseJSON.data.length;i++){
						var commentID = parseJSON.data[i].id;
						//Assemble posting here
						var xtra = "";
						if(parseJSON.data[i].type == 1){
							xtra = "<div class='ex-img'>\
								<img onclick='launchModal(0,\""+parseJSON.data[i].text_add+"\");' style='cursor:pointer;' src='/usr_content/pics/"+parseJSON.data[i].text_add+"_w.jpg'/>\
							</div>";
						}else if(parseJSON.data[i].type == 2){
								xtra = "<div class='video-view'>\
									<img src='/data/img/play_btn.png' width='45px;' onclick='displayVideo("+parseJSON.data[i].id+");' class='vid-pic-play"+parseJSON.data[i].id+"' style='position:relative; cursor:pointer; top:75px; left:155px;'/>\
									<img class='vid-pic"+parseJSON.data[i].id+"' width='336' height='252' style='cursor:pointer; margin-left:auto; margin-top:-40px; margin-right:auto; display:block;' onclick='displayVideo("+parseJSON.data[i].id+");' src='http://img.youtube.com/vi/"+parseJSON.data[i].text_add+"/mqdefault.jpg' />\
									<object width='336' height='252' class='video"+parseJSON.data[i].id+"' style='display:none;'>\
									  <param name='movie' value='https://www.youtube.com/v/"+parseJSON.data[i].text_add+"?controls=0&showinfo=0&version=3&autoplay=1'></param>\
									  <param name='allowFullScreen' value='true'></param>\
									  <param name='allowScriptAccess' value='always'></param>\
									  <embed src='https://www.youtube.com/v/"+parseJSON.data[i].text_add+"?showinfo=0&version=3&autoplay=1' type='application/x-shockwave-flash' allowfullscreen='true' allowScriptAccess='always' width='336' height='252'></embed>\
									</object>\
								</div>";
						}else if(parseJSON.data[i].type == 3){
								$.ajax({
									url: "actions.php?type=getLink&l_id="+parseJSON.data[i].text_add,
									success: function(data){
										var parseJSON = $.parseJSON(data);
										xtra = "<div class='link-view'>\
											"+replaceURLWithHTMLLinks(parseJSON.data[0].link_content,parseJSON.data[0].link,13)+"\
										</div>";
									}
								});
						}

						var removeX = "";

						if(parseJSON.data[i].name.u_id == logId){
							removeX = "<div style='float:right;'><i class='icon-remove' onclick='removePosting("+parseJSON.data[i].id+")' rel='tooltip' title='Remove' data-placement='left' data-trigger='hover' style='cursor:pointer;'></i></div>";
						}else{
							removeX = "";
						}

						$(".feed-area").append("<!--<div style='position:relative; top:50px; font-size:50px; font-weight:bold; color:white;'>"+i+"("+parseJSON.data[i].id+")</div>--><div class='notif-i'>\
										<table border='0' width='100%'>\
											<tr>\
												<td valign='top' width='40px;'><img src='/usr_content/pics/"+parseJSON.data[i].name.profile_pic+"_t.jpg' class='img-rounded' width='40px' height='40px'><img src='/data/img/flag_red.png' style='margin-top:3px; display:block; margin-left:auto; margin-right:auto; position:relative; bottom:0;' rel='tooltip' class='flag-post' title='Flag' data-placement='bottom' data-trigger='hover'/></td>\
												<td style='padding-left:10px; font-size:12px; color:white;' valign='top'>"+removeX+"<b style='color:#ffff00;'><a  style='color:blue;' href='/?p=profile&id="+parseJSON.data[i].name.u_id+"'>"+((parseJSON.data[i].name.fname != undefined) ? parseJSON.data[i].name.fname : "")+""+((parseJSON.data[i].name.bname != undefined) ? parseJSON.data[i].name.bname : "")+""+((parseJSON.data[i].name.tname != undefined) ? parseJSON.data[i].name.tname : "")+" "+((parseJSON.data[i].name.lname != undefined) ? parseJSON.data[i].name.lname : "")+"</a></b>\
												<div class='text' style='color:black;'>"+parseJSON.data[i].text+"\
													"+xtra+"\
												</div>\
												<table border='0' width='100%'>\
													<tr>\
														<!--<td valign='top'>\
															<div class='comment' style='color:#ffff00;'><div><span class='comment"+parseJSON.data[i].id+"'></span> <span style='display:none;' class='comment-hidden"+parseJSON.data[i].id+"'></span></div><a class='comment-load"+parseJSON.data[i].id+"' style='display:none;' href='javascript:loadMore("+parseJSON.data[i].id+");'></a><textarea class='comment-area-show"+parseJSON.data[i].id+"' type='text' placeholder='Comment...' style='resize:none; display:none; height:30px; font-size:12px; width:100%; margin-top:3px;' /></textarea><button class='btn btn-mini btncustom comment-area-show-button"+parseJSON.data[i].id+"' style='color:black; float:right; display:none;' onclick='makeComment2("+parseJSON.data[i].id+");'>Comment</button></span>\
														</td>-->\
														<td valign='bottom' align='middle'>\
															<span style='font-size:12px;'>"+parseJSON.data[i].date+" ago</span>\
															<div class='btn-group'>\
																<button onclick='clap("+parseJSON.data[i].id+");' class='btn btn-small user_type btncustom btn-clap' rel='tooltip' title='Clap' data-placement='top' data-trigger='hover'><img src='http://i.imm.io/14rOO.png' width='15px' height='15px' style='position:relative; bottom:2px;'/> <span style='color:#2727ff; font-weight:700;' class='clap"+parseJSON.data[i].id+"'>0</span></button>\
																<button onclick='showComment("+parseJSON.data[i].id+");' style='height:26px;' class='btn btn-small user_type btncustom btn-respond' rel='tooltip' title='Respond' data-placement='top' data-trigger='hover'><img src='http://i.imm.io/14rOG.png' width='20px' height='20px' style='position:relative; bottom:2px;'/></button>\
															</div>\
														</td>\
													</tr>\
												</table>\
												</td>\
											</tr>\
										</table>\
									</div>");

							grabComments2(parseJSON.data[i].id);
							getClaps(parseJSON.data[i].id);
						}
					}
				}
				$(".feed-area").fadeIn('fast');
				$(".feed-area").fadeIn('fast');

			  $(".user_type").tooltip('toggle');
			  $(".user_type").tooltip('hide');
			  $(".flag-post").tooltip('toggle');
			  $(".flag-post").tooltip('hide');
			  $(".btn-clap").tooltip('toggle');
			  $(".btn-clap").tooltip('hide');
			  $(".btn-respond").tooltip('toggle');
			  $(".btn-respond").tooltip('hide');
			  $(".btn-remove").tooltip('toggle');
			  $(".btn-remove").tooltip('hide');
		}
	  });
}

function loadTab(s){
	$(".loading-area-top").show();
	$(".content-area").load("tab_templates/"+s,function(){
		$(".loading-area-top").hide();
	});
	if(s == "tab_myfavs_standard.inc"){
		$(".fact-content").attr("class","fact-content gradient");
	}else{
		$(".fact-content").attr("class","fact-content");
	}
}

function changePostExtra(num){
	if(num != -1){
		$(".post-extra").show();
		$(".post-extra-remove").show();
		var classes = [];
		classes[0] = "photo";
		classes[1] = "album";
		classes[2] = "video";
		classes[3] = "link";
		for(i = 0;i < 4;i++){
			if(num == i){
				$("."+classes[i]).show();
				eval("get"+i+"()");
			}else{
				$("."+classes[i]).hide();
			}
		}
	}else{
		$(".post-extra").hide();
		$(".post-extra-remove").hide();
		$(".selected-item").hide();
		contId = "";
		contType = 0;
	}
}

var contId = "";
var contType = 0;

function getURLPhoto(){
	$.ajax({
		url: "uploadifive.php?url="+$(".photo-url").val(),
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					setContent(parseJSON.data,1);
					$(".post-extra").hide();
					$(".post-extra-remove").hide();
					$(".photo-url").val("");
				}
			}else{
				alert("There was an error posting your photo from the given URL.");
			}
		}
  });
}

function submitLinkPosting(){
	$(document).ready(function(){
		if( ($(".submitLinkTitle").val() != "") && ($(".submitLinkURL").val() != "") ){
			$.ajaxSetup({async:false});
			var actionUrl = "actions.php?type=addLink";
			$.post(
				actionUrl,
				{
					link: $(".submitLinkTitle").val(),
					link_content: $(".submitLinkURL").val()
				},
				function(data,status){
					var parseJSON = $.parseJSON(data);
					if(parseJSON.status != "error"){
						setContent(parseJSON.data,3);
					}else{
						if(parseJSON.status_msg != "")
							alert(parseJSON.status_msg);
						alert("Spuzik was not able to add your link.");
					}
				}
			);
		}else{
			alert("You must fill out all fields.");
		}
	});
}

function createUploader() {
var uploader = new qq.FineUploader({
  element: document.getElementById('fine-uploader'),
  request: {
	endpoint: 'uploadifive.php'
  },
  text: {
	uploadButton: '<div><i class="icon-upload icon-white"></i> Upload Photo</div>',
	dragZone: 'Drag photo here.'
  },
  validation: {
  	itemLimit: 1,
  	allowedExtensions: ['jpeg', 'jpg', 'gif', 'png']
  },
  template: '<div class="qq-uploader" width="100%;">' +
			  '<pre class="qq-upload-drop-area" width="100%;"><span>{dragZoneText}</span></pre>' +
			  '<div class="qq-upload-button btn btn-success" style="width: auto;">{uploadButtonText}</div><br />' +
			  '<span class="qq-drop-processing"><span>{dropProcessingText}</span><span class="qq-drop-processing-spinner"></span></span>' +
			  '<div style="width:215px;"><ul class="qq-upload-list" style="margin-top: 10px; list-style:none; color:black;"></ul></div>' +
			'</div>',
  classes: {
	success: 'alert alert-success',
	fail: 'alert alert-error'
  }
});
}

//photos
function get0(){
	$.ajax({
		url: "actions.php?type=getPhotos&uid="+logId,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					$(".photo").empty();
					$(".photo").append("<table border='0' cellpadding='0' cellspacing='0' width='100%;'>\
						<tr>\
							<td width='50%;'><span style='color:black; text-size:16px; font-weight:bold;'>Upload photo</span></td>\
							<td width='50%;'><span style='color:black; text-size:16px; font-weight:bold;'>Grab photo</span></td>\
						</tr>\
						<tr>\
							<td>\
								<div id='fine-uploader'></div>\
							</td>\
							<td valign='top'>\
								<input type='text' class='photo-url' placeholder='Photo URL...' style='height:25px; margin-top:5px;' /><button class='btn btn-small btn-primary' style='position:relative; bottom:3px; left:2px;' onclick='getURLPhoto();'><span style='color:yellow;'>Get photo</span></button>\
							</td>\
						</tr>\
					</table>\
					<span style='color:black; font-size:16px; font-weight:bold;'>Choose from existing...</span><br />");

					for(var i = 0;i < parseJSON.data.length;i++){
						var data_disp = "\'"+parseJSON.data[i]+"\'";
						$(".photo").append("<a href=\"javascript:setContent("+data_disp+",1);\"><img src='/usr_content/pics/"+parseJSON.data[i]+"_t.jpg' width='75px' /></a>");
					}
					//$(".photo").append("<br /><button href='?p=profile='"+logId+"'#tab_photosvideo_standard' class='btn btn-small btncustom'>Add Photo</button>");
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
  });
  createUploader();
}

//videos
function get2(){
	$.ajax({
		url: "actions.php?type=getVideos&uid="+logId,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				$(".video").empty();
				if(parseJSON.data != undefined){
					for(var i = 0;i < parseJSON.data.length;i++){
						var data_disp = "\'"+parseJSON.data[i]+"\'";
						$(".video").append("<a href=\"javascript:setContent("+data_disp+",2);\"><img src='http://i.ytimg.com/vi/"+parseJSON.data[i]+"/2.jpg' width='125px' /></a>");
					}
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
  });
}

//links
function get3(){
	$(document).ready(function(){
		$.ajax({
			url: "actions.php?type=getLinks&uid="+logId,
			success: function(data){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.length > 0){
					$(".post-extra .link").empty();
					$(".post-extra .link").append("<table border='0'>\
						<tr>\
							<td colspan='2'><span style='color:black; text-size:16px; font-weight:bold;'>Create new link</span></td>\
						</tr>\
						<tr>\
							<td><input type='text' class='submitLinkTitle' style='height:28px;' placeholder='Link title...' /></td>\
							<td></td>\
						</tr>\
						<tr>\
							<td><input type='text' class='submitLinkURL' style='height:28px;' placeholder='Link URL...' /></td>\
							<td align='left'><button class='btn btn-primary btn-small' onclick='submitLinkPosting();' style='position:relative; bottom:4px;'><span style='color:yellow;'>Create Link</span></button></td>\
						</tr>\
					</table>\
					<span style='color:black; font-size:16px; font-weight:bold;'>Choose from existing...</span><br />");
					for(var i = 0;i < parseJSON.length;i++){
						var data_disp = "\'"+parseJSON[i].id+"\'";
						$(".post-extra .link").append("<span style='color:black; text-decoration:underline; cursor:pointer;' onclick=\"setContent("+data_disp+",3);\">"+parseJSON[i].link+"</span><a target='ext' style='font-size:13px; margin-left:20px; font-weight:450; color:#156ed4;' href="+parseJSON[i].link_content+">Test Link</a><br />");
					}
				}
			}
		});
	});
}

function getLikePeople(){
	$(".feed-area").html("");
	$.ajax({
		url: "actions.php?type=grabLikeUsers",
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					for(var i = 0;i < parseJSON.data.length;i++){
						$(".feed-area").append("<div class='notif-i'>\
							<table border='0' width='100%;'>\
								<tr>\
									<td rowspan='3' width='60px;' valign='top'><img class='img-circle' style='width:50px; height:50px;'src='http://54.243.129.126/usr_content/pics/"+parseJSON.data[i][0].profile_pic+"_t.jpg' /></td>\
									<td><a style='color:blue; font-size:14px; font-weight:bold;' href='/?p=profile&u_id="+parseJSON.data[i][0].u_id+"'>"+parseJSON.data[i][0].fname+" "+parseJSON.data[i][0].lname+"</a></td>\
								</tr>\
								<tr>\
									<td style='padding:10px;'>\
										<span style='color:black; font-size:14px;'>\
										<i onclick='javascript:changeID([\""+parseJSON.data[i][2][0].y_id+"\",\""+parseJSON.data[i][2][0].name+"\",\""+parseJSON.data[i][2][0].album+"\",\""+parseJSON.data[i][2][0].artist+"\"])' class='icon-play' style='cursor:pointer;'></i></a>\
										"+parseJSON.data[i][2][0].name+"<br />\
										<i style='color:black;'>"+parseJSON.data[i][2][0].artist+"</i></span>\
									</td>\
								</tr>\
								<tr>\
									<td><span style='color:black; font-size:14px;'><img src='http://i.imm.io/1daFj.png' width='16px;' height='16px;' style='position:relative; bottom:1px; right:2px;'/>Suggested to you because of "+parseJSON.data[i][1]+"</span></td>\
								</tr>\
							</table>\
						</div>");
					}
				}
			}else{
				alert("There was an error grabbing your reccomendations.");
			}
		}
  });
}

function setContent(cId,type){
	contId = cId;
	contType = type;
	$(".selected-item").show();
	if(type == 1){ 			//photo asset
		$(".selected-item img").attr("src","http://54.243.129.126/usr_content/pics/"+cId+"_t.jpg");
	}else if(type == 3){	//link asset
		//get from database the link
		$.ajax({
			url: "actions.php?type=getLink&l_id="+cId,
			success: function(data){
				var parseJSON = $.parseJSON(data);
				$(".selected-item .link").show();
				$(".selected-item img").hide();
				$(".selected-item .link").html("<span style='color:blue; font-size:16px; font-weight:bold; position:relative; bottom:15px; left:16px; float:left;'>"+parseJSON.data[0].link+"</span>");
			}
		});
	}
	$(".post-extra").hide();
	$(".post-extra-remove").hide();
}

function addAppend(type,id){
	switch(type){
		case 0: //photo
			//Render photo detail area
			break;
		case 1: //album
			//Render album detail area
			break;
		case 2: //video
			//Render video detail area
			break;
		case 3: //link
			//Render link detail area
			loadLinks();
			break;
	}
}

var user_id = <?php echo $u_id; ?>;
<?php
$u2 = new User();
$userInfo2 = $u->userInfo($u_id);
?>
var profileSongID = <?php echo $userInfo2['profile_music'].";"; ?>
var logId = <?php echo $_SESSION['user_id'].";"; ?>
</script>
<div class='site-content'>
<table border="0" width="100%;" height="100%" cellpadding="0" cellspacing="0">
	<tr>
		<td colspan="3" height="65px;"></td>
	</tr>
	<tr>
		<td width="35%;" valign="top" class="feed" style="border-right:1px solid black;"><!-- #fc5a1e -->
			<div class="post-input" style="background:white; /* background-image:url('http://i44.tinypic.com/35ir4g7.png'); */ position:relative;">
				<div style='padding:5px;'>
					<div class='pick-cat' style='padding:10px; display:none;'>
						<span style='color:black; font-size:13px;'>What is this posting about?</span><br />
						<a style='color:blue; font-size:13px;' href='#' onclick='makePostingCats(1);'><img src='http://i.imm.io/1dbuU.png' width='20px;' height='20px;' />Sports &raquo;</a> <a style='color:blue; font-size:13px;' onclick='makePostingCats(2);' href='#'><img src='http://i.imm.io/1dbvx.png' width='20px;' height='20px;' />Music &raquo;</a>
					</div>
					<table class='post-adder' border="0" width="100%">
						<tr>
							<td><textarea style="width:100%; resize:none; border:1px solid black;" placeholder="Express yourself..." class="post-textbox"></textarea></td>
						</tr>
						<tr>
							<td>
								<div class='selected-item' style='display:none;'>
									<i class='icon-remove' onclick='changePostExtra(-1);' style='cursor:pointer;'></i>
									<img src='' width='60px;' />
									<div class='link' style='display:none;'></div>
								</div>
							</td>
						</tr>
						<tr>
							<td>
							<!--<button class="btny btn-primary" style="float:right;" onclick="makePosting();"><b style="color:blue; /* #0769d7 #FCDC3B */">Vent</b></button>-->
							<button class="btn btncustomblack" style="float:right; background-color:black;" onclick="makePosting();"><b style="color:yellow; /* #0769d7 #FCDC3B */">Vent</b></button>
							<div style='float:right; margin-right:5px; margin-top:5px;'>
								<a href="javascript:changePostExtra(0);" style="margin-left:10px;" class="icon-pic-up" rel="tooltip" title="Photo" data-placement="top" data-trigger="hover"><i class="icon-picture"></i></a>
								<!--<a href="javascript:changePostExtra(2);" style="margin-left:10px;" class="icon-film-up" rel="tooltip" title="Video" data-placement="top" data-trigger="hover"><i class="icon-film icon-film-up"></i></a>-->
								<a href="javascript:changePostExtra(3);" style="margin-left:10px;" class="icon-link-up" rel="tooltip" title="Link" data-placement="top" data-trigger="hover"><i class="icon-share"></i></a>
							</div>
							<!--<div>
								<div style='position:relative; bottom:0px;'><label style='font-size:13px; color:black;'><input type='radio' name='sportsCat' style='position:relative; bottom:4px;' /> Football</label></div>
								<div style='position:relative; bottom:5px;'><label style='font-size:13px; color:black;'><input type='radio' name='sportsCat' style='position:relative; bottom:4px;' /> Cricket</label></div>
								<div style='position:relative; bottom:10px;'><label style='font-size:13px; color:black;'><input type='radio' name='sportsCat' style='position:relative; bottom:4px;' /> Bowling</label></div>
							</div>-->
							<!--<img src="http://i.imm.io/1c2eL.png" width="16px;" height="16px;" onclick="repaintPostings();" style="cursor:pointer; margin-top:5px; margin-left:5px;" />-->
							</td>
						</tr>
						<tr>
							<td><a href="javascript:changePostExtra(-1);" style="float:right; display:none;" class="post-extra-remove"><i class="icon-remove"></i></a></td>
						</tr>
						<tr>
							<td>
								<div class="post-extra" style="display:none; background-color:yellow;">
									<div class="photo" style="display:none;"></div>
									<div class="video" style="display:none;"></div>
									<div class="link" style="display:none;"></div>
								</div>
							</td>
						</tr>
					</table>
				</div>
				<style type='text/css'>
				.tab-holder{

				}.tab-holder td{
					padding:5px;
					background-color:#179bff;
					color:white;
					-moz-border-top-right-radius:5px;
					-webkit-border-top-right-radius:5px;
					border-top-right-radius:5px;
					-moz-border-top-left-radius:5px;
					-webkit-border-top-left-radius:5px;
					border-top-left-radius:5px;
					cursor:pointer;
				}.tab-holder td:hover{
					background-color:red;
					color:white;
					font-weight:bold;
					-moz-border-top-right-radius:5px;
					-webkit-border-top-right-radius:5px;
					border-top-right-radius:5px;
					-moz-border-top-left-radius:5px;
					-webkit-border-top-left-radius:5px;
					border-top-left-radius:5px;
					cursor:pointer;
				}
				.media-type-tab{
					background-color:#173aff;
					-moz-border-top-right-radius:5px;
					-webkit-border-top-right-radius:5px;
					border-top-right-radius:5px;
					-moz-border-top-left-radius:5px;
					-webkit-border-top-left-radius:5px;
					border-top-left-radius:5px;
					padding:5px;
					width:100px;
				}.media-type-viewer{
					position:absolute;
					width:100px;
					z-index:1000;
					padding:5px;
					background-color:#173aff;
					-moz-border-bottom-left-radius:5px;
					-webkit-border-bottom-left-radius:5px;
					border-bottom-left-radius:5px;
					-moz-border-bottom-right-radius:5px;
					-webkit-border-bottom-right-radius:5px;
					border-bottom-right-radius:5px;
				}
				</style>
				<table width='100%' cellpadding='0' cellspacing='0' style='border-bottom:1px solid black;'>
					<tr>
						<td width="40px" align="center">
							<img src="http://i.imm.io/1c2eL.png" width="16px;" height="16px;" onclick="repaintPostings();" style="cursor:pointer; margin-top:5px; margin-left:5px;" />
						</td>
						<td>
							<table width='100%' class='tab-holder' border='0'>
								<tr>
									<td align='center' onclick='changePType(1);'><img src='http://i.imm.io/1dkAY.png' width='20px;' height='20px;' /></td>
									<td align='center' onclick='getLikePeople();'><img src='http://i.imm.io/1dkAN.png' width='20px;' height='20px;' /></td>
									<td align='center' onclick='changePType(2);'><img src='http://i.imm.io/1dkzn.png' width='20px;' height='20px;' /></td>
								</tr>
							</table>
						</td>
					</tr>
				</table>
			</div>
			<style type='text/css'>
			.feed-area{
				padding:5px;
				margin:5px;
				/*border:1px dashed grey;
				border-radius:5px;
				-moz-radius:5px;
				-webkit-radius:5px;*/
				border-top:1px solid white;
				border-bottom:1px solid white;
				text-align:center;
			}.feed-area p{
				color:white;
				margin-top:10px;
				font-size:16px;
			}
			</style>
			<div class="feed-area">
				<div class='feed-load-ind'>
					<center>
					<table border='0'>
						<tr>
							<td><img src='/data/img/load.gif' /></td>
							<td><p>Loading</p></td>
						</tr>
					</table>
					</center>
				</div>
            </div>
		</td>
		<td style="padding:0px; min-width:500px; border-right:1px solid white; background-color:white;" width="50%;" valign="top">
			<table border="0" width="100%;" height="100%;" cellspacing="0" cellpadding="0">
				<tr>
					<td height="400px;">
						<div class="img-cont" style="width:100%;" onclick='pause()'>
							<img class="init-image fix-w-img" src="http://www.dynamictherapies.com/images/Cleardot.GIF" />
						</div>
					</td>
				</tr>
				<tr>
					<td valign="top">
						<a class="scroll-area" href=""></a>
						<?php
						if($userInfo['type'] == 0){  //standard
							//$color = "#156ed4";
							$color = "#179bff";
							echo "<style type='text/css'>
							.tab-area a{
								text-decoration:none;
								color:yellow;
							}.tab-area a:hover{
								background-color:red;
								color:black !imporatant;
							}
							</style>";
						}else if($userInfo['type'] == 3){ //musician
							$color = "#156ed4";
							echo "<style type='text/css'>
							.tab-area a{
								text-decoration:none;
								color:yellow;
							}
							</style>";
						}else if($userInfo['type'] == 2){ //team
							$color = "#156ed4";
							echo "<style type='text/css'>
							.tab-area a{
								text-decoration:none;
								color:yellow;
							}
							</style>";
						}else if($userInfo['type'] == 5){ //agent
							$color = "#fc5a1e";
							echo "<style type='text/css'>
							.tab-area a{
								text-decoration:none;
								color:black;
							}
							</style>";
						}else if($userInfo['type'] == 1){ //athlete
							$color = "#156ed4";
							echo "<style type='text/css'>
							.tab-area a{
								text-decoration:none;
								color:yellow;
							}
							</style>";
						}else if($userInfo['type'] == 4){ //band
							$color = "#156ed4";
							echo "<style type='text/css'>
							.tab-area a{
								text-decoration:none;
								color:yellow;
							}
							</style>";
						}
						?>
						<div style="overflow:hidden; margin-top:-2px;">
						<div class="tab-scroll" style="padding:0px; background-color:<?php echo $color; ?>; display:none; padding-top:5px; position:relative;">
							<table border="0" width="100%" class="tab-area" valign="top" style='padding:0px;' cellspacing="0" cellpadding="0">
								<tr>
									<?php
									$tabContent = $u->tabContent($userInfo['type']);

									foreach($tabContent as $num=>$item){
										echo "<td align='center'>
											<a href=\"javascript:loadTab('".$item['tab_script']."');\">";
												echo "<div class='tab' style='color:white;'";
												if($num == 0){ echo "style='padding-left:11px;'"; }
												echo ">";
												//echo "<div class='tab'>";
												if($item['title'] == "Chat Zone"){
													echo $item['title']."<span class='badge badge-important chat-badge' style='background-color:red; color:white; font-size:12px; position:relative; bottom:2px; left:3px; display:none;'>!</span>";
												}else{
													echo $item['title'];
												}
												echo "</div>";
											echo "</a>
										</td>";
									}
									?>
								</tr>
							</table>
						</div>
						</div>

						<script type='text/javascript'>

						</script>
						<div class="fact-content">
							<span class="loading-area-top" style="margin-left:50%;">Loading...</span>
							<div class="content-area"></div>
						</div>
					</td>
				</tr>
			</table>
		</td>
		<td style="color:white; background-color:black;" valign="top">
			<table border="0" cellpadding="3" width="250px;" cellspacing="0" cellpadding="0">
				<tr>
					<?php
						if($u_id != $_SESSION['user_id']){
							echo '<td><button class="btn btn-mini btn-primary support-yes" type="button" onclick="support();" ><i class="icon-plus icon-white" style="position:relative; bottom:2px;"></i><span style="color:yellow;">Support</span></button>';
						}else{
							echo '<td>';
						}
					?>
					</td>
					<!--<td>
						<table border="0" style="margin-left:8px;" cellpadding="3" width="100%">
							<tr align="center">
								<td style="font-size:13px; color:white;">Fans</td>
								<td style="font-size:13px; color:white;">Supporting</td>
							</tr>
							<tr align="center">
								<td><a href="#myModal1" role="button" data-toggle="modal"><span style="color:red; font-weight:bold; /* #fa5c23 #FCDC3B */"><?php echo $u->getFansNumeric($u_id); ?></span></a></td>
								<td><a href="#myModal2" role="button" data-toggle="modal"><span style="color:red; font-weight:bold; /* #FCDC3B */"><?php echo $u->getSupportersNumeric($u_id); ?></span></a></td>
							</tr>

							<div id="myModal1" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
							  <div class="modal-header" style="background-color:#173aff;">
								<button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
								<h3 id="myModalLabel" style="color:yellow;">Fans</h3>
							  </div>
							  <div class="modal-body" style="background-color:#173aff;">
								<div style="width:100%;" class="user-fans"></div>
							  </div>
							  <div class="modal-footer" style="background-color:#173aff;">
								<button class="btn btn-primary" data-dismiss="modal" aria-hidden="true" style="color:yellow;">Close</button>
							  </div>
							</div>
							<div id="myModal2" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
							  <div class="modal-header" style="background-color:#173aff;">
								<button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
								<h3 id="myModalLabel" style="color:white;">Supporting</h3>
							  </div>
							  <div class="modal-body" style='background-color:#173aff;'>
								<div style="width:100%;" class="user-supporters"></div>
							  </div>
							  <div class="modal-footer" style="background-color:#173aff;">
								<button class="btn btn-primary" data-dismiss="modal" aria-hidden="true" style="color:yellow;">Close</button>
							  </div>
							</div>

						</table>
					</td>-->
				</tr>
				<tr align="right" style="border-top:1px solid white; border-bottom:1px solid white;">
					<!--<td colspan="2" align="center">
					<?php
					$text_type = "";
					$imgpath = "";
					switch(convertIntTypetoString($userInfo['type'])){
						case "general_user":
							$text_type = "Standard";
							$imgpath = "http://i.imm.io/OON6.png";
							break;
						case "musician_user":
							$text_type = "Musician";
							$imgpath = "http://i.imm.io/OON3.png";
							break;
						case "band_user":
							$text_type = "Band";
							$imgpath = "http://i.imm.io/OONt.png";
							break;
						case "athelete_user":
							$text_type = "Athelete";
							$imgpath = "http://i.imm.io/XaEd.png";
							break;
						case "team_user":
							$text_type = "Team";
							$imgpath = "http://i.imm.io/XcH8.png";
							break;
						case "agent_user":
							$text_type = "Agent";
							$imgpath = "http://i.imm.io/X5OY.png";
							break;
					}
					echo '<img class="user_type" rel="tooltip" title="'.$text_type.'" data-placement="left" data-trigger="hover" src="'.$imgpath.'" width="16" height="16" style="float:right;"/>';
					?>

					<b style="position:relative; left:5px; color:yellow;"><?php
						switch(convertIntTypeToString($userInfo['type'])){
							case "general_user":
							case "athelete_user":
							case "musician_user":
							case "agent_user":
								echo $userInfo['fname']." ".$userInfo['lname'];
								break;
							case "team_user":
								echo $userInfo['tname'];
								break;
							case "band_user":
								echo $userInfo['bname'];
								break;
						}
					?></b></td>-->
				</tr>
				<tr>
					<td colspan="2" valign="top" align="center">
					<style type="text/css">
						.selected-item{
							padding:10px;
							border:1px dashed black;
							-webkit-border-radius:5px;
							-moz-border-radius:5px;
							boder-radius:5px;
							margin-bottom:5px;
						}.lineup-list li{
							padding:2px 0px 2px 0px;
							color:white;
						}.lineup-list{
							list-style:none;
						}
						.qq-upload-list {
							text-align: left;
							margin-left:0px;
						}.qq-upload-list li{
							color:black;
						}
						li.alert-success {
							background-color: #DFF0D8;
						}
						li.alert-error {
							background-color: #F2DEDE;
						}
						.alert-error .qq-upload-failed-text {
							display: inline;
						}.qq-uploader{
							font-size:13px;
							color:black;
						}.qq-uploader a{
							color:blue;
						}
					</style>
					<script>
					//setInterval(blink, 710);
					function blink() {
						var elm = $(".donate-btn"),
						mycolor = elm.css('color');
						mycolor == 'rgb(0, 0, 0)' ? mycolor='transparent' : mycolor='rgb(0, 0, 0)';
						elm.animate({color: mycolor},300);
					}
					</script>
					<!-- DONATE -->
					<?php
						switch(convertIntTypeToString($userInfo['type'])){
							case "general_user":
							case "athelete_user":
							case "musician_user":
							case "agent_user":
								echo '<!--<img src="/usr_content/pics/'.$userInfo['profile_pic'].'_t.jpg" width="150" height="150" style="margin-right:5px; margin-top:15px; margin-bottom:10px; cursor:pointer;" class="img-circle" onclick="launchModal(0,\''.$userInfo['profile_pic'].'\');" />-->';
								break;
							case "team_user":
								//echo '<div class="img-container">';
								echo '<img src="/usr_content/pics/'.$userInfo['profile_pic'].'_t.jpg" width="120" height="120" style="margin-right:5px; width:100%;" onclick="launchModal(0,\"'+$userInfo['profile_pic']+'\");" />';
								//echo '</div>';
								echo '<div class="logo-cont"><img src="http://i.imgur.com/qKH7evc.gif" style="height:100px; margin-left:auto; margin-right:auto; display:block; margin-top:5px;"/></div>';
								break;
							case "band_user":
								//echo '<div class="img-container">';
								echo '<img src="/usr_content/pics/'.$userInfo['profile_pic'].'_t.jpg" width="95" height="100" style="margin-right:5px; width:100%;" onclick="launchModal(0,\"'+$userInfo['profile_pic']+'\");" />';
								break;
						}
						if($userInfo['type'] == 3 || $userInfo['type'] == 4)
							echo "<br /><br /><button class=\"btn btn-mini btn-success donate-btn\" style=\"color:white; text-decoration:blink;\"><i class=\"icon-gift icon-white\"></i> Donate</button>";
					?>
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<table border="0" width="100%">
							<tr>
								<!--<td style='padding-left:5px; padding-right:5px;'>
									<div class="def-status" style="font-size:15px; overflow:hidden; width:250px;"><i style="color:white;"><?php echo $userInfo['status']; ?></i></div>
									<div class="edit-status" style="font-size:15px; display:none;">
										<textarea style="width:100%; resize:none;" placeholder="Status update..." class="status-enter"></textarea>
									</div>
								</td>-->
							</tr>
							<tr align="right">
								<td style='padding-left:5px; padding-right:5px;'>
									<?php if($_SESSION['user_id'] == $u_id){ echo '<a class="status-1" href="#" style="font-size:12px; color:yellow;" onclick="status()">Update status</a>'; } ?>
									<a class="status-cancel" href="#" style="font-size:13px; display:none;" onclick="statusCancel()">Cancel</a>
									<button class="btn btn-warning btn-small status-save" style="display:none;" onclick="statusSubmit()">Save</button>
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</table>
			<?php
			if($userInfo['type'] != 2){
			echo "
			<div class='lineup' style='padding-top:10px; margin-top:-10px;'>
				<table border='0' width='100%;'>
					<tr>
						<th colspan='3'><div style='color:white;'>".$userInfo['fname'].$userInfo['bname'].$userInfo['tname']."'s Lineup</div></th>
					</tr>
					<tr>
						<td colspan='3'>
							<div class='lineup-enter' style='display:none; background-color:black;'>
								<table border='0' width='100%;'>
									<tr>
										<td valign='top'>
											<input type='text' class='fav-text' style='height:25px; border:1px solid black;' placeholder='Add a favorite...' />
										</td>
										<td valign='top'>
											<button class='btn btn-mini btncustomwhite' style='margin-top:1px; background-color:white;' onclick='javascript:addLineup();'><span style='color:#2727ff;'>Add</span></button>
										</td>
									</tr>
								</table>
							</div>
						</td>
					</tr>
					<tr>
						<td colspan='3' align='center' style='padding-bottom:15px;'><button class='btn btn-small btncustomwhite shufflebtn' onclick='randomFonts();' style='color:#2727ff; background-color:white;'><i class='icon-refresh'></i>Shuffle</button></td>
					</tr>
					<!--<tr>
						<td colspan='3'>
							<img src='http://54.243.129.126/usr_content/pics/50ff4359c6ec3_w.jpg' />
						</td>
					</tr>-->
					<tr>
						<td colspan='3'>
							<ul class='lineup-list'></ul>
						</td>
					</tr>
				</table>
			</div>";
			}else{
				echo "
				<style type='text/css'>
				.sponsor-imgs{
					border-bottom:1px dashed yellow;
					padding-bottom:10px;
				}.sponsor-imgs img{
					display:block;
					margin-right:auto;
					margin-left:auto;
				}.press{
					padding-top:5px;
					overflow:hidden;
					width:250px;
				}
				</style>
				<div class='sponsor-imgs'>
					<br /><center><span style='color:yellow; font-weight:bold; border-bottom:1px solid yellow;'>Sponsors</span></center><br />
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/logo-autonomy-hp-company.png' style='width:75%;'/>
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/logo-under-armour-new.png' style='width:75%;'/>
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/logo-investec-2012-2013-new.jpg' style='width:75%;'/>
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/logo-ea-sports1.png' style='width:75%;'/>
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/logo-carlsberg-new.png' style='width:75%;'/>
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/stubhub-ebay-company.jpg' style='width:75%;'/>
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/logo-thomas-cook-sport.png' style='width:75%;'/>
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/mbna.png' style='width:75%;'/>
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/betfred-com-98x55-new.jpg' style='width:75%;'/>
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/Fun88_logo_vector-new.gif' style='width:75%;'/>
					<img src='http://static.tottenhamhotspur.com//media/images/decorative/furniture/logos/logo-premier-league-new.png' style='width:75%;'/>
				</div>
				<div class='press'>
					<center><span style='color:yellow; font-weight:bold; border-bottom:1px solid yellow;'>Press</span></center><br />
					<ul style='font-size:15px; list-style:none;'>
					<li><a href='http://www.tottenhamhotspur.com'>www.tottenhamhotspur.com</a></li>
					<li><a href='http://www.bbc.com/sport/football/teams/tottenham-hotspur'>www.bbc.com/sport/football/teams/tottenham-hotspur</a></li>
					<li><a href='http://www.premierleague.com'>www.premierleague.com</a></li>
					<li><a href='http://www.tottenham-today.co.uk>www.tottenham-today.co.uk</a></li>
					<li><a href='http://www.spurs-web.com'>http://www.spurs-web.com</a></li>
					<li><a href='http://www.skysports.com'>www.skysports.com</a></li>
					</ul>
				</div>";
			}
			?>
		</td>
	</tr>
</table>

<script>

var pageId = 1;
var pageMAX = 0;

//page_id passed for the next infinite page passed.
function loadMoreContent(){
	if(pageId < pageMAX){
		repaintPostings(++pageId);
	}else{
		$(".ldmore").html("No more content");
	}
}

function grabPreferences(type){
	var returnArray = [];
	$.ajax({
		url: "actions.php?type=grabPreferences",
		success: function(data){
			var parseJSON = $.parseJSON(data);

			for(var i = 0;i < parseJSON.data.length;i++){
				if(parseJSON.data[i].type == type){  //sport or music
					returnArray.push([parseJSON.data[i].id, parseJSON.data[i].type, parseJSON.data[i].item]);
				}
			}
		}
	});
	return returnArray;
}

function pickCat(type){
	switch(type){
		case 0: //sports
			var preferences = grabPreferences(0);
			var cbxs = "<option value='-'>Select sport...</option>";

			for(var i = 0;i < preferences.length;i++){
				cbxs += "<option value='"+preferences[i][0]+"'>"+preferences[i][2]+"</option>";
			}
			cbxs += "<option value='-'>-----</option>";
			$.ajax({
				url: "actions.php?type=grabSports",
				success: function(data){
					var parseJSON = $.parseJSON(data);

					for(var i = 0;i < parseJSON.data.length;i++){
						var yep = true;
						for(var j = 0;j < preferences.length;j++){
							if(parseJSON.data[i].id == preferences[j][0]){
								yep = false;
							}
						}
						if(yep){
							cbxs += "<option value='"+parseJSON.data[i].id+"'>"+parseJSON.data[i].sport+"</option>";
						}
					}
				}
			});

			$(".pick-cat").html("<select width='100px' class='sport-sel'>"+cbxs+"</select><br /><a href='javascript:void(0);' onclick='pickCat(2);' style='font-size:13px; color:blue;'>&laquo; Back</a>");
			/*$(".sport-sel").change(function(){
				makePostingCats();
			});*/
			break;
		case 1:	//music
			var preferences = grabPreferences(1);
			var cbxs = "<option value='-'>Select genre...</option>";

			for(var i = 0;i < preferences.length;i++){
				cbxs += "<option value='"+preferences[i][0]+"'>"+preferences[i][2]+"</option>";
			}
			cbxs += "<option value='-'>-----</option>";
			$.ajax({
				url: "actions.php?type=grabGenres",
				success: function(data){
					var parseJSON = $.parseJSON(data);

					for(var i = 0;i < parseJSON.data.length;i++){
						var yep = true;
						for(var j = 0;j < preferences.length;j++){
							if(parseJSON.data[i].id == preferences[j][0]){
								yep = false;
							}
						}
						if(yep){
							cbxs += "<option value='"+parseJSON.data[i].id+"'>"+parseJSON.data[i].genre+"</option>";
						}
					}
				}
			});

			$(".pick-cat").html("<select width='100px' class='genre-sel'>"+cbxs+"</select><br /><a href='javascript:void(0);' onclick='pickCat(2);' style='font-size:13px; color:blue;'>&laquo; Back</a>");
			/*$(".genre-sel").change(function(){
				makePostingCats();
			});*/
			break;
		case 2: //orgin
			$(".pick-cat").html("<span style='color:black; font-size:13px;'>What is this posting about?</span><br />\
						<a style='color:blue; font-size:13px;' onclick='makePostingCats(1);' href='#'><img src='http://i.imm.io/1dbuU.png' width='20px;' height='20px;' />Sports &raquo;</a> <a style='color:blue; font-size:13px;' onclick='makePostingCats(2);' href='#'><img src='http://i.imm.io/1dbvx.png' width='20px;' height='20px;' />Music &raquo;</a>");
			break;
	}
}
</script>

<!-- Modal -->
<div id="myModal" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" style="height:80%; width:93%; margin-left:-47%;">
    <table border="0" width="100%" height="100%">
    	<tr>
    		<td style="background-color:black;" align="center" valign="center">
    		<div class="imgvid-content" style='width:100%; height:100%;'></div>
    		<img class="modal-img" style="display:none;" src="http://www.dynamictherapies.com/images/Cleardot.GIF" style="height:100%;" img-id=""/>
    		</td>
    		<td align="right" valign="top" width="300px;" style='background-color:yellow;'><button type="button" class="close" data-dismiss="modal" aria-hidden="true" onclick="removeModal()">×</button>
    			<div class="resource-content" style="color:black;">
    			<table border="0" style="margin:10px;" width="100%">
    				<tr>
    					<td rowspan="2" align="right" valign="top" width="50px;"><img class="profile-pic img-rounded" src="http://www.dynamictherapies.com/images/Cleardot.GIF" width="30px;" height="30px;" style="margin-right:5px;"/></td>
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
</div>