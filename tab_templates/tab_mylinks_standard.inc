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
	background-color:white;
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
					$(".link-content-area").append("<tr style='background-color:white;'><th style='color:black; border-bottom:1px dashed black; margin-left:10px;' align='left'>Link</th><th style='color:black; border-bottom:1px dashed black;' align='center'>Share</th></tr>");
					var edit = "";
					for(var i = 0;i < parseJSON.length;i++){
						if(user_id == logId){

							edit = "<a href='javascript:removeLink("+parseJSON[i].id+");'><i class='icon-trash' onclick='javascript:deleteLink();' style='margin-left:3px;'></i></a>";
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

$(document).ready(function(){
	loadLinksOntoPage();
});
</script>
<style type="text/css">
.link-content-area a{
	color:blue !important;
}
</style>
<div class="link-wrap">
	<table border='0' width='100%'><tr><td align='center'><button class='btn btncustomwhite addlinkbtn' onclick='javascript:addLink();' style='color:black; text-align:center; background-color:white;'><span style='color:#156ed4;'>Add Link</span></button></td></tr></table>
	<div class='addLink' style='display:none;'>
		<button class='btn btncustom' style='color:black; float:right;' onclick='javascript:submitLink();'>Submit</button>
		<input type='text' style='height:30px; width:30%;' class='link-text' placeholder='Link Title' />
		<input type='text' style='height:30px; width:50%;' class='link-content' placeholder='http://' />
	</div>
</div>

<table class="link-content-area stylel" cellpadding="5" cellspacing="5" border="0" width="100%;" style="padding-right:10px;"></table>