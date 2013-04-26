<style type='text/css'>
.present-gigs{

}.present-gigs th{
	/*font-size:13px;*/
	font-weight:bold;
	color:yellow;
}.present-gigs td{
	font-size:13px;
	padding:10px;
}.manage-top{
	background-color:#fc5a1e;
	text-align:center;
	padding:10px;
}.ven-table .ven-head{
	font-size:13px;
	font-weight:bold;
	color:orange;
}.ven-table .ven-val{
	font-size:13px;
}.venue-title{
	color:yellow;
	font-size:18px;
	font-weight:bold;
}.venue-description{
	margin-top:5px;
}.p-gig{
	margin:10px;
	width:20%;
	float:left;
}.p-gig img{
	border:1px solid black;
	padding:2px;
}.p-gig .p-gig-text{
	font-size:13px;
	color:white;
	font-weight:bold;
	width:100%;
	text-align:center;
}.create-gig{
	display:none;
	padding:10px;
}.create-gig .prompt-title{

}
</style>
<script>
function showCreate(){
	$(".create-gig").show();
}
</script>
<div class='manage-top'>
	<button type='button' class='btn btn-small btn-primary' onclick='showCreate();'><span style='color:yellow;'>Post Gig</span></button>
	<div class='create-gig'>
		<table border='0' width='100%'>
			<tr>
				<td class='prompt-title'>Gig Headline</td>
				<td>
					<input type='text' style='height:25px;' class='headline' />
				</td>
			</tr>
			<tr>
				<td class='prompt-title' valign='top'>Description</td>
				<td>
					<textarea width='100%;' class='description'></textarea>
				</td>
			</tr>
			<tr>
				<td colspan='2'><span style='color:orange;'>Where?</span></td>
			</tr>
			<tr>
				<td colspan='2' style='padding-left:15px;'>
					<table border='0'>
						<tr>
							<td class='prompt-title'>Address</td>
							<td>
								<input type='text' style='height:25px;' class='address' />
							</td>
						</tr>
						<tr>
							<td class='prompt-title'>City</td>
							<td>
								<input type='text' style='height:25px;' class='city' />
							</td>
						</tr>
						<tr>
							<td class='prompt-title'>Zip</td>
							<td>
								<input type='text' style='height:25px;' class='zip' />
							</td>
						</tr>
					</table>
				</td>
			</tr>
			<tr>
				<td colspan='2'><span style='color:orange;'>When?</span></td>
			</tr>
			<tr>
				<td colspan='2' style='padding-left:15px;'>
					<table border='0' width="100%">
						<tr>
							<td>
								<script>
								$(".month").change(function(){
										if(jQuery.inArray(parseInt($(".month").val()),[9,4,6,11]) != -1){ //has 30 days
												displayDays(30);
										}else if(jQuery.inArray(parseInt($(".month").val()),[1,3,5,7,8,10,12]) != -1){ //has 31 days
												displayDays(31);
										}else{ //has 28 days
												displayDays(29);
										}
								});
								function displayDays(amt){
										var s = "";
										for(var i = 1;i <= amt;i++){
												s+="<option>"+String(i)+"</option>";
										}
										$(".days").html(s);
								}
								</script>
								<table border='0' width='100%'>
									<tr>
										<td valign='middle'>
											Date
											<select class='month' style='width:75px;'>
												<option val='1'>Jan</option>
												<option val='2'>Feb</option>
												<option val='3'>Mar</option>
												<option val='4'>Apr</option>
												<option val='5'>May</option>
												<option val='6'>Jun</option>
												<option val='7'>Jul</option>
												<option val='8'>Aug</option>
												<option val='9'>Sep</option>
												<option val='10'>Oct</option>
												<option val='11'>Nov</option>
												<option val='12'>Dec</option>
											</select>
											<select class="days" id="day" style="width:60px;">
											<?php
												foreach(range(1,31) as $i){
														echo "<option value=\"".$i."\">".$i."</option>";
												}
											?>
											</select>
											<select style="width:90px;" id="year">
											<?php
												$goto = date('Y'); //users must be 13 and older
												foreach(range($goto,($goto+10)) as $year){
													echo "<option value=\"".$year."\">".$year."</option>";
												}
											?>
											</select>
										</td>
										<td align='right'>
											From
											<select class='hour' style='margin-left:15px; margin-right:5px; width:50px;'>
											<?php
												foreach(range(1,12) as $year){
													echo "<option value=\"".$year."\">".$year."</option>";
												}
											?>
											</select>:
											<select class='hour' style='margin-left:5px; width:50px;'>
											<?php
												foreach(range(0,55, 5) as $year){
													if($year < 10)
														$year = "0".$year;
													echo "<option value=\"".$year."\">".$year."</option>";
												}
											?>
											</select>
											<select class='ampm' style='maring-left:15px; width:60px;'>
												<option val='am'>AM</option>
												<option val='pm'>PM</option>
											</select>

											<br />

											To
											<select class='hour' style='margin-left:15px; margin-right:5px; width:50px;'>
											<?php
												foreach(range(1,12) as $year){
													echo "<option value=\"".$year."\">".$year."</option>";
												}
											?>
											</select>:
											<select class='hour' style='margin-left:5px; width:50px;'>
											<?php
												foreach(range(0,55, 5) as $year){
													if($year < 10)
														$year = "0".$year;
													echo "<option value=\"".$year."\">".$year."</option>";
												}
											?>
											</select>
											<select class='ampm' style='maring-left:15px; width:60px;'>
												<option val='am'>AM</option>
												<option val='pm'>PM</option>
											</select>
										</td>
									</tr>
								</table>
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
	</div>
</div>
<table border="0" width="100%;" class="present-gigs">
	<tr style="background-color:#fc5a1e;">
		<th style="border-bottom:1px solid yellow; color:blue;">Venue</th>
		<th style="border-bottom:1px solid yellow; color:blue;">Details</th>
	</tr>
	<tr>
		<td  width="50%;">
			<table border="0" class="">
				<tr>
					<td colspan="2">
						<span class='venue-title'>Big Bob's Karaoke Night</span>
					</td>
				</tr>
				<tr>
					<td width="125px;">
						<img src='http://i.imm.io/WOdG.jpeg' class='img-rouded' width="150px;" /><br />
						<div style='margin:3px; margin-top:10px;'>
							<button class='btn btn-mini btncustom' style='color:black; margin-right:3px;'>I'm Going!</button>34 people going
						</div>
					</td>
					<td valign="top">
						<div class='venue-desc'>Make sure you arrive ready to sing! This night will be filled with all the fun and excitement that a crowd of old go-getters sets.</div>
						<div style='margin-top:3px;'>Age Limit: <i>21 and older</i></div>
					</td>
				</tr>
			</table>
		</td>
		<td valign="top">
			<table border="0" class="ven-table" style='margin-top:45px;'>
				<tr>
					<td class="ven-head" valign="top"></td>
					<td class="ven-val"><span style='font-size:15px; color:orange; font-weight:bold;'>When?</span><br />Feb 20, 2013<br />9am - 10pm</td>
					<td rowspan='2' valign="top"><img class="img-circle" src='http://maps.googleapis.com/maps/api/staticmap?center=420 Van Ness Avenue Santa Cruz, CA 95064&zoom=14&size=150x150&sensor=false' width="150px;"/></td>
				</tr>
				<tr>
					<td class="ven-head" valign="top"></td>
					<td class="ven-val"><span style='font-size:15px; color:orange; font-weight:bold;'>Where?</span><br />412 Van Ness Avenue<br />Santa Cruz, CA 95064<br /></td>
				</tr>
			</table>
		</td>
	</tr>
</table>
<table border="0" width="100%;" class="past-gigs">
	<tr>
		<th style="background-color:#063d78; border-top:1px solid yellow; border-bottom:1px solid yellow; color:yellow;">Past Gigs</th>
	</tr>
	<tr>
		<td>
			<div class='p-gig'>
				<img src='http://i.imm.io/WXAm.jpeg' />
				<div class='p-gig-text'>Big Bob's Karaoke Night</div>
			</div>
			<div class='p-gig'>
				<img src='http://i.imm.io/WXCn.jpeg' />
				<div class='p-gig-text'>Wedding Gig</div>
			</div>
		</td>
	</tr>
	<!--<tr>
		<td></td>
		<td></td>
		<td></td>
	</tr>-->
</table>