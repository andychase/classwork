<?php
require_once('setup.php');

if (get_total() == 0) {
    print_r("Nothing in the chart to order");
} else {
    $smarty->assign("order_number", DB::add_order(intval($_SESSION['user']), $_SESSION['cart']));
    $smarty->assign("drinks", $drinks);
    $smarty->assign("cart", $_SESSION['cart']);
    $smarty->assign("cart_total", 0);

    $smarty->display("views/checkout.tpl");

    $_SESSION['cart'] = array();
}
