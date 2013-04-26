<p>This website allows you to manage bugs for <b>Spuzik</b>.</p>
<h2>Statistics</h2>
<table border="0" style="width:400px;">
	<tr>
		<td>Existing Bugs</td>
		<td><?php
			$stmt = $db->prepare("SELECT COUNT(id) FROM spuzik_bug_bugs WHERE state = 0;");
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			echo $result['COUNT(id)'];
		?></td>
	</tr>
	<tr>
		<td>Resolved Bugs</td>
		<td><?php
			$stmt = $db->prepare("SELECT COUNT(id) FROM spuzik_bug_bugs WHERE state = 1;");
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			echo $result['COUNT(id)'];
		?></td>
	</tr>
	<tr>
		<td>Lifetime Bugs</td>
		<td><?php
			$stmt = $db->prepare("SELECT COUNT(id) FROM spuzik_bug_bugs WHERE state = 0 OR state = 1;");
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			echo $result['COUNT(id)'];
		?></td>
	</tr>
	<tr>
		<td></td>
		<td></td>
	</tr>
	<tr>
		<td>Users</td>
		<td><?php
			$stmt = $db->prepare("SELECT COUNT(id) FROM spuzik_bug_users WHERE ok = 1;");
			$stmt->execute();
			$result = $stmt->fetch(PDO::FETCH_ASSOC);
			echo $result['COUNT(id)'];
		?></td>
	</tr>
</table>