<?php

include("dbcon.php");
include("functions.php");

class User{
	public $db = null;
	public $memcache = null;
	public function __construct(){
		$this->db = new PDO("mysql:dbname=spk;host=localhost","spk_handler","qaw3ufRa");
		//$this->memcache = new Memcache;
		//$this->memcache->connect("spk.gencop.0001.use1.cache.amazonaws.com",11211);
	}

	public function addUser(/*$_POST*/$request){

		$jsonArray = array("status"=>"success");
		$data = array();

		$data['type'] = trim($request['type']);
		$data['fname'] = ucfirst(trim($request['fname']));
		$data['lname'] = ucfirst(trim($request['lname']));
		$data['email'] = trim($request['email']);
		$data['dob'] = 	trim(strtotime($request['day']."-".$request['month']."-".$request['year']));
		$data['password'] = $request['password'];
		$data['passwordv'] = $request['passwordv'];
		$data['reg_date'] = strtotime("now");
		/*$data['aname'] = trim(trim($request['aname']));*/
		/*$data['gender'] = $request['gender'];
		$data['zip'] = trim($request['zip']);*/

		foreach($data as $a=>$b){
			$data[$a] = strip_tags($b);
		}

		//VALIDATION//
		$error = 0;
		$jsonArray['status_itr'] = array();

		//Check user type for all accounts

		if(!empty($data['password'])){
			if($data['password'] != $data['passwordv']){
				$error++;
				$jsonArray['status_itr'] = $jsonArray['status_itr']+array("password"=>"Passwords do not match.");
			}else{ //password info successful
				$data['password'] = md5($data['password']);
			}
		}else{
			$error++;
			$jsonArray['status_itr'] = $jsonArray['status_itr']+array("password"=>"You must enter a password.");
		}

		if(!isValidEmail($data['email']) && !$dup){
			$error++;
			$jsonArray['status_itr'] = $jsonArray['status_itr']+array("email"=>"You must enter a valid email.");
		}else{ //EMAIL IS VALID, CHECK FOR DUPLICATES//
                	//QUERY//
                	$query = "SELECT COUNT(email) FROM user WHERE email = :email;";
                	$stmt = $this->db->prepare($query);
                	$stmt->bindParam("email",$data['email']);
                	$stmt->execute();
                	$val = $stmt->fetch(PDO::FETCH_ASSOC);
			if($val['COUNT(email)'] != 0){
				$error++;
				$jsonArray['status_itr'] = $jsonArray['status_itr']+array("email"=>" Email is registered with another user.");
			}
		}

		switch($data['type']){
			case 0: //general
			case 1: //athelete
			case 3: //musician
			case 5: //agent
				if(empty($data['fname'])){
					$error++;
					$jsonArray['status_itr'] = $jsonArray['status_itr']+array("fname"=>"You must enter your first name.");
				}

				if(empty($data['lname'])){
					$error++;
					$jsonArray['status_itr'] = $jsonArray['status_itr']+array("lname"=>"You must enter your last name.");
				}

				if(!is_numeric((int)($data['dob']))){
					$error++;
					$jsonArray['status_itr'] = $jsonArray['status_itr']+array("dob"=>"You must enter a valid DOB.");
				}

				/*
				if(empty($data['gender'])){
					$error++;
					$jsonArray['status_itr'] = $jsonArray['status_itr']+array("gender"=>"You must enter your gender.");
				}else{
					$data['gender'] = ( $data['gender'] == "m" ? 1 : 0);
				}

				if(empty($data['zip'])){
					$error++;
					$jsonArray['status_itr'] = $jsonArray['status_itr']+array("zip"=>"You must enter a valid zip code.");
				}
				*/
				break;
			case 2: //team
			case 4: //band
				if(empty($data['aname'])){
					$error++;
					$jsonArray['status_itr'] = $jsonArray['status_itr']+array("aname"=>"You must enter a name.");
				}
				break;
		}

		if($error == 0){
			//QUERY//
			$query = "INSERT INTO user (email,reg_date,password,type) VALUES (:email,:reg_date,:password,:type);";

			$stmt = $this->db->prepare($query);
			$email_lower = strtolower($data['email']);
			$stmt->bindParam("email",$email_lower);
			$stmt->bindParam("reg_date",$data['reg_date']);
			$stmt->bindParam("password",$data['password']);
			$stmt->bindParam("type",$data['type']);
			$result = $stmt->execute();

			$select = "SELECT id FROM user WHERE email = :email;";
			$stmt = $this->db->prepare($select);
			$stmt->bindParam("email",$data['email']);
			$stmt->execute();
			$id = $stmt->fetch(PDO::FETCH_ASSOC);

			$data['u_id'] = $id['id']; //get the id
			switch($data['type']){
				case 0: //general
						$query2 = "INSERT INTO general_user (fname,lname,dob,u_id,gender,zip) VALUES (:fname,:lname,:dob,:u_id,:gender,:zip);";
						$stmt = $this->db->prepare($query2);
						$stmt->bindParam("fname",$data['fname']);
						$stmt->bindParam("lname",$data['lname']);
						$stmt->bindParam("dob",$data['dob']);
						$stmt->bindParam("u_id",$data['u_id']);
						$blankwhite = "";
						$stmt->bindParam("gender",$blankwhite);
						$stmt->bindParam("zip",$blankwhite);

						//The below information is requested in subsequent portion.
						/*$stmt->bindParam("gender",$data['gender']);
						$stmt->bindParam("zip",$data['zip']);*/
						$result2 = $stmt->execute();
						break;
				case 1: //athelete
						$query2 = "INSERT INTO athelete_user (fname,lname,dob,u_id) VALUES (:fname,:lname,:dob:,:u_id);";
						$stmt = $this->db->prepare($query2);
						$stmt->bindParam("fname",$data['fname']);
						$stmt->bindParam("lname",$data['lname']);
						$stmt->bindParam("dob",$data['dob']);
						$stmt->bindParam("u_id",$data['u_id']);
						$result2 = $stmt->execute();
						break;
				case 2: //team
						$query2 = "INSERT INTO team_user (tname,u_id) VALUES (:tname,:u_id);";
						$stmt = $this->db->prepare($query2);
						$stmt->bindParam("tname",$data['aname']);
						$stmt->bindParam("u_id",$data['u_id']);
						$result2 = $stmt->execute();
						break;
				case 3: //musician
						$query2 = "INSERT INTO musician_user (fname,lname,dob,u_id) VALUES (:fname,:lname,:dob,:u_id);";
						$stmt = $this->db->prepare($query2);
						$stmt->bindParam("fname",$data['fname']);
						$stmt->bindParam("lname",$data['lname']);
						$stmt->bindParam("dob",$data['dob']);
						$stmt->bindParam("u_id",$data['u_id']);
						$result2 = $stmt->execute();
						break;
				case 5: //agent
						$query2 = "INSERT INTO agent_user (fname, lname, dob, u_id) VALUES (:fname, :lname, :dob, :u_id);";
						$stmt = $this->db->prepare($query2);
						$stmt->bindParam("fname",$data['fname']);
						$stmt->bindParam("lname",$data['lname']);
						$stmt->bindParam("dob",$data['dob']);
						$stmt->bindParam("u_id",$data['u_id']);
						$result2 = $stmt->execute();
						break;
				case 4: //band
						$query2 = "INSERT INTO band_user (bname,u_id) VALUES (:bname,:u_id);";
						$stmt = $this->db->prepare($query2);
						$stmt->bindParam("bname",$data['aname']);
						$stmt->bindParam("u_id",$data['u_id']);
						$result2 = $stmt->execute();
						break;
			}
			/*if($result && $result2){*/
				$jsonArray['status_msg'] = "User successfully created.";
				unset($jsonArray['status_itr']);
				//send the email out
				$q = "INSERT INTO verification (u_id,verif_token,reg_date) VALUES (:u_id,:verif_token,:reg_date);";
				$stmt = $this->db->prepare($q);
				$stmt->bindParam("u_id",$data['u_id']);
				$verif_token = md5(md5($data['password']));
				$stmt->bindParam("verif_token",$verif_token);
				$stmt->bindParam("reg_date",$data['reg_date']);
				$stmt->execute();

				//$jsonArray['status'] = "error";
				//$jsonArray['status_type'] = "internal";
				//$jsonArray['status_msg'] = "Email: ".$data['email'];

				$headers  = 'MIME-Version: 1.0' . "\r\n";
				$headers .= 'Content-type: text/html; charset=iso-8859-1' . "\r\n";
				$headers .= 'To: '.$data['fname'].' '.$data['lname'].' <'.$data['email'].'>' . "\r\n";
				$headers .= 'From: Spuzik Support <support@spuzik.us>' . "\r\n";

				$message = "<h3>Welcome to Spuzik!</h3><p><b>Activate your account</b> Please click on the link below to activate your account.<br />http://54.243.129.126/index.php?p=verif&token=".$verif_token."|".$data['u_id']."</p>";

				mail($data['email'],"Activate Spuzik Account",$message);
				//mail($data['email'],"Activate Spuzik Account",$message,$headers);
			/*}else{
				$jsonArray['status'] = "error";
				$jsonArray['status_type'] = "internal";
				foreach($stmt->errorInfo() as $a=>$b){
					$data_str.="[".$a."]=>".$b;
				}
				$jsonArray['status_msg'] = $data_str."Failed to create user.";
			}*/
		}else{
			$jsonArray['status'] = "error";
			$jsonArray['status_type'] = "validation";
		}

		echo json_encode($jsonArray, JSON_FORCE_OBJECT);
	}

	public function verif($vid){
		$jsonArray = array("status"=>"success");

		$parts = explode("|",$vid);

		$stmt = $this->db->prepare("DELETE FROM verification WHERE u_id = :uid AND verif_token = :token;");
		$stmt->bindParam("uid",$parts[1]);
		$stmt->bindParam("token",$parts[0]);
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "We were unable to activate your Spuzik account. 0:".$parts[0]." 1:".$parts[1];
		}

		//echo json_encode($jsonArray);
	}

	public function editUser($id, $switchvals){
		//QUERY//
		$jsonArray = array("status"=>"success");
		$query = "SELECT * FROM user WHERE id = :id;";
		$query_md5 = md5($query);
		if($vals = $this->memcache->get($query_md5)){ //get info from the database
			$vals = unserialize($vals);
		}else{
			$stmt = $this->db->prepare($query);
			$stmt->bindParam("id",$id);
			$stmt->execute();
			$vals = $stmt->fetch(PDO::FETCH_ASSOC);
			$this->memcache->set($query_md5,serialize($vals),0,3600); //store info for one hour
		}
		if(is_array($vals)){
			foreach($switchvals as $a=>$b){
				$vals[$a] = $b;
			}
			$query = "UPDATE user SET id = :id, fname = :fname, lname = :lname, email = :email, dob = :dob, reg_date = :reg_date;";
			$stmt = $this->db->prepare($query);
			$result = $stmt->execute($vals);
			if($result){
				$jsonArray['status_msg'] = "User edited successfully.";
			}else{
				$jsonArray['status'] = "error";
				$jsonArray['status_type'] = "internal";
				$jsonArray['status_msg'] = "Failed to edit user. [Layer 2]";
			}
		}else{
			$jsonArray['status'] = "error";
			$jsonArray['status_type'] = "internal";
			$jsonArray['status_msg'] = "Failed to edit user. [Layer 1]";
		}

		$respJSON = json_encode($jsonArray);
		echo $respJSON;
	}

	public function editInfo($post){
		$jsonEncode = array("status"=>"success");
		$stmt = $this->db->prepare("UPDATE general_user SET nickname = :nickname, gender = :gender, dob = :dob, hmtown = :hmtown WHERE u_id = :u_id;");
		$stmt->bindParam("nickname",$post['nickname']);
		$stmt->bindParam("gender",$post['gender']);
		//$dob_array = explode("/",$post['dob']);
		$dobP = strtotime($post['birthday']);
		$stmt->bindParam("dob",$dobP);
		$stmt->bindParam("hmtown",$post['hometown']);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Failed to edit user.";
		}
		echo json_encode($jsonEncode);
	}

	public function editInfoAgent($post){
		$jsonEncode = array("status"=>"success");
		$stmt = $this->db->prepare("UPDATE agent_user SET gender = :gender, hmtown = :hmtown, company = :company, agent_type = :agent_type, num_clients = :num_clients WHERE u_id = :u_id;");
		$stmt->bindParam("gender",$post['gender']);
		$stmt->bindParam("hmtown",$post['hmtown']);
		$stmt->bindParam("company",$post['company']);
		$stmt->bindParam("agent_type",$post['agent_type']);
		$stmt->bindParam("num_clients",$post['num_clients']);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Failed to edit agent user.";
		}

		echo json_encode($jsonEncode);
	}

	public function signIn($post) {
		$password = $post['password'];
		$email = $post['email'];
		$jsonArray = array("status"=>"success");
   		// Using prepared Statements means that SQL injection is not possible.
   		if ($stmt = $this->db->prepare("SELECT id, password FROM user WHERE email = :email LIMIT 1;")) {
      			$stmt->bindParam(':email', $email); // Bind "$email" to parameter.
      			$stmt->execute(); // Execute the prepared query.
      			$results = $stmt->fetch(PDO::FETCH_ASSOC);
			$user_id = $results['id'];
			$db_password = $results['password'];
      			$password = md5($password); // hash the password with the unique salt.

      		if($stmt->rowCount() == 1) { // If the user exists
         		// We check if the account is locked from too many login attempts
         		$regdate = checkverf($user_id, $this->db);
			if($regdate != -1) {
            			// User has not verified their account via email.
            			// Send an email to user saying their account is locked
				$jsonArray['status'] = "error";
				$jsonArray['status_type'] = "verification";
				$jsonArray['status_msg'] = "We send you a verification email on ".date('M j \'y',$regdate)." ( ".relTime($regdate)." ago ), please click on the link within the email.";
         		} else {
         			if($db_password == $password) { // Check if the password in the database matches the password the user submitted.
            				// Password is correct!

               				$ip_address = $_SERVER['REMOTE_ADDR']; // Get the IP address of the user.
               				$user_browser = $_SERVER['HTTP_USER_AGENT']; // Get the user-agent string of the user.

					//Log this login for reference
					$query = "INSERT INTO logins (u_id,ip,browser,date,request_uri) VALUES ('".$user_id."','".$ip_address."','".$user_browser."','".strtotime('now')."','".$_SERVER['REQUEST_URI']."');";
					$this->db->query($query);

               				$user_id = preg_replace("/[^0-9]+/", "", $user_id); // XSS protection as we might print this value
               				$_SESSION['user_id'] = $user_id;
               				$_SESSION['email'] = $email;
               				$_SESSION['login_string'] = hash('sha512', $password.$ip_address.$user_browser);
               				$jsonArray['status_msg'] = $query." - Login was successful.";// Login successful.
         			} else{
            				// Password is not correct
            				// We record this attempt in the database
            				// == Possibly record this as an attempt to login to the account. ==
					//$now = time();
            				//$mysqli->query("INSERT INTO login_attempts (user_id, time) VALUES ('$user_id', '$now')");
            				$jsonArray['status'] = "error";
					$jsonArray['status_type'] = "verfication";
					$jsonArray['status_msg'] = "Email and password combination was incorrect.";
         			}
      			}
      		} else {
         		// No user exists.
         		$jsonArray['status'] = "error";
			$jsonArray['status_type'] = "verification";
			$jsonArray['status_msg'] = "User account does not exist with supplied credentials.";
      		}
		}else{
			$jsonArray['status'] = "error";
			$jsonArray['status_type'] = "internal";
			$jsonArray['status_msg'] = "Connection to database could not be made.";
		}
		$jsonEncode = json_encode($jsonArray);
		echo $jsonEncode;

	}

	public function loginCheck(){
		// Check if all session variables are set
   		if(isset($_SESSION['user_id']) && isset($_SESSION['login_string'])) {
    	 	$user_id = $_SESSION['user_id'];
     		$login_string = $_SESSION['login_string'];

     		$ip_address = $_SERVER['REMOTE_ADDR']; // Get the IP address of the user.
     		$user_browser = $_SERVER['HTTP_USER_AGENT']; // Get the user-agent string of the user.

			$query = "SELECT password FROM user WHERE id = :id LIMIT 1;";

			$stmt = $this->db->prepare($query);

			$stmt->bindParam("id",$user_id);
			$stmt->execute();
			$results = $stmt->fetch(PDO::FETCH_ASSOC);
			$password = $results['password'];
			$rowCount = $stmt->rowCount();

			if($rowCount == 1) { // If the user exists
				$login_check = hash('sha512', $password.$ip_address.$user_browser);
				if($login_check == $login_string) {
					// Logged In!!!!
					return true;
				} else {
					// Not logged in
					return false;
				}
			} else {
				// Not logged in
				return false;
			}
   		} else {
			// Not logged in
			return false;
   		}
	}

	public function logout(){
		// Unset all session values
		$_SESSION = array();
		// get session parameters
		$params = session_get_cookie_params();
		// Delete the actual cookie.
		setcookie(session_name(), '', time() - 42000, $params["path"], $params["domain"], $params["secure"], $params["httponly"]);
		// Destroy session
		session_destroy();
		header('Location: ./');
	}

	/*
		Further improvement: pass parameters to decide what information you want returned.
	*/
	public function userInfo($u_id){
		//Always grab this info
		$query = "SELECT email, type, profile_pic, home_pic, last_on, profile_music FROM user WHERE id = :u_id";
		$stmt = $this->db->prepare($query);
		$stmt->bindParam("u_id",$u_id);
		$stmt->execute();
		$results = $stmt->fetch(PDO::FETCH_ASSOC);
		//Grab first and last name
		$query2 = "SELECT * FROM ".convertIntTypetoString($results['type'])." WHERE u_id = :u_id";
		$stmt = $this->db->prepare($query2);
		$stmt->bindParam("u_id",$u_id);
		$stmt->execute();
		$results2 = $stmt->fetch(PDO::FETCH_ASSOC);
		if(is_array($results) && is_array($results2)){
			$results = array_merge($results,$results2);
			$time = strtotime("now");
			$timesincelast = (strtotime("now") - $results['last_on']);
			if($timesincelast < 300){
				$results['online'] = 0;
			}else if($timesincelast < 600){
				$results['online'] = 1;
			}else{
				$results['online'] = 2;
			}
			$results['fans'] = $this->getFansNumeric($u_id);
			$results['supporters'] = $this->getSupportersNumeric($u_id);
			return $results;
		}
	}

	public function getInfo($u_id){
		$displayInfo = $this->userInfo($u_id);
		$displayInfo['dob'] = date("m/d/y",$displayInfo['dob']);
		$displayInfo['fans'] = $this->getFansNumeric($u_id);
		$displayInfo['supporters'] = $this->getSupportersNumeric($u_id);
		echo json_encode($displayInfo);
	}

	public function headerBar(){
		$u_id = $_SESSION['user_id'];
		//echo $u_id;
		$displayInfo = $this->userInfo($u_id);
		echo json_encode($displayInfo);
	}

	/*
		Allows you to edit information about a user by passing an associative array with key and value.
	*/
	public function editInfoGeneral($info){
		$json_status = array("status"=>"success");
		$act_fields = array('fname','lname','dob','hmtown','hmtown_perms','dob','dob_perms','status','gender','company','agent_type','num_clients');
		foreach($info as $key=>$value){
			if(in_array($key,$act_fields)){
				//deals with permissions that need their own objects made.
				if(strpos($key,"_perms")){
					if($value == "fan"){ $value = 1; }else{ $value = 0; }
					//accommodates for an update of permissions.
					//check if permissions exist for this already, if they do then dont make another, if not then make a new one.
					$select = "SELECT ".$key." FROM general_user WHERE u_id = :u_id;";
					$stmt = $this->db->prepare($select);
					$stmt->bindParam("u_id",$_SESSION['user_id']);
					$stmt->execute();
					$results = $stmt->fetch(PDO::FETCH_ASSOC);

					//means i need to do an update
					if($results[$key] != null){
						$update = "UPDATE permissions SET type = :type WHERE id = :id;";
						$stmt = $this->db->prepare($update);
						$stmt->bindParam("type",$value);
						$stmt->bindParam("id",$results[$key]);
						$stmt->execute();
						//echo "/////// UPDATE permissions SET type = '".$value."' WHERE id = '".$results[$key]."'; ///////";
						//no need to set new id, already is linked.

						$results = $results[$key];
					//entirely new permission, make a new object and set it.
					}else{
						$queryIn = "INSERT INTO permissions (type,u_id) VALUES (:type,:u_id);";
						$stmt = $this->db->prepare($queryIn);
						//convert to number not string
						$stmt->bindParam("type",$value);
						$stmt->bindParam("u_id",$_SESSION['user_id']);
						$stmt->execute();
						//get the last inserted item with user id, since other items likely are not going to change quickly.
						$query2 = "SELECT id FROM permissions WHERE u_id = :u_id ORDER BY id DESC LIMIT 1;";
						$stmt = $this->db->prepare($query2);
						$stmt->bindParam("u_id",$_SESSION['user_id']);
						$stmt->execute();
						$results = $stmt->fetch(PDO::FETCH_ASSOC);

						$value = $results['id'];
					}
				}

				if($key == "dob"){
					$value = trim(strtotime($value));
				}
				$query = "UPDATE general_user SET ".$key." = :value WHERE u_id = :user_id;";
				$stmt = $this->db->prepare($query);
				$stmt->bindParam("value",$value);
				$stmt->bindParam("user_id",$_SESSION['user_id']);
				$res = $stmt->execute();
				if(!$res){
					$json_status["status"] = "error";
					$json_status["status_msg"] = "There was an internal error in editing this information.";
				}
			}else{
				$json_status["status"] = "error";
				$json_status["status_msg"] = "That field does not exist.";
			}
		}
		echo json_encode($json_status);
	}

	public function updateStatus($post){
		$jsonArray = array("status","error");
		$ui = $this->userInfo($_SESSION['user_id']);
		$stmt = $this->db->prepare("UPDATE ".convertIntTypetoString($ui['type'])." SET status = :s WHERE u_id = :uid;");
		$stmt->bindParam("s",$post['status']);
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$res = $stmt->execute();
		if(!$res){
			$ei = $stmt->errorInfo();
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "There was an error with the database.".$ei[0]." ".$ei[1]." ".$ei[2]." ";
		}
		echo json_encode($jsonArray);
	}

	public function search($query){
		$json_return = array("results"=>array());

		//search users (general, band, musician, athelete, team, agent) all
		$query = $query["query"]."%";
		//different account types.

		//ENABLE THESE SELECTORS FOR WHEN MULTIPLE ACCOUNTS ARE SUPPORTED
		$selectors = array(
			"SELECT fname, lname, u_id, hmtown FROM general_user 	WHERE fname LIKE :query OR lname LIKE :query;",
			"SELECT fname, lname, u_id 		   FROM athelete_user 	WHERE fname LIKE :query OR lname LIKE :query;",
			"SELECT fname, lname, u_id         FROM musician_user 	WHERE fname LIKE :query OR lname LIKE :query;",
			"SELECT bname, 		  u_id         FROM band_user 		WHERE bname LIKE :query;",
			"SELECT tname,        u_id         FROM team_user 		WHERE tname LIKE :query;",
			"SELECT fname, lname, u_id, hmtown FROM agent_user 		WHERE fname LIKE :query OR lname LIKE :query;"
		);

		$orgin = array("standard","athelete","musician","band","team","agent");

		foreach($selectors as $num=>$select){
			$stmt = $this->db->prepare($select);
			$stmt->bindParam("query",$query);
			$stmt->execute();

			$results = $stmt->fetchAll(PDO::FETCH_ASSOC);
			//$results_prep = array_merge((array)$num,$results);

			foreach($results as $index=>$r){
				$uInfo = $this->userInfo($r['u_id']);
				$results[$index]['profile_pic'] = $uInfo['profile_pic'];
			}

			$json_return["results"][$orgin[$num]] = $results;
		}

		echo json_encode($json_return);
	}

	/*
		u1 = person that seeked the fanship   	u1 is fan of u2
		u2 = person that acknowledges fanship	u2 is given a supporter
	*/

	/*
		Must implement security procedures to ensure that this data cannot be easily changed.
	*/
	public function editFriends($u1, $u2, $status){
		//get the friendship with two people
		$query = "UPDATE fans SET u1 = :u1, u2 = :u2, status = :status WHERE (u1 = :u1 AND u2 = :u2);";

		//filter status data to just numbers
		switch($status){
			case 0: //pending
				$status = 0;
				break;
			case 1: //fans
				$status = 1;
				break;
			case 2: //blocked
				$status = 2;
				break;
			case 3: //unfanned
				$status = 3;
				break;
			case 4: //deny request
				$status = 4;
				break;
			default:
				$status = 0;
				break;
		}

		$stmt = $this->db->prepare($query);
		$stmt->bindParam("u1",$u1);
		$stmt->bindParam("u2",$u2);
		$stmt->bindParam("status",$status);
		$stmt->execute();
	}

	/*
		Makes a fans friendship setting the type to pending with the u1 and u2 ids associated with it.
		Don't want to make friendship if it already exists.

		JSON may not be needed for this. Because it will be used as an internal PHP function.

		u1 initializes friend request first.
		u2 will either accept or deny request.
	*/
	public function createFans($u1, $u2){
		$json_return = array("status"=>"success");
		//check if it exists
		$query = "SELECT COUNT(id) FROM fans WHERE (u1 = :u1 AND u2 = :u2);";
		$stmt = $this->db->prepare($query);
		$stmt->bindParam("u1",$u1);
		$stmt->bindParam("u2",$u2);
		$stmt->execute();
		$val = $stmt->fetch(PDO::FETCH_ASSOC);
		if($val['COUNT(*)'] == 0){
			//status is default 0 by mysql db
			$query = "INSERT INTO fans (u1, u2) VALUES (:u1,:u2);";
			$stmt = $this->db->prepare($query);
			$stmt->bindParam("u1",$u1);
			$stmt->bindParam("u2",$u2);
			//make the friendship
			$stmt->execute();
		}else{
			$json_return['status'] = "error";
			$json_return['status_msg'] = "There was a user with these id's already in use.";
		}
		echo json_encode($json_return);
	}

	/*
		Returns an array list of all friends of the user.
		Definitely involve memcache with this function!

		By default grabs all the friends of the user id that is passed.

		=====
		Use with userInfo function as declared above to get the info associated with the user once the ids is returned.
		=====
	*/
	public function getFriends($u_id,$type = 1){
		$fan_ids = array();

		//allow for getting different types of data about the friend ships.
		switch($type){
			case 0: //pending
				$type = 0;
				break;
			case 1: //fans
				$type = 1;
				break;
			case 2: //blocked
				$type = 2;
				break;
			case 3: //unfanned
				$type = 3;
				break;
			case 4: //denyrequest
				$type = 4;
				break;
			default:
				$type = 1; //get friends by default
				break;
		}

		//check u1 first
		$query = "SELECT u1 FROM fans WHERE u2 = :u_id WHERE type = :type;";

		if($val = $this->memcache->get(md5($query))){
			$val = unserialize($val);
			array_merge($fan_ids,$val);
		}else{
			$stmt = $this->db->prepare($query);
			$stmt->bindParam("u_id",$u_id);
			$stmt->bindParam("type",$type);
			$stmt->execute();
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC); //will be multiple ids
			array_merge($fan_ids,$data);

			$this->memcache->set(md5($query),serialize($data),0,(60*30)); //store for 30 mins
		}

		//check u2 second
		$query = "SELECT u2 FROM fans WHERE u1 = :u_id WHERE type = :type;";

		if($val = $this->memcache->get(md5($query))){
			$val = unserialize($val);
			array_merge($fan_ids,$val);
		}else{
			$stmt = $this->db->prepare($query);
			$stmt->bindParam("u_id",$u_id);
			$stmt->bindParam("type",$type);
			$stmt->execute();
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			array_merge($fan_ids,$data);

			$this->memcache->set(md5($query),serialize($data),0,(60*30)); //store for 30 mins
		}
	}

	public function fan($post){
		$json_array = array("status"=>"success");
		$info = array(
			"u1"=>$_SESSION['user_id'],
			"u2"=>$post['u_id'],
			"status"=>1
		);

		$check = "SELECT COUNT(id) FROM fans WHERE u1 = :u1 AND u2 = :u2;";
		$ck_stmt = $this->db->prepare($check);
		$ck_stmt->bindParam("u1",$info['u1']);
		$ck_stmt->bindParam("u2",$info['u2']);
		$ck_stmt->execute();

		$res = $ck_stmt->fetch(PDO::FETCH_ASSOC);

		if($res['COUNT(id)'] == 0){ //check if this friendship has been created
			$insert = "INSERT INTO fans (u1, u2, status) VALUES (:u1, :u2, :status);";
			$stmt = $this->db->prepare($insert);

			$result = $stmt->execute($info);
			$error = $stmt->errorInfo();

			if(!$result){
				$json_array = array("status"=>"error","status_msg"=>"Error, Come again later.");
			}else{
				$thumbnailPic = $this->userInfo($info['u1']);

				$params = array(
					'snapshotmult' 	=> "http://54.243.129.126/usr_content/pics/".$thumbnailPic['profile_pic']."_t.jpg",  //get this from the post db
					'actiontype' 	=> 2, //0 is commented
					'type'			=> 1, //0 is thoughtstream, 1 profile
					'subjecttype'	=> 4,  //get this from the post db, this is grabbed from above
					'useractionid'	=> $info['u2'],   //get this from the post db
					'postid'		=> $info['u1']	  //this is the follower that did it.
				);
				ob_start();
				$this->makeNotification($params);
				ob_end_flush();
			}
		}else{
			$json_array = array("status"=>"error","status_msg"=>"You're already a fan.");
		}

		echo json_encode($json_array);
	}

	public function getFansNumeric($id){
		$select = "SELECT COUNT(id) FROM fans WHERE u2 = :u2 AND status = 1;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("u2",$id);
		$stmt->execute();

		$res = $stmt->fetch(PDO::FETCH_ASSOC);
		return $res['COUNT(id)'];
	}

	public function getSupportersNumeric($id){
		$select = "SELECT COUNT(id) FROM fans WHERE u1 = :u1 AND status = 1;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("u1",$id);
		$stmt->execute();

		$res = $stmt->fetch(PDO::FETCH_ASSOC);
		return $res['COUNT(id)'];
	}

	public function getFans($post, $type=0){
		$id = $post['id'];
		$select = "SELECT u1 FROM fans WHERE u2 = :u2 AND status = 1;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("u2",$id);
		$stmt->execute();

		$res = $stmt->fetchAll(PDO::FETCH_ASSOC);

		$fans = array();

		foreach($res as $r){
			$userInfo = $this->userInfo($r['u1']);
			if($userInfo != null)
				$fans[] = $userInfo;
		}
		if($type == 0)
			echo json_encode($fans);
		else
			return $fans;
	}

	public function getSupporters($post){
		$id = $post['id'];
		$select = "SELECT u2 FROM fans WHERE u1 = :u1 AND status = 1;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("u1",$id);
		$stmt->execute();

		$res = $stmt->fetchAll(PDO::FETCH_ASSOC);

		$fans = array();

		foreach($res as $r){
			$userInfo = $this->userInfo($r['u2']);
			if($userInfo != null)
				$fans[] = $userInfo;
		}

		echo json_encode($fans);
	}

	public function tabContent($type){
		$query = "SELECT title,tab_script FROM tab_preset WHERE tab_type = :tab_type ORDER BY pos ASC;";
		$stmt = $this->db->prepare($query);
		$stmt->bindParam("tab_type",$type);
		$stmt->execute();

		$results = $stmt->fetchAll(PDO::FETCH_ASSOC);
		return $results;
	}

	public function addLink($post){
		// link & link_content
		$jsonEncode = array("status"=>"success");

		$exists = false;
		$file_headers = @get_headers($post['link_content']);
		if($file_headers[0] == 'HTTP/1.1 404 Not Found') {
			$exists = false;
		}else {
			$exists = true;
		}

		if($exists){
			$insert = "INSERT INTO link	(u_id, link, link_content) VALUES (:u_id, :link, :link_content);";
			$stmt = $this->db->prepare($insert);
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->bindParam("link",$post['link']);
			$stmt->bindParam("link_content",$post['link_content']);
			$res = $stmt->execute();

			$select = "SELECT id FROM link WHERE u_id = :uid ORDER BY id DESC LIMIT 1;";
			$stmt = $this->db->prepare($select);
			$stmt->bindParam("uid",$_SESSION['user_id']);
			$res = $stmt->execute();

			$data = $stmt->fetch(PDO::FETCH_ASSOC);
			$jsonEncode['data'] = $data['id']; //get the id of the link

			if(!$res){
				$jsonEncode['status'] = "error";
				$jsonEncode['status_msg'] = "There was an error submitting the link because the database is not working properly.";
			}
		}else{
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "You must provide a valid link.";
		}

		echo json_encode($jsonEncode);
	}

	public function getLinks($usersid){
		$key = 'AIzaSyCu7yh4EBVz1town2w7Pk7iy2ZJ4ZizOEE';
		$googer = new GoogleURLAPI($key);

		$select = "SELECT id, link, link_content FROM link WHERE u_id = :u_id ORDER BY id DESC;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("u_id",$usersid);
		$stmt->execute();

		$return = $stmt->fetchAll(PDO::FETCH_ASSOC);

		foreach($return as $pos=>$r){
			$shortDWName = $googer->shorten($r['link_content']);
			$return[$pos]['link_short'] = $shortDWName;
		}

		echo json_encode($return);
	}

	public function getLink($l_id){
		$jsonReturn = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT id, link, link_content FROM link WHERE id = :id;");
		$stmt->bindParam("id",$l_id);
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "The description for this photo could not be updated.";
		}else{
			$data = $stmt->fetch(PDO::FETCH_ASSOC);
			$jsonReturn['data'][] = $data;
		}

		echo json_encode($jsonReturn);
	}

	public function removeLink($post){
		$jsonReturn = array("status"=>"success");

		$remove = "DELETE FROM link WHERE id = :id AND u_id = :u_id;";

		$stmt = $this->db->prepare($remove);
		$stmt->bindParam("id",$post['link']);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->execute();

		echo json_encode($jsonReturn);
	}

	public function editDescription($post){
		$jsonArray = array("status"=>"success");

		$select = "UPDATE photo SET description = :description WHERE photo_path = :photo_path AND u_id = :u_id;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->bindParam("photo_path",$post['id']);
		$stmt->bindParam("description",$post['text']);
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "The description for this photo could not be updated.";
		}

		echo json_encode($jsonArray);
	}

	/*
		Grabs photos from the specified id passed to the function.

		TODO: Account for users that dont have permissions to view these photos.
	*/
	public function getPhotos($u_id){
		$jsonArray = array("status"=>"success");

		$select = "SELECT photo_path FROM photo WHERE u_id = :u_id AND remove = 0;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("u_id",$u_id);
		$outcome = $stmt->execute();

		if($outcome){
			$results = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($results as $pos=>$val){
				$jsonArray["data"][] = $val['photo_path'];
			}
		}else{
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "There was an error retrieving the images from this user.";
		}

		echo json_encode($jsonArray);
	}

	public function getPhotoData($id){
		$jsonArray = array("status"=>"success");

		$select = "SELECT description,date,u_id FROM photo WHERE photo_path = :id AND remove = 0;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("id",$id);
		$outcome = $stmt->execute();

		if($outcome){
			$results = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($results as $pos=>$val){
				$jsonArray["data"]["description"] = $val['description'];
				$jsonArray["data"]["date"] = date("M j\, Y",$val['date']);

				$userData = $this->userInfo($val['u_id']);
				$jsonArray["data"]["user_id"] = $val['u_id'];
				$jsonArray["data"]["profile_pic"] = $userData['profile_pic'];
				if(($userData['type'] <= 1) || ($userData['type'] == 3) || ($userData['type'] == 5))
					$jsonArray["data"]["name"] = $userData['fname']." ".$userData['lname'];
				else
					if($userData['type'] == 2)
						$jsonArray["data"]["name"] = $userData['tname'];
					else
						$jsonArray["data"]["name"] = $userData['bname'];
			}
		}else{
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "There was an error retrieving the images from this user.";
		}

		echo json_encode($jsonArray);
	}

	public function getVideoData($id){
		$jsonArray = array("status"=>"success");

		$select = "SELECT date,u_id FROM video WHERE y_id = :id AND remove = 0;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("id",$id);
		$outcome = $stmt->execute();

		if($outcome){
			$results = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($results as $pos=>$val){
				$jsonArray["data"]["date"] = date("M j\, Y",$val['date']);

				$userData = $this->userInfo($val['u_id']);
				$jsonArray["data"]["user_id"] = $val['u_id'];
				$jsonArray["data"]["profile_pic"] = $userData['profile_pic'];
				if(($userData['type'] <= 1) || ($userData['type'] == 3) || ($userData['type'] == 5))
					$jsonArray["data"]["name"] = $userData['fname']." ".$userData['lname'];
				else
					if($userData['type'] == 2)
						$jsonArray["data"]["name"] = $userData['tname'];
					else
						$jsonArray["data"]["name"] = $userData['bname'];
			}
		}else{
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "There was an error retrieving the videos from this user.";
		}

		echo json_encode($jsonArray);
	}

	public function getVideos($u_id){
		$jsonArray = array("status"=>"success");

		$select = "SELECT y_id FROM video WHERE u_id = :u_id AND remove = 0;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("u_id",$u_id);
		$outcome = $stmt->execute();

		if($outcome){
			$results = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($results as $pos=>$val){
				$jsonArray["data"][] = $val['y_id'];
			}
		}else{
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "There was an error retrieving the videos from this user.";
		}

		echo json_encode($jsonArray);
	}

	public function addTune($post){
		$jsonArray = array("status","success");

		$zero = 0;
		$date = strtotime("now");

		$stmt = $this->db->prepare("INSERT INTO tune (y_id,name,a_id,date,u_id,duration,artist,album) VALUES (:y_id,:name,:a_id,:date,:u_id,:duration,:artist,:album);");
		$stmt->bindParam("y_id",$post['y_id']);
		$stmt->bindParam("name",$post['name']);
		$stmt->bindParam("artist",$post['artist']);
		$stmt->bindParam("album",$post['album']);
		$stmt->bindParam("a_id",$zero);
		$stmt->bindParam("date",$date);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->bindParam("duration",$post['duration']);
		$res = $stmt->execute();

		if(!$res){
			$error = $stmt->errorInfo();
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "There was an error adding the record to the database. -".$error[0]."-".$error[1]."-".$error[2];
		}

		echo json_encode($jsonArray);
	}

	public function getMusic($id){
		$results = array("status"=>"success");

		if($id == "")
			$id = $_SESSION['user_id'];
		$stmt = $this->db->prepare("SELECT y_id, name, a_id, id, duration, album, artist FROM tune WHERE u_id = :id AND remove = 0 ORDER BY position;");
		$stmt->bindParam("id",$id);
		$stmt->execute();

		$results2 = $stmt->fetchAll(PDO::FETCH_ASSOC);
		$results['data'] = $results2;

		echo json_encode($results);
	}

	public function addVideo($post){
		$jsonEncode = array("status"=>"success");
		$stmt = $this->db->prepare("INSERT INTO video (name, u_id, date, y_id) VALUES (:name,:u_id,:date,:y_id);");
		$stmt->bindParam("name",$post['name']);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$date = strtotime("now");
		$stmt->bindParam("date",$date);
		$stmt->bindParam("y_id",$post['y_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status'] = "error";
			$err = $stmt->errorInfo();
			$jsonEncode['status_msg'] = "There was an error with the database.".$err[0]." ".$err[1]." ".$err[2];
		}
		echo json_encode($jsonEncode);
	}

	/*
		Posting things here.
	*/

	public function addPosting($post){
		$jsonEncode = array("status"=>"success");
		$stmt = $this->db->prepare("INSERT INTO post (u_id, p_id, type, text, date, text_add, r_id, post_type) VALUES (:u_id, :p_id, :type, :text, :date, :text_add, :r_id, :pt);");
		$p_id = 0;
		$stmt->bindParam("p_id",$p_id);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->bindParam("text",$post['text']);
		$stmt->bindParam("type",$post['type']);
		$date = strtotime("now");
		$stmt->bindParam("date",$date);
		$stmt->bindParam("r_id",$post['r_id']);
		$stmt->bindParam("text_add",$post['text_add']);
		$stmt->bindParam("pt",$post['post_type']);
		//$stmt->bindParam("c",$post['cat']);  	//category
		//$stmt->bindParam("cb",$post['cat_b']); 	//category broad
		$res = $stmt->execute();

		$statement = "SELECT id FROM post WHERE u_id = :uid ORDER BY id DESC LIMIT 1;";
		$stmt = $this->db->prepare($statement);
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->execute();
		$stmt->execute();

		$data = $stmt->fetch(PDO::FETCH_ASSOC);

		$jsonEncode['data'] = $data['id'];

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "Posting could not be made.".$stmt->errorInfo[0]." ".$stmt->errorInfo[1];
		}

		echo json_encode($jsonEncode);
	}

	public function grabLikeUsers(){
		$jsonEncode = array("status"=>"success");

		$select = "SELECT type, preference FROM preferences WHERE u_id = :uid;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->execute();

		if($stmt){ //now you have all the desires that you like
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

			$userIDs = array();
			$userIDsMore = array();


			foreach($data as $d){
				$select2 = "SELECT u_id, type, preference FROM preferences WHERE type = :t AND preference = :p AND u_id != :uid;";
				$stmt2 = $this->db->prepare($select2);
				$stmt2->bindParam("t",$d['type']);
				$stmt2->bindParam("p",$d['preference']);
				$stmt2->bindParam("uid",$_SESSION['user_id']);
				$stmt2->execute();

				$data2 = $stmt2->fetchAll(PDO::FETCH_ASSOC);

				if($data2 != null){
					foreach($data2 as $d2){
						if(!in_array($d2['u_id'],$userIDs)){
							array_push($userIDsMore,$d2);
							array_push($userIDs,$d2['u_id']);
						}
					}
				}
			}

			$finalArray = array();

			foreach($userIDsMore as $uidm){
				$user_info = $this->userInfo($uidm['u_id']);
				if($uidm['type'] == 0){ //sport
					$select = "SELECT sport AS name FROM sport WHERE id = :i;";
				}else{
					$select = "SELECT genre AS name FROM genre WHERE id = :i;";
				}
				$stmt = $this->db->prepare($select);
				$stmt->bindParam("i",$uidm['preference']);
				$stmt->execute();

				$data3 = $stmt->fetch(PDO::FETCH_ASSOC);

				$select = "SELECT profile_music FROM user WHERE id = :uid;";
				$stmt = $this->db->prepare($select);
				$stmt->bindParam("uid",$uidm['u_id']);
				$stmt->execute();

				$data = $stmt->fetch(PDO::FETCH_ASSOC);

				if($stmt){
					$select = "SELECT * FROM tune WHERE id = :i;";
					$stmt = $this->db->prepare($select);
					$stmt->bindParam("i",$data['profile_music']);
					$stmt->execute();

					$data2 = $stmt->fetchAll(PDO::FETCH_ASSOC);

					array_push($userIDsMore,$data2);
				}

				$finalArraySmall = array($user_info, $data3['name'], $data2);
				array_push($finalArray, $finalArraySmall);
			}

			$jsonEncode['data'] = $finalArray;
		}

		echo json_encode($jsonEncode);
	}

	public function grabPostings($userID, $view, $category, $type){
		$jsonEncode = array("status"=>"success");

		$select = "SELECT * FROM post WHERE u_id = :userID, type = :type, category = :category, post_type = :post_type;";
		$stmt = $this->db->prepare($select);

		$stmt->bindParam("userID",$userID);
		$typeArray = array("image"=>1,"video"=>2,"link"=>3,"all"=>4);
		$stmt->bindParam("type",$typeArray[$type+1]); //needs filtering
		$categoryArray = array("sports"=>0,"genre"=>1,"suggestions"=>2,"both"=>3);
		$stmt->bindParam("category",$categoryArray[$category]);
		$stmt->bindParam("post_type",$view);
		$res = $stmt->execute();

		if($res){
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
		}else{
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was an error with retreiving your postings.";
		}

		echo json_encode($jsonEncode);
	}

	public function getPostings($rid,$ptype,$startLimit = 0){
		/*
			Account for multiple pages to be loaded by this function. And also take into account
			the fans that you are going to see their postings for.
		*/
		$jsonEncode = array("status"=>"success");

		//$stmt = $this->db->prepare("SELECT COUNT(id) FROM post WHERE remove = 0 AND ;");
		//use the function getFans to grab all of your fans.

		if(!isset($startLimit) || !is_numeric($startLimit))
			$startLimit = 0;
		if(((int)$ptype) == 1){ //sport
			$stmt = $this->db->prepare("SELECT * FROM post WHERE remove = 0 AND r_id = :rid AND category = 1 AND post_type = 0 ORDER BY date DESC LIMIT ".$startLimit.",20;");
		}else if(((int)$ptype) == 2){
			$stmt = $this->db->prepare("SELECT * FROM post WHERE remove = 0 AND r_id = :rid AND category = 2 AND post_type = 0 ORDER BY date DESC LIMIT ".$startLimit.",20;");
		}else{ //make support for a 3rd type of request.
			$stmt = $this->db->prepare("SELECT * FROM post WHERE remove = 0 AND r_id = :rid AND post_type = 0 ORDER BY date DESC LIMIT ".$startLimit.",20;");
		}

		//$stmt->bindParam("id",$_SESSION['user_id']);
		$stmt->bindParam("rid",$rid);
		$res = $stmt->execute();
		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

		//SELECT * FROM post WHERE remove = 0 AND r_id = :rid AND post_type = 0 ORDER BY date DESC LIMIT ,20;

		foreach($data as $id=>$post){
			$post['name'] = $this->userInfo($post['u_id']);
			$post['date'] = relTime($post['date']);
			$jsonEncode['data'][] = $post;
		}

		/*
		}else{
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "There was an error retrieving your postings.";
		}
		*/

		echo json_encode($jsonEncode);
	}

	public function addPostingCategory($post){
		$jsonEncode = array("status"=>"success");

		$update = "UPDATE post SET category = :cat, category_broad = :cat_b WHERE id = :post_id;";
		$stmt = $this->db->prepare($update);
		$stmt->bindParam("cat",$post['cat']); //category
		$stmt->bindParam("cat_b",$post['cat_b']); //category broad
		$stmt->bindParam("post_id",$post['post_id']); //post id
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was a problem associating the category with the posting.";
		}

		echo json_encode($jsonEncode);
	}

	public function getProfilePostings($rid,$startLimit = 0,$ptype){
		/*
			Account for multiple pages to be loaded by this function. And also take into account
			the fans that you are going to see their postings for.
		*/
		$jsonEncode = array("status"=>"success");

		if(!isset($startLimit) || !is_numeric($startLimit))
			$startLimit = 0;
		$amountLoad = 10;
		$startLimit *= $amountLoad;

		if(((int)$ptype) == 1){ //sport
			$stmt = $this->db->prepare("SELECT * FROM post WHERE remove = 0 AND category = 1 AND r_id = :rid AND post_type = 0 ORDER BY date DESC LIMIT ".$startLimit.",".$amountLoad.";"); // AFTER DESC:  LIMIT ".$startLimit.",10;
		}else if(((int)$ptype) == 2){
			$stmt = $this->db->prepare("SELECT * FROM post WHERE remove = 0 AND category = 2 AND r_id = :rid AND post_type = 0 ORDER BY date DESC LIMIT ".$startLimit.",".$amountLoad.";"); // AFTER DESC:  LIMIT ".$startLimit.",10;
		}else{
			$stmt = $this->db->prepare("SELECT * FROM post WHERE remove = 0 AND r_id = :rid AND post_type = 0 ORDER BY date DESC LIMIT ".$startLimit.",".$amountLoad.";"); // AFTER DESC:  LIMIT ".$startLimit.",10;
		}
		$stmt->bindParam("rid",$rid);
		$res = $stmt->execute();
		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

		if(((int)$ptype) == 1){ //sport
			$stmt2 = $this->db->prepare("SELECT COUNT(id) FROM post WHERE remove = 0 AND category = 1 AND r_id = :rid AND post_type = 0;");
		}else if(((int)$ptype) == 2){
			$stmt2 = $this->db->prepare("SELECT COUNT(id) FROM post WHERE remove = 0 AND category = 2 AND r_id = :rid AND post_type = 0;");
		}else{
			$stmt2 = $this->db->prepare("SELECT COUNT(id) FROM post WHERE remove = 0 AND r_id = :rid AND post_type = 0;");
		}
		$stmt2->bindParam("rid",$rid);
		$stmt2->execute();
		$data2 = $stmt2->fetch(PDO::FETCH_ASSOC);

		$jsonEncode['amt'] = intval(ceil($data2['COUNT(id)']/$amountLoad));

		foreach($data as $id=>$post){
			$post['name'] = $this->userInfo($post['u_id']);
			$post['date'] = relTime($post['date']);
			$jsonEncode['data'][] = $post;
		}

		echo json_encode($jsonEncode);
	}

	public function addEditLineup($post){
		$jsonEncode = array("status"=>"success");

		//REQUIRES - add, item, font_id, color_id, position_id
		if($post['action'] == "add"){
			$stmt = $this->db->prepare("INSERT INTO lineup (u_id, item, font_id, color_id, position_id) VALUES (:u_id, :item, :font_id, :color_id, :position_id);");
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->bindParam("item",ucfirst($post['item']));
			$stmt->bindParam("font_id",$post['font_id']);
			$stmt->bindParam("color_id",$post['color_id']);
			$stmt->bindParam("position_id",$post['position_id']);
			$res = $stmt->execute();
			if(!$res){
				$jsonEncode['status'] = "error";
				$jsonEncode['status_msg'] = "Lineup item could not be added. ";
			}
		//REQUIRES - edit, position_id_1, position_id_2, id1, id2
		}else if($post['action'] == "edit"){

			// id 		-- Id of the element
			// moveTo	-- Position to move to

			/*
			//LINEUP ITEM #1
			$stmt = $this->db->prepare("UPDATE lineup SET position_id = :position_id WHERE id = :id1 AND u_id = :u_id;");
			$stmt->bindParam("position_id",$post['position_id_1']);
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->bindParam("id1",$post['id1']);
			$res1 = $stmt->execute();
			*/

			//pass a list of updated positions with their ids
			$index = 0;
			foreach($post['items_list'] as $li){
				$stmt = $this->db->prepare("UPDATE lineup SET position_id = :li_pos WHERE id = :li_id AND u_id = :u_id;");
				$stmt->bindParam("li_pos",$index,PDO::PARAM_INT);
				$stmt->bindParam("li_id",$li,PDO::PARAM_INT);
				$stmt->bindParam("u_id",$_SESSION['user_id']);
				$res = $stmt->execute();
				if(!$res){
					$errorInfo = $stmt->errorInfo();
					$jsonEncode['status'] = "error";
					$jsonEncode['status_msg'] = "Item could not be moved up. DB ERRORS:".$errorInfo[0].$errorInfo[2];
				}
				$index++;
			}

			/*
			//LINEUP ITEM #2
			$stmt = $this->db->prepare("UPDATE lineup SET position_id = :position_id WHERE id = :id2 AND u_id = :u_id;");
			$stmt->bindParam("position_id",$post['position_id_2']);
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->bindParam("id2",$post['id2']);
			$res2 = $stmt->execute();


			if((!$res1) || (!$res2)){
				$jsonEncode['status'] = "error";
				$jsonEncode['status_msg'] = "Item could not be moved up. DB ERRORS:".$stmt->errorInfo[0].$stmt->errorInfo[1]." DATA:".$post['position_id_1']." ".$post['position_id_2']." ".$post['id1']." ".$post['id2'];
			}
			*/
		//REQUIRES - remove, id
		}else if($post['action'] == "remove"){
			$stmt = $this->db->prepare("DELETE FROM lineup WHERE id = :id AND u_id = :u_id;");
			$stmt->bindParam("id",$post['id']);
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->execute();
			$res = $stmt->execute();
			if(!$res){
				$jsonEncode['status'] = "error";
				$jsonEncode['status_msg'] = "The lineup item could not be removed!";
			}else{
				//now retrieve all items and
				$stmt = $this->db->prepare("SELECT position_id, id FROM lineup WHERE u_id = :uid ORDER BY position_id ASC;");
				$stmt->bindParam("uid",$_SESSION['user_id']);
				$res = $stmt->execute();
				if(!$res){
					$jsonEncode['status'] = "error";
					$jsonEncode['status_msg'] = "The lineup item could not be removed!";
				}else{
					$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
					$i = 0;
					foreach($data as $r){
						//now update the positions
						$stmt = $this->db->prepare("UPDATE lineup SET position_id = :pos_id WHERE id = :pid;");
						$stmt->bindParam("pos_id",$i);
						$stmt->bindParam("pid",$r['id']);
						$res = $stmt->execute();
						if(!$res){
							$jsonEncode['status'] = "error";
							$jsonEncode['status_msg'] = "The lineup item could not be removed!";
						}
						$i++;
					}
				}
			}
		}
		echo json_encode($jsonEncode);
	}

	public function getLineup($post_id){
		$jsonArray = array("status"=>array("status"=>"success"));
		if(isset($post_id)){
			$stmt = $this->db->prepare("SELECT * FROM lineup WHERE u_id  = :id ORDER BY position_id;");
			$stmt->bindParam("id",$post_id);
			$res = $stmt->execute();
			if($res){
				$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
				foreach($data as $id=>$item){
					$jsonArray['data'][] = $item;
				}
			}else{
				$jsonArray['status']['status'] = "error";
				$jsonArray['status']['status_msg'] = "Could not fetch lineup from DB.";
			}
		}else{
			$jsonArray['status']['status'] = "error";
			$jsonArray['status']['status_msg'] = "Could not fetch lineup.";
		}
		echo json_encode($jsonArray);
	}

	public function editProfilePic($post){
		$jsonEncode = array("status","success");
		$stmt = $this->db->prepare("UPDATE user SET profile_pic = :pic_id WHERE id = :u_id;");
		$stmt->bindParam("pic_id",$post['pic_id']);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "Profile picture could not be updated.";
		}
		echo json_encode($jsonEncode);
	}

	public function editHomePic($post){
		$jsonEncode = array("status","success");
		$stmt = $this->db->prepare("UPDATE user SET home_pic = :pic_id WHERE id = :u_id;");
		$stmt->bindParam("pic_id",$post['pic_id']);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "Profile picture could not be updated.";
		}
		echo json_encode($jsonEncode);
	}

	public function randomFonts(){
		$stmt2 = $this->db->prepare("SELECT id FROM lineup;");
		$stmt2->execute();
		$res = $stmt2->fetchAll(PDO::FETCH_ASSOC);

		foreach($res as $item){
			$stmt = $this->db->prepare("UPDATE lineup SET color_id = :cid, font_id = :fid WHERE id = :id AND u_id = :u_id;");
			$r1 = rand(0,7);
			$stmt->bindParam("cid",$r1);
			//$r2 = rand(0,1);
			$r2 = 0;
			$stmt->bindParam("fid",$r2);
			$stmt->bindParam("id",$item['id']);
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$stmt->execute();
		}
	}

	public function addChat($post){
		$jsonEncode = array("status","success");
		$stmt = $this->db->prepare("INSERT INTO chat (msg, date, u_id, u2_id) VALUES (:msg,:date,:u_id,:u2_id);");
		$stmt->bindParam("msg",$post['msg']);
		$dt = time();
		$stmt->bindParam("date",$dt);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->bindParam("u2_id",$post['u2']);
		$res = $stmt->execute();

		$stmt = $this->db->prepare("SELECT id FROM chat WHERE date = :datep AND u_id = :u_id LIMIT 1;");
		$stmt->bindParam("datep",$dt);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->execute();

		$data2 = $stmt->fetch(PDO::FETCH_ASSOC);
		$chatId = $data2['id'];

		$stmt2 = $this->db->prepare("INSERT INTO chat_alerts (u1, u2, date_created, reviewed, c_id) VALUES (:u1, :u2, :date_created, :reviewed, :c_id);");
		$stmt2->bindParam("u1",$_SESSION['user_id']);
		$stmt2->bindParam("u2",$post['u2']);
		$stmt2->bindParam("date_created",$dt); //$dt should be strtotime("now"), so that it grabs the int timestamp
		$zero = 0;
		$stmt2->bindParam("reviewed",$zero);
		$stmt2->bindParam("c_id",$chatId);
		$stmt2->execute();

		//insert into review area for alert from above command ^^^

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "Chat was not delivered.";
		}
		echo json_encode($jsonEncode);
	}

	public function getChatUsers(){
		$jsonEncode = array("status","success");

		//make it support filtering of fans etc.
		$stmt = $this->db->prepare("SELECT id FROM user;");
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display users.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$userInfo = $this->userInfo($d['id']);

				$stmt = $this->db->prepare("SELECT COUNT(id) FROM chat_alerts WHERE u1 = :u1 AND u2 = :u2 AND reviewed = :reviewed;");
				$stmt->bindParam("u1",$d['id']);
				$stmt->bindParam("u2",$_SESSION['user_id']);
				$zero = 0;
				$stmt->bindParam("reviewed",$zero);
				$stmt->execute();

				$data = $stmt->fetch(PDO::FETCH_ASSOC);

				$userInfo['alert'] = $data['COUNT(id)'];
				$jsonEncode['data'][] = $userInfo;
			}
		}
		echo json_encode($jsonEncode);
	}

	public function checkChat($u1_id){
		$jsonEncode = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT * FROM chat_alerts WHERE u1 = :u1 AND u2 = :u2 AND reviewed = :reviewed LIMIT 1;");
		$stmt->bindParam("u1",$u1_id);
		$stmt->bindParam("u2",$_SESSION['user_id']);
		$zero = 0;
		$stmt->bindParam("reviewed",$zero);
		$stmt->execute();

		$data = $stmt->fetch(PDO::FETCH_ASSOC);

		//Taken directly from grabChats function.
		$stmt = $this->db->prepare("SELECT * FROM chat WHERE id = :id;");
		$stmt->bindParam("id",$data['c_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display chats.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $js){
				$js['date'] = relTime($js['date'])." ago";
				if($_SESSION['user_id'] == $js['u_id']){
					$js['who'] = 0;
				}else{
					$js['who'] = 1;
				}
				$jsonEncode['data'][] = $js;
			}
		}
		//end block

		//set reviewed to 1 to indicate that this chat has already been reviewed., might just want to delete this shit, because it's useless

		echo json_encode($jsonEncode);
	}

	public function markCheckChat($u1_id){
		$jsonArray = array("status"=>"success");

		$stmt = $this->db->prepare("UPDATE chat_alerts SET reviewed = 1 WHERE u1 = :u1 AND u2 = :u2;");
		$stmt->bindParam("u1",$u1_id);
		$stmt->bindParam("u2",$_SESSION['user_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display chats.";
		}

		echo json_encode($jsonArray);
	}

	public function keepAlive(){
		$stmt = $this->db->prepare("UPDATE user SET last_on = :timeup WHERE id = :id;");
		$d = strtotime("now");
		$stmt->bindParam("timeup",$d);
		$stmt->bindParam("id",$_SESSION['user_id']);
		$stmt->execute();
	}

	public function grabChats($id){
		$jsonEncode = array("status","success");
		$stmt = $this->db->prepare("SELECT * FROM chat WHERE (u_id = :id AND u2_id = :id2) OR (u_id = :id3 AND u2_id = :id4) ORDER BY date;");
		$stmt->bindParam("id",$_SESSION['user_id']);
		$stmt->bindParam("id2",$id);
		$stmt->bindParam("id3",$id);
		$stmt->bindParam("id4",$_SESSION['user_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display users.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $js){
				$js['date'] = relTime($js['date'])." ago";
				if($_SESSION['user_id'] == $js['u_id']){
					$js['who'] = 0;
				}else{
					$js['who'] = 1;
				}
				$jsonEncode['data'][] = $js;
			}
		}
		echo json_encode($jsonEncode);
	}

	public function grabQuotes($u_id){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("SELECT * FROM quote WHERE u_id = :u_id ORDER BY id;");
		$stmt->bindParam("u_id",$u_id);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display quotes.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$jsonEncode['data'][] = $d;
			}
		}
		echo json_encode($jsonEncode);
	}

	public function addQuote($post){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("INSERT INTO quote (u_id, quote, auth, date) VALUES (:u_id, :quote, :auth, :date);");
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->bindParam("quote",$post['quote']);
		$stmt->bindParam("auth",$post['auth']);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not insert quote.";
		}
		echo json_encode($jsonEncode);
	}

	public function deleteQuote($id){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("DELETE FROM quote WHERE id = :id AND u_id = :u_id;");
		$stmt->bindParam("id",$id);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display memory.";
		}

		echo json_encode($jsonEncode);
	}

	public function addMemory($post){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("INSERT INTO memory (u_id, memory, year, date) VALUES (:u_id, :memory, :year, :date);");
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->bindParam("memory",$post['memory']);
		$stmt->bindParam("year",$post['year']);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not insert quote.";
		}
		echo json_encode($jsonEncode);
	}

	public function grabMemories($u_id){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("SELECT * FROM memory WHERE u_id = :u_id ORDER BY year DESC;");
		$stmt->bindParam("u_id",$u_id);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display memories.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$jsonEncode['data'][] = $d;
			}
		}
		echo json_encode($jsonEncode);
	}

	public function deleteMemory($id){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("DELETE FROM memory WHERE id = :id AND u_id = :u_id;");
		$stmt->bindParam("id",$id);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display memory.";
		}

		echo json_encode($jsonEncode);
	}

	public function removePhoto($id){
		$stmt = $this->db->prepare("UPDATE photo SET remove = 1 WHERE u_id = :uid AND photo_path = :pp;");
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->bindParam("pp",$id);
		$stmt->execute();
	}

	public function removeVideo($id){
		$stmt = $this->db->prepare("UPDATE video SET remove = 1 WHERE u_id = :uid AND y_id = :pp;");
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->bindParam("pp",$id);
		$stmt->execute();
	}

	public function editImageDescription($post){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("UPDATE photo SET description = :desc WHERE photo_path= :photo_path;");
		$stmt->bindParam("desc",$post['description']);
		$stmt->bindParam("photo_path",$post['r_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not edit description.";
		}
		echo json_encode($jsonEncode);
	}

	public function editAboutMe($post){
		$jsonEncode['status'] = "success";
		$u = $this->userInfo($_SESSION['user_id']);
		$stmt = $this->db->prepare("UPDATE ".convertIntTypetoString($u['type'])." SET about_me = :aboutme WHERE u_id = :id;");
		$stmt->bindParam("id",$_SESSION['user_id']);
		$stmt->bindParam("aboutme",$post['aboutme']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display memories.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$jsonEncode['data'][] = $d;
			}
		}
		echo json_encode($jsonEncode);
	}

	public function grabAboutMe($u_id){
		$jsonEncode['status'] = "success";
		$u = $this->userInfo($u_id);
		$stmt = $this->db->prepare("SELECT about_me FROM ".convertIntTypeToString($u['type'])." WHERE u_id = :u_id;");
		$stmt->bindParam("u_id",$u_id);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display memories.";
		}else{
			$data = $stmt->fetch(PDO::FETCH_ASSOC);
			$jsonEncode['data'][] = $data['about_me'];
		}
		echo json_encode($jsonEncode);
	}

	public function grabComments($r_id, $type){
		$jsonEncode['status'] = "success";
		switch($type){
			case 0: //feed
				$stmt = $this->db->prepare("SELECT * FROM comment WHERE r_id = :r_id AND type = :type ORDER BY date ASC;");
				$stmt->bindParam("r_id",$r_id);
				$stmt->bindParam("type",$type);
				$res = $stmt->execute();
				if(!$res){
					$jsonEncode['status']['status'] = "error";
					$jsonEncode['status']['status_msg'] = "Could not grab comments for the feed.";
				}else{
					//add comments to data
					$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
					foreach($data as $d){
						$u = $this->userInfo($d['u_id']);
						$d['name'] = $u['fname']." ".$u['lname']."".$u['tname']."".$u['bname'];
						$d['date'] = relTime($d['date']);
						$jsonEncode['data'][] = $d;
					}
				}
				break;
			case 1: //photo/video
				$stmt = $this->db->prepare("SELECT * FROM comment WHERE r_id = :r_id AND type = :type;");
				$stmt->bindParam("r_id",$r_id);
				$stmt->bindParam("type",$type);
				$res = $stmt->execute();
				if(!$res){
					$jsonEncode['status']['status'] = "error";
					$jsonEncode['status']['status_msg'] = "Could not grab comments.";
				}else{
					//add comments to data
					$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
					foreach($data as $d){
						$u = $this->userInfo($d['u_id']);
						$d['name'] = $u['fname']." ".$u['lname']."".$u['tname']."".$u['bname'];
						$d['date'] = date("M j, Y",$d['date']);
						$jsonEncode['data'][] = $d;
					}
				}
				break;
		}
		echo json_encode($jsonEncode);
	}

	public function addComment($post){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("INSERT INTO comment (u_id, comment, type, date, r_id) VALUES (:u_id, :comment, :type, :date, :r_id);");
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->bindParam("comment",$post['comment']);
		$stmt->bindParam("type",$post['type']);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$stmt->bindParam("r_id",$post['r_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not post comment.";
		}else{
			//grab info about the post
			$stmt2 = $this->db->prepare("SELECT * FROM post WHERE id = :r_id LIMIT 1;");
			$stmt2->bindParam("r_id",$post['r_id']);
			$res = $stmt2->execute();

			$postData = $stmt2->fetch(PDO::FETCH_ASSOC);

			//add notification here
			$thumbnailPic = $postData['text_add'];

			if($postData['type'] == 1)
				$thumbnailPic = "http://54.243.129.126/usr_content/pics/".$postData['text_add']."_t.jpg";
			else if($postData['type'] == 2)
				$thumbnailPic = "http://i.ytimg.com/vi/".$postData['text_add']."/2.jpg";
			else
				$thumbnailPic = "";

			/*if($postData['type'] == 0)
				$postData['type'] = 1;
			else if($postData['type'] == 1)
				$postData['type'] = 0;*/

			$params = array(
				'snapshotmult' 	=> $thumbnailPic,  //get this from the post db
				'actiontype' 	=> 0, //0 is commented
				'type'			=> ($postData['post_type'] == 0 ? 1 : 0), //0 is thoughtstream
				'subjecttype'	=> $postData['type'],  //get this from the post db, this is grabbed from above
				'useractionid'	=> $postData['u_id'],   //get this from the post db
				'postid'		=> $post['r_id']
			);
			ob_start();
			$this->makeNotification($params);
			ob_end_clean();
		}

		echo json_encode($jsonEncode);
	}

	public function createAlbum($post){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("INSERT INTO album (title, description, u_id, p_id, date) VALUES (:title, :description, :u_id, :p_id, :date);");
		$stmt->bindParam("title",$post['title']);
		$stmt->bindParam("description",$post['description']);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$pid = 0;
		$stmt->bindParam("p_id",$pid);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not post comment.";
		}
		echo json_encode($jsonEncode);
	}

	public function grabAlbumPhotos($aid){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("SELECT photo_path FROM photo WHERE a_id = :aid;");
		$stmt->bindParam("aid",$aid);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not post comment.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$jsonEncode['data'][] = $d;
			}
		}
		echo json_encode($jsonEncode);
	}

	public function selectAlbumText(){
		$jsonEncode['status'] = "success";
		$stmt = $this->db->prepare("SELECT * FROM album WHERE u_id = :uid;");
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not post comment.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$jsonEncode['data'][] = $d;
			}
		}
		echo json_encode($jsonEncode);
	}

	public function removeAlbumItem($p_id){
		$stmt = $this->db->prepare("UPDATE photo SET a_id = 0 WHERE photo_path = :p_path;");
		$stmt->bindParam("p_path",$p_id);
		$stmt->execute();
	}

	public function addAlbumItem($a_id,$p_id){
		$stmt = $this->db->prepare("UPDATE photo SET a_id = :a_id WHERE photo_path = :p_path;");
		$stmt->bindParam("a_id",$a_id);
		$stmt->bindParam("p_path",$p_id);
		$stmt->execute();
	}

	public function grabNonAlbumPhotos($u_id){
		$jsonArray = array("status"=>"success");

		$select = "SELECT photo_path FROM photo WHERE u_id = :u_id AND remove = 0 AND a_id = 0;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("u_id",$u_id);
		$outcome = $stmt->execute();

		if($outcome){
			$results = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($results as $pos=>$val){
				$jsonArray["data"][] = $val['photo_path'];
			}
		}else{
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "There was an error retrieving the images from this user.";
		}

		echo json_encode($jsonArray);
	}

	public function removePosting($p_id){
		$stmt = $this->db->prepare("UPDATE post SET remove = 1 WHERE id = :p_id AND u_id = :u_id;");
		$stmt->bindParam("p_id",$p_id);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->execute();
	}

	public function removeAlbum($aid){
		$stmt = $this->db->prepare("UPDATE photo SET a_id = 0 WHERE a_id = :a_id AND u_id = :uid;");
		$stmt->bindParam("a_id",$aid);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->execute();

		$stmt = $this->db->prepare("DELETE FROM album WHERE id = :a_id AND u_id = :u_id;");
		$stmt->bindParam("a_id",$aid);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->execute();
	}

	public function grabGenres(){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT * FROM genre;");
		$stmt->execute();
		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
		foreach($data as $d){
			$jsonArray['data'][] = $d;
		}

		echo json_encode($jsonArray);
	}

	public function grabSports(){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT * FROM sport;");
		$stmt->execute();
		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
		foreach($data as $d){
			$jsonArray['data'][] = $d;
		}

		echo json_encode($jsonArray);
	}

	public function addClient($post){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("INSERT INTO client (name, photo_url, description, u_id, crea_date) VALUES (:name, :photo_url, :description, :u_id, :crea_date);");
		$stmt->bindParam("name",$post['name']);
		$stmt->bindParam("photo_url",$post['photo_url']);
		$stmt->bindParam("description",$post['description']);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$d = strtotime("now");
		$stmt->bindParam("crea_date",$d);
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Client could not be added, there was a database issue.";
		}
		echo json_encode($jsonArray);
	}

	public function grabClients($uid){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT * FROM client WHERE u_id = :uid ORDER BY name DESC;");
		$stmt->bindParam("uid",$uid);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Client could not be added, there was a database issue.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$jsonArray['data'][] = $d;
			}
		}
		echo json_encode($jsonArray);
	}

	public function addAchievement($post){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("INSERT INTO achievement (text, date, u_id) VALUES (:text, :date, :u_id);");
		$stmt->bindParam("text",$post['text']);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Achievement could not be added, there was a database issue.";
		}
		echo json_encode($jsonArray);
	}

	public function grabAchievements($u_id){
		$jsonArray = array("status"=>"error");
		$stmt = $this->db->prepare("SELECT * FROM achievement WHERE u_id = :uid AND remove = 0;");
		$stmt->bindParam("uid",$u_id);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Achievement could not be grabbed, problem with database.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$jsonArray['data'][] = $d;
			}
		}
		echo json_encode($jsonArray);
	}

	public function deleteComment($rid){
		$stmt = $this->db->prepare("DELETE FROM comment WHERE id = :rid AND u_id = :uid;");
		$stmt->bindParam("rid",$rid);
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->execute();
	}

	public function deleteAch($a_id){
		$stmt = $this->db->prepare("UPDATE achievement SET remove = 1 WHERE u_id = :uid AND id = :id;");
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->bindParam("id",$a_id);
		$stmt->execute();
	}

	public function deleteGoal($a_id){
		$stmt = $this->db->prepare("UPDATE goal SET remove = 1 WHERE u_id = :uid AND id = :id;");
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->bindParam("id",$a_id);
		$stmt->execute();
	}

	public function addGoal($post){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("INSERT INTO goal (text, date, u_id) VALUES (:text, :date, :u_id);");
		$stmt->bindParam("text",$post['text']);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Goal could not be added, there was a database issue.";
		}
		echo json_encode($jsonArray);
	}

	public function grabGoals($u_id){
		$jsonArray = array("status"=>"error");
		$stmt = $this->db->prepare("SELECT * FROM goal WHERE u_id = :uid AND remove = 0;");
		$stmt->bindParam("uid",$u_id);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Goal could not be grabbed, problem with database.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$jsonArray['data'][] = $d;
			}
		}
		echo json_encode($jsonArray);
	}

	public function deleteCoach($a_id){
		$stmt = $this->db->prepare("UPDATE coach SET remove = 1 WHERE u_id = :uid AND id = :id;");
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->bindParam("id",$a_id);
		$stmt->execute();
	}

	public function addCoach($post){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("INSERT INTO coach (text, date, u_id) VALUES (:text, :date, :u_id);");
		$stmt->bindParam("text",$post['text']);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();
		$u = $stmt->errorInfo();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Coach could not be added, there was a database issue.".$u[0]." ".$u[1]." ".$u[2];
		}
		echo json_encode($jsonArray);
	}

	public function grabCoach($u_id){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT * FROM coach WHERE u_id = :uid AND remove = 0;");
		$stmt->bindParam("uid",$u_id);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Goal could not be grabbed, problem with database.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$jsonArray['data'][] = $d;
			}
		}
		echo json_encode($jsonArray);
	}

	public function grabEvents($cid){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT * FROM event WHERE c_id = :cid AND date_disp > :ts;");
		$stmt->bindParam("cid",$cid);
		$ts = strtotime("now");
		$stmt->bindParam("ts",$ts);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "The events could not be grabbed.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$d['day_text'] = strtoupper(date("D",$d['date_disp'])); //day nice
				$d['month_day'] = date("n/t",$d['date_disp']);
				$d['time'] = date("g:i",$d['date_disp']); //hour min
				$d['ampm'] = date("A",$d['date_disp']); //ampm
				$jsonArray['data'][] = $d;
			}
		}
		echo json_encode($jsonArray);
	}

	public function editClientPic($post){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("UPDATE client SET photo_url = :photo_url WHERE u_id = :uid AND id = :c_id;");
		$stmt->bindParam("photo_url",$post['photo_url']);
		$stmt->bindParam("c_id",$post['c_id']);
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Editing of the client pic could not happen.";
		}
		echo json_encode($jsonArray);
	}

	public function editClientName($post){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("UPDATE client SET name = :name WHERE u_id = :uid AND id = :c_id;");
		$stmt->bindParam("name",$post['name']);
		$stmt->bindParam("c_id",$post['c_id']);
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Editing of the client name could not happen.";
		}
		echo json_encode($jsonArray);
	}

	public function editClientDesc($post){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("UPDATE client SET description = :description WHERE u_id = :uid AND id = :c_id;");
		$stmt->bindParam("description",$post['description']);
		$stmt->bindParam("c_id",$post['c_id']);
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Editing of the client description could not happen.";
		}
		echo json_encode($jsonArray);
	}

	public function addEvent($post){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("INSERT INTO event (text, date, date_disp, c_id) VALUES (:text, :datep, :date_disp, :c_id);");
		$stmt->bindParam("text",$post['text']);
		$d = strtotime("now");
		$stmt->bindParam("datep",$d);
		$f = strtotime($post['date']." ".$post['hour'].":".$post['min']." ".$post['ampm']);
		$stmt->bindParam("date_disp",$f);
		$stmt->bindParam("c_id",$post['c_id']);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "We could not add this event to your list.";
		}
		echo json_encode($jsonArray);
	}

	function deleteEvent($c_id, $e_id){ //client id, event id
		$stmt = $this->db->prepare("DELETE FROM event WHERE id = :e_id AND c_id  = :c_id;");
		$stmt->bindParam("e_id",$e_id);
		$stmt->bindParam("c_id",$c_id);
		$stmt->execute();
	}

	function addSponsor($post){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("INSERT INTO sponsor (name, w_address, p_url, c_id, date, u_id) VALUES (:name, :w_address, :p_url, :c_id, :date, :u_id);");
		$stmt->bindParam("name",$post['name']);
		$stmt->bindParam("w_address",$post['w_address']);
		$stmt->bindParam("p_url",$post['p_url']);
		$stmt->bindParam("c_id",$post['c_id']);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();
		$e = $stmt->errorInfo();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "We could not add sponsor to your profile.".$e[0]." ".$e[1]." ".$e[2];
		}
		echo json_encode($jsonArray);
	}

	function grabSponsors($uid){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT * FROM client WHERE u_id = :uid;");
		$stmt->bindParam("uid",$uid);
		$res = $stmt->execute();

		if($res){
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$sTemp = array();
				$sTemp['info']['name'] = $d['name'];
				$sTemp['info']['id'] = $d['id'];
				$sTemp['info']['photo_url'] = $d['photo_url'];

				$stmt2 = $this->db->prepare("SELECT * FROM sponsor WHERE c_id = :c_id;");
				$stmt2->bindParam("c_id",$d['id']);
				$res = $stmt2->execute();

				if(!$res){
					$jsonArray['status'] = "error";
					$jsonArray['status_msg'] = "We could could not get your sponsors.";
				}else{
					$data2 = $stmt2->fetchAll(PDO::FETCH_ASSOC);
					foreach($data2 as $l){
						$sTemp['sponsors'][] = $l;
					}
					$jsonArray['data'][] = $sTemp;
				}
			}
		}
		echo json_encode($jsonArray);
	}

	public function deleteSponsor($sid){
		$stmt = $this->db->prepare("DELETE FROM sponsor WHERE id = :sid;");
		$stmt->bindParam("sid",$sid);
		$stmt->execute();
	}

	public function clap($post){
		$jsonArray2 = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT COUNT(id) FROM clap WHERE u_id = :uid AND r_id = :rid;");
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->bindParam("rid",$post['r_id']);
		$stmt->execute();
		$a = $stmt->fetch(PDO::FETCH_ASSOC);
		if($a['COUNT(id)'] <= 0){
			$stmt = $this->db->prepare("INSERT INTO clap (r_id, u_id, date, type) VALUES (:r_id, :u_id, :date, :type);");
			$stmt->bindParam("r_id",$post['r_id']);
			$stmt->bindParam("u_id",$_SESSION['user_id']);
			$d = strtotime("now");
			$stmt->bindParam("date",$d);
			$stmt->bindParam("type",$post['type']);
			$res = $stmt->execute();

			if(!$res){
				$jsonArray2['status'] = "error";
				$jsonArray2['status_msg'] = "We were unable to clap this for you.";
			}
		}else{
			$jsonArray2['status'] = "error";
			$jsonArray2['status_msg'] = "You already clapped this post.";
		}

		$stmt2 = $this->db->prepare("SELECT * FROM post WHERE id = :r_id LIMIT 1;");
		$stmt2->bindParam("r_id",$post['r_id']);
		$res = $stmt2->execute();

		$postData = $stmt2->fetch(PDO::FETCH_ASSOC);

		//add notification here
		$thumbnailPic = $postData['text_add'];

		if($postData['type'] == 1)
			$thumbnailPic = "http://54.243.129.126/usr_content/pics/".$postData['text_add']."_t.jpg";
		else if($postData['type'] == 2)
			$thumbnailPic = "http://i.ytimg.com/vi/".$postData['text_add']."/2.jpg";
		else
			$thumbnailPic = "";

		$params = array(
			'snapshotmult' 	=> $thumbnailPic,  //get this from the post db
			'actiontype' 	=> 1, //0 is commented
			'type'			=> ($postData['post_type'] == 0 ? 1 : 0), //0 is thoughtstream
			'subjecttype'	=> $postData['type'],  //get this from the post db, this is grabbed from above
			'useractionid'	=> $postData['u_id'],   //get this from the post db
			'postid'		=> $post['r_id']
		);
		ob_start();
		$this->makeNotification($params);
		ob_end_clean();

		echo json_encode($jsonArray2);
	}

	public function grabClaps($rid){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT COUNT(*) FROM clap WHERE r_id = :rid;");
		$stmt->bindParam("rid",$rid);
		$res = $stmt->execute();
		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "We could not retrieve the claps.";
		}else{
			$data = $stmt->fetch(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$jsonArray['data'][] = $d;
			}
		}
		echo json_encode($jsonArray);
	}

	public function grabThoughtstream($pid){
		$jsonEncode = array("status"=>"success");

		//SET THIS AMOUNT TO THE AMOUNT OF ITEMS YOU WANT LOADED.
		$loadAmount = 20;

		$pid *= $loadAmount; //grab at least 20 postings, request the amount from where to grab them
		$stmt = $this->db->prepare("SELECT * FROM post WHERE remove = 0 AND post_type = 1 ORDER BY date DESC LIMIT :pid, ".$loadAmount.";"); //AFTER DESC:
		$stmt->bindParam("pid",$pid,PDO::PARAM_INT);
		$res = $stmt->execute();
		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

		$stmt2 = $this->db->prepare("SELECT COUNT(id) FROM post WHERE remove = 0 AND post_type = 1;");
		$stmt2->execute();
		$data2 = $stmt2->fetch(PDO::FETCH_ASSOC);

		$jsonEncode['amt'] = intval(ceil($data2['COUNT(id)']/$loadAmount));

		foreach($data as $id=>$post){
			$post['name'] = $this->userInfo($post['u_id']);
			$post['date'] = relTime($post['date']);
			$jsonEncode['data'][] = $post;
			//echo "<h3 style='color:red;'>".$post['id']."</h3> <h3>".$post['text']."</h3>";
			//echo "<hr />";
		}
		echo json_encode($jsonEncode);
	}

	public function createChatroom($post){
		$jsonEncode = array("status"=>"success");

		/*
				CREATE CHATROOM
		*/
		$stmt = $this->db->prepare("INSERT INTO chatroom (title, u_id, perms, date, photo_url) VALUES (:title, :u_id, :perms, :date, :photo_url);");
		$stmt->bindParam("title",$post['title']);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$perms = ($post['perms'] == "priv" ? 1 : 0);
		$stmt->bindParam("perms",$perms);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$stmt->bindParam("photo_url",$post['photo_url']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "We could not create the chat room.";
		}

		/*
				CREATE CHATROOM MEMBERS
		*/
		$stmt = $this->db->prepare("SELECT id FROM chatroom WHERE date = :d LIMIT 1;");
		$stmt->bindParam("d",$d);
		$stmt->execute();
		$data2 = $stmt->fetch(PDO::FETCH_ASSOC);

		foreach($post['members'] as $mid){
			$stmt = $this->db->prepare("INSERT INTO chatroom_members (c_id, m_id, date, status) VALUES (:c_id, :m_id, :date, :status);");
			$stmt->bindParam("c_id",$data2['id']);
			$stmt->bindParam("m_id",$mid);
			$d = strtotime("now"); //date that member was invited to join, not date that they joined.
			$stmt->bindParam("date",$d);
			$zero = 0; // 0 pending | 1 confirm | 2 denied
			$stmt->bindParam("status",$zero);
			$res = $stmt->execute();
		}

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "We could not create the chat room.";
		}

		echo json_encode($jsonEncode);
	}

	function getChatrooms($id){
		$jsonArray = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT * FROM chatroom WHERE u_id = :id;");
		$stmt->bindParam("id",$id);
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "We could not grab the requested chatrooms.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			foreach($data as $d){
				$stmt = $this->db->prepare("SELECT COUNT(id) AS members FROM chatroom_members WHERE c_id = :cid;");
				$stmt->bindParam("cid",$d['id']);
				$stmt->execute();

				$data2 = $stmt->fetch(PDO::FETCH_ASSOC);
				$d['members'] = $data2['members'];

				$jsonArray['data'][] = $d;
			}
		}

		echo json_encode($jsonArray);
	}

	function getChatroom($cid){
		$jsonArray = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT * FROM chatroom WHERE id = :cid LIMIT 1;");
		$stmt->bindParam("cid",$cid);
		$res = $stmt->execute();
		$data = $stmt->fetch(PDO::FETCH_ASSOC);

		$data['date'] = date("M j, Y \a\\t g:ia",$data['date']);

		$jsonArray['data']['info'] = $data;

		$stmt = $this->db->prepare("SELECT * FROM chatroom_members WHERE c_id = :cid;");
		$stmt->bindParam("cid",$data['id']);
		$res = $stmt->execute();
		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

		$jsonArray['data']['users'] = array();

		foreach($data as $d){
			if(count($this->userInfo($d['m_id'])) != 0)
				$d['user_info'] = $this->userInfo($d['m_id']);
			else
				$d['user_info'] = array();

			$d['date'] = date("M j, Y \a\\t g:ia",$d['date']);
			$jsonArray['data']['users'][] = $d;

			$stmt = $this->db->prepare("SELECT COUNT(id) AS members FROM chatroom_members WHERE c_id = :cid;");
			$stmt->bindParam("cid",$d['id']);
			$stmt->execute();

			$data2 = $stmt->fetch(PDO::FETCH_ASSOC);
			$data[$num]['members'] = $data2['members'];
		}
		$jsonArray['data']['info']['admin'] = $this->userInfo($jsonArray['data']['info']['u_id']);

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "We could not grab the requested chatroom, and it's information.";
		}else{

		}

		echo json_encode($jsonArray);
	}

	function grabChatroomNotifications(){
		$jsonArray = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT * FROM chatroom_members WHERE m_id = :mid AND status = 0;");
		//$id = 28;
		$stmt->bindParam("mid",$_SESSION['user_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "Your notifications are unable to be presented.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

			foreach($data as $pos=>$d){
				$stmt = $this->db->prepare("SELECT * FROM chatroom WHERE id = :cid;");
				$stmt->bindParam("cid",$d['c_id']);
				$stmt->execute();

				$data2 = $stmt->fetchAll(PDO::FETCH_ASSOC);
				$d['info'] = $data2;
				$data[$pos] = $d;
			}
			$jsonArray['data'] = $data;
		}

		echo json_encode($jsonArray);
	}

	function decideChatroom($cid, $uid, $type){
		$stmt = $this->db->prepare("UPDATE chatroom_members SET status = :type, date = :d WHERE c_id = :cid AND m_id = :uid;");
		$stmt->bindParam("type",$type);
		$d = strtotime("now");
		$stmt->bindParam("d",$d);
		$stmt->bindParam("cid",$cid);
		$stmt->bindParam("uid",$uid);
		$stmt->execute();
	}

	function searchChatrooms($query){
		$jsonEncode = array("status"=>"success");

		$queryTemp = strip_tags($query);
		$query = "%".$query."%";

		$stmt = $this->db->prepare("SELECT * FROM chatroom WHERE title LIKE :query;");
		$stmt->bindParam("query",$query);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was a problem searching.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

			foreach($data as $num=>$d){
				$stmt = $this->db->prepare("SELECT COUNT(id) AS members FROM chatroom_members WHERE c_id = :cid;");
				$stmt->bindParam("cid",$d['id']);
				$stmt->execute();

				$data2 = $stmt->fetch(PDO::FETCH_ASSOC);
				$data[$num]['members'] = ((int)$data2['members'])+1;
			}

			$jsonEncode['data'] = $data;
			$jsonEncode['query'] = $queryTemp;
		}

		echo json_encode($jsonEncode);
	}

	function getAllChatrooms($uid){
		$jsonArray = array("status"=>"success");
		//Get the ids of the chatrooms that are associated with the user
		$stmt = $this->db->prepare("SELECT c_id FROM chatroom_members WHERE m_id = :uid AND status = 1;");
		$stmt->bindParam("uid",$uid);
		$stmt->execute();
		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

		$stmt = $this->db->prepare("SELECT id FROM chatroom WHERE u_id = :uid;");
		$stmt->bindParam("uid",$uid);
		$stmt->execute();
		$data5 = $stmt->fetchAll(PDO::FETCH_ASSOC);

		foreach($data5 as $d5){
			$data[] = array('c_id'=>$d5['id']);
			//print_r($d5);
		}

		//print_r($data);

		foreach($data as $pos=>$d){
			//grab the actual chatrooms given the id
			$stmt = $this->db->prepare("SELECT * FROM chatroom WHERE id = :cid;");
			$stmt->bindParam("cid",$d['c_id']);
			$stmt->execute();
			$data2 = $stmt->fetch(PDO::FETCH_ASSOC);

			foreach($data2 as $pin=>$p){
				$chatroomId = $data2['id'];

				$stmt = $this->db->prepare("SELECT COUNT(id) FROM chatroom_members WHERE c_id = :cid;");
				$stmt->bindParam("cid",$chatroomId);
				$stmt->execute();
				$data3 = $stmt->fetch(PDO::FETCH_ASSOC);

				$data2['num_users'] = ((int)$data3['COUNT(id)'])+1;

				if(count($this->userInfo($data2['u_id'])) != 0)
					$data2['user_info'] = $this->userInfo($data2['u_id']);
				else
					$data2['user_info'] = array();
				$data2[$pin] = $p;
			}
			$data[$pos] = $data2;
		}

		$jsonArray['data'] = $data;

		echo json_encode($jsonArray);
	}

	function chatChatroom($post){
		$jsonArray = array("status"=>"success");

		$stmt = $this->db->prepare("INSERT INTO chatroom_chat (msg, date, u_id, c_id) VALUES (:msg,:date,:u_id,:c_id);");
		$stmt->bindParam("msg",$post['msg']);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->bindParam("c_id",$post['c_id']);
		$res = $stmt->execute();

		$stmt = $this->db->prepare("SELECT id FROM chatroom_chat WHERE date = :date AND c_id = :cid;");
		$stmt->bindParam("date",$d);
		$stmt->bindParam("cid",$post['c_id']);
		$stmt->execute();

		$data = $stmt->fetch(PDO::FETCH_ASSOC);


		$stmt = $this->db->prepare("INSERT INTO chatroom_alerts (c_id, p_id, date_created, reviewed) VALUES (:c_id, :p_id, :date_created, :reviewed);");
		$stmt->bindParam("c_id",$post['c_id']);
		$stmt->bindParam("p_id",$data['id']);
		$d2 = strtotime("now");
		$stmt->bindParam("date_created",$d2);
		$zero = 0;
		$stmt->bindParam("reviewed",$zero);
		$res = $stmt->execute();

		if(!res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "We could not post the desired chat to your chatroom.";
		}

		echo json_encode($jsonArray);
	}

	function grabChatroomChats($c_id){
		$jsonArray = array("status"=>"success");

		//grabs all the chats made in the chatroom
		$stmt = $this->db->prepare("SELECT * FROM chatroom_chat WHERE c_id = :cid;");
		$stmt->bindParam("cid",$c_id);
		$res = $stmt->execute();

		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
		foreach($data as $d){
			$d['user_info'] = $this->userInfo($d['u_id']);
			$d['date'] = relTime($d['date']);
			$jsonArray['data'][] = $d;
		}

		if(!res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "We could not post the desired chat to your chatroom.";
		}

		echo json_encode($jsonArray);
	}

	//returns the amount of chat items, if the number of chats does not match then it updates the chatroom.
	public function checkChatChatroom($c_id){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT COUNT(id) FROM chatroom_chat WHERE c_id = :cid;");
		$stmt->bindParam("cid",$c_id);
		$res = $stmt->execute();

		//Taken directly from grabChats function.
		/*$stmt = $this->db->prepare("SELECT * FROM chat WHERE id = :id;");
		$stmt->bindParam("id",$data['c_id']);
		$res = $stmt->execute();*/

		if(!$res){
			$jsonEncode['status']['status'] = "error";
			$jsonEncode['status']['status_msg'] = "Could not display chats.";
		}else{
			$data = $stmt->fetch(PDO::FETCH_ASSOC);
			$jsonEncode['data'] = $data['COUNT(id)'];
		}
		//end block

		//set reviewed to 1 to indicate that this chat has already been reviewed., might just want to delete this shit, because it's useless

		echo json_encode($jsonEncode);
	}

	public function createPlaylist($post){
		$jsonArray = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT position FROM playlist WHERE u_id = :u_id AND remove = 0 ORDER BY position DESC LIMIT 1;");
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->execute();
		$last_pos = $stmt->fetch(PDO::FETCH_ASSOC);
		$last_pos = strval((intval($last_pos['position']))+1);

		$stmt = $this->db->prepare("INSERT INTO playlist (title, u_id, date, position) VALUES (:title, :u_id, :date, :position);");
		$stmt->bindParam("title",$post['title']);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$stmt->bindParam("position",$last_pos);
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status']['status'] = "error";
			$jsonArray['status']['status_msg'] = "Could not add playlist.";
		}

		echo json_encode($jsonArray);
	}

	public function grabPlaylist($pid){
		$jsonArray = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT * FROM playlist WHERE u_id = :pid AND remove = 0;");
		$stmt->bindParam("pid",$pid);
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status']['status'] = "error";
			$jsonArray['status']['status_msg'] = "Could not display playlists.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

			foreach($data as $d){
				$stmt = $this->db->prepare("SELECT count(id) FROM playlist_collection WHERE p_id = :pid;");
				$stmt->bindParam("pid",$d['id']);
				$stmt->execute();

				$data2 = $stmt->fetch(PDO::FETCH_ASSOC);
				$d['amt'] =  $data2['count(id)'];
				$jsonArray['data'][] = $d;
			}
		}

		echo json_encode($jsonArray);
	}

	public function addSongPlaylist($post){
		$jsonArray = array("status"=>"success");

		$stmt = $this->db->prepare("INSERT INTO playlist_collection (u_id, p_id, date, t_id) VALUES (:u_id,:p_id,:date,:t_id);");
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$stmt->bindParam("p_id",$post['p_id']);
		$d = strtotime("now");
		$stmt->bindParam("date",$d);
		$stmt->bindParam("t_id",$post['t_id']); //t_id = tune id
		$res = $stmt->execute();

		if(!$res){
			$jsonArray['status']['status'] = "error";
			$jsonArray['status']['status_msg'] = "Could not display playlists.";
		}

		echo json_encode($jsonArray);
	}

	public function grabPlaylistSongs($pid){ //playlist id is passed as reference
		$jsonArray = array("status"=>"success");

		if(!$res){
			$jsonArray['status']['status'] = "error";
			$jsonArray['status']['status_msg'] = "Could not display playlists.";
		}

		echo json_encode($jsonArray);
	}

	public function requestAddChatroomMember($post){
		$jsonArray = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT count(id) AS amount FROM chatroom_members WHERE m_id = :mid AND c_id = :cid;");
		$stmt->bindParam("mid",$_SESSION['user_id']);
		$stmt->bindParam("cid",$post['c_id']);
		$stmt->execute();
		$data = $stmt->fetch(PDO::FETCH_ASSOC);

		$stmt2 = $this->db->prepare("SELECT count(id) AS amount2 FROM chatroom WHERE u_id = :uid AND id = :cid;");
		$stmt2->bindParam("uid",$_SESSION['user_id']); //owner's id
		$stmt2->bindParam("cid",$post['c_id']); //list id
		$stmt2->execute();
		$data6 = $stmt2->fetch(PDO::FETCH_ASSOC);

		if( (((int)$data['amount']) <= 0) && (((int)$data6['amount2']) <= 0) ){
			$stmt = $this->db->prepare("INSERT INTO chatroom_members (c_id, m_id, date, status) VALUES (:c_id, :m_id, :date, :status);");
			$stmt->bindParam("c_id",$post['c_id']);
			$stmt->bindParam("m_id",$_SESSION['user_id']);
			$d = strtotime("now");
			$stmt->bindParam("date",$d);
			$four = 1;
			$stmt->bindParam("status",$four);
			$res = $stmt->execute();
		}else{
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "You are already registered to this chatroom!";
		}

		if(!$res){
			$jsonArray['status'] = "error";
			$jsonArray['status_msg'] = "You are already registered to this chatroom!";
		}

		echo json_encode($jsonArray);
	}

	/*
		SELECTS ALL users that are not currently in the Chatroom.
	*/
	public function getChatUsersUnique($cid){
		$jsonArray = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT id FROM user;");
		$stmt->bindParam("cid",$cid); //defines the chatroom to look into.
		$res = $stmt->execute();

		$stmt2 = $this->db->prepare("SELECT m_id FROM chatroom_members WHERE c_id = :cid;");
		$stmt2->bindParam("cid",$cid);
		$stmt2->execute();

		$data2 = $stmt2->fetchAll(PDO::FETCH_NUM);
		$dataF = array();
		foreach($data2 as $d2){
			$dataF[] = $d2[0];
		}

		if(!$res){
			$jsonArray['status']['status'] = "error";
			$jsonArray['status']['status_msg'] = "Could not request membership.";
		}else{
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

			foreach($data as $d){
				if(!in_array($d['id'],$dataF)){
					$jsonArray['data'][] = $this->userInfo($d['id']);
				}
			}
		}

		echo json_encode($jsonArray);
	}

	public function inviteMoreUsers($post){
		$jsonArray = array("status"=>"success");

		foreach($post['members'] as $mid){
			$stmt = $this->db->prepare("INSERT INTO chatroom_members (c_id, m_id, date, status) VALUES (:c_id, :m_id, :date, :status);");
			$stmt->bindParam("c_id",$post['c_id']);
			$stmt->bindParam("m_id",$mid);
			$d = strtotime("now"); //date that member was invited to join, not date that they joined.
			$stmt->bindParam("date",$d);
			$zero = 0; // 0 pending | 1 confirm | 2 denied
			$stmt->bindParam("status",$zero);
			$res = $stmt->execute();

			if(!$res){
				$jsonArray['status']['status'] = "error";
				$jsonArray['status']['status_msg'] = "Could not add more members.";
			}
		}

		echo json_encode($jsonArray);
	}

	public function removePlaylist($pid){
		$stmt = $this->db->prepare("UPDATE playlist SET remove = 1 WHERE id = :id;");
		$stmt->bindParam("id",$pid);
		$stmt->execute();
	}

	public function removeTune($tid){
		$stmt = $this->db->prepare("UPDATE tune SET remove = 1 WHERE id = :tid;");
		$stmt->bindParam("tid",$tid);
		$stmt->execute();
	}

	public function getPlaylistMusic($playlist_id){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT * FROM playlist WHERE id = :pid AND remove = 0;");
		$stmt->bindParam("pid",$playlist_id);
		$stmt->execute();

		$playlist = $stmt->fetch(PDO::FETCH_ASSOC);
		$jsonEncode['data']['title'] = $playlist['title'];

		$stmt = $this->db->prepare("SELECT t_id FROM playlist_collection WHERE p_id = :pid AND remove = 0;");
		$stmt->bindParam("pid",$playlist_id);
		$stmt->execute();

		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

		$songs = array();
		foreach($data as $d){
			$stmt = $this->db->prepare("SELECT * FROM tune WHERE id = :t_id AND remove = 0;");
			$stmt->bindParam("t_id",$d['t_id']);
			$stmt->execute();

			$data2 = $stmt->fetch(PDO::FETCH_ASSOC);

			$songs[] = $data2;
		}
		$jsonEncode['data']['songs'] = $songs;

		echo json_encode($jsonEncode);
	}

	/*
		$id 	Id of the user that needs to be removed from the database.

		Does not return text to indicate that it was successful or unsuccessful.
	*/
	public function removeChatroomUser($id){
		$stmt = $this->db->prepare("DELETE FROM chatroom_members WHERE m_id = :mid AND id = :;");
		$stmt->bindParam("mid",$id);
		$stmt->execute();
	}

	/*
		$type	Notification type.
	*/
	public function grabNotifications($type){
		$jsonEncode = array("status"=>"success");
		$stmt = $this->db->prepare("SELECT * FROM notification WHERE type = :type AND user_action_id = :uid AND reviewed = 0 ORDER BY crea_date DESC;");
		switch($type){
			case "thoughtstream":
				$zero = 0;
				$stmt->bindParam("type", $zero);
				break;
			case "myzone":
				$one = 1;
				$stmt->bindParam("type", $one);
				break;
		}
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->execute();

		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
		//assemble the individual elements here.
		foreach($data as $num=>$d){
			$userInfoSm = $this->userInfo($d['u_id']);
			switch($d['action_type']){
				case 0:
					$action = "commented on";
					break;
				case 1:
					$action = "clapped";
					break;
				case 2:
					$action = "supports";
					break;
			}

			switch($d['subject_type']){
				case 0:
					$subject = "post";
					break;
				case 1:
					$subject = "photo";
					break;
				case 2:
					$subject = "video";
					break;
				case 3:
					$subject = "link";
					break;
				case 4:
					$subject = "profile";
					break;
			}

			$data[$num]['snapshot'] = "<b style='color:black;' postid='".$d['post_id']."'>".$userInfoSm['fname']."</b> ".$action." your ".$subject.".<br /><i style='color:#333; font-size:12px;'>".relTime($d['crea_date'])." ago</i>";
		}
		$jsonEncode['data'] = $data;

		echo json_encode($jsonEncode);
	}

	public function grabPastNotifications($type){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT * FROM notification WHERE type = :type AND user_action_id = :u_id AND reviewed = 1 AND crea_date > :dateby ORDER BY crea_date DESC;");
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		switch($type){
			case "thoughtstream":
				$zero = 0;
				$stmt->bindParam("type", $zero);
				break;
			case "myzone":
				$one = 1;
				$stmt->bindParam("type", $one);
				break;
		}
		$d = strtotime("-1 week");
		$stmt->bindParam("dateby",$d);
		$res = $stmt->execute();

		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
		//assemble the individual elements here.
		foreach($data as $num=>$d){
			$userInfoSm = $this->userInfo($d['u_id']);
			switch($d['action_type']){
				case 0:
					$action = "commented on";
					break;
				case 1:
					$action = "clapped";
					break;
				case 2:
					$action = "supports";
					break;
			}

			switch($d['subject_type']){
				case 0:
					$subject = "post";
					break;
				case 1:
					$subject = "photo";
					break;
				case 2:
					$subject = "video";
					break;
				case 3:
					$subject = "link";
					break;
				case 4:
					$subject = "profile";
					break;
			}

			$data[$num]['snapshot'] = "<b style='color:black;' postid='".$d['post_id']."'>".$userInfoSm['fname']."</b> ".$action." your ".$subject.".<br /><i style='color:#333; font-size:12px;'>".relTime($d['crea_date'])." ago</i>";
			//$data[$num]['crea_date'] = relTime($d['crea_date'])." ago";
		}
		$jsonEncode['data'] = $data;

		echo json_encode($jsonEncode);
	}

	public function makeNotification($post){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("INSERT INTO notification (u_id, snapshot, snapshot_mult, crea_date, reviewed, type, action_type, subject_type, user_action_id, post_id) VALUES (:uid, :snapshot, :snapshotmult, :creadate, :reviewed, :type, :actiontype, :subjecttype, :useractionid, :postid);");

		$nthing = "";
		$d = strtotime("now");
		$rev = 0;

		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->bindParam("snapshot",$nthing);
		$stmt->bindParam("snapshotmult",$post['snapshotmult']);
		$stmt->bindParam("creadate",$d);
		$stmt->bindParam("reviewed",$rev);
		$stmt->bindParam("type",$post['type']);
		$stmt->bindParam("actiontype",$post['actiontype']);
		$stmt->bindParam("subjecttype",$post['subjecttype']);
		$stmt->bindParam("useractionid",$post['useractionid']);
		$stmt->bindParam("postid",$post['postid']);

		$res = $stmt->execute();

		if(!$res){
			$er = $stmt->errorInfo();
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was a problem creating the notification.".$er[0]." ".$er[1]." ".$er[2];
		}

		echo json_encode($jsonEncode);
	}

	public function markReadNotification($id){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("UPDATE notification SET reviewed = 1 WHERE id = :id;");
		$stmt->bindParam("id",$id);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was a problem updating the notifications.";
		}

		echo json_encode($jsonEncode);
	}

	public function pendingNotifications(){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT COUNT(id) FROM notification WHERE reviewed = 0 AND user_action_id = :u_id;");
		$stmt->bindParam("u_id",$_SESSION['user_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was a problem checking pending notifications.";
		}else{
			$data = $stmt->fetch(PDO::FETCH_ASSOC);

			$jsonEncode['data'] = $data['COUNT(id)'];
		}

		echo json_encode($jsonEncode);
	}

	public function changeTunePosition($post){
		$tune_list = $post['tune_list'];

		$jsonEncode = array("status"=>"success");

		//loop through all
		$pos = 1;
		foreach($tune_list as $l){
			$stmt = $this->db->prepare("UPDATE tune SET position = :pos WHERE id = :id AND remove = 0;");
			$stmt->bindParam("pos",$pos);
			$stmt->bindParam("id",$l);
			$res = $stmt->execute();
			if(!$res){
				$jsonEncode['status'] = "error";
				$jsonEncode['status_msg'] = "Could not change tunes' position.";
			}
			$pos++;
		}

		echo json_encode($jsonEncode);
	}

	public function changePlaylistPosition($post){
		$playlist_list = $post['playlist_list'];

		$jsonEncode = array("status"=>"success");

		//loop through all playlists
		$pos = 1;
		foreach($playlist_list as $l){
			$stmt = $this->db->prepare("UPDATE playlist SET position = :pos WHERE id = :id AND remove = 0;");
			$stmt->bindParam("pos",$pos);
			$stmt->bindParam("id",$l);
			$res = $stmt->execute();
			if(!$res){
				$jsonEncode['status'] = "error";
				$jsonEncode['status_msg'] = "Could not change playlist position.";
			}
			$pos++;
		}

		//doesn't return much, but just the status of whether it worked or not.
		echo json_encode($jsonEncode);
	}

	public function switchPage($pid, $_GET=array()){
		switch($pid){ //There are some other things that need to be considered when doing these items.
			case "notifications":
				include("templates/notifications.inc");
				break;
			case "profile":
				include("templates/profile.inc");
				break;
			case "thoughtstream":
				include("templates/thoughtstream.inc");
				break;
		}
	}

	public function searchMusic($searchTerm, $limit = 5){
		$searchTerm = urlencode($searchTerm);
		$json = file_get_contents("http://tinysong.com/s/".$searchTerm."?format=json&limit=".$limit."&key=e645c4270980103b19215d1bf7439438");

		echo $json;
	}

	public function getChatAlerts(){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT COUNT(id) AS num_alerts FROM chat_alerts WHERE u2 = :log_id AND reviewed = 0;");
		$stmt->bindParam("log_id",$_SESSION['user_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was a problem with grabbing the alerts.";
		}else{
			$data = $stmt->fetch(PDO::FETCH_ASSOC);
			$jsonEncode['data'] = $data;
		}

		echo json_encode($jsonEncode);
	}

	public function removeFromChatroom($c_id){ //chatroom id
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("DELETE FROM chatroom_members WHERE m_id = :mid AND c_id = :cid;");
		$stmt->bindParam("mid",$_SESSION['user_id']);
		$stmt->bindParam("cid",$c_id);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was a problem removing yourself from the chatroom member area.";
		}

		echo json_encode($jsonEncode);
	}

	public function grabPosting($p_id){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT * FROM post WHERE id = :p_id;");
		$stmt->bindParam("p_id",$p_id);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "Could not find the posting, with that posting key.";
		}else{
			//display the posts now
			$data = $stmt->fetch(PDO::FETCH_ASSOC); //info about the post is here

			$stmt = $this->db->prepare("SELECT * FROM comment WHERE r_id  = :p_id;");
			$stmt->bindParam("p_id",$p_id);
			$stmt->execute();

			$data2 = $stmt->fetch(PDO::FETCH_ASSOC); //info about the comments that this post has

			$stmt = $this->db->prepare("SELECT COUNT(*) FROM clap WHERE r_id = :r_id;");
			$stmt->bindParam("r_id",$data['id']);
			$stmt->execute();

			$data3 = $stmt->fetch(PDO::FETCH_ASSOC); //info about the amount of claps that this post has.

			//put all the data together now into a neat JSON.
			$jsonEncode['data']['post'] = $data;
			$jsonEncode['data']['post']['user'] = $this->userInfo($data['u_id']);
			$jsonEncode['data']['post']['date'] = relTime($data['date']);
			$jsonEncode['data']['comments'] = $data2;
			$jsonEncode['data']['claps'] = $data3;
		}

		echo json_encode($jsonEncode);
	}

	public function recs(){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->query("select * from user order by last_on desc;");
		$data = $stmt->fetchAll(PDO::FETCH_ASSOC);

		//shuffle($data); //randomize the numbers

		$stmt = $this->db->prepare("select u2 from fans where u1 = :u1p;");
		$stmt->bindParam("u1p",$_SESSION['user_id']);
		$stmt->execute();

		$data2 = $stmt->fetchAll(PDO::FETCH_ASSOC);
		$haystack = array();
		foreach($data2 as $d2){
			$haystack[] = $d2['u2'];
		}

		for($i = 0; $i < count($data); $i++){
			if($data[$i]['id'] != $_SESSION['user_id']){
				$user = $this->userInfo($data[$i]['id']);
				if(!in_array($user['id'],$haystack))
					$jsonEncode['data'][] = $this->userInfo($data[$i]['id']);
			}
		}

		//print_r($haystack);
		echo json_encode($jsonEncode);
	}

	public function profileSong($songPOST){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("UPDATE user SET profile_music = :p_sid WHERE id = :uid;");
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->bindParam("p_sid",$songPOST['song_id']);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was an issue setting up a new profile song for your account.";
		} //else everything came through properly without error

		echo json_encode($jsonEncode);
	}

	public function getProfileSong(){
		$jsonEncode = array("status"=>"success");

		$select = "SELECT profile_music FROM user WHERE id = :uid;";
		$stmt = $this->db->prepare($select);
		$stmt->bindParam("uid",$_SESSION['user_id']);
		$stmt->execute();

		$data = $stmt->fetch(PDO::FETCH_ASSOC);

		if($stmt){
			$select = "SELECT * FROM tune WHERE id = :i;";
			$stmt = $this->db->prepare($select);
			$stmt->bindParam("i",$data['profile_music']);
			$stmt->execute();

			$data2 = $stmt->fetchAll(PDO::FETCH_ASSOC);

			$jsonEncode['data'] = $data2;
		}else{
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was an error trying to retrieve the profile song.";
		}

		echo json_encode($jsonEncode);
	}

	public function getSongsAll($s_id){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT y_id, name, album, artist FROM tune WHERE id = :sid LIMIT 1;");
		$stmt->bindParam("sid",$s_id);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was a problem getting information corresponding to that song.";
		}else{	//format the data for acceptance
			$data = $stmt->fetch(PDO::FETCH_ASSOC);
			$jsonEncode['data'] = $data;
		}

		echo json_encode($jsonEncode);
	}

	public function grabPreferences(){
		$jsonEncode = array("status"=>"success");

		$stmt = $this->db->prepare("SELECT * FROM preferences WHERE u_id = :u_id;");
		$stmt->bindParam("u_id",$_SESSION["user_id"]);
		$res = $stmt->execute();

		if(!$res){
			$jsonEncode['status'] = "error";
			$jsonEncode['status_msg'] = "There was a problem retrieving your preferences information.";
		}else{ //grab the info
			$data = $stmt->fetchAll(PDO::FETCH_ASSOC);
			$data_temp = array();

			foreach($data as $d){
				if($d['type'] == 0){ //sport item
					$stmt2 = $this->db->prepare("SELECT * FROM sport WHERE id = :id;");
					$stmt2->bindParam("id",$d['preference']);
					$res = $stmt2->execute();
					$data2 = $stmt2->fetch(PDO::FETCH_ASSOC);

					$data_temp[] = array("id"=>$data2['id'],"type"=>"0","item"=>$data2['sport']);
				}else{				 //music item
					$stmt2 = $this->db->prepare("SELECT * FROM genre WHERE id = :id;");
					$stmt2->bindParam("id",$d['preference']);
					$res = $stmt2->execute();
					$data2 = $stmt2->fetch(PDO::FETCH_ASSOC);

					$data_temp[] = array("id"=>$data2['id'],"type"=>"1","item"=>$data2['genre']);
				}
			}

			$jsonEncode['data'] = $data_temp;
		}

		echo json_encode($jsonEncode);
	}
}





///////////////////////////////////////////////////
//												  ////
//	////////  ///////  //       //  //////////        ////
//	//        //   //  //       //      //                ////
//	///////   //////   //       //      //                    ////
//		 //   //       //       //      //                ////
//	///////   //       ///////  //      //            ////
//												  ////
///////////////////////////////////////////////////









// Declare the class
class GoogleUrlApi {

  // Constructor
  function GoogleURLAPI($key,$apiURL = 'https://www.googleapis.com/urlshortener/v1/url') {
    // Keep the API Url
    $this->apiURL = $apiURL.'?key='.$key;
  }

  // Shorten a URL
  function shorten($url) {
    // Send information along
    $response = $this->send($url);
    // Return the result
    return isset($response['id']) ? $response['id'] : false;
  }

  // Expand a URL
  function expand($url) {
    // Send information along
    $response = $this->send($url,false);
    // Return the result
    return isset($response['longUrl']) ? $response['longUrl'] : false;
  }

  // Send information to Google
  function send($url,$shorten = true) {
    // Create cURL
    $ch = curl_init();
    // If we're shortening a URL...
    if($shorten) {
      curl_setopt($ch,CURLOPT_URL,$this->apiURL);
      curl_setopt($ch,CURLOPT_POST,1);
      curl_setopt($ch,CURLOPT_POSTFIELDS,json_encode(array("longUrl"=>$url)));
      curl_setopt($ch,CURLOPT_HTTPHEADER,array("Content-Type: application/json"));
    }
    else {
      curl_setopt($ch,CURLOPT_URL,$this->apiURL.'&shortUrl='.$url);
    }
    curl_setopt($ch,CURLOPT_RETURNTRANSFER,1);
    // Execute the post
    $result = curl_exec($ch);
    // Close the connection
    curl_close($ch);
    // Return the result
    return json_decode($result,true);
  }
}
?>
