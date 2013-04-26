<style type="text/css">
.user-info{
	/*background-color:rgba(255,255,255,.4);*/
	background-color:#fc5a1e; /* red, #063d78 */
	font-size:13px;
	padding:8px;
	position:relative;
	bottom:5px;
	right:5px;
	margin-right:-10px;
	/*margin-bottom:10px;*/
}.user-info .user-info-table th{
	font-size:13px;
	color:white;
	padding-left:5px;
}.user-info .user-info-table td{
	font-size:13px;
	color:yellow;
	padding-left:5px;
}.user-info .user-info-table th .bigtext{
	font-size:25px;
	color:white;
}.quotes li{
	font-size:13px;
	color:orange;
}.soundlike li{
	font-size:13px;
	color:orange;
}.memory td{
	font-size:13px;
	color:white;
}.about{
	font-size:13px;
	color:white;
	/*background-image:url('http://i.imm.io/W0y3.jpeg'); XbPr  YFnm YFqF YFuu YFsK*/
	background-image:url('http://i.imm.io/YFuO.jpeg');
	background-size:100%;
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
			$(".nickname").html(parseJSON.nickname);
			$(".nickname-edit").val(parseJSON.nickname);
			$(".gender").html(((parseJSON.gender == 1) ? "Male" : "Female"));
			if(parseJSON.gender == 1)
				$(".gender-edit-male").attr('checked', 'checked');
			else
				$(".gender-edit-female").attr('checked', 'checked');
			$(".birthday").html(parseJSON.dob);
			$(".birthday-edit").val(parseJSON.dob);
			$(".hometown").html(parseJSON.hmtown);
			$(".hometown-edit").val(parseJSON.hmtown);
			$(".email").html(parseJSON.email);
		}
	});
}

function editInfo(){
	var gender_p = 0;
	if($("#gender-edit:checked").val() == "m"){ //male
		gender_p = 1;
	}
	$.ajaxSetup({async:false});
	var actionUrl = "actions.php?type=editInfo";
	$.post(
		actionUrl,
		{
			nickname: $(".nickname-edit").val(),
			dob: $(".birthday-edit").val(),
			hmtown: $(".hometown-edit").val(),
			gender: gender_p
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

function addQuote(){
	var text = $(".quote-text").val();
	var person = $(".quote-person").val();
	if((text.length > 0) && (person.length > 0)){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addQuote";
		$.post(
			actionUrl,
			{
				quote: text,
				auth: person
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					//$(".quotes li:last").after("<li>"+text+" -<i>"+person+"</i> <i class='icon-trash icon-white'></i></li>");
					grabQuotes();
					$(".quote-text").val("");
					$(".quote-person").val("");
					$(".quote-text").select();
				}
			}
		);
	}else{
		alert("You didn't enter anything.");
	}
}

function grabQuotes(){
	$.ajax({
		url: "actions.php?type=grabQuotes&u_id="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			$(".quotes").empty();
			if(parseJSON.data != undefined){
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".quotes").append("<li><span style='color:white;'>"+parseJSON.data[i].quote+" -<i style='color:yellow;'>"+parseJSON.data[i].auth+"</i></span> <i class='icon-trash icon-white' onclick='deleteQuote("+parseJSON.data[i].id+")'></i></li>");
				}
			}
		}
    });
}

function deleteQuote(q_id){
	$.post("actions.php?type=deleteQuote&q_id="+q_id);
	grabQuotes();
}

grabQuotes();

function addMemory(){
	var memory = $(".memory-text").val();
	var year = $(".memory-date").val();
	if((memory.length > 0) && (!isNaN(parseInt(year)))){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addMemory";
		$.post(
			actionUrl,
			{
				memory: memory,
				year: year
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					grabMemories();
					$(".memory-text").val("");
					$(".memory-date").val("");
					$(".memory-text").select();
				}
			}
		);
	}else{
		alert("The date must consist of numbers.");
	}
}

function grabMemories(){
	$.ajax({
		url: "actions.php?type=grabMemories&u_id="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			$(".memory").empty();
			$(".memory").html("<tr><td></td><td></td><td></td></tr>");
			if(parseJSON.data != undefined){
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".memory tr:last").after("<tr>\
													<td valign='top'><span style='color:white;'>"+parseJSON.data[i].year+"</span></td>\
													<td style='color:yellow;'>"+parseJSON.data[i].memory+"</td>\
													<td valign='top'><i class='icon-trash icon-white' onclick='deleteMemory("+parseJSON.data[i].id+");'></i></td>\
												</tr>");
				}
			}
		}
    });
}

function deleteMemory(m_id){
	$.post("actions.php?type=deleteMemory&m_id="+m_id);
	grabMemories();
}

grabMemories();

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

function grabGenres(){
	$.ajax({
		url: "actions.php?type=grabGenres",
		success: function(data){
			var parseJSON = $.parseJSON(data);
			//$(".about-me-text").empty();
			if(parseJSON.data != undefined){
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".music-genres").append("<option value='"+parseJSON.data[i].id+"'>"+parseJSON.data[i].genre+"</option>");
				}
			}
		}
    });
}

grabGenres();

for(var i = 1;i <= 60;i++){
	$(".yrs-exp").append("<option value='"+i+"'>"+i+" yrs.</option>");
}

function editPullUp(){
	$(".edit-aboutme").hide();
	$(".save-aboutme").show();
	$(".aboutme").show();
	$(".aboutme").select();
}

$(".memory-text").elastic();

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

function addGoal(){
	var text = $(".goal-text").val();
	if((text.length > 0)){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addGoal";
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
					grabGoal();
					$(".goal-text").val("");
					$(".goal-text").select();
				}
			}
		);
	}else{
		alert("You didn't enter anything.");
	}
}

function grabGoal(){
	$.ajax({
		url: "actions.php?type=grabGoals&uid="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			$(".goal").empty();
			if(parseJSON.data != undefined){
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".goal").append("<li><span style='color:yellow;'>"+parseJSON.data[i].text+"</span> <i class='icon-trash icon-white' onclick='deleteGoal("+parseJSON.data[i].id+")'></i></li>");
				}
			}
		}
    });
}

function deleteGoal(q_id){
	$.post("actions.php?type=deleteGoal&a_id="+q_id);
	grabGoal();
}
grabGoal();

function addCoach(){
	var text = $(".coach-text").val();
	if((text.length > 0)){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addCoach";
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
					grabCoach();
					$(".coach-text").val("");
					$(".coach-text").select();
				}
			}
		);
	}else{
		alert("You didn't enter anything.");
	}
}

function grabCoach(){
	$.ajax({
		url: "actions.php?type=grabCoach&uid="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			$(".coached-by").empty();
			if(parseJSON.data != undefined){
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".coached-by").append("<li><span style='color:yellow;'>"+parseJSON.data[i].text+"</span> <i class='icon-trash icon-white' onclick='deleteCoach("+parseJSON.data[i].id+")'></i></li>");
				}
			}
		}
    });
}

function deleteCoach(q_id){
	$.post("actions.php?type=deleteCoach&a_id="+q_id);
	grabCoach();
}

grabCoach();

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

function grabSports(){
	$.ajax({
		url: "actions.php?type=grabSports",
		success: function(data){
			var parseJSON = $.parseJSON(data);
			//$(".about-me-text").empty();
			if(parseJSON.data != undefined){
				for(var i = 0;i < parseJSON.data.length;i++){
					$(".sport-genres").append("<option value='"+parseJSON.data[i].id+"'>"+parseJSON.data[i].sport+"</option>");
				}
			}
		}
    });
}

grabSports();

</script>
<div style="padding-top:3px; padding-right:5px; padding-left:5px;">
<div class="user-info">
	<table border="0" class="user-info-table" cellspacing="5" width="100%;">
		<tr>
			<th align="left" valign="middle">Sport</th>
			<th align="left" valign="middle">Height/Weight</th>
			<th align="left" valign="middle">Gender</th>
			<th align="left" valign="middle">Lvl. of play</th>
			<th align="left" valign="middle">Education</th>
			<th align="left" valign="middle">Hometown</th>
			<th align="left" valign="middle">Age</th>
			<th align="left" valign="middle"><div class="edit" style="float:right;"><button class="btn btn-mini btn-primary" onclick="editInfo();" style="margin-right:5px;"><span style="color:yellow;">Save</span></button><a href="javascript:cancelInfoEdit();">Cancel</a></th>
			<th rowspan="2">
				<div class="view"><button class="btn btn-small btn-primary" onclick="editInfoDisp();" style='color:yellow;'><i class="icon-edit icon-white"></i>Edit</button></div>
			</th>
		</tr>
		<tr>
			<td valign="middle">
				<div class="view">Basketball</div>
				<div class="edit">
					<select class="sport-genres" style="width:150px;">
					</select>
				</div>
			</td>
			<td valign="middle">
				<div class="view stats">6'8" - 300lbs</div>
				<div class="edit"><input type="text" class="specialty-edit" style="height:25px; width:90px; font-size:13px;" /></div>
			</td>
			<td valign="middle">
				<div class="view gender">Male</div>
				<div class="edit">
					<label style="font-size:13px;"><input type="radio" name="gen" id="gender-edit" value="m" class="gender-edit-male" style="position:relative; bottom:4px;"> Male</label>
					<label style="font-size:13px; margin-top:-7px;"><input type="radio" name="gen" id="gender-edit" value="f" class="gender-edit-female" style="position:relative; bottom:4px;"> Female</label>
				</div>
			</td>
			<td valign="middle">
				<div class="view type">Professional</div>
				<div class="edit">
					<select style='width:110px;'>
						<option value='pro'>Professional</option>
						<option value='col'>College</option>
						<option value='clu'>Club</option>
						<option value='hs'>High School</option>
						<option value='amt'>Amateur</option>
					</select>
				</div>
			</td>
			<td valign="middle">
				<div class="view education">Lower Marion HS</div>
				<div class="edit"><input type="text" class="specialty-edit" style="height:25px; width:100px; font-size:13px;" /></div>
			</td>
			<td valign="middle">
				<div class="view hmtown">Philadelphia, PA</div>
				<div class="edit"><input type="text" class="specialty-edit" style="height:25px; width:100px; font-size:13px;" /></div>
			</td>
			<td valign="middle">
				<div class="view age">35</div>
				<div class="edit"><b>35</b><br /><span class='text-warning'>Can't Edit.</span></div>
			</td>
		</tr>
	</table>
</div>
<div class="about" style="min-height:175px;">
	<div class="about-me-text" style="color:white; margin-right:120px;">

	</div>
	<textarea style="width:100%; height:100%; resize:none; background:none; color:black; display:none;" class="aboutme"></textarea>
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
			<ul class="ach" style='font-size:13px;'>
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
		<td><span style="color:#ffff00; border-bottom:2px solid white;">Personal Goals</span></td>
	</tr>
	<!-- QUOTES AREA -->
	<tr>
		<td>
			<ul class="goal" style='font-size:13px;'>
				<li><span style="color:white;">Life is hard; it's harder if you're stupid. -<i style="color:yellow;">John Wayne</i></span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">When everything is easy one quickly gets stupid. -<i style="color:yellow;">Maxim Gorky</i></span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">No matter how long you stare at it, it always looks phenomenal. -<i style="color:yellow;">Ollie Schindler</i></span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">He's what we call a mouthbreather. -<i style="color:yellow;">Jake Cohen</i></span> <i class="icon-trash icon-white"></i></li>
			</ul>
		</td>
	</tr>
	<tr class="edit-goal">
		<td align="left"><input type="text" class="goal-text" placeholder="Goal..." style="height:24px; margin-right:10px; width:400px;"/><button class="btn btn-mini btn-primary" style="position:relative; bottom:5px;" onclick="addGoal();"><span style="color:yellow;">Save</span></button></td>
	</tr>

	<tr>
		<td><span style="color:#ffff00; border-bottom:2px solid white;">Coached By</span></td>
	</tr>
	<tr>
		<td>
			<ul class="coached-by" style="margin-top:10px; font-size:13px;">
				<li><span style="color:white;">Lady Gaga</span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">ICE T</span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">50 Cent</span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">Fat Joe</span> <i class="icon-trash icon-white"></i></li>
			</ul>
		</td>
	</tr>
	<tr class="coach-goal">
		<td align="left"><input type="text" class="coach-text" placeholder="Coach..." style="height:24px; margin-right:10px; width:200px;"/><button class="btn btn-mini btn-primary" style="position:relative; bottom:5px;" onclick="addCoach();"><span style="color:yellow;">Save</span></button></td>
	</tr>
</table>
</div>