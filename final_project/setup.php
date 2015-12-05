<?php
require_once('./vendor/autoload.php');
session_start();

if (gethostname() == "e44d230a.local")
    $_pdo = new PDO('mysql:host=127.0.0.1;dbname=chasean-db', "root");
else
    $_pdo = new PDO('mysql:host=oniddb.cws.oregonstate.edu;dbname=chasean-db', "chasean-db", "GKyIAFpEw2vvGFeo");


$PDO = new FluentPDO($_pdo);

date_default_timezone_set('UTC');
$smarty = new Smarty();
if ($_SESSION['user'])
    $smarty->assign("user", $_SESSION['user']);

function get_total() {
    $total = 0;
    foreach($_SESSION['cart'] as $drink) {
        $total += $drink * 20;
    }
    return $total;
}

$drinks = array(
    array("001", "Coke", "20"),
    array("002", "Coke Light", "20"),
    array("009", "Cherry Coke", "20"),
    array("003", "Cherry 7UP", "20"),
    array("004", "7UP Free", "20"),
    array("006", "Fanta", "20"),
    array("005", "Fanta Can", "20"),
    array("008", "IceTea", "20"),
    array("007", "IceTea Can", "20"),
);


$smarty->setTemplateDir('views');
$smarty->setCompileDir('views/compile');
$smarty->setCacheDir('views/cache');

class DB
{
    static function pass_hash($password)
    {
        return sha1($password);
    }

    static function login($username, $password)
    {
        global $PDO;
        return $PDO
            ->from('users')
            ->where(array('username' => $username, 'password' => DB::pass_hash($password)))
            ->fetch('id');
    }

    static function register($username, $password)
    {
        global $PDO;
        $values = array(
            'username' => $username,
            'password' => DB::pass_hash($password),
            'first' => "",
            'last' => ""
        );
        return $PDO->insertInto('users', $values)->execute();
    }

    static function add_order($user_id, $order)
    {
        global $PDO;
        $values = array(
            'user' => $user_id,
            'order_text' => json_encode($order)
        );
        return $PDO->insertInto('orders', $values)->execute();
    }

    static function logout()
    {
        $_SESSION['user'] = null;
    }


    public static function user()
    {
        global $PDO;
        print_r($_SESSION['id']);

        return $PDO->from('users')->where('id', intval($_SESSION['user']))->fetch();
    }


}

$smarty->assign("cart_total", get_total());
