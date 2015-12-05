<?php

require_once('setup.php');

$data = false;

if ($_POST['password_confirm']) {
    header('Content-Type: application/json');

    if ($_POST['password'] != $_POST['password_confirm']) {
        $data = array("error" => "Passwords do not match!");
        echo json_encode($data);
        return;
    }

    DB::register(
        $_POST['username'],
        $_POST['password']
    );
    $id = DB::login($_POST['username'], $_POST['password']);
    if ($id) {
        $_SESSION['user'] = $id;
        $data = array("success" => "ok");
    } else {
        $data = array("error" => "Problem during registration. That username may already be taken.");
    }
    echo json_encode($data);
    return;
}


if ($_POST['username']) {
    header('Content-Type: application/json');
    $id = DB::login($_POST['username'], $_POST['password']);
    if ($id) {
        $_SESSION['user'] = $id;
        $data = array("success" => "ok");
    } else {
        $data = array("error" => "Username/Password are not correct.");
    }
    echo json_encode($data);
    return;
}

$smarty->display("views/login.tpl");
