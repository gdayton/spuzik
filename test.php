<html>
	<head>
		<script src="//ajax.googleapis.com/ajax/libs/jquery/2.0.0/jquery.min.js"></script>
    	<script src="http://ajax.cdnjs.com/ajax/libs/underscore.js/1.1.4/underscore-min.js"></script>
    	<script src="http://ajax.cdnjs.com/ajax/libs/backbone.js/0.3.3/backbone-min.js"></script>
    	<!--<script src="https://raw.github.com/documentcloud/backbone/master/backbone.js"></script>-->
    	<link rel="stylesheet" type="text/css" href="/data/bootstrap/css/bootstrap.min.css" />
		<link rel="stylesheet" type="text/css" href="/data/uploadifive.css" />
		<link rel="stylesheet" type="text/css" href="/data/main.css" />
		<link href='http://fonts.googleapis.com/css?family=Nosifer|Merienda|Satisfy|Medula+One|Covered+By+Your+Grace|Molle|Arbutus|Ranchers|Diplomata+SC|Bigelow+Rules|Emblema+One|Faster+One' rel='stylesheet' type='text/css'>
		<script src="/data/bootstrap/js/bootstrap.min.js"></script>
		<script src="/data/main.js"></script>
		<script src="/actions/swfobject.js"></script>
	  	<script src="/actions/grooveshark.js"></script>
	  	<script src="/data/waypoints.js"></script>
	</head>
	<body style="background-color:black;">
		<script type="text/template" id="post_template">
			<% _.each(feeds, function(feed){ %>
				<div class='notif-i'>
					<table border="0" width="100%" id="post">
						<tr>
							<td valign="top" width="40px;"><img src="/usr_content/pics/<%= feed.name.profile_pic %>_t.jpg" class="img-rounded" width="40px" height="40px"><img src="/data/img/flag_red.png" style="margin-top:3px; display:block; margin-left:auto; margin-right:auto;" rel="tooltip" class="flag-post" title="Flag" data-placement="bottom" data-trigger="hover" /></td>
							<td style="padding-left:10px; font-size:12px; color:white;" valign="top">
								<div style="float:right;">
									<img src="/data/img/remove.png" onclick="removePosting('<%= feed.id %>')" rel="tooltip" title="Remove" data-placement="left" data-trigger="hover" style="width:12px; height:12px;"/></div><b style='color:#ffff00;'><a style="color:#ffff33;" href="/?p=profile&id='<%= feed.u_id %>'"><%= feed.name.fname %> <%= feed.name.lname %></a></b>
							<div class="text">
								<%= feed.text %>
								<%= feed.extra_formatted %>
							</div>
							<table border='0' width='100%'>
								<tr>
									<td valign='top'>
										<div class='comment' style='color:#ffff00;'><div><span class='comment"<%= feed.id %>"'></span> <span style='display:none;' class='comment-hidden"<%= feed.id %>"'></span></div><a class='comment-load"<%= feed.id %>"' style='display:none;' href='javascript:loadMore("<%= feed.id %>");'></a><textarea class='comment-area-show"<%= feed.id %>"' type='text' placeholder='Comment...' style='resize:none; display:none; height:30px; font-size:12px; width:100%; margin-top:3px;' /></textarea><button class='btn btn-mini btncustom comment-area-show-button"<%= feed.id %>"' style='color:black; float:right; display:none;' onclick='makeComment2("<%= feed.id %>");'>Comment</button></span>
									</td>
									<td valign='bottom' align='right'>
										<span style='font-size:12px; color:white;'><%= feed.date %> ago</span>
										<div class='btn-group'>
											<button class='btn btn-small user_type btncustom btn-clap' rel='tooltip' title='Clap' data-placement='top' data-trigger='hover'><img src='http://i.imm.io/14rOO.png' width='15px' height='15px' style='position:relative; bottom:2px;'/> <span style='color:#2727ff; font-weight:700;' class='clap"<%= feed.id %>"'>0</span></button>
											<button class='btn btn-small user_type btncustom' id='commentBTN' style='height:26px;' rel='tooltip' title='Respond' data-placement='top' data-trigger='hover'><img src='http://i.imm.io/14rOG.png' width='20px' height='20px' style='position:relative; bottom:2px;'/></button>
										</div>
									</td>
								</tr>
							</table>
							</td>
						</tr>
					</table>
				</div>
			<% }); %>
		</script>

		<style type="text/css">
			#post .text{
				font-size:16px;
				color:white;
			}
		</style>

		<script type="text/javascript">
			var prms;
			// Define the model
			FeedItem = Backbone.Model.extend();

			// Define the collection
			Feeds = Backbone.Collection.extend({
				model: FeedItem,
				url: '/actions.php?type=getPostings&p_id=25', //datastream URL here
				parse: function(response) {
					return response.data;
				}/*,
				sync: function(method, model, options) {
					var that = this;

					var params = _.extend({
						type: 'GET',
						dataType: 'jsonp',
						url: '/actions.php?type=getPostings&p_id=17',
						processData: false
					}, options);

					return $.ajax(params);
				}*/
			});

			//The view
			FeedsView = Backbone.View.extend({
				initialize: function() {
			      this.el = ".feed-holder";
				  this.collection = new Feeds;
				  var that = this;
				  this.collection.fetch({
					success: function () {
						that.render();
					}
				  });
				  _.bindAll(this, 'render');
				},
				events: {
					"click #commentBTN": "postComment"
				},
				postComment: function(evt){
					//evt.preventDefault();
					alert("Post comment alerted");
				},
				template: _.template($('#post_template').html()),
				render: function() {
					var prms = this.collection.toJSON();
					for(var i = 0;i < prms.length;i++){
						if(prms[i].type == 3){ //link
							prms[i].extra_formatted = "LINK VIEW";
						}else if(prms[i].type == 1){ //photo
							prms[i].extra_formatted = "<div class='ex-img'>\
															<img onclick='launchModal(0,\""+prms[i].text_add+"\");' style='cursor:pointer;' src='/usr_content/pics/"+prms[i].text_add+"_w.jpg'/>\
														</div>";
						}else if(prms[i].type == 2){ //video
							prms[i].extra_formatted = "<div class='video-view'>\
															<img src='/data/img/play_btn.png' width='45px;' onclick='displayVideo("+prms[i].id+");' class='vid-pic-play"+prms[i].id+"' style='position:relative; cursor:pointer; top:75px; left:155px;'/>\
															<img class='vid-pic"+prms[i].id+"' width='336' height='252' style='cursor:pointer; margin-left:auto; margin-top:-40px; margin-right:auto; display:block;' onclick='displayVideo("+prms[i].id+");' src='http://img.youtube.com/vi/"+prms[i].text_add+"/mqdefault.jpg' />\
															<object width='336' height='252' class='video"+prms[i].id+"' style='display:none;'>\
															  <param name='movie' value='https://www.youtube.com/v/"+prms[i].text_add+"?controls=0&showinfo=0&version=3&autoplay=1'></param>\
															  <param name='allowFullScreen' value='true'></param>\
															  <param name='allowScriptAccess' value='always'></param>\
															  <embed src='https://www.youtube.com/v/"+prms[i].text_add+"?showinfo=0&version=3&autoplay=1' type='application/x-shockwave-flash' allowfullscreen='true' allowScriptAccess='always' width='336' height='252'></embed>\
															</object>\
														</div>";
						}
					}
					$(this.el).html(this.template({ feeds: prms }));
				}
			});

			/*
			CommentsView = Backbone.View.extend({
				initialize: function(){

				},
				template: _.template($('#comment_template').html())
			});
			*/

			var app = new FeedsView( {el: "feed-holder" } );
		</script>

		<div class="feed-holder" style="width:432px;"></div>
	</body>
</html>