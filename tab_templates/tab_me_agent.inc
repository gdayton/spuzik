<style type="text/css">
.user-info{
	/*background-color:rgba(255,255,255,.4);*/
	/*background-color:purple;*/
	background-color:#063d78;
	font-size:13px;
	padding:8px;
	position:relative;
	bottom:5px;
	right:5px;
	margin-right:-10px;
	/*margin-bottom:10px;*/
}.user-info .user-info-table th{
	font-size:13px;
	/*color:white;*/
	color:white;
	padding-left:5px;
}.user-info .user-info-table td{
	font-size:13px;
	/*color:yellow;*/
	color:yellow;
	padding-left:5px;
}.user-info .user-info-table th .bigtext{
	font-size:25px;
	color:white;
}.ach li{
	font-size:13px;
	color:white;
}.memory td{
	font-size:13px;
	color:white;
}.about{
	font-size:13px;
	color:white;
	background-image:url('http://i.imm.io/XbAS.jpeg');
	background-repeat:no-repeat;
	background-color:yellow;
	/*background-image: -webkit-gradient(linear, 0 top, 0 bottom, from(#496178), to(#2E4960));*/
	/*-moz-border-radius:5px;
	-webkit-border-radius:5px;
	border-radius:5px;
	border:0px solid #000;*/
	padding:10px;
	position:relative;
	bottom:5px;
	right:5px;
	margin-right:-10px;
}.user-info-table .edit{
	display:none;
}
</style>
<script>
function editInfoDisp(){
	$(".user-info-table .view").hide();
	$(".user-info-table .edit").show();
	popDates();
}

function cancelInfoEdit(){
	$(".user-info-table .view").show();
	$(".user-info-table .edit").hide();
}


grabInfo();

function grabInfo(){
	$.ajax({
		url: "actions.php?type=getInfo&u_id="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			$(".company").html(parseJSON.company);
			$(".company-edit").val(parseJSON.company);

			$(".gender").html(((parseJSON.gender == 1) ? "Male" : "Female"));
			if(parseJSON.gender == 1)
				$(".gender-edit-male").attr('checked', 'checked');
			else
				$(".gender-edit-female").attr('checked', 'checked');

			$(".agent").html(((parseJSON.agent_type == 1) ? "Sport" : "Music"));
			if(parseJSON.agent_type == 1)
				$(".type-edit-sport").attr('checked', 'checked');
			else
				$(".type-edit-music").attr('checked', 'checked');

			$(".num-clients").html(parseJSON.num_clients);
			$(".num-client-edit").val(parseJSON.num_clients);
			$(".hometown").html(parseJSON.hmtown);
			$(".hometown-edit").val(parseJSON.hmtown);
			$(".email").html(parseJSON.email);
		}
	});
}

function editInfo(){
	var gender_p = 0;
	var act_type = 0;
	if($("#gender-edit:checked").val() == "m"){ //male
		gender_p = 1;
	}

	if($("#type-edit:checked").val() == "s"){ //sport
		act_type = 1;
	}
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=editInfoAgent";

	$.post(
		actionUrl,
		{
			company: $(".company-edit").val(),
			agent_type: act_type,
			num_clients: $(".num-client-edit").val(),
			gender: gender_p,
			hmtown: $(".hometown-edit").val()
		},
		function(data,status){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status == "error"){
				alert(parseJSON.status_msg);
			}else{
				grabInfo();
				$(".user-info-table .view").show();
				$(".user-info-table .edit").hide();
			}
		}
	);
}

function addAch(){
	var text = $(".ach-text").val();
	if((text.length > 0)){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addAchievement";
		$.post(
			actionUrl,
			{
				text: text
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					grabAch();
					$(".ach-text").val("");
					$(".ach-text").select();
				}
			}
		);
	}else{
		alert("You didn't enter anything.");
	}
}

function grabAch(){
	$.ajax({
		url: "actions.php?type=grabAchievements&uid="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			$(".ach").empty();
			if(parseJSON.data != undefined){
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".ach").append("<li><span style='color:yellow;'>"+parseJSON.data[i].text+"</span> <i class='icon-trash icon-white' onclick='deleteAch("+parseJSON.data[i].id+")'></i></li>");
				}
			}
		}
    });
}

function deleteAch(q_id){
	$.post("actions.php?type=deleteAch&a_id="+q_id);
	grabAch();
}

grabAch();

function grabAboutMe(){
	$.ajax({
		url: "actions.php?type=grabAboutMe&u_id="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			//$(".about-me-text").empty();
			if(parseJSON.data != undefined){
				$(".about-me-text").html(parseJSON.data[0]);
				//$(".aboutme").html("");
				$(".aboutme").html(parseJSON.data[0]);
			}
		}
    });
}

grabAboutMe();

function editAboutMe(){
	var aboutme = $(".aboutme").val();
	if(aboutme.length > 0){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=editAboutMe";
		$.post(
			actionUrl,
			{
				aboutme: aboutme
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					$(".aboutme").val();
					$(".aboutme").select();
					$(".aboutme").hide();
					$(".edit-aboutme").show();
					$(".save-aboutme").hide();
					grabAboutMe();
				}
			}
		);
	}else{
		alert("The date must consist of numbers.");
	}
}

function editPullUp(){
	$(".edit-aboutme").hide();
	$(".save-aboutme").show();
	$(".aboutme").show();
	$(".aboutme").select();
}

$(".memory-text").elastic();
</script>
<div style="padding-top:3px; padding-right:5px; padding-left:5px;">
<div class="user-info">
	<table border="0" class="user-info-table" cellspacing="5" width="100%;">
		<tr>
			<th align="left" valign="middle">Email</th>
			<th align="left" valign="middle">Company</th>
			<th align="left" valign="middle">Agent type</th>
			<th align="left" valign="middle"># of Clients</th>
			<th align="left" valign="middle">Gender</th>
			<th align="left" valign="middle">Hometown</th>
			<th align="left" valign="middle"><div class="edit" style="float:right;"><button class="btn btn-mini btn-primary" onclick="editInfo();" style="margin-right:5px;"><span style="color:yellow;">Save</span></button><a href="javascript:cancelInfoEdit();" style='color:yellow;'>Cancel</a></th>
			<th rowspan="2">
				<div class="view"><button class="btn btn-small btncustom" onclick="editInfoDisp();" style='color:black;'><i class="icon-edit"></i>Edit</button></div>
			</th>
		</tr>
		<tr>
			<td valign="middle">
				<div class="email"></div>
				<div class="edit" style="color:#f9b14c;">Email cannot be changed.</div>
			</td>
			<td valign="middle">
				<div class="view company">GPS</div>
				<div class="edit"><input type="text" class="company-edit" style="height:25px; font-size:13px; width:100px;"/></div>
			</td>
			<td valign="middle">
				<div class="view agent">Sport</div>
				<div class="edit">
					<label style="font-size:13px;"><input type="radio" name="type" id="type-edit" value="s" class="type-edit-sport" style="position:relative; bottom:4px;"> Sport</label>
					<label style="font-size:13px; margin-top:-7px;"><input type="radio" name="type" id="type-edit" value="m" class="type-edit-music" style="position:relative; bottom:4px;"> Music</label>
				</div>
			</td>
			<td valign="middle">
				<div class="view num-clients">8</div>
				<div class="edit"><input type="text" class="num-client-edit" style="height:25px; font-size:13px; width:30px;"/></div>
			</td>
			<td valign="middle">
				<div class="view gender"></div>
				<div class="edit">
					<label style="font-size:13px;"><input type="radio" name="gen" id="gender-edit" value="m" class="gender-edit-male" style="position:relative; bottom:4px;"> Male</label>
					<label style="font-size:13px; margin-top:-7px;"><input type="radio" name="gen" id="gender-edit" value="f" class="gender-edit-female" style="position:relative; bottom:4px;"> Female</label>
				</div>
			</td>
			<td valign="middle">
				<div class="view hometown"></div>
				<div class="edit"><input type="text" class="hometown-edit" style="height:25px; width:100px; font-size:13px;" /></div>
			</td>
		</tr>
	</table>
</div>
<div class="about" style="min-height:175px;">
	<div class="about-me-text" style="margin-left:180px; color:#156ed4;">

	</div>
	<textarea style="width:70%; margin-left:180px; height:100%; resize:none; background:none; color:black; display:none;" class="aboutme"></textarea>
</div>
<table border="0" width="100%;">
	<tr>
		<td align="right">
		<button class="btn btn-mini btn-primary edit-aboutme"><span style="color:yellow;" onclick="editPullUp();">Edit</span></button>
		<button class="btn btn-mini btn-primary save-aboutme" style="display:none;"><span style="color:yellow;" onclick="editAboutMe();">Save</span></button></td>
	</tr>

	<tr>
		<td><span style="color:#ffff00; border-bottom:2px solid white;">Achievements</span></td>
	</tr>
	<!-- QUOTES AREA -->
	<tr>
		<td>
			<ul class="ach">
				<li><span style="color:white;">Life is hard; it's harder if you're stupid. -<i style="color:yellow;">John Wayne</i></span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">When everything is easy one quickly gets stupid. -<i style="color:yellow;">Maxim Gorky</i></span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">No matter how long you stare at it, it always looks phenomenal. -<i style="color:yellow;">Ollie Schindler</i></span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">He's what we call a mouthbreather. -<i style="color:yellow;">Jake Cohen</i></span> <i class="icon-trash icon-white"></i></li>
			</ul>
		</td>
	</tr>
	<tr class="edit-ach">
		<td align="left"><input type="text" class="ach-text" placeholder="Achievement..." style="height:24px; margin-right:10px; width:200px;"/><button class="btn btn-mini btn-primary" style="position:relative; bottom:5px;" onclick="addAch();"><span style="color:yellow;">Save</span></button></td>
	</tr>
	<tr>
		<td style="height:20px;"></td>
	</tr>
</table>
</div>