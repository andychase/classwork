<?php
require_once('setup.php');

$smarty->assign("drinks", $drinks);
$smarty->assign("cart", $_SESSION['cart']);

$smarty->display("views/checkout.tpl");

$_SESSION['cart'] = array();