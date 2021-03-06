<?php
include("actions/actions.class.php");
sec_session_start();
ob_start();
?>
<html>
	<head>
		<title>Spuzik | The Social Network for Sports and Music</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
		<link rel="stylesheet" type="text/css" href="/data/bootstrap/css/bootstrap.min.css" />
		<link rel="stylesheet" type="text/css" href="/data/uploadifive.css" />
		<link rel="stylesheet" type="text/css" href="/data/main.css" />
		<link href='http://fonts.googleapis.com/css?family=Nosifer|Autour+One|Cinzel|Roboto+Condensed|Permanent+Marker|Lily+Script+One|Milonga|Merienda|Satisfy|Medula+One|Covered+By+Your+Grace|Molle|Arbutus|Ranchers|Diplomata+SC|Bigelow+Rules|Emblema+One|Faster+One' rel='stylesheet' type='text/css'>
		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
		<script src="//ajax.googleapis.com/ajax/libs/jqueryui/1.9.2/jquery-ui.min.js"></script>
		<script src="/data/bootstrap/js/bootstrap.min.js"></script>
		<script src="/data/jquery.uploadifive-v1.0.js"></script>
		<script src="/data/jquery.elastic.min.js"></script>
		<script src="/data/jquery.cycle.all.latest.js"></script>
		<script src="/data/main.js"></script>
		<script src="/actions/swfobject.js"></script>
	  	<script src="/actions/grooveshark.js"></script>
	  	<script src="/data/waypoints.js"></script>
	  	<script src="/data/jquery.fineuploader-3.7.0.min.js"></script>
	  	<link rel="shortcut icon" href="/data/img/spuzik_icon.ico" type="image/x-icon" />
	</head>
	<body>
		<script>
			(function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
			(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
			m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
			})(window,document,'script','//www.google-analytics.com/analytics.js','ga');

			ga('create', 'UA-39389250-1', '54.243.129.126');
			ga('send', 'pageview');

			function replaceURLWithHTMLLinks(text,link_verbage, textSize) {
				if(isNaN(textSize))
					textSize = 18;
				var replacedText, replacePattern1, replacePattern2, replacePattern3;

				//URLs starting with http://, https://, or ftp://
				replacePattern1 = /(\b(https?|ftp):\/\/[-A-Z0-9+&@#\/%?=~_|!:,.;]*[-A-Z0-9+&@#\/%=~_|])/gim;
				replacedText = text.replace(replacePattern1, "<a target='_blank' style='font-size:"+textSize+"px; font-weight:450; color:yellow;' href='$1'>"+link_verbage+"</a>");

				//URLs starting with "www." (without // before it, or it'd re-link the ones done above).
				replacePattern2 = /(^|[^\/])(www\.[\S]+(\b|$))/gim;
				replacedText = replacedText.replace(replacePattern2, "$1<a target='_blank' style='font-size:"+textSize+"px; font-weight:450; color:yellow;' href='http://$2'>"+link_verbage+"</a>");

				//Change email addresses to mailto:: links.
				replacePattern3 = /(\w+@[a-zA-Z_]+?\.[a-zA-Z]{2,6})/gim;
				replacedText = replacedText.replace(replacePattern3, "<a target='_blank' style='font-size:"+textSize+"px; font-weight:450; color:yellow;' href='mailto:$1'>"+link_verbage+"</a>");

				return replacedText;
			}

			Array.prototype.move = function (old_index, new_index) {
				if (new_index >= this.length) {
					var k = new_index - this.length;
					while ((k--) + 1) {
						this.push(undefined);
					}
				}
				this.splice(new_index, 0, this.splice(old_index, 1)[0]);
				return this; // for testing purposes
			};

			Array.prototype.shuffle = function() {
			   var i = this.length;
			   while (--i) {
				  var j = Math.floor(Math.random() * (i + 1))
				  var temp = this[i];
				  this[i] = this[j];
				  this[j] = temp;
			   }

			   return this; // for convenience, in case we want a reference to the array
			};

			function getURLParameter(name){
				return decodeURI(
					(RegExp(name + '=' + '(.+?)(&|$)').exec(location.search)||[,null])[1]
				);
			}

			function switchPage(pid, args) {
				if(arguments.length === 1) { //page with no parameters
					window.history.pushState("", "Spuzik", "/?p="+pid);
					$(".site-content").load("actions.php?type=switchPage&page="+pid);
					loadBackground(pid);
				}else{    //page with parameters for loading args is an array with added items
					var argsString = "";

					for(var i = 0;i < args.length;i++) {
						argsString += "&"+args[i].key+"="+args[i].val;
						alert(args[i].key);
					}
					window.history.pushState("", "Spuzik", "/?p="+pid+""+argsString);
					$(".site-content").empty();
					$(".site-content").load("actions.php?type=switchPage&page="+pid+""+argsString);
					loadBackground(id);
				}
			}

			var logId = <?php echo ( isset($_SESSION['user_id']) ? $_SESSION['user_id'] : 0) .";" ?>

			<?php
				$u = new User();
				$userInfo = $u->userInfo($_SESSION['user_id']);
			?>
			var profileSongID = <?php echo ( isset($userInfo['profile_music']) ? $userInfo['profile_music'] : 0 ).";"; ?>
			function loadBackground(pid){
				if(pid == ""){
					$(".css-content").html("body{\
						background-color:#179bff;\
						background-position: center center;\
						background-repeat: no-repeat;\
						/*background-color:#173aff;*/\
						font-family:Helvetica;\
					}");
				}else if(pid == "thoughtstream"){
					$(".css-content").html("body{\
						/*background: -webkit-gradient(radial, center center, 0, center center, 460, from(#2727ff), to(#0000f3));\
						background: -webkit-radial-gradient(circle, #2727ff, #0000f3);\
						background: -moz-radial-gradient(circle, #2727ff, #0000f3);\
						background: -ms-radial-gradient(circle, #2727ff, #0000f3);\
						background-position: center center;\
						background-repeat: no-repeat;*/\
						background-color:white;\
						font-family:Helvetica;\
					}");
				}else if(pid == "notifications"){
					var htmladd = "";
					if(<?php echo strlen($userInfo['home_pic']) ?> > 0){
						htmladd = "background-image:url('/usr_content/pics/<?php echo $userInfo['home_pic'] ?>.jpg');";
					}else{
						htmladd = "background-image:url('http://54.243.129.126/usr_content/pics/512061ec972bf_w.jpg');";
					}
					$(".css-content").html("body{\
						"+htmladd+"\
						background-clip:padding-box;\
						background-size:100%; 100%;\
						font-family:Helvetica;\
					}");
				}else if(pid == "main"){
					$(".css-content").html("body{\
						background-color:#173aff;\
						font-family:Helvetica;\
					}");
				}else if(pid == "unite"){
					$(".css-content").html("body{\
						background-color:white;\
					}");
				}else if(pid == "verif"){
					$(".css-content").html("body{\
						background-color:#173aff;\
					}");
				}else{
					$(".css-content").html("body{\
						background-color:white;\
						font-family:Helvetica;\
					}");
				}
			}

		</script>
		<style type="text/css" class="css-content">
		<?php
		$u = new User();
		$userInfo = $u->userInfo($_SESSION['user_id']);
		$file = $_REQUEST['p'];
		//if(!isset($file) || $file == "main" || $file == "signin") {
		echo "body{
			/*background-color:#173aff;*/
			/*background-position: center center;
			background-repeat: no-repeat;*/";
			if($file == "thoughtstream"){
				echo "background-color:white;";
				//echo "background-size:100% 100%;";
				//echo "background-image:url('http://i39.tinypic.com/nbcgt2.png');";
			}else if($file == "notifications"){
				if(strlen($userInfo['home_pic']) > 0){
					echo "background-image:url('/usr_content/pics/".$userInfo['home_pic'].".jpg');";
				}else{
					echo "background-image:url('http://54.243.129.126/usr_content/pics/512061ec972bf_w.jpg');";
				}
				echo "background-clip:padding-box;
				background-repeat:no-repeat;
				background-size:100% 100%;";
			}else if($file == ""){
				//echo "background-color:#179bff;";
				//echo "background-image:url('http://i.imm.io/1ea0P.png');";
				//echo "background-size:100% 100%;";
				//echo "width:100%;";
				echo "background-repeat:no-repeat;
				background-size:100% 100%;";
				//echo "background-image:url('http://wallpoh.com/wp-content/uploads/2013/03/Skyrim-Wallpaper-1920x1080.jpg');";
				//echo "background-image:url('http://awesomewallpapers.files.wordpress.com/2010/08/pepsi_ms-desktop-4-0112.jpg');";
				//echo "background-image:url('http://2.bp.blogspot.com/-Vcftg4BT8jM/TrSohajSD7I/AAAAAAAAHjk/9ix52KPvxKg/s1600/Qualcomm%2BStadium1.jpg');";
				//echo "background-image:url('http://tnjn.com/content/storyimage/2012/09/06/Screen_Shot_2012-09-06_at_9.40.45_PM.box.png');";
				echo "background-image:url('http://www.erikvermeulen.com/wp-content/uploads/2012/08/rock-crowd.jpeg');";
				//echo "background-image:url('http://54.243.129.126/usr_content/pics/5124642f3e532.jpg');";
				//echo "background-image:url('http://i44.tinypic.com/25un045.jpg');";
			}else if($file == "main"){
				echo "background-color:#179bff;";
			}else if($file == "unite"){
				echo "background-color:white;";
			}else if ($file == "verif"){
				echo "background-color:#173aff;";
			}else{
				echo "background-color:white; /* #0e0eff #156ed4 3B5998 */";
				//echo "background-image:url('http://i39.tinypic.com/nbcgt2.png');";
			}

			echo "font-family:Helvetica;
		}";
		//}else{
		//	echo "body{ background-color:#003F87; /* Navajo White: FFDEAD */ }";
		//}
		?>
		</style>
		<style type="text/css">
		html, body{
			height:100%;
			width:100%;
		}.signup{
			-moz-border-radius:5px;
			-webkit-border-radius:5px;
			border-radius:5px;
			border:0px solid #000;
			background-color:rgb(255,255,255);
			padding:10px;
		}.posmid{
			position:relative;
			top:100px;
		}.ind-act{
			cursor:pointer;
			width:100%;
			margin-left:-10px;
			padding:10px;
			padding-left:20px;
			padding-right:0px;
		}.ind-sel{
			background-color:#1a82f7;
			color:white;
		}.arrow{
			padding-right:10px;
		}h1,h2,h3,h4,h5,h6,h7,li,b,i,td{
			color:white;
		}a{
			color:#FCDC3B;
		}a:hover{
			color:yellow;
		}.ui-datepicker{
			background-color:white;
			padding:3px;
			-moz-border-radius:4px;
			-webkit-border-radius:4px;
			border-radius:4px;
			border:0px solid #000;
		}.ui-datepicker-header{
			color:black;
		}.ui-datepicker-calendar tr td{
			color:black;
		}.ui-datepicker-year{
			color:black;
		}.ui-datepicker-month{
			color:black;
		}.ui-datepicker-prev{
			float:left;
			cursor:nw-resize;
		}.ui-datepicker-prev a span{
			color:blue;
		}.ui-datepicker-next{
			float:right;
			cursor:ne-resize;
		}.ui-datepicker-next a span{
			color:blue;
		}.ui-datepicker a{
			color:blue;
		}

		/* BUG CSS */
		.bug{
			position:fixed;
			bottom:0px;
			left:0px;
			float:left;
			z-index:1000;
			padding:2px;
		}.bug .beta{
			background-color:red;
			padding:2px;
			color:white;
			font-size:13px;
			margin-right:3px;
		}.terms{
			position:fixed;
			bottom:0px;
			right:0px;
			float:right;
			z-index:1000;
			padding:2px;
		}

		::selection {
			background: yellow;
		}
		::-moz-selection {
			background: yellow;
		}
		</style>

		<!--
			TO DO: Build Javascript module to handle transactions with new page URLs.
		-->
		<?php
		if($file == "main" || $file == "" || $file == "verif"){
		}else{
			include("templates/header_bar.inc");
		}
		if(isset($file)){
			if(file_exists("templates/".$file.".inc"))
				//If the user is not logged in
				if(!$u->loginCheck()){
					//check if the script is main or signin, then display them if they are.
					if(($file == "main" || $file == "signin" || $file == "forgot_password" || $file == "verif"))
						include("templates/".$file.".inc");
					//else redirect user to the homepage.
					else{
						header("Location: /?p=main");
					}
				//user is logged in, redirect them to the notifications page.
				}else{
					include("templates/".$file.".inc");
				}
			else
				echo "File does not exist!";
		}else{
			if($u->loginCheck())
				header("Location: /?p=profile");
			include("templates/main.inc");
		}
		?>
		<script>
		function exposeBugPanel(){
			$(".bug-report-content").slideToggle();
		}
		</script>
		<div class="bug">
			<!--<span class="beta">BETA</span><a target="_blank" href="https://docs.google.com/forms/d/17XSZt6U_9lXMpNLaRwV96cG136CLAhUh4JkkX97l6cE/viewform?entry.1686089211=http://&entry.820742360&entry.448320425&entry.691100220&entry.860091091">Report Bug or Critique</a>-->
			<!--<textarea style="width:250px; height:75px;"></textarea>-->
			<div class="bug-report" style="background-color:white; -moz-border-top-right-radius:5px; -webkit-border-top-right-radius:5px; border-top-right-radius:5px; -moz-border-top-left-radius:5px; -webkit-border-top-left-radius:5px; border-top-left-radius:5px;">
			<div class="bug-report-content" style="display:none;">
				<b style="color:black;">Bug or Feedback form</b><br />
				<textarea style="width:250px;"></textarea>
				<table border="0" cellpadding="0" cellspacing="0">
					<tr>
						<td><label style="font-size:13px; color:black;"><input name="bugtype" id="bugtype" type="radio" style="position:relative; bottom:3px; right:2px;">Bug</label></td>
						<td style="padding-left:10px;"><label style="font-size:13px; color:black;"><input name="bugtype" id="bugtype" type="radio" style="position:relative; bottom:3px; right:2px;"/>Critique</label></td>
					</tr>
				</table>
				<button class="btn btn-small btn-primary"><span style="color:white;" style="position:relative; bottom:3px; right:2px;">Submit Report</span></button>
			</div>
			Bug or Feedback form<i class="icon-chevron-up" style="margin-left:5px; cursor:pointer;" onclick="exposeBugPanel();"></i></div>
		</div>
	<body>
</html>
<?php
ob_end_flush();
?>
