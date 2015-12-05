<?php

require_once('setup.php');
$drinks = array(
    array("001", "Coke", "20"),
    array("002", "Coke", "20"),
    array("003", "Coke", "20"),
    array("004", "Coke", "20"),
    array("005", "Coke", "20"),
    array("006", "Coke", "20"),
    array("007", "Coke", "20"),
    array("008", "Coke", "20"),
    array("009", "Coke", "20"),
);

$smarty->assign("drinks", $drinks);
$smarty->display("views/index.tpl");
