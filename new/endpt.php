<?php
require "src/Spuzik/Users/Session.php";
require "src/Spuzik/Users/User.php";
require "src/Spuzik/Users/Lineup.php";
require "src/Spuzik/Users/AboutMe.php";
require "src/Spuzik/Users/FavQuote.php";
require "src/Spuzik/Users/MemZone.php";
require "src/Spuzik/Users/Links.php";
require "src/Spuzik/Users/Image.php";
require "src/Spuzik/Users/UploadHandler.php"; //Doesn't have any affiliations with Spuzik\User\* ...

require "packages/Slim/Slim.php";

\Slim\Slim::registerAutoloader();

$app = new \Slim\Slim();

$app->post('/login', 'logIn'); 					// Logs user in.
$app->get('/login', 'getInfo');					// Gets info about user.
$app->get('/logout', 'logOut');					// Logs user out.

$app->get('/user', 'user');						// Gets info about logged in user.
$app->get('/user/:id', 'user');					// Gets info about user with defined id.

$app->get('/lineup/:id', 'lineupGet');			// Gets lineup information with passed id.
$app->put('/lineup/:id','lineupAdd');			// Adds an item to the lineup. Id means nothing
$app->delete('/lineup/:id', 'lineupRemove');	// Remove an item from the lineup.

$app->get('/aboutme/:id', 'getAboutMe');		// Get the about me information according to id.
$app->put('/aboutme/:id', 'editAboutMe');		// Updates the about me information. Id means nothing

$app->get('/fq/:id', 'getFavQuote');			// Gets a favorite quote object
$app->put('/fq/:id', 'createFavQuote');			// Create a favorite quote object, id means nothing
$app->delete('/fq/:id', 'removeFavQuote');		// Removes the favorite quote object
$app->get('/fqc/:id', 'getFavQuoteCol');		// Gets a favorite quote collection object

$app->get('/mz/:id', 'getMemZone');				// Gets a memory zone object
$app->put('/mz/:id', 'createMemZone');			// Create a memory zone object, id means nothing
$app->delete('/mz/:id', 'removeMemZone');		// Removes the memory zone object
$app->get('/mzc/:id', 'getMemZoneCol');			// Gets a memory zone collection object

$app->get('/link/:id', 'getLink');				// Gets a memory zone object
$app->put('/link/:id', 'createLink');			// Create a memory zone object, id means nothing
$app->delete('/link/:id', 'removeLink');		// Removes the memory zone object
$app->get('/links/:id', 'getLinks');			// Gets a memory zone collection object

$app->post('/imageUpload', 'uploadImage');		// Upload an image.

//zone for media tab
$app->get('/media/:id', 'getMedia');			// Returns all the media objects
$app->put('/media/:id', 'updateDescription');	// Updates or adds a description to the image.
$app->delete('/media/:id', 'deleteMedia');		// Deletes an image from the media tab.
$app->get('/mediac/:id', 'getMediaCollection'); // Get a media zone collection object

//TESTERS
//$app->get('/lineupremove', 'lineupRemove');	//Remove an item from the lineup.
//$app->get('/lineupadd', 'lineupAdd');

$app->run();

/*
	TODO: Get it working so that facebook login is supported as well.
*/
function logIn(){
	$request = \Slim\Slim::getInstance()->request();
	$data = json_decode($request->getBody());

	$user = new \Spuzik\Users\User();

	if($user->checkCredentials($data->username, $data->password)){
		$session = new \Spuzik\Users\Session();

		$session->registerSession($user->fetchWithEmail($data->username),\Spuzik\Users\Session::SPUZIK);

		//echo json_encode($jsonEncode);
	}else{	//Auth was incorrect. Supplied parameters were incorrect.
		$jsonEncode = array("status"=>"error");
		$jsonEncode['message'] = "Could not be authenticated.";

		echo json_encode($jsonEncode);
	}

	$user = null;
	$session = null;
}

/*
	Log the current user out.
*/
function logOut(){
	$session = new \Spuzik\Users\Session();

	$session->logOut();
}

/*
	Returns details of the currently logged in user.
*/
function getInfo(){
	$jsonEncode = array("status"=>"success");

	$user = new \Spuzik\Users\User();
	$session = new \Spuzik\Users\Session();

	if($session->serviceType() == \Spuzik\Users\Session::SPUZIK){ //if the service is Spuzik, then give information about user away.
		$jsonEncode['login_status'] = true;
		$jsonEncode['user'] = $user->fetchWithId($_SESSION['spuzik_uid']);
	}else{
		$jsonEncode['login_status'] = false;
		$jsonEncode['message'] = "Not logged in. You must log in or make an account.";
	}

	echo json_encode($jsonEncode);

	$user = null;
	$session = null;
}

/*
	Gets information about the user, however does not do it very securely.
*/
function user($id = -1){
	session_start();

	$user = new \Spuzik\Users\User();

	if($id == -1){ 		//get logged in user
		$user->fetchWithId($_SESSION['spuzik_uid']);
	}else{		   		//get custom user with custom id
		$user->fetchWithId($id);
	}

	echo json_encode($user->attrs());

	$user = null;
}

/*
	Gets lineup information according to passed user id.
*/
function lineupGet($id){
	$lineup = new \Spuzik\Users\Lineup();
	$lineup->load($id);
	echo $lineup->toJSON();

	$lineup = null;
}

/*
	Adds an item to the lineup.
*/
function lineupAdd(){
	$request = \Slim\Slim::getInstance()->request();
	$data = json_decode($request->getBody());

	$lineup = new \Spuzik\Users\Lineup();
	$lineup->addLineup($data->Text);

	$lineup = null;
}

function lineupRemove($id){
	$request = \Slim\Slim::getInstance()->request();
	$data = json_decode($request->getBody());

	$lineup = new \Spuzik\Users\Lineup();
	$lineup->removeLineup($id);

	$lineup = null;
}

/*
	Gets the users aboue me information.
*/
function getAboutMe($id){
	$aboutMe = new \Spuzik\Users\AboutMe();
	$aboutMe->get($id);
	echo $aboutMe->toJSON();

	$aboutMe = null;
}

/*
	Edits the users about me information.
	Refer to lineupAdd() method
*/
function editAboutMe($id){
	$request = \Slim\Slim::getInstance()->request();
	$data = json_decode($request->getBody());

	$aboutMe = new \Spuzik\Users\AboutMe();

	$arrayUpdate = array(
		"Age"		=> $data->Age,
		"Location"	=> $data->Location,
		"Bio"		=> $data->Bio,
		"Nickname"	=> $data->Nickname
	);

	$aboutMe->update($arrayUpdate);

	$aboutMe = null;
}

/*
	Returns a favorite quote object in JSON notation
*/
function getFavQuote($id){
	$fq = new \Spuzik\Users\FavQuoteItem();
	$fq->get($id);

	echo $fq->toJSON();

	$fq = null;
}

/*
	Returns a favorite quote collection object in JSON notation
	- userid According to the passed userid, the object will be returned.
*/
function getFavQuoteCol($id){ //not in here
	$fq = new \Spuzik\Users\FavQuote();
	$fq->get($id);

	echo $fq->toJSON();

	$fq = null;
}

/*
	Create a fav quote object and throw it into the database.
*/
function createFavQuote($id){
	$request = \Slim\Slim::getInstance()->request();
	$data = json_decode($request->getBody());

	$fq = new \Spuzik\Users\FavQuote();

	$data = array(
		"FQLId"		=> $data->FQLId,
		"Text"		=> $data->Text,
		"Author"	=> $data->Author,
		"UserId"	=> $data->UserId
	);

	/*$data = array(
		"FQLId"		=> "1",
		"Text"		=> "Testing Text",
		"Author"	=> "Test User",
		"UserId"	=> "1"
	);*/

	$fq->add($data);

	$fq = null;
}

/*
	Remove a favorite quote object from the database.
	-id String This is the id of the favorite quote thats being removed
*/
function removeFavQuote($id){
	//Put code to remove the SOB here.
	$fq = new \Spuzik\Users\FavQuote();
	$fq->delete($id);

	$fq = null;
}

/*
	Gets a memzone object according to passed id.
*/
function getMemZone($id){
	$mz = new \Spuzik\Users\MemZoneItem();
	$mz->get($id);

	echo $mz->toJSON();

	$mz = null;
}

/*
	Creates a memzone object with the database, and then returns the object.
*/
function createMemZone($id){
	$request = \Slim\Slim::getInstance()->request();
	$data = json_decode($request->getBody());

	$mem = new \Spuzik\Users\MemZone();

	$data = array(
		"MemId"		=> $data->MemId,
		"Text"		=> $data->Text,
		"Date"		=> $data->Date,
		"UserId"	=> $data->UserId
	);

	/*$data = array(
		"MemId"		=> "1",
		"Text"		=> "Testing Text",
		"Date"		=> "2003",
		"UserId"	=> "1"
	);*/

	$mem->add($data);

	$mem = null;
}

/*
	Removes the memory zone object from the collection, and from the database.
*/
function removeMemZone($id){
	$mem = new \Spuzik\Users\MemZone();
	$mem->delete($id);

	$mem = null;
}

/*
	Gets a JSON collection of memory zone objects.
*/
function getMemZoneCol($id){
	$mem = new \Spuzik\Users\MemZone();
	$mem->get($id);

	echo $mem->toJSON();

	$mem = null;
}

/*
	Get the link object according to passed parameters.
*/
function getLink($id){
	$link = new \Spuzik\Users\LinkItem();
	$link->get($id);

	echo $link->toJSON();

	$link = null;
}

/*
	Create a link, put it in database, and then send the object back
*/
function createLink($id){
	$request = \Slim\Slim::getInstance()->request();
	$data = json_decode($request->getBody());

	$links = new \Spuzik\Users\Links();

	$data = array(
		"LinkId"	=> $data->LinkId,
		"Text"		=> $data->Text,
		"Url"		=> $data->Url,
		"UserId"	=> $data->UserId
	);

	/*$data = array(
		"MemId"		=> "1",
		"Text"		=> "Testing Text",
		"Date"		=> "2003",
		"UserId"	=> "1"
	);*/

	$links->add($data);

	$links = null;
}

/*
	Remove the link with it's id passed as the parameter of this method.
*/
function removeLink($id){
	$links = new \Spuzik\Users\Links();
	$links->delete($id);

	$links = null;
}

/*
	Get an entire listing of links and their objects.
*/
function getLinks($id){
	$links = new \Spuzik\Users\Links();
	$links->get($id);

	echo $links->toJSON();

	$links = null;
}

/*
	Allows you to upload a raw image to the webserver.
*/
function uploadImage(){
	error_reporting(E_ALL | E_STRICT);

	$upload_handler = new UploadHandler();
}

/*
	Deletes a photo item from the database and from Amazon S3.
*/
function deleteMedia($id){

}

/*
	Update a description for a photo in the media area.
*/
function updateDescription(){
	$request = \Slim\Slim::getInstance()->request();
	$data = json_decode($request->getBody());

/*
	ob_start();
	print_r($data);
	$e = ob_get_contents();
	ob_end_flush();

	$f = fopen("desc_u.txt","w");
	fwrite($f, $e);
	fclose($f);
*/

	$session = new Spuzik\Users\Session();
	$userId = $session->currentId();
	if($userId != false){
		$descObj = new Image();

		$arrayUpdate = array(
			"ImageId" 		=> $data->ImageId,
			"Description" 	=> $data->Description
		);

		$descObj->update($arrayUpdate);

		$descObj = null;
	}else{
		echo "null";
	}
}

/*
	Gets all the photos from the database.
*/
function getMedia($id){
	$image = new Image();
	$image->get($id, true);

	$image = null;
}

/*
	Gets all the objects of the media type.
*/
function getMediaCollection($uid){
	$request = \Slim\Slim::getInstance()->request();
	$data = json_decode($request->getBody());

	$image = new Image();
	// Get images returns a list in JSON format of the image objects.
	$image->getImages($uid);

	$image = null;
}
?>