<?php
include("actions/actions.class.php");
sec_session_start();
$post = $_POST;
$type = $_GET['type'];
$u = new User();
if(isset($type)){
	switch($type){
		case "addUser":
			$u->addUser($post);
			break;
		case "loginCheck":
			$u->loginCheck();
			break;
		case "signIn":
			$u->signIn($post);
			break;
		case "logout":
			$u->logout();
			break;
		case "headerBar":
			$u->headerBar();
			break;
		case "getInfo":
			$u->getInfo($_GET['u_id']);
			break;
		case "editInfoGeneral":
			$u->editInfoGeneral($post/*array("hmtown"=>"San Diego","hmtown_perms"=>"pub")*/);
			break;
		case "editInfo":
			$u->editInfo($post);
			break;
		case "editInfoAgent":
			$u->editInfoAgent($post);
			break;
		case "search":
			$u->search($post);
			break;
		case "fan":
			$u->fan($post);
			break;
		case "getFans":
			$u->getFans($post);
			break;
		case "getSupporters":
			$u->getSupporters($post);
			break;
		case "addLink":
			$u->addLink($post);
			break;
		case "getLinks":
			$u->getLinks($_GET['uid']);
			break;
		case "getLink":
			$u->getLink($_GET['l_id']);
			break;
		case "removeLink":
			$u->removeLink($post);
			break;
		case "addDescription":
			$u->editDescription($post/*array("id"=>"50f84de4e0d87","text"=>"This is a really cool picture.")*/);
			break;
		case "getPhotos":
			$u->getPhotos($_GET['uid']);
			break;
		case "grabNonAlbumPhotos":
			$u->grabNonAlbumPhotos($_GET['uid']);
			break;
		case "addTune":
			$u->addTune($post);
			break;
		case "getMusic":
			$u->getMusic($_GET['id']);
			break;
		case "addVideo":
			$u->addVideo($post);
			break;
		case "getVideos":
			$u->getVideos($_GET['uid']);
			break;
		case "getPhotoData":
			$u->getPhotoData($_GET['id']);
			break;
		case "getVideoData":
			$u->getVideoData($_GET['id']);
			break;
		case "addPosting":
			$u->addPosting($post);
			break;
		case "addEditLineup":
			$u->addEditLineup($post /*array("action"=>"edit","list"=>array(149,168,148,150,165,492,291,167,170,246,293,290,292))*/);
			break;
		case "getLineup":
			$u->getLineup($_GET['u_id']);
			break;
		case "getPostings":
			header("Content-type: text/json");
			$u->getPostings($_GET['p_id'], $_GET['ptype']);
			break;
		case "grabPosting":
			$u->grabPosting($_GET['p_id']);
			break;
		case "getProfilePostings":
			$u->getProfilePostings($_GET['u_id'],$_GET['p_id'], $_GET['ptype']);
			break;
		case "editProfilePic":
			$u->editProfilePic($post);
			break;
		case "grabLikeUsers":
			$u->grabLikeUsers();
			break;
		case "editHomePic":
			$u->editHomePic($post);
			break;
		case "randomFonts":
			$u->randomFonts();
			break;
		case "addChat":
			$u->addChat($post);
			break;
		case "getChatUsers":
			$u->getChatUsers();
			break;
		case "keepAlive":
			$u->keepAlive();
			break;
		case "grabChats":
			$u->grabChats($_GET['id']);
			break;
		case "grabQuotes":
			$u->grabQuotes($_GET['u_id']);
			break;
		case "addQuote":
			$u->addQuote($post);
			break;
		case "deleteQuote":
			$u->deleteQuote($_GET['q_id']);
			break;
		case "addMemory":
			$u->addMemory($post);
			break;
		case "grabMemories":
			$u->grabMemories($_GET['u_id']);
			break;
		case "deleteMemory":
			$u->deleteMemory($_GET['m_id']);
			break;
		case "grabAboutMe":
			$u->grabAboutMe($_GET['u_id']);
			break;
		case "editAboutMe":
			$u->editAboutMe($post);
			break;
		case "grabComments":
			$u->grabComments($_GET['r_id'],$_GET['c_type']);
			break;
		case "addComment":
			$u->addComment($post);
			break;
		case "editImageDescription":
			$u->editImageDescription($post);
			break;
		case "removePhoto":
			$u->removePhoto($_GET['r_id']);
			break;
		case "createAlbum":
			$u->createAlbum($post);
			break;
		case "grabAlbumPhotos":
			$u->grabAlbumPhotos($_GET['a_id']);
			break;
		case "selectAlbumText":
			$u->selectAlbumText();
			break;
		case "removeAlbumItem":
			$u->removeAlbumItem($_GET['p_id']);
			break;
		case "addAlbumItem":
			$u->addAlbumItem($_GET['a_id'],$_GET['p_id']);
			break;
		case "removePosting":
			$u->removePosting($_GET['p_id']);
			break;
		case "removeAlbum":
			$u->removeAlbum($_GET['a_id']);
			break;
		case "removeVideo":
			$u->removeVideo($_GET['r_id']);
			break;
		case "grabGenres":
			$u->grabGenres();
			break;
		case "grabSports":
			$u->grabSports();
			break;
		case "grabPreferences":
			$u->grabPreferences();
			break;
		case "addClient":
			$u->addClient($post);
			break;
		case "grabClients":
			$u->grabClients($_GET['uid']);
			break;
		case "updateStatus":
			$u->updateStatus($post);
			break;
		case "addAchievement":
			$u->addAchievement($post);
			break;
		case "grabAchievements":
			$u->grabAchievements($_GET['uid']);
			break;
		case "deleteAch":
			$u->deleteAch($_GET['a_id']);
			break;
		case "addGoal":
			$u->addGoal($post);
			break;
		case "grabGoals":
			$u->grabGoals($_GET['uid']);
			break;
		case "deleteGoal":
			$u->deleteGoal($_GET['a_id']);
			break;
		case "addCoach":
			$u->addCoach($post);
			break;
		case "grabCoach":
			$u->grabCoach($_GET['uid']);
			break;
		case "deleteCoach":
			$u->deleteCoach($_GET['a_id']);
			break;
		case "editClientPic":
			$u->editClientPic($post);
			break;
		case "editClientName":
			$u->editClientName($post);
			break;
		case "editClientDesc":
			$u->editClientDesc($post);
			break;
		case "addEvent":
			$u->addEvent($post);
			break;
		case "grabEvents":
			$u->grabEvents($_GET['c_id']);
			break;
		case "deleteEvent":
			$u->deleteEvent($_GET['c_id'],$_GET['e_id']);
			break;
		case "addSponsor":
			$u->addSponsor($post);
			break;
		case "grabSponsors":
			$u->grabSponsors($_GET['u_id']);
			break;
		case "deleteSponsor":
			$u->deleteSponsor($_GET['s_id']);
			break;
		case "deleteComment":
			$u->deleteComment($_GET['r_id']);
			break;
		case "clap":
			$u->clap($post);
			break;
		case "grabClaps":
			$u->grabClaps($_GET['r_id']);
			break;
		case "grabThoughtstream":
			$u->grabThoughtstream($_GET['p_id']);
			break;
		case "checkChat":
			$u->checkChat($_GET['u_id']);
			break;
		case "markCheckChat":
			$u->markCheckChat($_GET['u_id']);
			break;
		case "createChatroom":
			$u->createChatroom($post);
			break;
		case "getChatrooms":
			$u->getChatrooms($_GET['u_id']); //put the user id in the parameter for the list of chatrooms that they own.
			break;
		case "getChatroom":
			$u->getChatroom($_GET['u_id']);
			break;
		case "grabChatroomNotifications":
			$u->grabChatroomNotifications();
			break;
		case "decideChatroom":
			$u->decideChatroom($_GET['c_id'], $_GET['u_id'], $_GET['ctype']);
			break;
		case "getAllChatrooms":
			$u->getAllChatrooms($_GET['u_id']);
			break;
		case "chatChatroom":
			$u->chatChatroom($post);
			break;
		case "grabChatroomChats":
			$u->grabChatroomChats($_GET['c_id']);
			break;
		case "checkChatChatroom":
			$u->checkChatChatroom($_GET['c_id']);
			break;
		case "createPlaylist":
			$u->createPlaylist($post);
			break;
		case "grabPlaylist":
			$u->grabPlaylist($_GET['u_id']);
			break;
		case "addSongPlaylist":
			$u->addSongPlaylist($post);
			break;
		case "requestAddChatroomMember":
			$u->requestAddChatroomMember($post);
			break;
		case "getChatUsersUnique":
			$u->getChatUsersUnique($_GET['c_id']);
			break;
		case "addPostingCategory":
			$u->addPostingCategory($post);
			break;
		case "grabPostings":
			$u->grabPostings($_GET['u_id'],$_GET['view'],$_GET['category'],$_GET['type']);
			break;
		case "getProfileSong":
			$u->getProfileSong();
			break;
		case "getChatAlerts":
			$u->getChatAlerts();
			break;
		case "inviteMoreUsers":
			$u->inviteMoreUsers($post);
			break;
		case "getPlaylistMusic":
			$u->getPlaylistMusic($_GET['p_id']); //playlist_id is passed via a get variable
			break;
		case "removePlaylist":
			$u->removePlaylist($_GET['p_id']);
			break;
		case "removeTune":
			$u->removeTune($_GET['t_id']);
			break;
		case "changeTunePosition":
			$u->changeTunePosition($post); // array("tune_list"=>array(5,4,14,17,16,46,57,74,75))
			break;
		case "changePlaylistPosition":
			$u->changePlaylistPosition($post);
			break;
		case "removeFromChatroom":
			$u->removeFromChatroom($_GET['c_id']); //c_id = Chatroom ID from which to remove current user from
			break;
		case "switchPage":
			if(count($_GET) > 1)
				$u->switchPage($_GET['page']);
			else{
				array_shift($_GET); //remove the page GET item, and pass the rest.
				$u->switchPage($_GET['page'], $_GET);
			}
			break;
		case "searchMusic":
			$u->searchMusic($_GET['s'],$_GET['a']);
			break;
		case "removeChatroomUser":
			$u->removeChatroomUser($_GET['u_id']);
			break;
		case "grabNotifications":
			$u->grabNotifications($_GET['t']);
			break;
		case "grabPastNotifications":
			$u->grabPastNotifications($_GET['t']);
			break;
		case "searchChatrooms":
			$u->searchChatrooms($_GET['q']);
			break;
		/*case "getMusicViaGrvName":
			$u->getMusicViaGrvName($_GET['name']);
			break;*/
		//cas "makeNotification":
		//	$u->makeNotification(array(
		//		'snapshotmult' 	=> 'http://54.243.129.126/usr_content/pics/51524b9107efd_w.jpg',  //get this from the post db
		//		'actiontype' 	=> 0, //0 is commented
		//		'type'			=> 0, //0 is thoughtstream
		//		'subjecttype'	=> 1,  //get this from the post db, this is grabbed from above
		//		'useractionid'	=> 17  //get this from the post db
		//	)/*$post*/);
		//	break;
		//array("fname"=>"Test",
		//							   "lname"=>"Testing",
		//							   "type"=>"0",
		//							   "email"=>"gdayton@ucla.edu",
		//							   "day"=>"1",
		//							   "month"=>"1",
		//							   "year"=>"1994",
		//							   "password"=>"this",
		//						       "passwordv"=>"this")
		case "markReadNotification":
			$u->markReadNotification($_GET['n_id']);
			break;
		case "pendingNotifications":
			$u->pendingNotifications();
			break;
		case "recs":  //TODO make this only return the name, id, photo url, and hometown, not the whole shabang
			$u->recs();
			break;
		case "profileSong":
			$u->profileSong($post);
			break;
		case "getSongsAll":
			$u->getSongsAll($_GET['s_id']);
			break;
		default:
			$returnJSON = array("status"=>"error","status_type"=>"internal","status_msg"=>"Not a valid function.");
			echo json_encode($returnJSON);
			break;
	}
}else{
	$returnJSON = array("status"=>"error","status_type"=>"internal","status_msg"=>"Nothing was posted.");
        echo json_encode($returnJSON);
}
?>
