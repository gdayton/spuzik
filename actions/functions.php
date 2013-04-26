<?php
//$db = new PDO("mysql:dbname=spk;host=localhost;","spk_handler","qaw3ufRa");
function inputSQLMemcache($statement,$data){
	$memcache = Memcache;
	$mem = $memcache->connect("spk.gencop.0001.use1.cache.amazonaws.com",11211);
	$db = new PDO("mysql:dbname=spk;host=localhost;","spk_handler","qaw3ufRa");
}
function isValidEmail($email){
    return preg_match("^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$^", $email);
}
function sec_session_start() {
	ini_set('session.use_trans_sid', false);
	ini_set('session.use_cookies', true);
	ini_set('session.use_only_cookies', true);
	$https = false;
	if(isset($_SERVER['HTTPS']) and $_SERVER['HTTPS'] != 'off') $https = true;
	$dirname = rtrim(dirname($_SERVER['PHP_SELF']), '/').'/';
	session_name('spuzik_session');
	session_set_cookie_params(0, $dirname, $_SERVER['HTTP_HOST'], $https, true);
	session_start();

	/*
    $session_name = 'spuzik_session'; // Set a custom session name
    $secure = false; // Set to true if using https.
	$httponly = true; // This stops javascript being able to access the session id.

    ini_set('session.use_only_cookies', 1); // Forces sessions to only use cookies.
	$cookieParams = session_get_cookie_params(); // Gets current cookies params

	//set session for one week
	session_set_cookie_params(time()+60*60*24*7, $cookieParams["path"], $cookieParams["domain"], $secure, $httponly);
	session_name($session_name); // Sets the session name to the one set above.
	session_start(); // Start the php session
    session_regenerate_id(true); // regenerated the session, delete the old one.
    */
}
function checkverf($id,$db){ //returns the date of the registration
	$query = "SELECT reg_date FROM verification WHERE u_id = :id;";
	$stmt = $db->prepare($query);
	$stmt->bindParam("id",$id);
	$stmt->execute();
	$results = $stmt->fetch(PDO::FETCH_ASSOC);

	if($stmt->rowCount() > 0)
		return $results['reg_date'];
	else
		return -1;
}

function relTime($ptime){
    $etime = time() - $ptime;

    if ($etime < 1) {
        return '0 seconds';
    }

    $a = array( 12 * 30 * 24 * 60 * 60  =>  'year',
                30 * 24 * 60 * 60       =>  'month',
                24 * 60 * 60            =>  'day',
                60 * 60                 =>  'hour',
                60                      =>  'min',
                1                       =>  'sec'
                );

    foreach ($a as $secs => $str) {
        $d = $etime / $secs;
        if ($d >= 1) {
            $r = round($d);
            return $r . ' ' . $str . ($r > 1 ? 's' : '');
        }
    }
}

function convertIntTypetoString($type){
	switch($type){
		case 0: return "general_user";
		case 1: return "athelete_user";
		case 2: return "team_user";
		case 3: return "musician_user";
		case 4: return "band_user";
		case 5: return "agent_user";
	}
}

/*
	rid = resource id
	id = id to compare the canShow against
*/
function canShow($rid, $id, $idf){
	$db = new PDO("mysql:dbname=spk;host=localhost;","spk_handler","qaw3ufRa");
	$select = "SELECT type FROM permissions WHERE id = :rid LIMIT 1;";
	$stmt = $db->prepare($select);
	$stmt->bindParam("rid",$rid);
	$stmt->execute();
	$result = $stmt->fetch(PDO::FETCH_ASSOC);
	switch($result['type']){
		case 0: return true; 			//public
		case 1: return isFan($id, $idf, $db);	//fans
	}
}

/*
	Returns true if the user with passed id is friends with logged in user.
	However, if a user id is passed in the second parameter then that id can be used to see a fans associated between other users.
*/
function isFan($id,$idf){
	$db = new PDO("mysql:dbname=spk;host=localhost;","spk_handler","qaw3ufRa");
	$query = "SELECT COUNT(id) FROM fans WHERE (u1 = :u1 AND u2 = :u2) OR (u1 = :u2 AND u2 = :u1) AND type = 1;";
	$stmt = $db->prepare($query);
	$stmt->bindParam("u1",$id);
	$stmt->bindParam("u2",$idf);
	$stmt->execute();
	$result = $stmt->fetch(PDO::FETCH_ASSOC);
	if($result['COUNT(*)'] > 0){
		return true;
	}else{
		return false;
	}
}
?>