<!doctype html>
<html class="no-js" lang="">
<head>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <title></title>
    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    <link rel="apple-touch-icon" href="apple-touch-icon.png">
    <!-- Place favicon.ico in the root directory -->

    <link rel="stylesheet" href="css/normalize.css">
    <link rel="stylesheet" href="css/main.css">
    <script src="js/vendor/modernizr-2.8.3.min.js"></script>
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
            <?php } else { ?>
                <li><a href="register.php">Register</a></li>
                <li><a href="login.php">Login</a></li>
            <?php } ?>
            <li><a href="play.php">Play</a></li>
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