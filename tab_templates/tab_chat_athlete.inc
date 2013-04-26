<style type="text/css">
.header-txt{
	font-size:18px;
	color:yellow;
	font-weight:bold;
	border-bottom:1px dashed yellow;
}.name{
	float:right;
	color:yellow;
}.msg{
	color:yellow;
}.msg-cont{
	width:100%;
}.msg-cont th{
	color:yellow;
	border-bottom:1px dashed yellow;
}.msg-cont .name{
	color:yellow;
	float:left;
	margin-right:5px;
	font-weight:bold;
}.msg-cont td{
	font-size:13px;
	color:white;
}.msg-cont .time{
	color:black;
	float:right;
}.name-item img{
	float:left;
	width:40px;
	height:40px;
}.name-item .txt{
	float:left;
	font-size:14px;
	color:yellow;
}.msg-cont .invitation{
	color:black;
	background-color:yellow;
	padding:10px;
	-moz-border-radius:5px;
	-webkit-border-radius:5px;
	border-radius:5px;
	border:0px solid #000;
	margin-bottom:10px;
}.chatbox-area{
	resize:none;
	bottom:0px;
	width:100%;
	margin-top:10px;
}
</style>
<div class="msg-cont">
	<table border="0" width="100%" cellpadding="5">
		<tr>
			<th width="50%;" align="left" style="background-color:#fc5a1e; color:black;">Inbox</th>
			<th width="50%;" align="left" style="background-color:#fc5a1e; color:black;">Chat</th>
		</tr>
		<tr>
			<td valign="top">
				<div class="name-item">
					<table border="0" width="100%">
						<tr>
							<td width="40px;"><img class="img-rounded" src="http://54.243.129.126/usr_content/pics/51203693c19d5_t.jpg" /></td>
							<td><span class="txt">Glenn Dayton</span><span class="badge badge-important" style="background-color:red; margin-left:5px;">!</span></td>
							<td></td>
						</tr>
					</table>
				</div>
				<div class="name-item">
					<table border="0" width="100%">
						<tr>
							<td width="40px;"><img class="img-rounded" src="http://54.243.129.126/usr_content/pics/51203693c19d5_t.jpg" /></td>
							<td><span class="txt">Bob Filner</span></td>
							<td></td>
						</tr>
					</table>
				</div>
				<div class="name-item">
					<table border="0" width="100%">
						<tr>
							<td width="40px;"><img class="img-rounded" src="http://54.243.129.126/usr_content/pics/51203693c19d5_t.jpg" /></td>
							<td><span class="txt">Tom, Jeff, Evan, Lou, Brian</span></td>
							<td></td>
						</tr>
					</table>
				</div>
			</td>
			<td valign="top">
				<div class="invitation">
				Would you like to join Jeff Costco's chat?<br />
				<button class="btn btn-mini btn-success" type="button" style="color:white; margin-right:5px;">Yes</button><button class="btn btn-mini btn-danger" type="button" style="color:white;">No</button>
				</div>
				<span class="name">Glenn Dayton</span> This is a message that has just been put in the inbox. <span class="time">3 mins ago.</span>
				<span class="name">Me</span> Another testing message for the sake of testing. <span class="time">8 mins ago.</span>
				<textarea class="chatbox-area"></textarea>
			</td>
		</tr>
	</table>
</div>