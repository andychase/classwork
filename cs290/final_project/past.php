<?php
require_once('setup.php');

$orders = array();
foreach(DB::past_orders(intval($_SESSION['user'])) as $order) {
    $orders[] = array("number" => $order['id'], "order" => json_decode($order['order_text']));
}

$smarty->assign("orders", $orders);
$smarty->display("views/past.tpl");
