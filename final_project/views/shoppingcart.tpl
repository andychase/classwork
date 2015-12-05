{extends 'base.tpl'}
{block 'content'}
    <div class="container">
        <div class="row">
            <div class="col-md-6 col-md-offset-4">
                <table class="drink-checkout-list">
                    <thead>
                    <tr>
                        <th>Remove</th>
                        <th>Drink</th>
                        <th>Number of drinks</th>
                    </tr>
                    </thead>
                    <tbody>
                    {foreach $cart as $name => $amount}
                        <tr>
                            <td>
                                <button class="btn btn-default remove-drink-button" id="{$name}">-</button>
                            </td>
                            <td>{$name}</td>
                            <td>{$amount}</td>
                        </tr>
                    {/foreach}
                    </tbody>
                </table>
                {if $user}
                    {if $cart_total}
                        <p><a class="btn btn-primary btn-lg" href="checkout.php" role="button">Checkout</a></p>
                    {else}
                        <p>Add things to your chart to checkout!</p>
                    {/if}
                {else}
                    <p><a class="btn btn-primary btn-lg" href="login.php" role="button">Signin to Checkout</a></p>
                {/if}
            </div>
        </div>
    </div>
{/block}