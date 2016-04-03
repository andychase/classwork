<?php
require_once('./vendor/autoload.php');
session_start();

if (strpos(gethostname(), "e44d230a") !== false)
    $_pdo = new PDO('mysql:host=127.0.0.1;dbname=chasean-db', "root");
else
    $_pdo = new PDO('mysql:host=oniddb.cws.oregonstate.edu;dbname=chasean-db', "chasean-db", "GKyIAFpEw2vvGFeo");


$PDO = new FluentPDO($_pdo);

class DB
{
    static function pass_hash($password)
    {
        global $PDO;
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

    static function register($username, $password, $first_name, $last_name)
    {
        global $PDO;
        $values = array(
            'username' => $username,
            'password' => DB::pass_hash($password),
            'first' => $first_name,
            'last' => $last_name
        );
        return $PDO->insertInto('users', $values)->execute();
    }

    static function logout()
    {
        $_SESSION['user'] = null;
    }

    static function scoreboard()
    {
        global $PDO;
        return $PDO
            ->from('games')
            ->leftJoin("users on users.id = games.user")
            ->select(array('users.first as first', 'users.last as last', 'sum(won) as won'))
            ->groupBy('users.id')
            ->fetchAll();
    }

    static function scoreboard_for_user()
    {
        global $PDO;
        return $PDO
            ->from('games')
            ->leftJoin("users on users.id = games.user")
            ->select(array('users.first as first', 'users.last as last', 'sum(won) as won', 'count(won) - sum(won) as lost'))
            ->where("users.id", intval($_SESSION['user']))
            ->groupBy('users.id')
            ->fetch();
    }

    public static function user()
    {
        global $PDO;
        print_r($_SESSION['id']);

        return $PDO->from('users')->where('id', intval($_SESSION['user']))->fetch();
    }

    public static function save_score($won)
    {
        global $PDO;
        $values = array(
            'user' => $_SESSION['user'],
            'won' => $won
        );
        return $PDO->insertInto('games', $values)->execute();
    }
}