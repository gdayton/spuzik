<script>
$.ajax({
	url: "actions.php?type=getPhotos&uid="+user_id,
	success: function(data){
		var parseJSON = $.parseJSON(data);
		if(parseJSON.data != undefined){
			parseJSON.data.shuffle();
			//$(".init-image-zn").attr("src","/usr_content/pics/"+parseJSON.data[0]+".jpg");
			$(".img-cntr-zn").append("<img src='/usr_content/pics/"+parseJSON.data[0]+".jpg' style='width:100%; top:0px; left:0px; z-index:10000; position:fixed;' />");
		}

		if(parseJSON.status != "error"){
			if(parseJSON.data != undefined){
				for(var i = 1;i < parseJSON.data.length;i++){
					$(".img-cntr-zn").append("<img src='/usr_content/pics/"+parseJSON.data[i]+".jpg' style='width:100%; top:0px; left:0px; z-index:10000; position:fixed;'/>");
				}
				//$(".photo-ctr").html(parseJSON.data.length);
				$('.img-cntr-zn').cycle({
					fx: 'fade',
					timeout: 4000
				});
			}
		}else{
			alert("There was an error obtaining your photos.");
		}
	}
});
</script>
<button class='btn btn-small btn-warning' onclick="$('.img-cntr-zn').hide(); $(this).hide();" style='position:fixed; top:100px; left:20px; z-index:10002; color:black;'>Back</button>
<div class="img-cntr-zn" style='width:100%; top:0px; left:0px; z-index:10000; position:fixed; background-color:white; margin-bottom:20%;'>
	<!--<img class="init-img-zn" src="" style="width:100%; top:0px; left:0px; z-index:10000; position:fixed;" />-->
</div>