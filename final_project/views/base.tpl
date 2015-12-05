<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <title>{block 'title'}DrinkShop{/block}</title>
    {if isset($page_description_short)}
        <meta name="description" content="{$page_description_short}">
    {/if}
    <link rel="stylesheet" href="./static/bootstrap.min.css">
    <link rel="stylesheet" href="./static/style.css">
    {block 'head'}{/block}
</head>
<body>


<nav class="navbar navbar-default">
    <div class="container-fluid">
        <div class="navbar-header">
            <h1><a class="navbar-brand" href="."><span class="drink">Drink</span>Shop</a></h1>
        </div>
        <ul class="nav navbar-nav navbar-right">
            {if $user}
                <li><a href="./logout.php">Log out</a></li>
                <li><a href="./past.php">Past Orders</a></li>
            {else}
                <li><a href="./login.php">Sign In / Register</a></li>
            {/if}
            <li><a href="./cart.php">Shopping Chart<span class="badge" id="shopping-amount">${$cart_total}.00</span></a></li>
        </ul>
    </div>
</nav>
{block 'content'}{/block}
<footer class="footer">
    <div class="container">
        <p class="text-muted">(c) 2015 DrinkShop. <a href="./contact.php">Contact/References</a></p>
    </div>
</footer>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>
<script src="./static/script.js"></script>
</body>
</html>
