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
	color:black;
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
	/*background-image:url('http://i.imm.io/W0y3.jpeg'); WO04 X6Dg */
	background-image:url('http://i.imm.io/X6Dg.jpeg');
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
</script>
<div style="padding-top:3px; padding-right:5px; padding-left:5px;">
<div class="user-info">
	<table border="0" class="user-info-table" cellspacing="5" width="100%;">
		<tr>
			<th align="left" valign="middle">Genre</th>
			<th align="left" valign="middle">Specialty</th>
			<th align="left" valign="middle">Experience</th>
			<th align="left" valign="middle">Gender</th>
			<th align="left" valign="middle"><div class="edit" style="float:right;"><button class="btn btn-mini btn-primary" onclick="editInfo();" style="margin-right:5px;"><span style="color:yellow;">Save</span></button><a href="javascript:cancelInfoEdit();" style='color:blue'>Cancel</a></div>Email</th>
			<th rowspan="2">
				<div class="view"><button class="btn btn-small btn-primary" onclick="editInfoDisp();" style='color:yellow;'><i class="icon-edit"></i>Edit</button></div>
			</th>
		</tr>
		<tr>
			<td valign="middle">
				<div class="view">Blues</div>
				<div class="edit">
					<select class="music-genres" style="width:150px;">
					</select>
				</div>
			</td>
			<td valign="middle">
				<div class="view specialty"></div>
				<div class="edit"><input type="text" class="specialty-edit" style="height:25px; width:100px; font-size:13px;" /></div>
			</td>
			<td valign="middle">
				<div class="view yrsofexp"></div>
				<div class="edit">
					<select class="yrs-exp" style="width:75px;">
					</select>
				</div>
			</td>
			<td valign="middle">
				<div class="view gender"></div>
				<div class="edit">
					<label style="font-size:13px;"><input type="radio" name="gen" id="gender-edit" value="m" class="gender-edit-male" style="position:relative; bottom:4px;"> Male</label>
					<label style="font-size:13px; margin-top:-7px;"><input type="radio" name="gen" id="gender-edit" value="f" class="gender-edit-female" style="position:relative; bottom:4px;"> Female</label>
				</div>
			</td>
			<td valign="middle">
				<div class="email"></div>
				<div class="edit" style="color:#f9b14c;">Email cannot be changed.</div>
			</td>
		</tr>
	</table>
</div>
<div class="about" style="min-height:175px;">
	<div class="about-me-text"></div>
	<div style='margin-left:100px;'>
	<span style='color:yellow; font-size:13px;'>This is some text.This is some text.This is some text.This is some text.This is some text.<br /><br />
	This is some text.This is some text.This is some text.This is some text.This is some text.<br /><br />
	This is some text.This is some text.This is some text.This is some text.This is some text.<br /><br />
	</span>
	</div>
	<textarea style="width:100%; height:100%; resize:none; background:none; color:white; display:none;" class="aboutme"></textarea>
</div>
<table border="0" width="100%;">
	<tr>
		<td align="right">
		<button class="btn btn-mini btn-primary edit-aboutme"><span style="color:yellow;" onclick="editPullUp();">Edit</span></button>
		<button class="btn btn-mini btn-primary save-aboutme" style="display:none;"><span style="color:yellow;" onclick="editAboutMe();">Save</span></button></td>
	</tr>

	<tr>
		<td><span style="color:#ffff00; border-bottom:2px solid white;">Favorite Quotes/ Lyrics</span></td>
	</tr>
	<!-- QUOTES AREA -->
	<tr>
		<td>
			<ul class="quotes">
				<li><span style="color:white;">Life is hard; it's harder if you're stupid. -<i style="color:yellow;">John Wayne</i></span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">When everything is easy one quickly gets stupid. -<i style="color:yellow;">Maxim Gorky</i></span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">No matter how long you stare at it, it always looks phenomenal. -<i style="color:yellow;">Ollie Schindler</i></span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">He's what we call a mouthbreather. -<i style="color:yellow;">Jake Cohen</i></span> <i class="icon-trash icon-white"></i></li>
			</ul>
		</td>
	</tr>
	<tr class="edit-quote">
		<td align="left"><input type="text" class="quote-text" placeholder="Quote/Lyric..." style="height:24px; margin-right:10px; width:200px;"/><input type="text" class="quote-person" placeholder="Author..." style="height:24px; margin-right:10px; width:200px;"/><button class="btn btn-mini btn-primary" style="position:relative; bottom:5px;" onclick="addQuote();"><span style="color:yellow;">Save</span></button></td>
	</tr>
	<tr>
		<td style="height:20px;"></td>
	</tr>

	<tr>
		<td><span style="color:#ffff00; border-bottom:2px solid white;">Memory Zone</span></td>
	</tr>
	<tr>
		<td>
			<table border="0" class="memory" cellpadding="5">
			</table>
		</td>
	</tr>
	<tr class="edit-mem">
		<td align="left">
			<input type="text" placeholder="Year..." class="memory-date" style="height:24px; width:60px; margin-right:5px;"/>
			<textarea style="width:50%; height:20px; width:200px; resize:none; margin-right:7px;" placeholder="Memory..." class="memory-text"></textarea>
			<button class="btn btn-mini btn-primary" style="position:relative; bottom:5px;" onclick="addMemory();"><span style="color:yellow;">Save</span></button>
		</td>
	</td>

	<tr>
		<td><span style="color:#ffff00; border-bottom:2px solid white;">Inspirations</span></td>
	</tr>
	<tr>
		<td>
			<ul class="soundlike" style="margin-top:10px;">
				<li><span style="color:white;">Lady Gaga</span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">ICE T</span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">50 Cent</span> <i class="icon-trash icon-white"></i></li>
				<li><span style="color:white;">Fat Joe</span> <i class="icon-trash icon-white"></i></li>
			</ul>
		</td>
	</tr>
	<tr class="edit-mem">
		<td align="left">
			<input type="text" placeholder="Name..." class="memory-date" style="height:24px; margin-right:5px;"/>
			<button class="btn btn-mini btn-primary" style="position:relative; bottom:5px;" onclick="addMemory();"><span style="color:yellow;">Save</span></button>
		</td>
	</td>
</table>
</div>