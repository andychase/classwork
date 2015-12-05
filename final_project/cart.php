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