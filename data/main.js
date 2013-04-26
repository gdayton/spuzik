/*
	Functions for feed items
*/
function showComment(id){
	$(".comment-area-show"+id).slideToggle();
	$(".comment-area-show"+id).elastic();
	$(".comment-area-show-button"+id).slideToggle();
}

function getClaps(id){
	$.ajax({
		url: "actions.php?type=grabClaps&r_id="+id,
		success: function(data){
			var parseJSON = $.parseJSON(data);
			if(parseJSON.status != "error"){
				if(parseJSON.data != undefined){
					$(".clap"+id).html(parseJSON.data[0]);
				}
			}else{
				alert("There was an error obtaining your photos.");
			}
		}
	});
}

function loadMore(id){
	$(".comment-hidden"+id).slideToggle();
}

function deleteComment(id, id2){
	var yn = confirm("Are you sure you want to remove this comment?");
	if(yn){
		$.post("actions.php?type=deleteComment&r_id="+id);
		grabComments2(id2);
	}
}

function displayVideo(id){
	$(".video"+id).show();
	$(".vid-pic"+id).hide();
	$(".vid-pic-play"+id).hide();
}

function setContent(cId,type){
	contId = cId;
	contType = type;
	$(".selected-item").show();
}