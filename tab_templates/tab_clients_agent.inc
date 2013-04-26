<style type='text/css'>
.client{
	width:100%;
}.client .client-name{
	font-size:16px;
	color:yellow;
	font-weight:bold;
	margin:3px;
}.client .prof-pic{
	/*width:150px;
	height:150px;*/
	width:200px;
}.client .stats .blue{
	font-size:12px;
	color:white;
	background-color:#89cff0;
}.client .stats th{
	font-size:12px;
	color:white;
	background-color:red;
}.client .stats .red{
	font-size:12px;
	color:white;
	background-color:red;
	padding-top:2px;
	padding-bottom:2px;
	padding-right:3px;
	padding-left:3px;
}.client .stats td{
	font-size:12px;
	color:black;
	padding-top:2px;
	padding-bottom:2px;
	background-color:white;
}.client .event-name{
	font-size:16px;
	font-weight:bold;
	color:white;
}.client .time-wrapper{
	/*background-color:red;*/
	padding:3px;
}.client .description{
	font-size:13px;
	color:yellow;
}.manage-clients{
	background-color:#063d78;
	padding:10px;
}.edit-dropdown{
	/*background-color:rgba(255,255,255,.4);
	padding:10px;
	-moz-border-radius:5px;
	-webkit-border-radius:5px;
	border-radius:5px;
	border:0px solid #000;*/
}.pic-up{
	float:right;
	position:relative;
	color:black;
	top:1px;
	-moz-border-radius:3px;
	-webkit-border-radisu:3px;
	border-radius:3px;
	background-color:rgba(255,255,255,.8);
	padding:2px;
}.pic-up:hover{
	color:orange;
	background-color:rgba(0,0,0,.8);
}
</style>
<script>
function addClient(){
	$(".add-client").slideToggle();
}
//$(".info-url-area").tooltip('hide');
//$(".info-url-area").tooltip('toggle');

function createClient(){
	var name = $(".client-name").val();
	var imgurl = $(".client-img-url").val();
	var desc = $(".client-description").val();
	if((name.length > 0) && (imgurl.length > 0) && (desc.length > 0)){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addClient";
		$.post(
			actionUrl,
			{
				name: name,
				photo_url: imgurl,
				description: desc
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					$(".client-name").val("");
					$(".client-img-url").val("");
					$(".client-description").val("");
					grabClients();
				}
			}
		);
	}else{
		alert("You must enter a name, photo, and description for your client.");
	}
}

function dispThumbPic(){
	$(".thumb").attr("src",$(".client-img-url").val());
}

function changeName(id){
	$(".name"+id+"-edit").show();
	$(".name"+id+"-show").hide();
}

function undoName(id){
	$(".name"+id+"-edit").hide();
	$(".name"+id+"-show").show();
}

function changeDesc(id){
	$(".desc"+id+"-edit").show();
	$(".desc"+id+"-show").hide();
}

function undoDesc(id){
	$(".desc"+id+"-edit").hide();
	$(".desc"+id+"-show").show();
}

function changePic(id){
	$(".pic"+id+"-edit").show();
	$(".pic"+id+"-edit input").select();
	$(".pic"+id+"-show").hide();
}

function undoPic(id){
	$(".pic"+id+"-edit").hide();
	$(".pic"+id+"-edit input").select();
	$(".pic"+id+"-show").show();
}

function makeChange(type,id){
	switch(type){
		case 0: //name
			$.ajaxSetup({async:false});
			var actionUrl = "actions.php?type=editClientName";
			$.post(
				actionUrl,
				{
					name:  $(".name"+id+"-editval").val(),
					c_id: id
				},
				function(data,status){
					var parseJSON = $.parseJSON(data);
					if(parseJSON.status == "error"){
						alert(parseJSON.status_msg);
					}else{
						$(".name"+id+"-edit").hide();
						$(".name"+id+"-show").html($(".name"+id+"-editval").val()+"<i onclick='changeName("+id+");' class='icon-edit icon-white' style='margin-left:3px;'></i>");
						$(".name"+id+"-show").show();
					}
				}
			);
			break;
		case 1: //desc
			$.ajaxSetup({async:false});
			var actionUrl = "actions.php?type=editClientDesc";
			$.post(
				actionUrl,
				{
					description:  $(".desc"+id+"-editval").val(),
					c_id: id
				},
				function(data,status){
					var parseJSON = $.parseJSON(data);
					if(parseJSON.status == "error"){
						alert(parseJSON.status_msg);
					}else{
						$(".desc"+id+"-edit").hide();
						$(".desc"+id+"-show").html($(".desc"+id+"-editval").val());
						$(".desc"+id+"-show").show();
					}
				}
			);
			break;
		case 2: //pic
			$.ajaxSetup({async:false});
			var actionUrl = "actions.php?type=editClientPic";
			$.post(
				actionUrl,
				{
					photo_url: $(".pic"+id+"-editval").val(),
					c_id: id
				},
				function(data,status){
					var parseJSON = $.parseJSON(data);
					if(parseJSON.status == "error"){
						alert(parseJSON.status_msg);
					}else{
						$(".pic"+id+"-edit").hide();
						$(".pic"+id+"-showprev").attr("src",$(".pic"+id+"-editval").val());
						$(".pic"+id+"-show").show();
					}
				}
			);
			break;
	}
}

function showEventEdit(id){
	$(".event-edit"+id).slideToggle();
}

function addEvent(id){
	if($(".text"+id).val().length > 0){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addEvent";
		$.post(
			actionUrl,
			{
				text: $(".text"+id).val(),
				date: $(".date"+id).val(),
				hour: $(".hour"+id).val(),
				min: $(".min"+id).val(),
				c_id: id
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					$(".text"+id).val("")
					$(".date"+id).val("")
					$(".hour"+id).val("1")
					$(".min"+id).val("1")
					showEventEdit(id);
				}
			}
		);
	}else{
		alert("You must enter a title for this event.");
	}
}

function deleteEvent(id,e_id){
	$.post("actions.php?type=deleteEvent&c_id="+id+"&e_id="+e_id);
	grabEvents(id,0);
}

function grabClients(){
	$.ajax({
		url: "actions.php?type=grabClients&uid="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);

			//main display
			$(".client table").empty();
			$(".client table").append("<tr><td></td><td></td><td></td></tr>");

			//top edit display
			$(".client-edit-view").empty();
			$(".client-edit-view").append("<tr><td></td><td></td><td></td></tr>");
			if(parseJSON.data != undefined){
				$(".num-clients").html(parseJSON.data.length+" total");
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".client-edit-view tr:last").after("<tr>\
						<td><img src='"+parseJSON.data[i].photo_url+"' width='30px;' height='30px;' /></td>\
						<td>"+parseJSON.data[i].name+"</td>\
						<td align='right'><i class='icon-calendar icon-white' onclick='showPanel("+parseJSON.data[i].id+",1);'></i> <i class='icon-edit icon-white' onclick='showPanel("+parseJSON.data[i].id+",0);'></i> <i class='icon-trash icon-white' onclick='showPanel("+parseJSON.data[i].id+",2);'></i></td>\
					</tr>\
					<tr class='"+parseJSON.data[i].id+"edit edit-dropdown' style='display:none;'>\
						<td colspan='3'></td>\
					</tr>");
					var pos = 1;
					$(".client-table > tbody:first").after("<tr>\
															<td class='client-name'>\
																<div class='client-name-show name"+parseJSON.data[i].id+"-show'>"+parseJSON.data[i].name+"<i onclick='changeName("+parseJSON.data[i].id+");' class='icon-edit icon-white' style='margin-left:3px;'></i></div>\
																<div class='client-name-edit name"+parseJSON.data[i].id+"-edit' style='width:200px; display:none;'><div style='float:right;'><button class='btn btn-primary btn-mini' style='color:yellow;' onclick='makeChange(0,"+parseJSON.data[i].id+");'>Save</button><br /><a style='font-size:13px;' href='javascript:undoName("+parseJSON.data[i].id+");'>Cancel</a></div><input type='text' placeholder='Name...' style='height:25px; width:150px;' class='name"+parseJSON.data[i].id+"-editval' value='"+parseJSON.data[i].name+"'/></div>\
															</td>\
															<td align='right' valign='bottom'>\
																<i onclick='changeDesc("+parseJSON.data[i].id+");' style='float:right;' class='icon-edit icon-white'></i>\
															</td>\
															<td></td>\
														</tr>\
														<tr>\
															<td valign='top'>\
																<div style='height:125px; overflow:hidden;'>\
																	<a class='pic"+parseJSON.data[i].id+"-show pic-up' style='font-size:13px;' href='javascript:changePic("+parseJSON.data[i].id+");'>Change photo</a>\
																	<img class='pic"+parseJSON.data[i].id+"-showprev' style='margin-top:-20px;' width='250px;' class='prof-pic img-rounded' src='"+parseJSON.data[i].photo_url+"' />\
																</div>\
																<div class='pic"+parseJSON.data[i].id+"-edit' style='display:none;'><input type='text' class='pic"+parseJSON.data[i].id+"-editval' value="+parseJSON.data[i].photo_url+"' style='height:25px;' placeholder='Photo URL...'/><br />\
															<button class='btn btn-mini btn-primary' style='color:yellow;' onclick='makeChange(2,"+parseJSON.data[i].id+");'>Save</button><a style='font-size:13px;' href='javascript:undoPic("+parseJSON.data[i].id+");'>Cancel</a></div></td>\
															<td class='description' valign='top' align='left' width='33%'>\
																<div class='client-desc-show desc"+parseJSON.data[i].id+"-show' style='padding-left:5px;'>"+parseJSON.data[i].description+"</div>\
																<div class='client-desc-edit desc"+parseJSON.data[i].id+"-edit' style='display:none;'>\
																	<textarea class='desc"+parseJSON.data[i].id+"-editval' style='resize:none; width:100%; height:200px; font-size:13px;'>"+parseJSON.data[i].description+"</textarea>\
																	<button class='btn btn-mini btn-primary' style='color:yellow;' onclick='makeChange(1,"+parseJSON.data[i].id+");'>Save</button><a href='javascript:undoDesc("+parseJSON.data[i].id+");' style='font-size:13px; margin-left:3px;'>Cancel</a>\
																</div>\
															</td>\
															<td valign='top' align='middle' width='33%'>\
																<b style='color:yellow;'>Next Event</b><br />\
																<table border='0' width='100%;' style='margin-top:10px;'>\
																	<tr>\
																		<td>\
																			<table border='0' width='100%'>\
																				<tr><td colspan='2' align='center' class='event-name event-name"+parseJSON.data[i].id+"'>--</td></tr><!-- name -->\
																				<tr>\
																					<td align='center' valign='middle' class='event-date' width='50%'>\
																						<table border='0' width='40px;' class='stats'>\
																							<tr>\
																								<td class='red day"+parseJSON.data[i].id+"' align='center'>FRI</td>\
																								<td align='center' class='period"+parseJSON.data[i].id+"'>12/22</td>\
																							</tr>\
																						</table>\
																					</td>\
																					<td class='event-time' width='50%'>\
																						<div class='time-wrapper'>\
																							<img src='http://i.imm.io/Y28I.png' width='20px;' style='position:relative; bottom:2px;'/><span style='color:yellow;' class='time"+parseJSON.data[i].id+"'>12:30</span><span style='font-size:13px; color:yellow;' class='ampmd"+parseJSON.data[i].id+"'>PM</span>\
																						</div>\
																					</td>\
																				</tr>\
																			</table>\
																		</td>\
																	</tr>\
																	<tr>\
																		<td align='center' valign='middle'>\
																			<table border='0'>\
																				<tr>\
																					<td align='left' width='40px;'>\
																						<img class='client-left"+parseJSON.data[i].id+"' src='http://i.imm.io/Y2h9.png' width='40px;' style='display:none;'/>\
																					</td>\
																					<td>\
																						<span style='color:orange; font-weight:bold; font-size:13px;'><span class='out-of-div"+parseJSON.data[i].id+"'>0</span>/<span class='out-of"+parseJSON.data[i].id+"'>0</span>\
																					</td>\
																					<td align='right' width='40px;'>\
																						<img src='http://i.imm.io/Y2fU.png' width='40px;' style='display:none;' class='client-right"+parseJSON.data[i].id+"' />\
																					</td>\
																				</tr>\
																			</table>\
																		</td>\
																	</tr>\
																	<tr>\
																		<td>\
																			<center><button class='btn btn-mini btn-primary' style='color:yellow; margin-bottom:5px;' onclick='showEventEdit("+parseJSON.data[i].id+");'>Add Event</button></center>\
																			<div class='event-edit"+parseJSON.data[i].id+"' style='display:none;'>\
																				<input type='text' class='text"+parseJSON.data[i].id+"' placeholder='Title...' style='height:25px;'/>\
																				<select class='hour"+parseJSON.data[i].id+"' style='width:55px'>\
																					<option value='1'>1</option>\
																					<option value='2'>2</option>\
																					<option value='3'>3</option>\
																					<option value='4'>4</option>\
																					<option value='5'>5</option>\
																					<option value='6'>6</option>\
																					<option value='7'>7</option>\
																					<option value='8'>8</option>\
																					<option value='9'>9</option>\
																					<option value='10'>10</option>\
																					<option value='11'>11</option>\
																					<option value='12'>12</option>\
																				</select> : \
																				<select class='min"+parseJSON.data[i].id+"' style='width:55px'>\
																					<option value='0'>00</option>\
																					<option value='5'>05</option>\
																					<option value='10'>10</option>\
																					<option value='15'>15</option>\
																					<option value='20'>20</option>\
																					<option value='25'>25</option>\
																					<option value='30'>30</option>\
																					<option value='35'>35</option>\
																					<option value='40'>40</option>\
																					<option value='45'>45</option>\
																					<option value='50'>50</option>\
																					<option value='55'>55</option>\
																				</select>\
																				<select class='ampm"+parseJSON.data[i].id+"' style='width:55px'>\
																					<option value='am'>AM</option>\
																					<option value='pm'>PM</option>\
																				</select>\
																				<input type='text' class='popDates date"+parseJSON.data[i].id+"' placeholder='Date...' style='height:25px;'/>\
																				<button class='btn btn-small btn-primary' style='color:yellow;' onclick='addEvent("+parseJSON.data[i].id+");'>Save</button>\
																			</div>\
																		</td>\
																	</tr>\
																</table>\
															</td>\
														</tr>");
														popDates();
														grabEvents(parseJSON.data[i].id,0);
				}
			}
		}
    });
}

function grabEvents(id,pos){
	$.ajax({
		url: "actions.php?type=grabEvents&c_id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.data != undefined){
				$(".out-of"+id).html(parseJSON.data.length);
				if(pos == 0){ //remove left arrow
					$(".client-left"+id).hide();
					$(".client-right"+id).show();
					$(".client-right"+id).attr("onclick","grabEvents("+id+","+(pos+1)+");");
				}else if(pos == (parseJSON.data.length-1)){
					$(".client-right"+id).hide();
					$(".client-left"+id).show();
					$(".client-left"+id).attr("onclick","grabEvents("+id+","+(pos-1)+");");
				}else{
					$(".client-right"+id).show();
					$(".client-right"+id).attr("onclick","grabEvents("+id+","+(pos+1)+");");
					$(".client-left"+id).show();
					$(".client-left"+id).attr("onclick","grabEvents("+id+","+(pos-1)+");");
				}
				if(pos <= parseJSON.data.length){
				//for(var i = 0;i < parseJSON.data.length;i++){
					$(".out-of-div"+id).html(pos+1);
					$(".event-name"+id).html(parseJSON.data[pos].text+" <i onclick='deleteEvent("+id+","+parseJSON.data[pos].id+");' style='cursor:pointer;' class='icon-trash icon-white'></i>");
					$(".day"+id).html(parseJSON.data[pos].day_text);
					$(".period"+id).html(parseJSON.data[pos].month_day);
					$(".time"+id).html(parseJSON.data[pos].time);
					$(".ampmd"+id).html(parseJSON.data[pos].ampm);
				}
			}else{
				$(".event-name"+id).html("No events have been added.");
				$(".day"+id).html("--");
				$(".period"+id).html("--");
				$(".time"+id).html("-:--");
				$(".ampmd"+id).html("--");
			}
		}
    });
}

//call this to expose an event
function showPanel(id,action){
	$("."+id+"edit").show();
	$("."+id+"edit").empty();
	switch(action){
		case 0: //edit
			$("."+id+"edit").append("<td colspan='3'>\
				<table border='0'>\
					<tr>\
						<td align='right'>Name</td>\
						<td><input type='text' class='name-edit' style='width:200px;'/></td>\
					</tr>\
					<tr>\
						<td align='right'>Photo URL</td>\
						<td><input type='text' class='img-edit' style='width:200px;'/></td>\
					</tr>\
					<tr>\
						<td align='right' valign='top'>Description</td>\
						<td><textarea style='resize:none; width:200px; font-size:13px;'></textarea></td>\
					</tr>\
					<tr>\
						<td colspan='2' align='right'><button class='btn btn-mini btncustom' style='color:#156ed4;'>Save</button></td>\
					</tr>\
				</table>\
			</td>");
			break;
		case 1: //eventAdd
			$("."+id+"edit").append("<td colspan='3'>\
				<table border='0'>\
					<tr>\
						<td align='right'><span style='position:relative; bottom:2px;'>Date</span></td>\
						<td><input type='text' class='name-edit' style='width:200px; height:23px;'/></td>\
						<td><button class='btn btn-mini btncustom' style='color:#156ed4; margin-left:5px;'>Save</button></td>\
					</tr>\
					<tr>\
						<td align='right'><span style='position:relative; bottom:2px;'>Event</span></td>\
						<td><input type='text' class='img-edit' style='width:200px; height:23px;'/></td>\
						<td></td>\
					</tr>\
				</table>\
			</td>");
			$(".name-edit").datepicker();
			break;
		case 2: //delete item
			var prompt = confirm("Are you sure that you want to remove this client?");
			if(prompt){
				//delete the client.
			}
			break;
	}
}

grabClients();
</script>
<div class="manage-clients">
	<center><button class="btn btn-small btncustom" style="color:#156ed4; margin-bottom:5px;" onclick="addClient();">Manage Clients</button></center>
	<div class="add-client" style="display:none;">
		<table border="0" width="100%">
			<tr>
				<td width="50%;" valign='top'>
					<b>New Client</b>
					<table border="0">
						<tr>
							<td align="right" valign="top"><span style="position:relative; top:3px; right:3px;">Name</span></td>
							<td><input class="client-name" type="text" style="height:23px;" placeholder="Name..." /></td>
						</tr>
						<tr>
							<td align="right" valign="top"><span style="position:relative; top:3px; right:3px;">Photo</span></td>
							<td><input class="client-img-url" type="text" style="height:23px;" onkeyup="dispThumbPic();" placeholder="Image URL..." /><i class="icon-info-sign icon-white info-url-area" style="position:relative; left:3px; bottom:2px;" rel='tooltip' title='<b>Mac & PC instructions</b><br />Grab an image URL, in a web browser, by right-clicking the image and selecting "Copy image URL".' data-placement='right' data-trigger='hover'></i></td>
						</tr>
						<tr>
							<td align="right" valign="top"><span style="position:relative; top:3px; right:3px;">Description</span></td>
							<td><textarea class="client-description" style="resize:none;"></textarea></td>
						</tr>
						<tr>
							<td></td>
							<td align="left"><button class="btn btn-small btncustom" style="color:#063d78;" onclick="createClient();">Save</button></td>
						</tr>
					</table>
				</td>
				<td width="50%;" valign="top" align="left">
					<img class='thumb' src='https://mail.google.com/mail/images/cleardot.gif' width='200px;' style='margin-top:15px;'/>
					<!--<b>Current Clients</b><i style="font-size:14px; float:right;" class="num-clients"></i>
					<table border="0" width="100%" style="max-height:400px;" class="client-edit-view">
					</table>-->
				</td>
			</tr>
		</table>
	</div>
</div>

<div class='client'>
	<table border='0' width='98%' style='margin:10px;' class='client-table'>
		<tr>
			<td>
			No clients have been added.
			</td>
		</tr>
	</table>
</div>