<?php

require_once('setup.php');

$smarty->assign("drinks", $drinks);
$smarty->display("views/index.tpl");
