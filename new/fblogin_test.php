<?php
namespace Spuzik;
require "src/Spuzik/Users/Session.php";

$session = new Users\Session();
echo $session->serviceType();

echo "<a href=\"".$session->facebookLink("LOGIN")."\">Login</a>";
















/*
if ($user) {
  try {
    // Proceed knowing you have a logged in user who's authenticated.
    $user_profile = $facebook->api('/me');
    print_r($user_profile);
  } catch (FacebookApiException $e) {
    error_log($e);
    $user = null;
  }
}

// Login or logout url will be needed depending on current user state.
if ($user)
	echo "<a href=".$facebook->getLogoutUrl().">Logout</a>";
else
	echo "<a href=".$facebook->getLoginUrl().">Login</a>";
*/
?>