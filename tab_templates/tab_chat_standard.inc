<style type="text/css">
.header-txt{
	font-size:18px;
	color:yellow;
	font-weight:bold;
	border-bottom:1px dashed yellow;
}.name{
	float:right;
	color:yellow;
}.msg{
	color:yellow;
}.msg-cont{
	width:100%;
}.msg-cont th{
	color:yellow;
	background-color:#fc5a1e;
	border-bottom:1px dashed yellow;
}.msg-cont .name{
	color:yellow;
	float:left;
	margin-right:5px;
	font-weight:bold;
}.msg-cont td{
	font-size:13px;
	color:white;
}.msg-cont .time{
	color:black;
	float:right;
}.name-item img{
	float:left;
	width:40px;
	height:40px;
}.name-item .txt{
	float:left;
	font-size:14px;
	margin-left:5px;
	color:yellow;
}.msg-cont .invitation{
	color:black;
	background-color:yellow;
	padding:10px;
	-moz-border-radius:5px;
	-webkit-border-radius:5px;
	border-radius:5px;
	border:0px solid #000;
	margin-bottom:10px;
	margin-top:10px;
}.chatbox{
	resize:none;
	bottom:0px;
	width:100%;
	margin-top:10px;
}.chat-area{
	border-bottom:1px solid white;
	max-height:400px;
	overflow:auto;
}.chat-item{
	padding:5px 0px 5px 0px;
	border-bottom:1px dashed #3188eb;
}.name-item:hover{
	background-color:#3188eb;
}
</style>
<script>
function addChat(){
	if($(".chatbox").val() != ""){
		$.ajaxSetup({async:false});
		//alert($(".chatbox").val()+" "+$(".chatbox").attr("u2id"));
		var actionUrl = "actions.php?type=addChat";
		$.post(
			actionUrl,
			{
				msg: $(".chatbox").val(),
				u2:  $(".chatbox").attr("u2id")
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					//Add posting to post list
					var d = new Date();
					var day = d.getHours();

					var ampm = "am";
					if(d.getHours() > 12){
						day = day - 12;
						ampm = "pm";
					}
					$(".container-clip").append("<div class='chat-item'>\
													<i style='color:white; float:right;'>"+day+":"+d.getMinutes()+""+ampm+"</i><span style='color:white;'><b style='color:yellow; margin-right:3px;'>Me</b>"+$(".chatbox").val()+"</span>\
											</div>");
					$(".chatbox").val("");
					$(".chatbox").select();
				}
			}
		);
	}else{
		alert("Please enter text.");
	}
	$('.chat-area').animate({scrollTop: $('.container-clip').height()}, 100);
}

function getChatUsers(/*type*/){ //type must be equal to 0 for regular users, and 1 for chat rooms consisting of groups of users.&type="+type
	 $.ajax({
			url: "actions.php?type=getChatUsers",
			success: function(data){
				var parseJSON = $.parseJSON(data);

				for(var i = 0;i < parseJSON.data.length;i++){
					if(parseJSON.data[i].u_id != undefined){
						if(logId != parseJSON.data[i].u_id){
							var name = "";
							var fname = "";
							switch(parseInt(parseJSON.data[i].type)){
								case 0:
								case 1:
								case 3:
								case 5:
									name = parseJSON.data[i].fname+" "+parseJSON.data[i].lname;
									fname = parseJSON.data[i].fname;
									break;
								case 2:
									name = parseJSON.data[i].tname;
									fname = name;
									break;
								case 4:
									name = parseJSON.data[i].bname;
									fname = name;
									break;
							}
							var name_disp = "\'"+name+"\'";
							var fname_disp = "\'"+fname+"\'";
							var online = "";

							switch(parseJSON.data[i].online){
								case 0: //online
									online = "<img style='float:right; width:25px; height:25px;' src='http://cdn4.iconfinder.com/data/icons/spirit20/bullet-green-alt.png' />";
									//online = "<div style='width:5px; float:left; height:20px; background-color:#00b300; margin-right:2px;'></div>";
									break;
								case 1: //idle 5 mins offline
									online = "<img style='float:right; width:25px; height:25px;' src='http://cdn4.iconfinder.com/data/icons/spirit20/bullet-orange-alt.png' />";
									//online = "<div style='width:5px; float:left; height:20px; background-color:#ffa500; margin-right:2px;'></div>";
									break;
								case 2: //not
									//online = "<div style='width:5px; float:left; height:20px; margin-right:2px;'></div>";
									break;
							}
							//$(".name-holder").append("<div class='name-item'>"+online+"<a href=\"javascript:chatWith("+parseJSON.data[i].u_id+","+name_disp+","+fname_disp+");\"><!--<span class='badge badge-important' style='color:white; float:left; background-color:red;'>!</span>--><span style='color:yellow;'>"+name+"</span><img style='float:right;' src='http://cdn1.iconfinder.com/data/icons/silk2/emoticon_smile.png' /><img class='img-circle' src='/usr_content/pics/"+parseJSON.data[i].profile_pic+"_t.jpg' /></a></div>");
							$(".name-holder").append("<div class='name-item'>\
								<a href=\"javascript:chatWith("+parseJSON.data[i].u_id+","+name_disp+","+fname_disp+");\">\
								<table border='0' width='100%'>\
								<tr>\
									<td width='40px;'><img class='img-rounded' src='http://54.243.129.126/usr_content/pics/"+parseJSON.data[i].profile_pic+"_t.jpg' /></td>\
									<td>"+(parseJSON.data[i].alert > 0 ? "<span class='badge badge-important chat-alert-notif"+parseJSON.data[i].u_id+"' style='background-color:red; color:white; float:right;'>"+parseJSON.data[i].alert+"</span>" : "" )+" "+online+"<span class='txt'>"+name+"</span></td>\
									<td></td>\
								</tr>\
							</table>\
							</a></div>");
							$(".selection-area").append("<li>\
								<li><label><input type='checkbox' name='members[]' style='position:relative; bottom:3px; right:2px;' value='"+parseJSON.data[i].u_id+"'/>"+name+"</label></li>\
							</li>");
						}
					}
				}
			}
	  });
}

var refreshIntervalId = null;

function chatWith(id,name,fname){
	clearInterval(refreshIntervalId);
	$(".chat-user").html(name).hide();
	$(".chat-user").show('slide', {direction: 'left'}, 1000);
	$(".chatbox").attr("u2id",id);
	$(".chat-alert-notif"+id).hide();
	grabChats(id, fname);
	refreshIntervalId = setInterval(function(){ checkChat(id, fname); /*grabChats(id, fname);*/ },500);
}

var chatRoomArray = [];

$(document).ready(function(){
	getChatrooms(user_id);
	showNotifications();
	getChatUsers();
	getAllChatrooms(user_id);
	if(user_id != logId){
		$(".btn-group-top").hide();
	}
});

function checkChat(id, fname){
	$.ajax({
		url: "actions.php?type=checkChat&u_id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);

			//There has been an update, display it onto the chat area.
			if(parseJSON.data != undefined){
				if(parseJSON.data.length > 0){
					$(".container-clip").append("<div class='chat-item'>\
														<i style='color:white; float:right;'>"+parseJSON.data[0].date+"</i><span style='color:white;'><b style='color:yellow; margin-right:3px;'>"+((parseJSON.data[0].who == 0) ? "Me" : fname)+"</b>"+parseJSON.data[0].msg+"</span>\
												</div>");
					markCheckChat(id);
					$('.chat-area').animate({scrollTop: $('.container-clip').height()}, 100);
					PlaySound();
				}
			}
		}
	});
}

function PlaySound() {
    var snd = new Audio("/data/qrecord.wav");
	snd.play();
}

function markCheckChat(id){
	$.ajax({
		url: "actions.php?type=markCheckChat&u_id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);

			//There has been an update, display it onto the chat area.
			if(parseJSON.status == "success"){
				//include function to remove alert from the right of the name of the indivdual.
			}
		}
	});
}

function grabChats(id,fname){
	$(".indv-chat-edit").show();
	markCheckChat(id);
	$.ajax({
		url: "actions.php?type=grabChats&id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			$(".chat-area").empty();
			$(".chat-area").html("<div class='container-clip'></div>");
			if(parseJSON != undefined){
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".container-clip").append("<div class='chat-item'>\
														<i style='color:white; float:right;'>"+parseJSON.data[i].date+"</i><span style='color:white;'><b style='color:yellow; margin-right:3px;'>"+((parseJSON.data[i].who == 0) ? "Me" : fname)+"</b>"+parseJSON.data[i].msg+"</span>\
												</div>");
				}
			}
		}
	});
	//$(".chat-area").attr({ scrollBottom: $(".chat-area").attr("scrollHeight") });
	//$('.chat-area').animate({scrollTop: $('.container-clip').height()}, 100);
	$(".chat-area").scrollTop($(".chat-area").height());
}

function makeChat(){
	$(".chat-area").append("<div class='chat-item'><span class='name'>Me</span> This is another comment testing for appending. <span class='time'>4:34 pm</span></div>");
}

function loadChatRooms(){
	$(".group-cont").show();
	$(".indv-chat").hide();
}

function loadIndv(){
	$(".indv-chat").show();
	$(".group-cont").hide();
}

function grabCheckboxArea(field){
	var allVals = [];
	$(field+' :checked').each(function() {
		allVals.push($(this).val());
	});
	return allVals;
}

function createChatroom(){
	if($(".croom-name").val() != ""){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=createChatroom";
		$.post(
			actionUrl,
			{
				title: $(".croom-name").val(),
				perms:  $(".croom-privacy").val(),
				photo_url: $(".croom-photourl").val(),
				members: grabCheckboxArea(".selection-area")
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					//Chatroom was created.
					alert("Chatroom created");
					$(".croom-name").val("");
					$(".croom-photourl").val("");
					$(".selected-area li").attr("checked",false);
				}
			}
		);
	}
}

function loadChatroomEdit(id){ //grabs the chatroom, with the users and their corresponding statuses
	$.ajax({
		url: "actions.php?type=getChatroom&u_id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON != undefined){
				$(".croom-img").attr("src",parseJSON.data.info.photo_url);
				$(".croom-name").html(parseJSON.data.info.title);
				$(".croom-privacy2").html((parseJSON.data.info.perms == "0" ? "Public <i class='icon-globe icon-white'></i>" : "Private <i class='icon-lock icon-white'></i>"));
				if(parseJSON.data.info.perms == "0"){
					$(".croom-requests").hide();
				}else{
					$(".croom-requests").show();
				}
				// Don't need this, because it is not shown to users.
				//$(".croom-memnum").html(parseJSON.data.users.length);
				$(".croom-date").html(parseJSON.data.info.date);
				$(".croom-name").attr("cid",id);

				//for all members
				$(".croom-members").empty();
				$(".croom-members").append("<tr>\
												<td style='font-weight:bold;'>Name</td>\
												<td style='font-weight:bold;'>Status</td>\
												<td style='font-weight:bold;'>Actions</td>\
												<td style='font-weight:bold;'>Joined</td>\
											</tr>");

				for(var j = 0;j < parseJSON.data.users.length;j++){
					//if(parseJSON.data.users[i].user_info != "null"){
						var status = "<span style='color:white'>--</span>";
						var date = parseJSON.data.users[j].date;

						var name = "";

						switch(parseInt(parseJSON.data.users[j].user_info.type)){
							case 0:
							case 1:
							case 3:
							case 5:
								name = parseJSON.data.users[j].user_info.fname+" "+parseJSON.data.users[j].user_info.lname;
								break;
							case 2:
								name = parseJSON.data.users[j].user_info.tname;
								break;
							case 4:
								name = parseJSON.data.users[j].user_info.bname;
								break;
						}

						if(parseInt(parseJSON.data.users[j].status) <= 3){
							switch(parseInt(parseJSON.data.users[j].status)){
								case 0: //pending
									status = "<span style='color:orange;'>Pending</span>";
									date = "<i>Waiting for confirmation</i>";
									break;
								case 1: //active
									status = "<span style='color:#00cc00;'>Active</span>";
									break;
								case 2: //blocked
									status = "<span style='color:red;'>Blocked</span>";
									break;
								case 3: //denied
									status = "<span style='background-color:red; color:white; padding:2px;'>Denied</span>";
									break;
							}

							$(".croom-members tr:last").after("<tr>\
								<td>"+name+"</td>\
								<td>"+status+"</td>\
								<td align='center'><i class='icon-trash icon-white' style='cursor:pointer;' onclick='deleteUser("+parseJSON.data.users[j].user_info.u_id+","+id+");'></i></td>\
								<td>"+date+"</td>\
							</tr>");
						}else{
							$(".croom-members-request tr:last").after("<tr>\
								<td>"+name+"</td>\
								<td><span style='color:orange;'>Pending</span></td>\
								<td align='center'><i class='icon-trash icon-white' style='cursor:pointer;' onclick='deleteUser("+parseJSON.data.users[j].user_info.u_id+","+id+");'></i></td>\
								<td><button class='btn btn-mini btn-success' onclick='verify("+parseJSON.data.users[j].user_info.u_id+","+id+");'>Verify</button></td>\
							</tr>");
						}
					//}
				}
			}
		}
	});
}

function getChatrooms(id){
	$.ajax({
		url: "actions.php?type=getChatrooms&u_id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON != undefined){
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".chatroom-list").append("<li>\
													<a href='javascript:void(0);' onclick='loadChatroomEdit("+parseJSON.data[i].id+");' style='color:white; font-size:16px;'>"+parseJSON.data[i].title+"</a><div style='height:40px; overflow:hidden;'>\
												</li>");
				}
			}
		}
	});
}

function removeFromChatroom(c_id){ //croom id passed here
	$.post("actions.php?type=removeFromChatroom&c_id="+c_id);
	$(".croomtr"+c_id).hide();
}

function getAllChatrooms(id){
	$.ajax({
		url: "actions.php?type=getAllChatrooms&u_id="+id,
		success: function(data){
			var addedList = [];
			var parseJSON = $.parseJSON(data);
			if(parseJSON != undefined){
				$(".chatrooms").html("");
				$(".chatrooms").html("<table border='0' width='100%;'>\
					<tr><td width='42%;'></td><td width='58%;'></td></tr>\
				</table>");
				for(var i = 0;i < parseJSON.data.length;i++){
					if($.inArray(parseJSON.data[i].id,addedList) == -1){
						addedList.push(parseJSON.data[i].id);
						var name = "";
						if(parseJSON.data[i].user_info.type != undefined){
							switch(parseInt(parseJSON.data[i].user_info.type)){
								case 0:
								case 1:
								case 3:
								case 5:
									name = parseJSON.data[i].user_info.fname+" "+parseJSON.data[i].user_info.lname;
									break;
								case 2:
									name = parseJSON.data[i].user_info.tname;
									break;
								case 4:
									name = parseJSON.data[i].user_info.bname;
									break;
							}
						}
						chatRoomArray.push(parseJSON.data[i].id);
						var join = "";
						if(user_id != logId){
							join = "<button style='float:right; color:black;' class='btn btn-small btn-warning' onclick='joinChatroom("+parseJSON.data[i].id+")'><i class='icon-plus'></i> Join</button>";
						}

						var photo = "";
						if(parseJSON.data[i].photo_url != "")
							photo = "<img src='"+parseJSON.data[i].photo_url+"' width='100px'/>";
						else
							photo = "<img src='https://mail.google.com/mail/images/cleardot.gif' width='100px;'/>";

						var removeX = "";
						if(parseJSON.data[i].u_id != logId)
							removeX = "<img onclick='removeFromChatroom("+parseJSON.data[i].id+");' src='http://cdn1.iconfinder.com/data/icons/aspneticons_v1.0_Nov2006/delete_16x16.gif' width='16px;' style='margin-right:15px; cursor:pointer;'/>";

						$(".chatrooms tr:last").after("<tr class='croomtr"+parseJSON.data[i].id+"'>\
														<td width='80px;' style='padding-left:25px;' align='right' valign='middle'>"+removeX+""+photo+"</td>\
														<td style='cursor:pointer;' onmouseover='slideBig("+parseJSON.data[i].id+");' onclick='showBig("+parseJSON.data[i].id+");'><span style='font-size:25px;'>"+parseJSON.data[i].title+"</span>\
															<div class='bigcroom"+parseJSON.data[i].id+"' style='display:none;'>\
																<span style='color:yellow; font-size:15px;'>"+parseJSON.data[i].num_users+" members</span>\
																<span style='color:#00cc00;'><i class='icon-user icon-white'></i> "+name+"</span>\
																<span style='color:white; fonts-size:15px;'>"+( parseJSON.data[i].perms == 1 ? "<i class='icon-lock icon-white'></i> Private" : "<i class='icon-globe icon-white'></i> Public")+"</span>\
															</div>\
															"+join+"\
														</td>\
													</tr>");
					}
				}
			}
		}
	});
}

function slideBig(id){
	for(var i = 0;i < chatRoomArray.length;i++){
		if(id != chatRoomArray[i]){
			$(".bigcroom"+chatRoomArray[i]).slideUp();
		}else{
			$(".bigcroom"+id).slideDown();
		}
	}
}

var refreshIntervalId2 = null;

function showBig(id){
	$(document).ready(function(){
		clearInterval(refreshIntervalId2);
		$(".msg-cont").hide();
		$(".croom").show();
		slideIn();
		loadCroomIndv(id);
		grabChatroomChats(id);
		refreshIntervalId2 = setInterval(function(){ updateChatChatroom(id); },500);
	});
}

function closeBig(){
	$(".msg-cont").show();
	$(".croom").hide();
}

function showNotifications(){
	$.ajax({
		url: "actions.php?type=grabChatroomNotifications",
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON != undefined){
				$(".notifications-holder").empty();
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".notifications-holder").append("<div class='invitation' style='background-color:#fc5a1e;'>\
													Would you like to join "+parseJSON.data[i].info[0].title+" chat room?<br />\
													<button class='btn btn-mini btn-success' type='button' style='color:white; margin-right:5px;' onclick='decideChatroom("+parseJSON.data[i].c_id+","+parseJSON.data[i].m_id+",0);'>Yes</button><button class='btn btn-mini btn-danger' type='button' style='color:white;' onclick='decideChatroom("+parseJSON.data[i].c_id+","+parseJSON.data[i].m_id+",1);'>No</button>\
												</div>");
				}
			}
		}
	});
}

function decideChatroom(c_id, u_id, type){ //c_id is the chatroom id and u_id is the user id
	if(type != null){
		switch(type){
			case 0: //confirm
				$.post("actions.php?type=decideChatroom&u_id="+u_id+"&c_id="+c_id+"&ctype=1");
				break;
			case 1: //declined
				$.post("actions.php?type=decideChatroom&u_id="+u_id+"&c_id="+c_id+"&ctype=3");
				break;
		}
		showNotifications();
	}
}

function slideIn(){
	$(".chatroom-title").show('slide', {direction: 'right'}, 1000);
}

function loadCroomIndv(id){
	$.ajax({
		url: "actions.php?type=getChatroom&u_id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON != undefined){
				//for(var i = 0;i < parseJSON.data.length;i++){
				$(".chatroom-title").html(parseJSON.data.info.title);
				$(".chatroom-text").attr("cid",id);
				$(".chatroom-pic").attr("src",parseJSON.data.info.photo_url);
				$(".user-container").empty();

				//append the admin onto the top of the list of users.
				var name = "";
				switch(parseInt(parseJSON.data.info.admin.type)){
					case 0:
					case 1:
					case 3:
					case 5:
						name = parseJSON.data.info.admin.fname+" "+parseJSON.data.info.admin.lname;
						break;
					case 2:
						name = parseJSON.data.info.admin.tname;
						break;
					case 4:
						name = parseJSON.data.info.admin.bname;
						break;
				}
				var online = "";

				switch(parseJSON.data.info.admin.online){
					case 0: //online
						online = "<img style='float:right; width:25px; height:25px;' src='http://cdn4.iconfinder.com/data/icons/spirit20/bullet-green-alt.png' />";
						break;
					case 1: //idle 5 mins offline
						online = "<img style='float:right; width:25px; height:25px;' src='http://cdn4.iconfinder.com/data/icons/spirit20/bullet-orange-alt.png' />";
						break;
					case 2: //not
						break;
				}

				$(".user-container").append("<div class='user'>\
									"+online+"<img class='img-rounded' src='http://54.243.129.126/usr_content/pics/"+parseJSON.data.info.admin.profile_pic+"_t.jpg' width='30px;' /><span style='color:white; font-size:13px; margin-left:5px;'>"+name+" <span class='label label-success' style='font-size:11px;'>ADMIN</span></span>\
								</div>");
				for(var i = 0;i < parseJSON.data.users.length;i++){
					var name = "";
					if(parseJSON.data.users[i].user_info.type != undefined){
						switch(parseInt(parseJSON.data.users[i].user_info.type)){
							case 0:
							case 1:
							case 3:
							case 5:
								name = parseJSON.data.users[i].user_info.fname+" "+parseJSON.data.users[i].user_info.lname;
								break;
							case 2:
								name = parseJSON.data.users[i].user_info.tname;
								break;
							case 4:
								name = parseJSON.data.users[i].user_info.bname;
								break;
						}
					}
					var online = "";

					switch(parseJSON.data.users[i].user_info.online){
						case 0: //online
							online = "<img style='float:right; width:25px; height:25px;' src='http://cdn4.iconfinder.com/data/icons/spirit20/bullet-green-alt.png' />";
							//online = "<div style='width:5px; float:left; height:20px; background-color:#00b300; margin-right:2px;'></div>";
							break;
						case 1: //idle 5 mins offline
							online = "<img style='float:right; width:25px; height:25px;' src='http://cdn4.iconfinder.com/data/icons/spirit20/bullet-orange-alt.png' />";
							//online = "<div style='width:5px; float:left; height:20px; background-color:#ffa500; margin-right:2px;'></div>";
							break;
						case 2: //not
							//online = "<div style='width:5px; float:left; height:20px; margin-right:2px;'></div>";
							break;
					}
					$(".user-container").append("<div class='user'>\
									"+online+"<img class='img-rounded' src='http://54.243.129.126/usr_content/pics/"+parseJSON.data.users[i].user_info.profile_pic+"_t.jpg' width='30px;' /><span style='color:white; font-size:13px; margin-left:5px;'>"+name+"</span>\
								</div>");
				}
			}
		}
	});
}

function deleteUser(user_id, croom_id){
	$.post("/actions.php?type=removeChatroomUser&u_id="+user_id);
	loadChatroomEdit(croom_id);
}

function searchChatrooms(){
	var query = $(".search-tbox").val();

	$.ajax({
		url: "actions.php?type=searchChatrooms&q="+query,
		success: function(data){
			//populate search results
			var parseJSON = $.parseJSON(data);

			if(parseJSON != undefined){
				//stats at top
				$(".num-results").html(parseJSON.data.length);
				$(".query-area").html(parseJSON.query);
				$(".search-table").empty();
				$(".search-tbox").select();
				$(".search-table").html("<tr><td></td><td></td><td></td><td></td></tr>");
				if(parseJSON.data.length > 0){
					for(var i = 0;i < parseJSON.data.length;i++){
						$(".search-table > tbody:last").append("<tr class='chatroom-searchident"+parseJSON.data[i].id+"'>\
							<td width='80px;'>\
								<div style='width:75px; height:35px; overflow:hidden;'>\
									<img src='"+parseJSON.data[i].photo_url+"' width='75px;' />\
								</div>\
							</td>\
							<td>"+parseJSON.data[i].title+"</td>\
							<td>"+parseJSON.data[i].members+" members</td>\
							<td align='right'><button class='btn btn-mini btncustom22' style='color:black; background-color:#fc5a1e;' onclick='joinSearchChatroom("+parseJSON.data[i].id+");'><i class='icon-plus'></i>Join</button></td>\
						</tr>");
					}
				}else{ //make table display 0 results
					$(".search-table > tbody:last").append("<tr>\
						<td colspan='4'>\
							<span style='color:white; font-size:16px;'><b>0</b> results were found.</span>\
						</td>\
					</tr>");
				}
			}
		}
	});
}

function makeChatroomChat(){
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=chatChatroom";
	$.post(
		actionUrl,
		{
			msg: $(".chatroom-text").val(),
			c_id:  $(".chatroom-text").attr("cid")
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				$(".chatroom-text").val("");
			}
		}
	);
}

$(document).ready(function(){
	$(".chatroom-text").keypress(function(e){
		if (e.keyCode == 13) {
			e.preventDefault();
			makeChatroomChat();
			$(".chatroom-text").val("");
		}
	});

	$(".chatbox").keypress(function(e){
		if (e.keyCode == 13) {
			e.preventDefault();
			addChat();
			$(".chatbox").val("");
		}
	});
});

function grabChatroomChats(id){
	$.ajax({
		url: "actions.php?type=grabChatroomChats&c_id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON != undefined){
				$(".chatroom-chats-holder").empty();
				$(".chatroom-chats-holder").append("<tr><td></td></tr>");
				if(parseJSON.data != undefined){
					$(".chatroom-chats-holder").attr("amount",parseJSON.data.length);
					for(var i = 0;i < parseJSON.data.length;i++){ //NO ------------
						var name = "";
						if(parseJSON.data[i].user_info.type != undefined){
							switch(parseInt(parseJSON.data[i].user_info.type)){
								case 0:
								case 1:
								case 3:
								case 5:
									name = parseJSON.data[i].user_info.fname+" "+parseJSON.data[i].user_info.lname;
									break;
								case 2:
									name = parseJSON.data[i].user_info.tname;
									break;
								case 4:
									name = parseJSON.data[i].user_info.bname;
									break;
							}
						}
						$(".chatroom-chats-holder tr:last").after("<tr>\
																		<td>\
																			<div class='chat'>\
																				<span style='float:right; color:white; font-size:13px;'>"+parseJSON.data[i].date+" ago</span><img class='img-circle' src='/usr_content/pics/"+parseJSON.data[i].user_info.profile_pic+"_t.jpg' width='20px;' /><span style='color:white; font-size:14px; color:yellow; margin-left:5px;'>"+name+"</span><span style='color:white; font-size:13px; padding-left:10px;'>"+parseJSON.data[i].msg+"</span>\
																			</div>\
																		</td>\
																	</tr>");
						//$('.chatroom-holder').animate({scrollTop: $('.chatroom-chats-holder').height()}, 10);
						$(".chatroom-holder").scrollTop($(".chatroom-holder").height());
					}
				}else{
					$(".chatroom-chats-holder").attr("amount",0);
				}
			}
		}
	});
}

function updateChatChatroom(id){
	$.ajax({
		url: "actions.php?type=checkChatChatroom&c_id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON != undefined){
				if($(".chatroom-chats-holder").attr("amount") != parseJSON.data){
					grabChatroomChats(id);
				}
			}
		}
	});
}

function joinChatroom(id){
	//make request to join the chatroom through the link right here.
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=requestAddChatroomMember";
	$.post(
		actionUrl,
		{
			c_id:  id
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				alert("Joined chatroom.");
			}
		}
	);
}

//gets all the users that are currently not apart of this chat.
function populateUsers(){
	$.ajax({
			url: "actions.php?type=getChatUsersUnique&c_id="+$(".croom-name").attr("cid"),
			success: function(data){
				var parseJSON = $.parseJSON(data);
				$(".new-members-list").empty();
				for(var i = 0;i < parseJSON.data.length;i++){ //NO ------------
					if(parseJSON.data[i].u_id != undefined){
						if(logId != parseJSON.data[i].u_id){
							var name = "";
							var fname = "";
							switch(parseInt(parseJSON.data[i].type)){
								case 0:
								case 1:
								case 3:
								case 5:
									name = parseJSON.data[i].fname+" "+parseJSON.data[i].lname;
									fname = parseJSON.data[i].fname;
									break;
								case 2:
									name = parseJSON.data[i].tname;
									fname = name;
									break;
								case 4:
									name = parseJSON.data[i].bname;
									fname = name;
									break;
							}
							$(".new-members-list").append("<li><label><input type='checkbox' name='members[]' style='position:relative; bottom:3px; right:2px;' value='"+parseJSON.data[i].u_id+"'/>"+name+"</label></li>");
						}
					}
				}
				$(".new-members-list").append("<li><button class='btn btn-mini btncustom' style='color:black;' onclick='inviteMoreUsers("+$(".croom-name").attr("cid")+");'>Invite Members</button></li>");
			}
	  });
}

function joinSearchChatroom(id){
	$(".chatroom-searchident"+id).fadeToggle();
	joinChatroom(id);
	getAllChatrooms(logId);
}

function inviteMoreUsers(id){
	$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=inviteMoreUsers";
		$.post(
			actionUrl,
			{
				c_id: id,
				members: grabCheckboxArea(".new-members-list")
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					//Chatroom was created.
					alert("More users added.");
					$(".new-members-list").empty();
					loadChatroomEdit(id);
				}
			}
		);
}

/*
$(window).scroll(function() {
	if(($(window).scrollTop() + $(window).height()) > $(".chatroom-holder").offset().top){ //make the chatroom-area bigger
		$(".chatroom-holder").attr("height", ($(window).scrollTop() - $(".chatroom-holder").offset().top));
	}else{ //still have not scrolled past the chatroom holder

	}
});
*/

</script>
<style type='text/css'>
.spec-tab{
	background-color:black;
	margin-top:5px;
}.indv{
	width:49%;
	color:#156ed4;
	font-weight:bold;
	font-size:25px;
	padding:4px;
	-moz-border-top-left-radius:5px;
	-webkit-border-top-left-radius:5px;
	border-top-left-radius:5px;
	cursor:pointer;
	text-align:center;
}.indv:hover{
	background-color:#333;
}.group{
	cursor:pointer;
	width:49%;
	float:right;
	color:#156ed4;
	font-weight:bold;
	font-size:25px;
	padding:4px;
	-moz-border-top-right-radius:5px;
	-webkit-border-top-right-radius:5px;
	border-top-right-radius:5px;
	text-align:center;
}.group:hover{
	background-color:#333;
}.chat-user{
	font-size:16px;
	font-weight:bold;
}.btn-group-top{
	margin-top:5px;
}.chatrooms table tr:hover{
	background-color:#3188eb;
}.selection-area{
	list-style:none;
}.selection-area li{
	display:inline;
}.mgmt-console{
	background-color:#3188eb;
	padding:10px;
	border:0px solid #000;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
}.croom{
}.croom .croom-bground{
	padding:10px;
	background-image:url('http://www.thelibertybeacon.com/wp-content/uploads/2013/02/green_forest.jpg');
}.croom-bground-info{
	border:0px solid #000;
	-webkit-border-radius:5px;
	-moz-border-radius:5px;
	border-radius:5px;
	background-color:rgba(255,255,255,.7);
	width:400px;
	padding:6px;
}.chat{
	padding:5px;
	border-bottom:1px dashed #3188eb;
}.leave-roomoutline:hover{
	border:1px solid yellow;
	margin-left:5px;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
	width:20px;
}
</style>

<div class="msg-cont">
	<div class='spec-tab'>
		<div class='group' onclick='loadChatRooms();' style='color:yellow;'><img src='http://i.imm.io/Zlqm.png' width='22px;' height='22px;'/>Chat Rooms</div>
		<div class='indv'  onclick='loadIndv();' style='color:yellow;'><img src='http://i.imm.io/ZlqC.png' width='28px;' height='28px;'/> Chat</div>
	</div>
	<div class='group-cont' style='display:none;'>
		<div class='btn-group-top' style='margin-bottom:15px;'>
			<center>
				<button class='btn btn-small btncustom22' style='color:black; background-color:rgb(252, 90, 30);' onclick='$(".create-chatroom").slideDown(); $(".manage-chatroom").slideUp(); $(".join-chatroom").slideUp();'>Create Chat Room</button>
				<!--<button class='btn btn-small btncustom22' style='color:black; background-color:rgb(252, 90, 30);' onclick='$(".manage-chatroom").slideDown(); $(".create-chatroom").slideUp(); $(".join-chatroom").slideUp();'>Manage Chat Rooms</button>-->
				<button class='btn btn-small btncustom22' style='color:black; background-color:rgb(252, 90, 30);' onclick='$(".join-chatroom").slideDown(); $(".create-chatroom").slideUp(); $(".manage-chatroom").slideUp();'>Join Chat Room</button>
			</center>
		</div>
		<div class='search-chatroom'>
			<style type='text/css'>
			.search-table{

			}.search-table tr{
				padding-top:2px;
				padding-bottom:2px;
			}.search-table th{
				font-size:14px;
				background-color:black;
				color:white;
			}.search-table td{
				font-size:13px;
				color:white;
			}.search-container{
				padding:10px;
				margin:0px 25px 0px 25px;
			}
			</style>
			<div class='join-chatroom search-container' style='display:none;'>
				<table border='0' width='100%;' style='padding-bottom:10px; margin-bottom:10px; border-bottom:1px dashed white;'>
					<tr>
						<td>
							<span style='color:white; font-size:15px;'>Search results for <i class='query-area'>--</i><br /><span style='color:yellow; font-size:12px;'><span class='num-results'>0</span> results</span></span>
						</td>
						<td align="right">
							<div>
								<input type='text' style='height:25px;' class='search-tbox' placeholder='Search...'/><i class='icon-search icon-white' style='position:relative; left:3px; bottom:3px; cursor:pointer;' onclick='searchChatrooms();'></i>
							</div>
						</td>
					</tr>
				</table>

				<table border='0' width='100%;' class='search-table'>
					<tr>
						<td></td>
						<td></td>
						<td></td>
						<td></td>
					</tr>
				</table>
			</div>
		</div>
		<div class='create-chatroom' style='display:none;'>
			<table border='0' style='padding:10px;'>
				<tr>
					<td align='right' style='padding-right:15px; width:85px;'>Chat room</td>
					<td valign='middle'><input type='text' class='croom-name' placeholder='Chat room title...' style='height:30px; position:relative; top:6px;'/></td>
					<td></td>
				</tr>
				<tr>
					<td align='right' style='padding-right:15px;'>Privacy</td>
					<td valign='middle'>
						<select class='croom-privacy' style='width:100px;'>
							<option value='pub'>Public</option>
							<!--<option value='priv'>Private</option>-->
						</select>
					</td>
					<td style='padding:10px;'>
					</td>
				</tr>
				<tr>
					<td align='right' style='padding-right:15px;'>Photo URL</td>
					<td><input type='text' class='croom-photourl' placeholder='http://' style='height:30px; position:relative; top:6px;'/></td>
					<td></td>
				</tr>
				<tr>
					<td colspan='3'><div style='height:20px;'></div></td>
				</tr>
				<tr>
					<td colspan='3' style='padding-left:25px;'><button type='button' class='btn btn-small btncustom' onclick='createChatroom();'>Create</button></td>
				</tr>
			</table>
		</div>

		<div class='manage-chatroom' style='display:none; padding-right:10px;'>
			<table border='0' width='100%;'>
				<tr>
					<td width='150px;'>
						<!-- listing on left side -->
						<ul style='list-style:none;' class='chatroom-list'></ul>
					</td>
					<td valign='top'>
						<!-- management console -->
						<div class='mgmt-console'>
							<table border='0' width="100%;">
								<tr>
									<td colspan='2' align='left' valign='top'><img src='' class='croom-img' width='70px;'/><span style='float:right' class='croom-privacy2'>--</span><span style='color:white; font-size:20px; margin-left:8px;' class='croom-name'>--</span></td>
								</tr>
								<tr>
									<td align='right' valign='top'><!--Stats--></td>
									<td>
										<table border='0'>
											<tr>
												<td style='color:yellow;'>
													<!--<span class='croom-memnum'>0</span> members --><button class='btn btn-mini btncustom' style='color:black;' onclick='populateUsers();'>Add members</button>
													<div class='new-members' style='max-height:200px; overflow:scroll;'>
														<ul style='list-style:none;' class='new-members-list'></ul>
													</div>
												</td>
											</tr>
											<tr>
												<td>Created on <span class='croom-date'>--</span></td>
											</tr>
										</table>
									</td>
								</tr>
								<tr>
									<td align='right' valign='top' width='75px;'><!--Members--></td>
									<td>
										<table border='0' width='100%;' class='croom-members'></table>
									</td>
								</tr>

								<tr class='croom-requests'>
									<td></td>
									<td>
										<b style='font-size:13px; color:white;'>Requests</b>
										<table border='0' width='100%;' class='croom-members-request'></table>
									</td>
								</tr>

							</table>
							<button class='btn btn-mini btn-danger' style='margin-top:15px; margin-left:75px;'><i class='icon-trash icon-white' style='position:relative; bottom:2px;'></i> Delete Chat Room</button>
						</div>
					</td>
				</tr>
			</table>
		</div>

		<center><div class='chatrooms' style='margin-top:30px;' width='100%;'>
			<table border='0' width='100%;'>
				<tr><td width='42%;'></td><td width='58%;'></td></tr>
			</table>
		</div></center>
	</div>

	<table border="0" width="100%" cellpadding="5" class='indv-chat'>
		<tr>
			<td valign="top" width="50%">
				<div class='name-holder' style='margin-top:5px;'></div>
			</td>
			<td valign="top" width="50%">
				<div class='notifications-holder'>
					<div class="invitation" style='background-color:#fc5a1e; display:none;'>
					Would you like to join Jeff Costco's chat?<br />
					<button class="btn btn-mini btn-success" type="button" style="color:white; margin-right:5px;">Yes</button><button class="btn btn-mini btn-danger" type="button" style="color:white;">No</button>
					</div>
				</div>
				<div class='indv-chat-edit' style='display:none;'>
					<div class='chat-user'></div>
					<div class='chat-area'>
						<span class="time">3 mins ago.</span><span class="name">Glenn Dayton</span> This is a message that has just been put in the inbox.
						<span class="time">8 mins ago.</span><span class="name">Me</span> Another testing message for the sake of testing.
					</div>
					<textarea class="chatbox"></textarea>
					<button class='btn btn-small btn-primary' style='color:yellow; float:right;' onclick='addChat();'>Chat</button>
				</div>
			</td>
		</tr>
	</table>

</div>
<div class='croom' style='display:none;'>
	<table border='0' width='100%;'>
		<tr>
			<td valign='middle' style='width:40px; background-color:yellow;'>
				<button class='btn btn-small btn-warning' style='color:black; margin-left:5px;' onclick='closeBig();'>Back</button>
			</td>
			<td style='background-color:yellow;'>
				<!--<button class='btn btn-mini btn-warning' style='color:black;'>Back</button>-->
				<div style='margin-left:10px;'>
					<center><span style='color:black; font-size:25px; display:none;' class='chatroom-title'>Lakers Zone</span></center>
					<!--<span style='color:green; font-size:13px;'>3 Online users: <i style='color:green;'>Glenn, Jake, Ollie</i></span>-->
				</div>
			</td>
			<td width='75px' style='background-color:yellow;'><img class='chatroom-pic' src='' width='75px;'></td>
		</tr>
	</table>
	<table border='0' width='100%;'>
		<tr>
			<td>
				<table border='0' width='100%'>
					<tr>
						<td valign='top'>
							<div class='chatroom-holder' style='width:100%; max-height:500px; overflow:scroll;'><table border='0' width='100%;' class='chatroom-chats-holder'></table></div>
							<textarea style='width:100%; resize:none; position:relative; bottom:2px;' class="chatroom-text"></textarea>
							<button class='btn btn-small btncustom' onclick='makeChatroomChat();' style='float:right;'>Chat</button>
						</td>
						<td width='200px' valign='top'>
							<div class='user-container'></div>
						</td>
					</tr>
				</table>
			</td>
		</tr>
	</table>
</div>