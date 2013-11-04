<style>
.ybox{
	background-color:yellow;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
	border:0px solid #000;
	width:500px;
	margin:0px auto;
}.error{
	background-color:red;
	color:white;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
	border:0px solid #000;
	padding:5px;
	font-weight:bold;
}.success{
	background-color:green;
	color:white;
	-moz-border-radius:5px;
	border-radius:5px;
	-webkit-border-radius:5px;
	border:0px solid #000;
	padding:5px;
	font-weight:bold;
}
</style>
<script>
$(document).ready(function(){
	grabSports();
	grabGenres();

	$(".sports-item").change(refreshCounters());
	$(".music-item").change(refreshCounters());
});

function refreshCounters(){
	var sports = [];
	$('.sports-selection input:checked').each(function() {
		sports.push(this.value);
	});

	var music = [];
	$('.music-selection input:checked').each(function() {
		music.push(this.value);
	});

	if(sports.length < 2){
		$(".sports-counter").html( (2 - sports.length) );
	}else{
		$(".sports-counter").html("many");
	}

	if(music.length < 2){
		$(".genre-counter").html( (2 - music.length) );
	}else{
		$(".genre-counter").html("many");
	}
}

function grabSports(){
	$.ajax({
		url: "actions.php?type=grabSports",
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					for(var i = 0;i < parseJSON.data.length;i++){
						$(".sports-selection").append("<label><input type='checkbox' name='sports-selection-item' class='sports-item' value='"+parseJSON.data[i].id+"' onclick='refreshCounters();'/>"+parseJSON.data[i].sport+"</label>");
					}
				}
			}else{
				alert("There was an error grabbing the sports.");
			}
		}
	});
}

function grabGenres(){
	$.ajax({
		url: "actions.php?type=grabGenres",
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					for(var i = 0;i < parseJSON.data.length;i++){
						$(".music-selection").append("<label><input type='checkbox' name='music-selection-item' class='music-item' value='"+parseJSON.data[i].id+"' onclick='refreshCounters();'/>"+parseJSON.data[i].genre+"</label>");
					}
				}
			}else{
				alert("There was an error grabbing the genres.");
			}
		}
	});
}
</script>
<div class='ybox'>
	<h3 style='color:black;'>
	<?php
		/*if(isset($_GET['token'])){
			$res = $u->verif($_GET['token']);
			echo "<span class='success'>Success!</span> Your account has now been verified.<br /><center><b style='font-size:18px; color:black;'>Redirecting in 3 seconds...</b></center>";
		}else{
			echo "<span class='error'>ERROR</span> There was an error in processing this token.<br /><center><b style='font-size:18px; color:black;'>Redirecting in 3 seconds...</b></center>";
		}*/
	?>
	</h3>
	<div style="width:100%; background-image:url('http://i43.tinypic.com/juydg9.png'); -moz-border-top-left-radius:5px; -webkit-border-top-left-radius:5px; border-top-left-radius:5px; -moz-border-top-right-radius:5px; -webkit-border-top-right-radius:5px; border-top-right-radius:5px; height:75px;">
		<div style="padding:10px 5px 25px 5px;">
			<span style="color:white; font-size:28px; font-weight:bold; position:relative; top:18px; left:10px;">Optimize your experience...</span>
			<!--<span style="color:#32cd32; float:right; margin:10px; font-size:20px;">&#8532; Complete</span>-->
		</div>
	</div>
	<div class="form-horizontal" style="padding:10px;">
		<div class="control-group">
			<label class="control-label" for="inputGender">Gender</label>
			<div class="controls">
				<label><input type="radio" name="genderRadio" id="inputGender" value="m" placeholder=""><span style="position:relative; top:4px; left:2px;"><img src="http://i40.tinypic.com/wsnuac.png" />Male</span></label>
				<label><input type="radio" name="genderRadio" id="inputGender" value="f" placeholder=""><span style="position:relative; top:4px; left:2px;"><img src="http://i42.tinypic.com/2ih7706.png" />Female</span></label>
			</div>
		</div>
		<div class="control-group">
			<label class="control-label" for="inputZip">Zipcode</label>
			<div class="controls">
				<input type="text" class="zip" placeholder="Zipcode..." style="height:30px;"/>
			</div>
		</div>
	</div>
	<style type="text/css">
	.sports-selection{
		height:300px;
		overflow:scroll;
		width:100%;
	}.sports-selection label{
		position:relative;
		bottom:3px;
		left:3px;
		color:black;
	}.sports-selection input{
		position:relative;
		bottom:3px;
		right:3px;
	}

	.music-selection{
		height:300px;
		overflow:scroll;
		width:100%;
	}.music-selection label{
		position:relative;
		bottom:3px;
		left:3px;
		color:black;
	}.music-selection input{
		position:relative;
		bottom:3px;
		right:3px;
	}
	</style>
	<table border="0" cellpadding="0" cellspacing="0" width="100%;">
		<tr>
			<td align="center">
				<div style="float:right; position:relative; right:10px;">
					<span style="color:black; font-size:14px;">Select <b class="sports-counter" style="color:black;">2</b> more</span>
				</div>
				<img src="http://i.imm.io/1bN1x.png" width="20px;" height="20px;"/><b style="color:black; position:relative; left:2px; top:2px;">Sports</b><br />
			</td>
			<td align="center">
				<div style="float:right; position:relative; right:10px;">
					<span style="color:black; font-size:14px;">Select <b class="genre-counter" style="color:black;">2</b> more</span>
				</div>
				<img src="http://i.imm.io/1bN1X.png" width="20px;" height="20px;"/><b style="color:black; position:relative; left:2px; top:2px;">Music</b><br />
			</td>
		</tr>
		<tr>
			<td width="50%;" style="padding:20px;">
				<div class="sports-selection"></div>
			</td>
			<td width="50%;" style="padding:20px;">
				<div class="music-selection"></div>
			</td>
		</tr>
		<tr>
			<td></td>
			<td align="right"><button class="btn btn-primary" style="margin:10px;">Save</button></td>
		</tr>
	</table>
</div>
<script>

</script>