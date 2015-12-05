<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <title>{block 'title'}DrinkShop{/block}</title>
    {if isset($page_description_short)}
        <meta name="description" content="{$page_description_short}">
    {/if}
    <link rel="stylesheet" href="/static/bootstrap.min.css">
    <link rel="stylesheet" href="/static/style.css">
    {block 'head'}{/block}
</head>
<body>


<nav class="navbar navbar-default">
    <div class="container-fluid">
        <div class="navbar-header">
            <h1><a class="navbar-brand" href="/"><span class="drink">Drink</span>Shop</a></h1>
        </div>
        <ul class="nav navbar-nav navbar-right">
            <li><a href="/login.php">Sign In</a></li>
            {if $user}
            <li><a href="/logout.php">Log out</a></li>
            {/if}
            <li><a href="/checkout.php">Shopping Chart<span class="badge" id="shopping-amount">$0.00</span></a></li>
        </ul>
    </div>
</nav>
{block 'content'}{/block}
<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"
        integrity="sha384-0mSbJDEHialfmuBBQP6A4Qrprq5OVfW37PRR3j5ELqxss1yVqOtnepnHVP9aJ7xS"
        crossorigin="anonymous"></script>
<script src="static/script.js"></script>
</body>
</html>
