<a href='?p=viewbugs'>&laquo; Back</a>
<?php
$stmt = $db->prepare("SELECT * FROM spuzik_bug_bugs WHERE id = :id;");
$stmt->bindParam("id",$_GET['id']);
$stmt->execute();

$result = $stmt->fetch(PDO::FETCH_ASSOC);
?>
<style type="text/css">
.code{
	font-family:courier;
	padding:10px 0px;
	padding-left:20px;
	margin:20px 0px;
	border-top:2px solid #000;
	border-bottom:2px solid #000;
}
</style>
<form method="post" action="">
<table border="0" width="100%;">
	<tr>
		<td style="border-bottom:2px dashed #000; padding-top:5px;">
			<div style="float:right;">

			</div>
			<a style="float:right;" href='?p=edit&id=<?php echo $result['id']; ?>'>Edit</a>
			<h2><?php echo $result['name']; ?></h2>
		</td>
	</tr>
	<tr>
		<td style="padding-top:10px;"><?php echo $result['descr']; ?></td>
	</tr>
	<tr>
		<?php
		if(strlen($result['scrsht']) > 0){
			echo "<td align='center' style='background-color:#DDD;'><a href='".$result['scrsht']."'><img style='width:50%;' src='".$result['scrsht']."' /></a></td>"; }else{ echo "<td></td>";
		}
		?>
	</tr>
	<tr>
		<td>
			<i>Browser:</i> <?php echo $result['browser']; ?>
		</td>
	</tr>
	<tr>
		<td style="border-top:1px solid #000;">
			<h3>Resolution</h3>
		</td>
	</tr>
	<tr>
		<td>
			What did you do to resolve the bug?<br />
				<?php
				if(isset($_POST['submit'])){
					$stmt = $db->prepare("UPDATE spuzik_bug_bugs SET resolve_text = :resolve_text, state = 1 WHERE id = ".$result['id']);
					$stmt->bindParam("resolve_text",$_POST['resolve_text']);
					$stmt->execute();
					header("Location: ?p=viewbugs");
				}
				?>
				<textarea name="resolve_text" style="width:100%; font-size:18px; height:100px;"></textarea>
		</td>
	</tr>
	<tr>
		<td>
			<input type="submit" name="submit" value="Resolve Bug" style="font-size:18px;"/>
		</td>
	</tr>
</table>
</form>
