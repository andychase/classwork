<?php

require_once('setup.php');

if ($_POST['add']) {
    $_SESSION['cart'][$_POST['add']]++;

    header('Content-Type: application/json');
    echo json_encode(array(
        'amount' => get_total()
    ));
    return;
}

if ($_POST['remove']) {
    unset($_SESSION['cart'][$_POST['remove']]);

    header('Content-Type: application/json');
    echo json_encode(array(
        'amount' => get_total()
    ));
    return;
}