<!doctype html>
<html class="no-js" lang="">
<head>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <title>Rock Paper Scissors Game</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/normalize/3.0.3/normalize.css"/>
    <link rel="stylesheet" href="./style.css"/>
</head>
<body>
<header>
    <nav>
        <ul>
            <li><a href=".">Home</a></li>
            <?php
            $user = DB::user();
            if ($user) { ?>
                <li><a href="logout.php">Logout</a></li>
                <li><a href="play.php">Play</a></li>
            <?php } else { ?>
                <li><a href="register.php">Register</a></li>
                <li><a href="login.php">Login</a></li>
            <?php } ?>
            <li><a href="scoreboard.php">Scoreboard</a></li>
        </ul>
        <span class="welcome">
            <?php
            if ($user) {
                echo("Hello " . $user['first'] . "!");
            }
            ?>
        </span>
    </nav>
</header>
<article class="main">