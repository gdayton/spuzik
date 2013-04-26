<?php

    session_start();

    if (isset($_POST['song']) && is_numeric($_POST['song'])) {
        $songID = $_POST['song'];
    } else {
        die("noSongID");
    }

    require("gsAPI.php");
    $gsapi = new gsAPI('classrecon', '05a6a2523a0ffda94fe10758a616c7cb');
    gsAPI::$headers = array("X-Client-IP: " . $_SERVER['REMOTE_ADDR']);

    if (isset($_SESSION['gsSession']) && !empty($_SESSION['gsSession'])) {
        $gsapi->setSession($_SESSION['gsSession']);
    } else {
        $_SESSION['gsSession'] = $gsapi->startSession();
    }

    if (!$_SESSION['gsSession']) {
        die("noSession");
    }
    if (isset($_SESSION['gsCountry']) && !empty($_SESSION['gsCountry'])) {
        $gsapi->setCountry($_SESSION['gsCountry']);
    } else {
        $_SESSION['gsCountry'] = $gsapi->getCountry();
    }
    if (!$_SESSION['gsCountry']) {
        die("noCountry");
    }
    $streamInfo = $gsapi->getStreamKeyStreamServer($songID, false);
    echo json_encode($streamInfo);

?>