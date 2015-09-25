<?php

require('../vendor/autoload.php');

$redis_url = getenv("REDIS_URL");
if (!isset($redis_url) || !$redis_url)
    $redis_url = "redis://h:@localhost:6379";

$redis = new Predis\Client([
    'host' => parse_url($redis_url, PHP_URL_HOST),
    'port' => parse_url($redis_url, PHP_URL_PORT),
    'password' => parse_url($redis_url, PHP_URL_PASS),
]);

$views = $redis->incr('clouds');

?><!doctype html>
<html class="no-js" lang="en">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
    <title>Hello Cloud! - Andy Chase</title>
    <link rel="stylesheet" href="css/main.css">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.4.0/css/font-awesome.min.css">
    <link href='https://fonts.googleapis.com/css?family=Sniglet:800' rel='stylesheet' type='text/css'>
</head>
<body>

<div class="content">
    <h1 class="title">
        <span class="q1"><span class="l1">H</span><span class="l2">e</span><span class="l3">l</span><span class="l4">l</span><span class="l5">o</span><span class="l6"></span><br></span><span class="q2"><span class="l7">C</span><span class="l8">l</span<span class="l9">o</span><span class="l10">u</span><span class="l10">d</span></span>
    </h1>
    <span class="clouds">
        <?php while(--$views >= 0) {
            ?><i class="fa fa-cloud c<?php echo(rand(0, 10)); ?> d<?php echo(rand(0, 10)); ?><?php
            if($views == 0) {
                ?> last<?php
            }?>"></i><?php
        } ?>
    </span>
</div>

<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
<script src="js/main.js"></script>
</body>
</html>
