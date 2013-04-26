<script>

var logId = <?php echo $_SESSION['user_id'].";"; ?>

$(document).ready(function() {
	setTimeout(function(){
		init();
	},10);
});

function init(){
	$(".type1").tooltip('toggle');
	$(".type1").tooltip('hide');
	$(".type2").tooltip('toggle');
	$(".type2").tooltip('hide');
	$(".type3").tooltip('toggle');
	$(".type3").tooltip('hide');
	$(".type4").tooltip('toggle');
	$(".type4").tooltip('hide');
	$(".type5").tooltip('toggle');
	$(".type5").tooltip('hide');
	$(".type6").tooltip('toggle');
	$(".type6").tooltip('hide');
	var amt = 0;
	setInterval(function(){
		//alert(amt);
		doit(amt);
		amt++;
	},5000);
	repaintPostings(0);

	loadRecs();

	var pageId = 1;
	var pageMAX = 0;
	var contId = "";
	var contType = 0;

	$(".comment-tbox").elastic();

	$(window).scroll(function(){
		if($(window).scrollTop() == $(document).height() - $(window).height()){
			loadMoreContent();
		}
	});
}

Array.prototype.shuffle = function() {
   var i = this.length;
   while (--i) {
	  var j = Math.floor(Math.random() * (i + 1))
	  var temp = this[i];
	  this[i] = this[j];
	  this[j] = temp;
   }

   return this; // for convenience, in case we want a reference to the array
};

function doit(num){
	$("."+num+"-item").show("slide", { direction: "up" }, 1000);
}

function expandInput(){
	$(".pop-large").attr('style','height:400px;');
	$(".express-tbox").attr('style','height:100px; resize:none; margin-left:10px;');
	$(".remove-btn").show();
	$(".action-icons").hide();
	$(".action-icons-real").show();
}

function condenseInput(){
	$(".pop-large").attr('style','height:47px;');
	$(".express-tbox").attr('style','height:30px; resize:none; margin-left:10px;');
	$(".remove-btn").hide();
	$(".action-icons-real").hide();
	$(".selected-item").hide();
	$(".action-icons").show();
}

/*
	IMPORTANT FUNCTIONS FOR THE THOUGHT STREAM POSTING
*/

//photos
function get0(){
	$.ajax({
		url: "actions.php?type=getPhotos&uid="+logId,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					$(".photo").empty();
					for(var i = 0;i < parseJSON.data.length;i++){
						var data_disp = "\'"+parseJSON.data[i]+"\'";
						$(".photo").append("<a href=\"javascript:setContent("+data_disp+",1);\"><img src='/usr_content/pics/"+parseJSON.data[i]+"_t.jpg' width='50px' /></a>");
					}
					//$(".photo").append("<br /><button href='?p=profile='"+logId+"'#tab_photosvideo_standard' class='btn btn-small btncustom'>Add Photo</button>");
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
  });
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
					for(var i = 0;i < parseJSON.length;i++){
						var data_disp = "\'"+parseJSON[i].id+"\'";
						$(".post-extra .link").append("<span style='color:yellow; text-decoration:underline; cursor:pointer;' onclick=\"setContent("+data_disp+",3);\">"+parseJSON[i].link+"</span><a target='ext' style='font-size:13px; margin-left:20px; font-weight:450; color:yellow;' href="+parseJSON[i].link_content+">Test Link</a><br />");
					}
				}
			}
		});
	});
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
				post_type: 1
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					//Add posting to post list
					$(".post-textbox").val("");
					repaintPostings(0);
					contId = "";
					contType = 0;
					$(".item-selected").hide();
					condenseInput();
				}
			}
		);
	});
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
		url: "actions.php?type=grabThoughtstream&p_id="+p_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			pageMAX = parseJSON.amt;
			if(parseJSON.status != "error"){
			    if(p_id == 0){
					$(".stream1").fadeOut('fast');
					$(".stream1").empty();
					$(".stream2").fadeOut('fast');
					$(".stream2").empty();
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
									var parseJSON2 = $.parseJSON(data);

									if(parseJSON2.data[0].link_content != undefined){
										xtra = "<div class='link-view'>\
												"+replaceURLWithHTMLLinks(parseJSON2.data[0].link_content,parseJSON2.data[0].link,13)+"\
											</div>";
									}
								},
								async: false
							});
							$(".link-view").css("background-color","yellow");
							$(".link-view a").css("color","#2727ff");
						}
						if(i%2==0){
							$(".stream1").append("<div class='notif-i'>\
												<table border='0' width='100%'>\
													<tr>\
														<td valign='top' width='40px;'><img src='/usr_content/pics/"+parseJSON.data[i].name.profile_pic+"_t.jpg' class='img-rounded' width='40px' height='40px'><img src='/data/img/flag_red.png' style='margin-top:3px; display:block; margin-left:auto; margin-right:auto;' rel='tooltip' class='flag-post' title='Flag' data-placement='bottom' data-trigger='hover'/></td>\
														<td style='padding-left:10px; font-size:12px; color:white;' valign='top'><div style='float:right;'><img src='/data/img/remove.png' onclick='removePosting("+parseJSON.data[i].id+")' rel='tooltip' title='Remove' data-placement='left' data-trigger='hover' style='width:12px; height:12px;'/></div><b style='color:#ffff00;'><a  style='color:#ffff33;' href='/?p=profile&id="+parseJSON.data[i].name.u_id+"'>"+((parseJSON.data[i].name.fname != undefined) ? parseJSON.data[i].name.fname : "")+""+((parseJSON.data[i].name.bname != undefined) ? parseJSON.data[i].name.bname : "")+""+((parseJSON.data[i].name.tname != undefined) ? parseJSON.data[i].name.tname : "")+" "+((parseJSON.data[i].name.lname != undefined) ? parseJSON.data[i].name.lname : "")+"</a></b>\
														<div class='text'>"+( parseJSON.data[i].type != 3 ? parseJSON.data[i].text : "")+"\
															"+xtra+"\
														</div>\
														<table border='0' width='100%'>\
															<tr>\
																<td valign='top'>\
																	<div class='comment' style='color:#ffff00;'><div><span class='comment"+parseJSON.data[i].id+"'></span> <span style='display:none;' class='comment-hidden"+parseJSON.data[i].id+"'></span></div><a class='comment-load"+parseJSON.data[i].id+"' style='display:none;' href='javascript:loadMore("+parseJSON.data[i].id+");'></a><textarea class='comment-area-show"+parseJSON.data[i].id+"' type='text' placeholder='Comment...' style='resize:none; display:none; height:30px; font-size:12px; width:100%; margin-top:3px;' /></textarea><button class='btn btn-mini btncustom comment-area-show-button"+parseJSON.data[i].id+"' style='color:black; float:right; display:none;' onclick='makeComment2("+parseJSON.data[i].id+");'>Comment</button></span>\
																</td>\
																<td valign='bottom' align='right'>\
																	<span style='font-size:12px;'>"+parseJSON.data[i].date+" ago</span>\
																	<div class='btn-group'>\
																		<button onclick='clap("+parseJSON.data[i].id+");' class='btn btn-small user_type btncustom btn-clap' rel='tooltip' title='Clap' data-placement='top' data-trigger='hover'><img src='http://i.imm.io/1454y.png' width='15px' height='15px' style='position:relative; bottom:2px;'/> <span style='color:black;' class='clap"+parseJSON.data[i].id+"'>0</span></button>\
																		<button onclick='showComment("+parseJSON.data[i].id+");' style='height:26px;' class='btn btn-small user_type btncustom btn-respond' rel='tooltip' title='Respond' data-placement='top' data-trigger='hover'><img src='http://i.imm.io/1454a.png' width='20px' height='20px' style='position:relative; bottom:2px;'/></button>\
																	</div>\
																</td>\
															</tr>\
														</table>\
														</td>\
													</tr>\
												</table>\
											</div>");
						}else{
							$(".stream2").append("<div class='notif-i'>\
												<table border='0' width='100%'>\
													<tr>\
														<td valign='top' width='40px;'><img src='/usr_content/pics/"+parseJSON.data[i].name.profile_pic+"_t.jpg' class='img-rounded' width='40px' height='40px'><img src='/data/img/flag_red.png' style='margin-top:3px; display:block; margin-left:auto; margin-right:auto;' rel='tooltip' class='flag-post' title='Flag' data-placement='bottom' data-trigger='hover'/></td>\
														<td style='padding-left:10px; font-size:12px; color:white;' valign='top'><div style='float:right;'><img src='/data/img/remove.png' onclick='removePosting("+parseJSON.data[i].id+")' rel='tooltip' title='Remove' data-placement='left' data-trigger='hover' style='width:12px; height:12px;'/></div><b style='color:#ffff00;'><a style='color:#ffff33;' href='/?p=profile&id="+parseJSON.data[i].name.u_id+"'>"+((parseJSON.data[i].name.fname != undefined) ? parseJSON.data[i].name.fname : "")+""+((parseJSON.data[i].name.bname != undefined) ? parseJSON.data[i].name.bname : "")+""+((parseJSON.data[i].name.tname != undefined) ? parseJSON.data[i].name.tname : "")+" "+((parseJSON.data[i].name.lname != undefined) ? parseJSON.data[i].name.lname : "")+"</a></b>\
														<div class='text'>"+( parseJSON.data[i].type != 3 ? parseJSON.data[i].text : "")+"\
															"+xtra+"\
														</div>\
														<table border='0' width='100%'>\
															<tr>\
																<td valign='top'>\
																	<div class='comment' style='color:#ffff00;'><div><span class='comment"+parseJSON.data[i].id+"'></span> <span style='display:none;' class='comment-hidden"+parseJSON.data[i].id+"'></span></div><a class='comment-load"+parseJSON.data[i].id+"' style='display:none;' href='javascript:loadMore("+parseJSON.data[i].id+");'></a><textarea class='comment-area-show"+parseJSON.data[i].id+"' type='text' placeholder='Comment...' style='resize:none; display:none; height:30px; font-size:12px; width:100%; margin-top:3px;' /></textarea><button class='btn btn-mini btncustom comment-area-show-button"+parseJSON.data[i].id+"' style='color:black; float:right; display:none;' onclick='makeComment2("+parseJSON.data[i].id+");'>Comment</button></span>\
																</td>\
																<td valign='bottom' align='right'>\
																	<span style='font-size:12px;'>"+parseJSON.data[i].date+" ago</span>\
																	<div class='btn-group'>\
																		<button onclick='clap("+parseJSON.data[i].id+");' class='btn btn-small user_type btncustom btn-clap' rel='tooltip' title='Clap' data-placement='top' data-trigger='hover'><img src='http://i.imm.io/1454y.png' width='15px' height='15px' style='position:relative; bottom:2px;'/> <span style='color:black;' class='clap"+parseJSON.data[i].id+"'>0</span></button>\
																		<button onclick='showComment("+parseJSON.data[i].id+");' style='height:26px;' class='btn btn-small user_type btncustom btn-respond' rel='tooltip' title='Respond' data-placement='top' data-trigger='hover'><img src='http://i.imm.io/1454a.png' width='20px' height='20px' style='position:relative; bottom:2px;'/></button>\
																	</div>\
																</td>\
															</tr>\
														</table>\
														</td>\
													</tr>\
												</table>\
											</div>");
						}
						grabComments2(parseJSON.data[i].id);
						getClaps(parseJSON.data[i].id);
					}
				}
				$(".stream1").fadeIn('fast');
				$(".stream2").fadeIn('fast');
			}else{
				alert("There was an error populating the postings.");
			}
		}
	  });

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

function showComment(id){
	$(".comment-area-show"+id).slideToggle();
	$(".comment-area-show"+id).elastic();
	$(".comment-area-show-button"+id).slideToggle();
}

function makeComment2(id){
	if( $(".comment-area-show"+id).val() !== "" ){
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

//page_id passed for the next infinite page passed.
function loadMoreContent(){
	if(pageId < pageMAX){
		repaintPostings(++pageId);
	}else{
		$(".ldmore").html("No more content");
	}
}

function loadRecs(){
	$.ajax({
		url: "actions.php?type=recs",
		success: function(data){
			var parseJSON = $.parseJSON(data);

			for(var i = 0;i < parseJSON.data.length;i++){

				var name = "";

				if(parseJSON.data[i].fname != undefined){
					name = parseJSON.data[i].fname+" "+parseJSON.data[i].lname;
				}else if(parseJSON.data[i].tname != undefined){
					name = parseJSON.data[i].tname;
				}else if(parseJSON.data[i].bname != undefined){
					name = parseJSON.data[i].bname;
				}


				var image = "";
				//if(parseJSON.data[i].profile_pic != "")
					image = "<img class='fix-w-img' src='http://54.243.129.126/usr_content/pics/"+parseJSON.data[i].profile_pic+"_t.jpg' />";

				$(".rec-feed-area").append("<div class='notif-i' style='width:300px;'>\
									<table border='0' width='300px;'>\
										<tr>\
											<td style='padding-left:10px; font-size:12px; color:white;' valign='top'><center><img src='http://54.243.129.126/usr_content/pics/"+parseJSON.data[i].profile_pic+"_t.jpg' class='img-rounded' width='25' height='25' style='margin-right:5px;' /><a href='javascript:void();' onclick=\"switchPage('profile',[{'key':'id','val':"+parseJSON.data[i].u_id+"}]);\"><b style='color:#ffff33; color:#2727ff; font-size:16px;'>"+name+"</b></a></center><br /></b><br />\
												<table border='0' width='100%;'>\
													<tr>\
														<td width='125px;'>\
															<div style='width:125px; height:125px; overflow:hidden;'>"+image+"</div>\
														</td>\
														<td valign='top'>\
															<table border='0' width='100%;'>\
																<tr>\
																	<td>\
																		<table border='0' width='100%;'>\
																			<tr>\
																				<td align='middle'>\
																					<span style='font-size:14px; color:#2727ff; font-size:15px; font-weight:500;'>Fans</span>\
																				</td>\
																				<td align='middle'>\
																					<span style='font-size:14px; color:#2727ff; font-size:15px; font-weight:500;'>Supporting</span>\
																				</td>\
																			</tr>\
																			<tr>\
																				<td align='middle'>\
																					<span style='color:red; font-size:14px;'>"+parseJSON.data[i].fans+"</span>\
																				</td>\
																				<td align='middle'>\
																					<span style='color:red; font-size:14px;'>"+parseJSON.data[i].supporters+"</span>\
																				</td>\
																			</tr>\
																		</table>\
																	</td>\
																</tr>\
																<tr>\
																	<td>\
																		<div style='padding:10px;'>\
																			<div style='padding:10px; -moz-border-radius:5px; border:0px solid #000; -webkit-border-radius:5px; border-radius:5px; background-color:rgba(190,190,190,.1);'>\
																				<span style='font-size:13px; color:#2727ff; font-weight:500;'>"+parseJSON.data[i].status+"</span>\
																			</div>\
																		</div>\
																	</td>\
																</tr>\
															</table>\
														</td>\
													</tr>\
												</table>\
											<br /><br />\
											<table border='0' width='100%'>\
												<tr>\
													<td valign='top' align='center'>\
														<button class='btn btn-mini btnbluelight' style='color:yellow;' type='button'><i class='icon-plus icon-white' style='position:relative; bottom:3px;'></i> Support</button>\
													</td>\
												</tr>\
											</table>\
											</td>\
										</tr>\
									</table>\
								</div>");
			}
		}
	});
}

function miniSlideshow(id){
	$.ajax({
		url: "actions.php?type=getPhotos&uid="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.data != undefined){
				parseJSON.data.shuffle();
				$(".init-image-mini"+id).attr("src","/usr_content/pics/"+parseJSON.data[0]+"_s.jpg");
			}

			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					for(var i = 1;i < parseJSON.data.length;i++){
						$(".img-cont-mini"+id).append("<img class='fix-w-img' src='/usr_content/pics/"+parseJSON.data[i]+"_s.jpg' />");
					}
					//$(".photo-ctr-mini").html(parseJSON.data.length);
					$('.img-cont-mini'+id).cycle({
						fx: 'fade',
						timeout: 20
					});
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
	});
}
</script>

<div class='site-content'>
<table border="0" width="100%;" height="100%">
	<tr>
		<td colspan="3" height="65px;"></td>
	</tr>
	<tr>
		<td valign="top">
			<table border="0" width="100%;" height="100%;">
				<tr>
					<td width="28%;" style="height:30px; border-bottom:1px dashed #fbd515; background-color:#2727ff;" ><!-- background-color:#063d78; -->
						<table border="0" style="float:left; padding-top:5px; padding-left:5px;" width="100%;">
							<tr>
								<td valign="center" align="left">
									<!-- white globe: http://i.imm.io/Nxd2.png http://i.imm.io/NxaO.png  -->
									<img src="http://i.imm.io/13XIk.png" width="40px;" height="40px;" /><b style="position:relative; top:2px; left:3px; color:white;">Recommendations</b>
								</td>
							</tr>
						</table>
					</td>
					<td colspan="2" style="border-bottom:1px dashed #fbd515; border-left:2px solid #fbd515; /*background-color:#063d78;*/ background-color:#2727ff;/*purple #800020*/;">
						<table border="0" style="float:right; padding-top:5px; padding-right:5px;" width="100%;">
							<tr>
								<td valign="center" align="left">
									<img src="/data/img/yellow_refresh.png" width="16px;" height="16px;" onclick="repaintPostings(0);" style="cursor:pointer; margin-top:5px; margin-left:5px;" /><b style="position:relative; top:2px; left:3px; color:white; /*#ffa500 #fad416*/;">Thoughts</b>
								</td>
								<td valign="center" height='45px;' align="right" style="padding-right:20px; padding-left:10px;">
									<style type='text/css'>
									.pop-large{
										position:fixed;
										top:66px;
										right:0px;
										background-color:#2727ff; /*purple #800020*/;
										padding-right:10px;
										padding-left:10px;
										z-index:1000;
									}.ldmore{
										background-color:#063d78;
										padding:5px;
										color:yellow;
										text-align:center;
									}
									</style>
									<div class='pop-large' style="height:47px;">
										<i class='icon-remove icon-white remove-btn' onclick='condenseInput();' style='cursor:pointer; display:none;'></i>
										<table border='0' style='position:relative; top:10px;'>
											<tr>
												<td valign='middle'>
													<div class='action-icons'>
														<a href="javascript:expandInput();" style="margin-left:10px;"><i class="icon-picture icon-white"></i></a><a href="javascript:expandInput();" style="margin-left:10px;"><i class="icon-film icon-white"></i></a><a href="javascript:expandInput();" style="margin-left:10px;"><i class="icon-edit icon-white"></i></a>
													</div>
												</td>
												<td>
													<textarea placeholder="Express yourself..." class='express-tbox post-textbox' style="resize:none; height:30px; margin-left:10px;" onfocus='expandInput();' ></textarea>
												</td>
												<td valign='top'>
													<button class="btn btn-primary btncustom" style='margin-left:5px; background-color:#ffff1a;' onclick='makePosting();'><b style="color:#2727ff;">Vent</b></button>
												</td>
											</tr>
											<tr>
												<td colspan="3">
													<div class='action-icons-real' style='display:none;'>
														<a href="javascript:changePostExtra(0);" style="margin-left:10px;"><i class="icon-picture icon-white" ></i></a><a href="javascript:changePostExtra(2);" style="margin-left:10px;"><i class="icon-film icon-white" ></i></a><a href="javascript:changePostExtra(3);" style="margin-left:10px;"><i class="icon-edit icon-white"></i></a>
														<div class="post-extra" style="display:none; width:260px; max-height:200px; overflow:scroll;">
															<div class="photo" style="display:none;"></div>
															<div class="video" style="display:none;"></div>
															<div class="link" style="display:none;"></div>
														</div>
														<span style="float:left; margin-left:10px; font-size:13px; color:white; display:none;" class="selected-item">Item selected</span>
													</div>
												</td>
											</tr>
										</table>
									</div>
								</td>
							</tr>
						</table>
					</td>
				</tr>
				<tr>
					<!-- PUBLIC COLUMN AREA #1 -->
					<td width="20%;" valign="top" style='background-color:#ffff15;'>
						<!--<div style="background-color:yellow; padding-top:5px; width:100%; padding-bottom:5px;">
							<center><b style="position:relative; top:2px; left:3px; color:black;">Recommendations</b></center>
							<table border="0" width="100%;" class="tab-area" style="margin-bottom:10px; display:none;">
								<tr>
									<td align="center">
										<a href="#">
											<div class="tab type1" rel="tooltip" title="Standard" data-placement="top" data-trigger="hover">
												<img src="http://i49.tinypic.com/30bh02h.png" width="20px;" height="20px;" />
											</div>
										</a>
									</td>
									<td align="center">
										<a href="#">
											<div class="tab type2" rel="tooltip" title="Networks" data-placement="top" data-trigger="hover">
												<img src="http://cdn1.iconfinder.com/data/icons/devine_icons/128/PNG/System%20and%20Internet/Network%20Setting.png" width="20px;" height="20px;" />
												<img src="http://i47.tinypic.com/21dj0c3.png" width="20px;" height="20px;" />
											</div>
										</a>
									</td>
									<td align="center">
										<a href="#">
											<div class="tab type3" rel="tooltip" title="Athelete" data-placement="top" data-trigger="hover">
												<img src="http://i46.tinypic.com/29xuhbm.png" width="20px;" height="20px;" />
											</div>
										</a>
									</td>
									<td align="center">
										<a href="#">
											<div class="tab type4" rel="tooltip" title="Team" data-placement="top" data-trigger="hover">
												<img src="http://i46.tinypic.com/racknc.png" width="20px;" height="20px;" />
											</div>
										</a>
									</td>
									<td align="center">
										<a href="#">
											<div class="tab type5" rel="tooltip" title="Muscian" data-placement="top" data-trigger="hover">
												<img src="http://i47.tinypic.com/2cqifj7.png" width="20px;" height="20px;" />
											</div>
										</a>
									</td>
									<td align="center">
										<a href="#">
											<div class="tab type6" rel="tooltip" title="Band" data-placement="top" data-trigger="hover">
												<img src="http://i50.tinypic.com/2lic02p.gif" width="20px;" height="20px;" />
											</div>
										</a>
									</td>
									<td align="center">
										<a href="#">
											<div class="tab type6" rel="tooltip" title="Agent" data-placement="top" data-trigger="hover">
												<img src="http://i50.tinypic.com/1pbdzr.gif" width="20px;" height="20px;" />
											</div>
										</a>
									</td>
								</tr>
							</table>
						</div>-->
						<div class="rec-feed-area"> <!-- REC FEED -->
						</div>
					</td>
					<!-- PRIVATE COLUMN AREA #1 -->
					<td width="40%;" style="border-left:2px solid #fbd515; padding-right:10px; padding-left:10px;" valign="top">
						<div class='stream1'></div>
						<div class='load-more1 ldmore'>Loading...</div>
					</td>
					<!-- PRIVATE COLUMN AREA #2 -->
					<td width="40%;" style="border-left:2px solid #fbd515; padding-left:10px; padding-right:10px;" valign="top">
						<div class='stream2'></div>
						<div class='load-more2 ldmore'>Loading...</div>
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>

<!-- Modal -->
<div id="myModal" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true" style="height:80%; width:93%; margin-left:-47%;">
    <table border="0" width="100%" height="100%">
    	<tr>
    		<td style="background-color:black;" align="center" valign="center">
    		<div class="imgvid-content" style='width:100%; height:100%;'></div>
    		<img class="modal-img" style="display:none;" src="" style="height:100%;" img-id=""/>
    		</td>
    		<td align="right" valign="top" width="300px;" style='background-color:yellow;'><button type="button" class="close" data-dismiss="modal" aria-hidden="true" onclick="removeModal()">×</button>
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
    				var user_id = <?php echo $_SESSION['user_id'].";"; ?>
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
	border-bottom:1px solid black;
	padding-top:3px;
	padding-bottom:3px;
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
	color:#003F87;
}.tab-area .tab:hover{
	background-color:#EEE;
	color:black;
}.btncustom2{
	background-image: -webkit-linear-gradient(top,#ff0000,#b10000);
	background-image: -o-linear-gradient(top,#ff0000,#b10000);
	background-image: -moz-linear-gradient(top,#ff0000,#b10000);
}.btncustom2:hover{
	background-color:#b10000;
}.rec-feed-area{
	padding-left:5px;
	padding-right:5px;
}.post-extra{
	background-color:rgba(255,255,255,.4);
	margin-top:5px;
	margin-bottom:5px;
	padding:10px;
	-moz-border-radius:5px;
	-webkit-border-radius:5px;
	border-radius:5px;
	border:0px solid #000;
	max-height:300px;
	overflow:scroll;
}.post-extra .album .album-extra{
	border-style:none;
}.post-extra .album-indv{
	margin:3px;
	padding:3px;
	border:0px solid #000;
}.post-extra .album-indv:hover{
	padding:3px;
	background-color:rgba(255,255,255,.4);
}.post-extra .album-indv b.album-title{
	color:white;
	text-decoration:none;
}.post-extra{
	max-height:350px;
}.post-extra .photo img{
	border-style:none;
	margin:2px;
}.post-extra .photo img:hover{
	margin:0px;
	border:2px solid yellow;
}.video-view iframe{
	/*margin-left:auto;
	margin-right:auto;
	display:block;*/
}.post-extra .video img{
	border-style:none;
	margin:2px;
}.post-extra .video img:hover{
	margin:0px;
	border:2px solid yellow;
}.post-input{
	border-bottom:2px solid white;
	margin-bottom:5px;
}.feed-area .comment{
	font-size:12px;
}.video-info{
	background-color:rgba(255,255,255,.4);
	padding:5px;
	-moz-border-radius:3px;
	-webkit-border-radius:3px;
	border-radius:3px;
	width:300px;
}.feed-area{
	padding:5px;
}.text{
	font-size:14px;
	padding-top:5px;
	padding-bottom:5px;
}.ex-img{
	margin-top:10px;
	/*background-color:rgba(255,255,255,.4);*/
}.ex-img img{
	width:250px;
	margin-left:14%;
	margin-right:auto;
	display:block;
}.album-view{
	margin-top:10px;
}.post-type{
	margin-top:5px;
	float:right;
}.btncustom22{
	background-image: -webkit-linear-gradient(top,#fc6c37,#fc5a1e);
	background-image: -moz-linear-gradient(top,#fc6c37,#fc5a1e);
	background-image: -o-linear-gradient(top,#fc6c37,#fc5a1e)
}.btncustom22:hover{
	background-color:#fc5a1e;
}.btncustom{
	background-image: -webkit-linear-gradient(top,#ffff1a,#ffff67);
	background-image: -moz-linear-gradient(top,#ffff1a,#ffff67);
	background-image: -o-linear-gradient(top,#ffff1a,#ffff67);
}.btncustom:hover{
	background-color:#ffff1a;
}.resource-content{
	margin-left:20px;
}.image-comments{
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