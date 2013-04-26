<style type="text/css">
.bug-main{
	width:100%;
	padding:10px;
}.org{
	/*border-top:2px solid #000;*/
	border-bottom:2px solid #000;
	padding-bottom:5px;
	margin-bottom:10px;
}
</style>
<h1>Bugs</h1>
<div class="org">
Sort by:
<select onchange="loadPage();" class="page">
	<option value="0" <?php if($_GET['sort'] == 0){ echo "selected='selected'";}?>>Recently Added</option>
	<option value="1" <?php if($_GET['sort'] == 1){ echo "selected='selected'";}?>>Completion Date</option>
	<option value="2" <?php if($_GET['sort'] == 2){ echo "selected='selected'";}?>>A - Z</option>
	<option value="3" <?php if($_GET['sort'] == 3){ echo "selected='selected'";}?>>Z - A</option>
</select>
<script>
function loadPage(){
	switch(parseInt($(".page").val())){
		case 0:
			window.location = "?p=viewbugs&sort=0";
			break;
		case 1:
			window.location = "?p=viewbugs&sort=1";
			break;
		case 2:
			window.location = "?p=viewbugs&sort=2";
			break;
		case 3:
			window.location = "?p=viewbugs&sort=3";
			break;
	}
}
</script>
</div>
<?php
switch($_GET['sort']){
	case 0: //recently added
		$stmt = $db->prepare("SELECT * FROM spuzik_bug_bugs WHERE state = 0 ORDER BY id DESC;");
		break;
	case 1: //completion date
		$stmt = $db->prepare("SELECT * FROM spuzik_bug_bugs WHERE state = 0 ORDER BY date_fut ASC;");
		break;
	case 2: //a - z
		$stmt = $db->prepare("SELECT * FROM spuzik_bug_bugs WHERE state = 0 ORDER BY name ASC;");
		break;
	case 3: //z - a
		$stmt = $db->prepare("SELECT * FROM spuzik_bug_bugs WHERE state = 0 ORDER BY name DESC;");
		break;
	default:
		$stmt = $db->prepare("SELECT * FROM spuzik_bug_bugs WHERE state = 0 ORDER BY id DESC;");
		break;
}
$stmt->execute();
$res = $stmt->fetchAll(PDO::FETCH_ASSOC);

foreach($res as $r){
	echo "<div class='bug-main'>
		<table border='0' width='100%'>
			<tr>
				<td width='100px'>";
				if(strlen($r['scrsht']) > 0){
					echo "<img src='".$r['scrsht']."' style='width:100px; height:100px;'/>";
				}else{
					echo "<div style='width:100px; height:100px; border:1px solid #000;'><b style='position:relative; top:40px; left:10px;'>No Image</b></div>";
				}
		echo "</td>
				<td valign='top'>
					<table border='0' style='width:100%; height:100%;'>
						<tr>
							<td>
								<b style='font-size:20px;'><a style='color:blue;' href='?p=item&id=".$r['id']."'>".$r['name']."</a></b>
								<i style='float:right; color:red; margin-left:50px;'>";
								$daysAmt = floor(($r['date_fut']-strtotime("now"))/86400);
								if($daysAmt > 7)
									echo "<span style='color:green;'>Due in ".$daysAmt." days</span>";
								else if($daysAmt > 5)
									echo "<span style='color:orange;'>Due in ".$daysAmt." days</span>";
								else
									echo "<span style='color:red;'>Due in ".$daysAmt." days</span>";
							echo "</i></td>
						</tr>
						<tr>
							<td>
							".substr($r['descr'],0, 150)."...
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
	</div>";
}
?>