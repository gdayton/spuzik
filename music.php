<html>
	<head>
		<link rel="stylesheet" type="text/css" href="/data/bootstrap/css/bootstrap.min.css" />
		<script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
		<script src="//ajax.googleapis.com/ajax/libs/jqueryui/1.9.2/jquery-ui.min.js"></script>
	</head>
	<body style="background-color:white;">
		<style type="text/css">
		body{
			font-family:Helvetica;
		}

		.music-list{
			width:500px;
			margin:0 auto;
			margin-top:30px;
		}

		.music-list .music-table td{
			color:black;
			font-size:14px;
			padding:0px 2px 0px 2px;
			height:20px;
		}.music-list .music-table td.actions:hover{
			background-color:#eee;
		}.music-list table th {
			font-weight:bold;
			font-size:14px;
			padding:2px;
			border-bottom:1px solid black;
		}.music-list .music-table tr{
			cursor:pointer;
		}.music-list .music-table td .artist{
			font-size:13px;
			color:gray;
		}.music-list table.stripes td{
			padding:0px;
		}
		.music-list .music-table tbody tr:nth-child(odd) {
		   background-color: #eee;
		}
		.music-list .music-table-key-text td{
			padding:2px;
		}
		.music-list .music-table-key-text td span{
			float:left;
			margin-left:12px;
			font-size:13px;
			color:gray;
			position:relative;
			bottom:2px;
		}.music-list .music-table-key td{
			padding:2px;
			font-weight:bold;
			font-size:14px;
		}
		</style>

		<div class="music-list">
			<!--<table class="music-table-key" border="0" cellpadding="0" cellspacing="0" style="height:20px; width:425px;">
				<tr>
					<td width="40%" style="background-color:#e60000;"><span style="color:white;">50%</span></td>
					<td width="20%" style="background-color:#4d4dff;"><span style="color:white;">20%</span></td>
					<td width="20%" style="background-color:green;"><span style="color:white;">20%</span></td>
					<td width="10%" style="background-color:yellow;"><span style="color:black;">10%</span></td>
					<td width="10%" style="background-color:gray;"><span style="color:white;">10%</span></td>
				</tr>
			</table>
			<table class="music-table-key-text" border="0" cellpadding="0" cellspacing="0" style="width:425px;">
				<tr>
					<td><span>Jazz</span><div style="height:10px; width:10px; background-color:#e60000;"></div></td>
					<td><span>Rock</span><div style="height:10px; width:10px; background-color:#4d4dff;"></div></td>
					<td><span>Electronic</span><div style="height:10px; width:10px; background-color:green;"></div></td>
					<td><span>Country</span><div style="height:10px; width:10px; background-color:yellow;"></div></td>
					<td><span>Unknown</span><div style="height:10px; width:10px; background-color:gray;"></div></td>
				</tr>
			</table>-->
			<table class="music-table" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<th></th>
					<th align="left">Title & Artist</th>
					<th align="left">Duration</th>
					<th align="left">Genre</th>
					<th></th>
					<th></th>
				</tr>
				<tr>
					<td></td>
					<td>Gimme Shelter - <span class="artist">The Rolling Stones</span></td>
					<td>3:45</td>
					<td>Rock</td>
					<td class="stripes-container">
						<table class="stripes" border="0" cellpadding="0" cellspacing="0">
							<tr>
								<td><div style="height:20px; width:2px; background-color:#e69500;"></div></td>
							</tr>
						</table>
					</td>
					<td class="actions"><img src="https://cdn2.iconfinder.com/data/icons/ios-7-icons/50/down4-16.png" width="12px;" height="12px;"/></td>
				</tr>
				<tr>
					<td></td>
					<td>Jazz Tempo - <span class="artist">Jack Bu</span></td>
					<td>1:45</td>
					<td>Jazz</td>
					<td class="stripes-container"></td>
					<td class="actions"><img src="https://cdn2.iconfinder.com/data/icons/ios-7-icons/50/down4-16.png" width="12px;" height="12px;"/></td>
				</tr>
				<tr>
					<td></td>
					<td>The Finer Things - <span class="artist">Steve Winwood</span></td>
					<td>4:45</td>
					<td>Rock</td>
					<td class="stripes-container"></td>
					<td class="actions"><img src="https://cdn2.iconfinder.com/data/icons/ios-7-icons/50/down4-16.png" width="12px;" height="12px;"/></td>
				</tr>
				<tr>
					<td><i class="icon-star"></i></td>
					<td>Can't Find My Way Home - <span class="artist">Steve Winwood</span></td>
					<td>4:34</td>
					<td>Rock</td>
					<td class="stripes-container">
						<table class="stripes" border="0" cellpadding="0" cellspacing="0">
							<tr>
								<td><div style="height:20px; width:2px; background-color:#e69500;"></div></td>
								<td><div style="height:20px; width:2px; background-color:green;"></div></td>
								<td><div style="height:20px; width:2px; background-color:red;"></div></td>
								<td><div style="height:20px; width:2px; background-color:purple;"></div></td>
								<td><div style="height:20px; width:2px; background-color:gray;"></div></td>
							</tr>
						</table>
					</td>
					<td class="actions"><img src="https://cdn2.iconfinder.com/data/icons/ios-7-icons/50/down4-16.png" width="12px;" height="12px;"/></td>
				</tr>
			</table>
		</div>
	</body>
</html>