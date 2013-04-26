<?php
//include("header_bar.inc");
$u = new User();
$userInfo = $u->userInfo($_SESSION['user_id']);
?>
<!-- JAVASCRIPT -->
<script>

$(document).ready(function() {
	//$(".blink-area").css("height",$(this).parent().height());
	$(".blink-area").fadeIn(100).fadeOut(100).fadeIn(100).fadeOut(100);
	//grab notifications for the thoughstream via a 2 step mechanizm.
	grabNotifications("thoughtstream","unq-2");
	grabNotifications("myzone","unq-3");

	$(".notif-main-area").draggable();

	$(".unq-3").click(function(){
		$(".unq-3i").slideToggle("fast");
		$(".unq-3i").css("max-height",( $(window).height() - ($(".unq-3i").offset().top+12) ));
	});

	$(".unq-2").click(function(){
		$(".unq-2i").slideToggle("fast");
		$(".unq-2i").css("max-height",( $(window).height() - ($(".unq-2i").offset().top+12) ));
	});

	$(window).resize(function() {
		if(getURLParameter("p") == "notifications"){
			$(".unq-2i").css("max-height",( $(window).height() - ($(".unq-2i").offset().top+12) ));
			$(".unq-3i").css("max-height",( $(window).height() - ($(".unq-3i").offset().top+12) ));
		}
	});
});

function grabNotifications(type, className){
	$("."+className+"i").html("");

	//PRESENT NOTIFICATIONS
	$.ajax({
		url: "actions.php?type=grabNotifications&t="+type,
		success: function(data){
			var parseJSON = $.parseJSON(data);

			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					if(parseJSON.data.length > 0){
						$("."+className).html("<span style='color:yellow;'>"+parseJSON.data.length+"</span>");
						$("."+className+"i").html("<div style='width:100%; background-color:black; height:2px;'></div>");
						type = "\""+type+"\"";
						for(var i = 0;i < parseJSON.data.length;i++){
							var img_second = "";
							if(parseJSON.data[i].snapshot_mult !== "")
								img_second = "<img src='"+parseJSON.data[i].snapshot_mult+"' width='45px;' style='border:1px solid black;' />";
							$("."+className+"i").append("<div width='100%;' class='notif-p' onclick='grabPosting("+parseJSON.data[i].id+","+parseJSON.data[i].post_id+", "+type+");' style='border-bottom:2px solid black;'>\
								<table border='0' style='width:100%; font-size:13px; color:black;'>\
									<tr>\
										<td style='background-color:green;'><div class='blink-area' style='width:3px; height:1px;'></div></td>\
										<td width='55px;'>"+img_second+"</td>\
										<td style='color:black;'>"+parseJSON.data[i].snapshot+"</td>\
										<!--<td><i class='icon-chevron-right icon-black' style='position:relative; top:4px; right:3px;'></i></td>-->\
									</tr>\
								</table>\
							</div>");
						}
						//$("."+className+"i").append("<div style='width:100%; background-color:black; height:2px;'></div>");
					}else{
						$("."+className+"i").append("<div style='background-color:black; padding-top:5px; padding-bottom:5px;'>\
							<b style='color:#fc5a1e;'>Notifications empty.</b>\
						</div>");
					}
				}
			}else{
				alert("There was an error grabbing your notifications.");
			}
		}
	});

	//PAST NOTIFICATIONS
	$.ajax({
		url: "actions.php?type=grabPastNotifications&t="+type,
		success: function(data){
			var parseJSON = $.parseJSON(data);

			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					$("."+className+"i").append("<div style='border-bottom:1px dashed black; margin-top:10px;'><b style='color:black; font-size:16px;'>Past Notifications</b></div>");
					type = "\""+type+"\"";
					for(var i = 0;i < parseJSON.data.length;i++){
						var img_second = "";
						if(parseJSON.data[i].snapshot_mult !== "")
							img_second = "<img src='"+parseJSON.data[i].snapshot_mult+"' width='45px;' style='border:1px solid black; padding:2px;' />";

						$("."+className+"i").append("<div width='100%;' class='notif-p' onclick='grabPosting("+parseJSON.data[i].id+","+parseJSON.data[i].post_id+", "+type+");'>\
							<table border='0' style='width:100%; font-size:13px; color:black;'>\
								<tr>\
									<td width='55px;'>"+img_second+"</td>\
									<td style='color:black;'>"+parseJSON.data[i].snapshot+"</td>\
									<!--<td><i class='icon-chevron-right icon-black' style='position:relative; top:4px; right:3px;'></i></td>-->\
								</tr>\
							</table>\
						</div>");
					}
				}
			}else{
				alert("There was an error grabbing your notifications.");
			}
		}
	});
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
								trash = "<i onclick='deleteComment("+parseJSON.data[i].id+","+id+");' class='icon-trash'></i>";
							else
								trash = "";
							$(".comment"+id).append("<b style='margin-right:3px; color:black;'>"+parseJSON.data[i].name+"</b><span style='color:black;'>&nbsp;"+parseJSON.data[i].comment+"</span><span style='color:black; padding-left:5px;'>"+parseJSON.data[i].date+" ago</span>"+trash+"<br />");
						}
					}else{
						$(".comment-load"+id).show();
						$(".comment-load"+id).html((parseJSON.data.length-3)+" more comments");
						for(var i = 0;i < 3;i++){
							var trash = "";
							if(parseJSON.data[i].u_id == logId)
								trash = "<i onclick='deleteComment("+parseJSON.data[i].id+","+id+");' class='icon-trash'></i>";
							else
								trash = "";
							$(".comment"+id).append("<b style='margin-right:3px; color:black;'>"+parseJSON.data[i].name+"</b><span style='color:black;'>&nbsp;"+parseJSON.data[i].comment+"</span><span style='color:black; padding-left:5px;'>"+parseJSON.data[i].date+" ago</span>"+trash+"<br />");
						}
						for(var i = 3;i < parseJSON.data.length;i++){
							var trash = "";
							if(parseJSON.data[i].u_id == logId)
								trash = "<i onclick='deleteComment("+parseJSON.data[i].id+","+id+");' class='icon-trash'></i>";
							else
								trash = "";
							$(".comment-hidden"+id).append("<b style='margin-right:3px; color:black;'>"+parseJSON.data[i].name+"</b><span style='color:black;'>&nbsp;"+parseJSON.data[i].comment+"</span><span style='color:black; padding-left:5px;'>"+parseJSON.data[i].date+" ago</span>"+trash+"<br />");
						}
					}
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
	});
}

function markReadNotification(id){
	$.ajax("actions.php?type=markReadNotification&n_id="+id);
	grabNotifications("thoughtstream","unq-2");
	grabNotifications("myzone","unq-3");
}

//p_id - posting id
function grabPosting(id, p_id, type){
	var side = "";
	if(type == "thoughtstream")
		side = "left";
	else
		side = "right";

	$.ajax({
		url: "actions.php?type=grabPosting&p_id="+p_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);

			if(parseJSON.status != "error"){
				var xtra = "";
				if(parseJSON.data.post.type == 1){
					xtra = "<td colspan='2' align='center' style=\"background-image:url('http://i.imm.io/12aJO.jpeg');\">\
						<img onclick='launchModal(0,\""+parseJSON.data.post.text_add+"\");' src='http://54.243.129.126/usr_content/pics/"+parseJSON.data.post.text_add+"_w.jpg' style='cursor:pointer; height:200px;'/>\
					</td>";
				}else if(parseJSON.data.post.type == 2){
						xtra = "<td colspan='2' align='center' style=\"background-image:url('http://i.imm.io/12aJO.jpeg');\">\
						<div class='video-view' style='margin-top:0px;'>\
							<img src='http://i.imm.io/10NhZ.png' width='45px;' onclick='displayVideo("+parseJSON.data.post.id+");' class='vid-pic-play"+parseJSON.data.post.id+"' style='position:relative; cursor:pointer; top:75px; left:35px;'/>\
							<img class='vid-pic"+parseJSON.data.post.id+"' width='336' height='252' style='cursor:pointer; margin-left:auto; margin-top:-40px; margin-right:auto; display:block;' onclick='displayVideo("+parseJSON.data.post.id+");' src='http://img.youtube.com/vi/"+parseJSON.data.post.text_add+"/mqdefault.jpg' />\
							<object width='336' height='252' class='video"+parseJSON.data.post.id+"' style='display:none;'>\
							  <param name='movie' value='https://www.youtube.com/v/"+parseJSON.data.post.text_add+"?controls=0&showinfo=0&version=3&autoplay=1'></param>\
							  <param name='allowFullScreen' value='true'></param>\
							  <param name='allowScriptAccess' value='always'></param>\
							  <embed src='https://www.youtube.com/v/"+parseJSON.data.post.text_add+"?showinfo=0&version=3&autoplay=1' type='application/x-shockwave-flash' allowfullscreen='true' allowScriptAccess='always' width='336' height='252'></embed>\
							</object>\
						</div>\
						</td>";
				}else if(parseJSON.data.post.type == 3){
						$.ajax({
							url: "actions.php?type=getLink&l_id="+parseJSON.data.post.text_add,
							success: function(data){
								var parseJSON2 = $.parseJSON(data);

								if(parseJSON2.data[0].link_content != undefined){
									xtra = "<td colspan='2'>\
												<div class='link-view'>\
													"+replaceURLWithHTMLLinks(parseJSON2.data[0].link_content,parseJSON2.data[0].link,13)+"\
												</div>\
											</td>";
									}
							},
							async: false
						});
						$(".link-view a").css("color","yellow");
				}
				//alert(side);
				$("."+side+"-prev").show();
				$("."+side+"-prev").html("<div class=''>\
												<table border='0' width='100%'>\
													<tr>\
														<td colspan='2' style='color:black;'>\
															<div style='padding:10px;'>"+parseJSON.data.post.text+"</div>\
														</td>\
													</tr>\
													<tr>\
														"+xtra+"\
													</tr>\
													</tr>\
														<td>\
															<table border='0' width='100%'>\
																<tr>\
																	<td valign='top'>\
																		<div class='comment' style='color:#ffff00;'><div><span class='comment"+parseJSON.data.post.id+"'></span> <span style='display:none;' class='comment-hidden"+parseJSON.data.post.id+"'></span></div><a class='comment-load"+parseJSON.data.post.id+"' style='display:none; color:#2727ff;' href='javascript:loadMore("+parseJSON.data.post.id+");'></a><textarea class='comment-area-show"+parseJSON.data.post.id+"' type='text' placeholder='Comment...' style='resize:none; display:none; height:30px; font-size:12px; width:100%; margin-top:3px;' /></textarea><button class='btn btn-mini btncustom comment-area-show-button"+parseJSON.data.post.id+"' style='color:black; float:right; display:none;' onclick='makeComment2("+parseJSON.data.post.id+");'>Comment</button></span>\
																	</td>\
																	<td valign='bottom' align='right'>\
																		<span style='font-size:12px; color:black;'>"+parseJSON.data.post.date+" ago</span>\
																		<div class='btn-group'>\
																			<button onclick='clap("+parseJSON.data.post.id+");' class='btn btn-small user_type btncustom22 btn-clap' rel='tooltip' style='background-color:#fc5a1e;' title='Clap' data-placement='top' data-trigger='hover'><img src='http://i50.tinypic.com/2el9i7c.gif' width='15px' height='15px' style='position:relative; bottom:2px;'/> <span style='color:black;' class='clap"+parseJSON.data.post.id+"'>0</span></button>\
																			<button onclick='showComment("+parseJSON.data.post.id+");' style='height:26px; background-color:#fc5a1e;' class='btn btn-small user_type btncustom22 btn-respond' rel='tooltip' title='Respond' data-placement='top' data-trigger='hover'><i class='icon-comment'></i></button>\
																		</div>\
																	</td>\
																</tr>\
															</table>\
														</td>\
													</tr>\
												</table>\
											</div>");
				grabComments2(parseJSON.data.post.id);
				getClaps(parseJSON.data.post.id);
			}else{
				alert("There was an error grabbing your preview.");
			}
		}
	});
	markReadNotification(id);
}
</script>
<div class='site-content'>
<table border="0" width="100%;" height="100%">
	<tr>
		<td colspan="3" height="65px;"></td>
	</tr>
	<tr>
		<td>
			<table border="0" width="100%;" height="100%;">
				<tr>
					<td width="20%;" height="100%;" valign="top" align="middle" style='background-color:#2727ff; padding-top:60px;'>
						<a href="javascript:void(0);" onclick='switchPage("thoughtstream");'><img src="/data/img/q_mark.png" width="35px" height="35px" style="margin-top:10px;"/></a>
						<a href="javascript:void(0);" onclick='switchPage("thoughtstream");' style="text-decoration:none;"><h3 style="text-align:center; color:#f2f200;">Thoughtstream</h3></a>
						<div class="signup" style="overflow:auto; background-color:#fc5a1e;">
							<i class='icon-refresh' onclick='grabNotifications("thoughtstream","unq2");' style='cursor:pointer;'></i>
							<b style="color:black;">Notifications</b>
							<span class="badge badge-info unq-2" style="cursor:pointer; background-color:#2727ff; float:right;"><span style="color:yellow;">0</span></span>
							<div class="unq-2i" style="display:none; width:100%; max-height:300px; overflow:auto;"></div>
						</div>
					</td>
					<td width="30%;" height="100%;" valign="middle" align="left" >
						<div class='notif-prev left-prev' style='display:none;'>
						</div>
					</td>
					<td width="30%;" height="100%;" valign="middle" align="left" >
						<div class='notif-prev right-prev' style='display:none;'>
						</div>
					</td>
					<td width="20%;" height="100%;" valign="top" align="middle" style='background-color:#2727ff; padding-top:60px;'>
						<a href="javascript:void(0);" onclick='switchPage("profile");'>
						<?php
							$profPic = "/usr_content/pics/".$userInfo['profile_pic']."_t.jpg";
							echo "<img class='img-circle prof_pic' src='".$profPic."' width='65px' height='65px'  style='margin-top:10px;'/>";
						?>
						</a>
						<a href="javascript:void(0);" onclick='switchPage("profile");' style="text-decoration:none;"><h3 style="text-align:center; color:#f2f200;">My Zone</h3></a><!-- FCDC3B -->
						<div class="signup" style="overflow:auto; background-color:#fc5a1e;">
							<i class='icon-refresh' onclick='grabNotifications("thoughtstream","unq3");' style='cursor:pointer;'></i>
							<b style="color:black;">Notifications</b>
							<span class="badge badge-info unq-3" style="cursor:pointer; background-color:#2727ff; float:right;"><span style="color:yellow;">0</span></span>
							<div class="unq-3i" style="display:none; width:100%; max-height:300px; overflow:auto;"></div>
						</div>
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>
</div>
<!-- STYLES -->
<style type="text/css">
.chat{
	margin-left:10px;
	float:left;
	position:relative;
	width:200px;
	background-color:#0769d7;
}
.chat .people .person{
	border-bottom:1px dashed white;
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
}.notif-p{
	border-bottom:1px dashed black;
	color:black;
	font-size:13;
	cursor:pointer;
	/*border-bottom:1px solid #CCC;*/
}.notif-p:hover{
	background-color:#F7F7F7;
}.notif-p .icon-chevron-right{
    float:right;
}.notif-p img{
	/*border:1px solid black;*/
	margin:1px;
}.notif-main-area{
	/*display:block;
	margin-left:0px;
	margin-right:0px;*/
	/*text-align:center;*/
	margin-top:-28px;
	margin-left:28%;
}.notif-main-area-alerts{
	background-color:#0769d7;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
	border:0px solid #000;
}.musicp{
	position:absolute;
	bottom:5px;
	margin-left:600px;
}.notif-prev{
	background-color:yellow;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
	border:0px solid #000;
	padding:5px;
	color:black;
	font-size:13px;
}.link-view{
	background-color:#2727ff;
}.link-view a{
	color:yellow;
}
</style>