<?php
require_once('setup.php');

if ($_POST['username']) {
    DB::register(
        $_POST['username'],
        $_POST['password'],
        $_POST['first'],
        $_POST['last']
    );
    $id = DB::login($_POST['username'], $_POST['password']);
    if ($id) {
        $_SESSION['user'] = $id;
        header('Location: .');
        exit();
    } else {
        ?> <i>Problem during registration</i><?php
    }
}

require_once('./views/header.php');

?>
    <form action="register.php" method="POST">
        <label>Username:
            <input name="username"/>
        </label>
        <label>Password:
            <input name="password" type="password"/>
        </label>
        <label>First:
            <input name="first"/>
        </label>
        <label>Last:
            <input name="last"/>
        </label>
        <input type="submit"/>
    </form>
<?php


require_once('./views/footer.php');