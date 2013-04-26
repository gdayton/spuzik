<?php include("../actions/actions.class.php"); sec_session_start(); ?>
<style type="text/css">
.addLink{
	-moz-border-radius:5px;
	-webkit-border-radius:5px;
	border-radius:5px;
	background-color:rgba(255,255,255,.4);
	padding:10px 10px 0px 10px;
	margin-top:5px;
}.link-wrap{
	background-color:#063d78;
	/*position:relative;
	right:6px;
	bottom:4px;
	margin-right:-12px;*/
	padding:5px;
}.link-content-area{
	margin-top:-5px;
	/*position:relative;
	left:6px;*/
}
</style>
<script type="text/javascript" language="javascript">
function addLink(){
	$(document).ready(function(){
		$(".addLink").slideToggle();
		$(".link-text").val("");
		$(".link-content").val("");
	});
}

function submitLink(){
	$(document).ready(function(){
		if( ($(".link-text").val() != "") && ($(".link-content").val() != "") ){
			$.ajaxSetup({async:false});
			var actionUrl = "actions.php?type=addLink";
			$.post(
				actionUrl,
				{
					link: $(".link-text").val(),
					link_content: $(".link-content").val()
				},
				function(data,status){
					var parseJSON = $.parseJSON(data);
					if(parseJSON.status != "error"){
						$(".addLink").slideUp();
						loadLinksOntoPage();
					}else{
						if(parseJSON.status_msg != "")
							alert(parseJSON.status_msg);
						alert("We were not able to add your link.");
					}
				}
			);
		}else{
			alert("You must fill out all fields.");
		}
	});
}

function removeLink(id){
	$(document).ready(function(){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=removeLink";
		$.post(
			actionUrl,
			{
				link: id
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status != "error"){
					loadLinksOntoPage();
				}else{
					alert("We were not able to remove your link.");
				}
			}
		);
	});
}

function loadLinksOntoPage(){
	$(document).ready(function(){
		$.ajax({
			url: "actions.php?type=getLinks&uid="+user_id,
			success: function(data){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.length > 0){
					$(".link-content-area").empty();
					$(".link-content-area").append("<tr style='background-color:#063d78;'><th style='color:yellow; border-top:1px dashed white; margin-left:10px;' align='left'>Link</th><th style='color:yellow; border-top:1px dashed #FCDC3B;' align='right'>Share</th></tr>");
					var edit = "";
					for(var i = 0;i < parseJSON.length;i++){
						if(user_id == logId){

							edit = "<a href='javascript:removeLink("+parseJSON[i].id+");'><i class='icon-trash icon-white' onclick='javascript:deleteLink();' style='margin-left:3px;'></i></a>";
						}else{
							$(".addlinkbtn").remove(); $(".addLink").remove();
						}
						$(".link-content-area tr:last").after("<tr><td>"+replaceURLWithHTMLLinks(parseJSON[i].link_content, parseJSON[i].link, 18)+"</td><td align='right'><input class='shortURL' type='text' style='height:25px; width:130px; font-size:12px; position:relative; top:3px;' onclick='javascript:this.select();' value='"+parseJSON[i].link_short+"'>"+edit+"</td></tr>");
					}
				}else{
					$(".link-content-area").append("<tr><td colspan='2'>No links have been uploaded.</td></tr>");
				}
			}
		});
  	});
}

function grabClients(){
	$.ajax({
		url: "actions.php?type=grabClients&uid="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			for(var i = 0;i < parseJSON.data.length;i++){
				$(".sponsor-of").append("<option value='"+parseJSON.data[i].id+"'>"+parseJSON.data[i].name+"</option>");
			}
		}
	});
}

function addSponsor(){
	if($(".sponsor-name").val() != ""){
		$.ajaxSetup({async:false});
		var actionUrl = "actions.php?type=addSponsor";
		$.post(
			actionUrl,
			{
				name: $(".sponsor-name").val(),
				w_address: $(".sponsor-address").val(),
				p_url: $(".sponsor-purl").val(),
				c_id: $(".sponsor-of").val()
			},
			function(data,status){
				var parseJSON = $.parseJSON(data);
				if(parseJSON.status == "error"){
					alert(parseJSON.status_msg);
				}else{
					$(".sponsor-name").val("");
					$(".sponsor-address").val("");
					$(".sponsor-purl").val("");
					grabSponsors();
				}
			}
		);
	}else{
		alert("You must enter a name for the sponsor.");
	}
}

function grabSponsors(){
	$(".sponsor-area-holder").empty();
	$.ajax({
		url: "actions.php?type=grabSponsors&u_id="+user_id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON != undefined){
				$(".sponsor-area-holder").html("<tr><td></td><td></td></tr>");
				for(var i = 0;i < parseJSON.data.length;i++){
					var spon_pics = "";
					if(parseJSON.data[i].sponsors != undefined){
						for(var l = 0;l < parseJSON.data[i].sponsors.length;l++){
							spon_pics += "<i style='position:relative; top:5px; font-size:13px; cursor:pointer;' class='icon-trash' onclick='deleteSponsor("+parseJSON.data[i].sponsors[l].id+");'></i>"+replaceURLWithHTMLLinks(parseJSON.data[i].sponsors[l].w_address,"<img src='"+parseJSON.data[i].sponsors[l].p_url+"' width='100px'/>",18);
						}
						$(".sponsor-area-holder tr:last").after("\
							<tr>\
								<td align='center'><span style='color:yellow; font-size:15px; font-weight:bold;'>"+parseJSON.data[i].info.name+"</span></td>\
								<td></td>\
							</tr>\
							<tr>\
								<td valign='top' width='155px;'>\
									<div style='height:125px; overflow:hidden;'>\
										<img class='make-size"+parseJSON.data[i].info.id+"' src='"+parseJSON.data[i].info.photo_url+"' />\
									</div>\
								</td>\
								<td valign='top'>\
									<div style='background-color:white; padding:3px; height:120px;'>\
										"+spon_pics+"\
									</div>\
								</td>\
							</tr>\
						");
					}
					resizeThumbnail(parseJSON.data[i].info.id);
				}
			}
		}
	});
}

function deleteSponsor(id){
	$.post("actions.php?type=deleteSponsor&s_id="+id);
	grabSponsors();
}

function resizeThumbnail(id){
	if( $(".make-size"+id).width() > $(".make-size"+id).height() ){ //wide image
		$(".make-size"+id).attr("style","height:125px");
	}
}

function showThumbnail(){
	$(".preview-img").attr("src",$(".sponsor-purl").val());
}

grabClients();
grabSponsors();

$(document).ready(function(){
	loadLinksOntoPage();
});

function toggleSponsors(){
	$(".edit-sponsor").slideToggle();
}
</script>
<div class="link-wrap">
	<table border='0' width='100%'><tr><td align='center'><button class='btn btn-primary addlinkbtn' onclick='javascript:addLink();' style='color:black; text-align:center;'><span style='color:yellow;'>Add Link</span></button></td></tr></table>
	<div class='addLink' style='display:none;'>
		<button class='btn btncustom' style='color:black; float:right;' onclick='javascript:submitLink();'>Submit</button>
		<input type='text' style='height:30px; width:30%;' class='link-text' placeholder='Link Title' />
		<input type='text' style='height:30px; width:50%;' class='link-content' placeholder='http://' />
	</div>
</div>

<table class="link-content-area stylel" cellpadding="5" cellspacing="5" border="0" width="100%;" style="padding-right:10px;"></table>

<table border="0" width='100%' cellspacing='0' cellpadding='0' class='sponsor-area'>
	<tr>
		<th colspan='2' style='color:yellow; border-top:1px solid #FCDC3B; background-color:#063d78; padding-top:5px; padding-bottom:5px;' align='center'>Sponsors</th>
	</tr>
	<tr>
		<td colspan='2' align='center'><button type='button' class='btn btn-primary' style='color:yellow; margin-top:3px; margin-bottom:3px;' onclick='toggleSponsors();'>Add Sponsor</button></td>
	</tr>
	<tr>
		<td align='left'>
			<div class='edit-sponsor' style='display:none;'>
				<table border='0' width='100%;'>
					<tr>
						<td align='right' style='color:yellow;'>Sponsor</td>
						<td>
							<input type='text' class='sponsor-name' style='height:25px; position:relative; top:3px; left:2px;' placeholder='Sponsor...'/>
						</td>
					</tr>
					<tr>
						<td align='right' style='color:yellow;'>Website Address</td>
						<td>
							<input type='text' class='sponsor-address' style='height:25px; position:relative; top:3px; left:2px;' placeholder='http://' value='http://' />
						</td>
					</tr>
					<tr>
						<td align='right' style='color:yellow;'>Photo URL</td>
						<td>
							<input type='text' class='sponsor-purl' style='height:25px; position:relative; top:3px; left:2px;' placeholder='Photo URL...' onkeyup='showThumbnail();' />
						</td>
					</tr>
					<tr>
						<td align='right' style='color:yellow;'>Sponsor of</td>
						<td>
							<select class='sponsor-of' style='margin-left:2px; width:205px;'>

							</select>
						</td>
					</tr>
					<tr>
						<td colspan='2' align="right">
							<button type='button' class='btn btn-primary' style='color:yellow; margin-right:75px;' onclick='addSponsor();'>Save</button>
						</td>
					</tr>
				</table>
			</div>
		</td>
		<td>
			<img class='preview-img' src='' height='150px;'/>
		</td>
	</tr>
</table>
<table width='100%;' class='sponsor-area-holder' style='margin-top:10px;'>
	<tr>
		<td></td>
		<td></td>
	</tr>
</table>