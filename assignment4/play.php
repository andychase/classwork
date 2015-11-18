<?php
require_once('setup.php');


if ($_POST['username']) {
    $id = DB::login($_POST['username'], $_POST['password']);
    if ($id) {
        $_SESSION['user'] = $id;
        header('Location: /');
    } else {
        require_once('./views/header.php');
        ?> <i>Username/password incorrect</i><?php
    }
} else {
    require_once('./views/header.php');

    ?>
    <form action="login.php" method="POST">
        <label>Username:
            <input name="username"/>
        </label>
        <label>Password:
            <input name="password" type="password"/>
        </label>
        <input type="submit"/>
    </form>
    <?php


    require_once('./views/footer.php');
}