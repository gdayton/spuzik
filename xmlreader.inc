<?php
$songs = simplexml_load_file("data/Library.xml");
//$songs = simplexml_load_file("http://www.w3schools.com/xml/note.xml");
//print_r($songs);
//echo $songs->to;
/*
echo "song name<Br />";
print_r($songs->dict->dict->dict->string[0]);
echo "<hr />";
//song name instead of implementing this technique immediately look to further with JSON requests.
//print_r($songs->dict->dict->dict->string[0][0];

//albumn name
echo "albumn name<br />";
print_r($songs->dict->dict->dict->string[3][0]);
echo "<hr />";

//artist name
echo "artist name<br />";
print_r($songs->dict->dict->dict->string[1][0]);
echo "<hr />";
*/

foreach(range(0,150) as $i){
	$songArrayLocation = 0;
	$albumnArrayLocation = 0;
	$artistArrayLocation = 0;

	foreach($songs->dict->dict->dict[$i]->key as $ctr=>$g){
		echo $ctr." - ".$g;
		/*
		if($g == "Name"){
			$songArrayLocation = $ctr;
		}else if($g == "Artist"){
			$artistArrayLocation = $ctr;
		}else if($g == "Albumn"){
			$albumnArrayLocation = $ctr;
		}*/
	}
	echo "Song name: ".$songs->dict->dict->dict[$songArrayLocation]->string[0]."<br />";
	echo "Albumn name: ".$songs->dict->dict->dict[$albumnArrayLocation]->string[3]."<br />";
	echo "Artist name: ".$songs->dict->dict->dict[$artistArrayLocation]->string[1]."<hr />";
}
?>