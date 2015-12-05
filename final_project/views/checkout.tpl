{extends 'base.tpl'}
{block 'content'}
    <div class="jumbo-wrapper-2">
        <div class="jumbotron">
            <div class="container">
                <h1>Thanks! Your order has been made.</h1>

                <p>&nbsp;</p>
            </div>
        </div>
    </div>
    <div class="container">
        <div class="row">
            <div class="col-md-6 col-md-offset-4">
                <p>Keep this receipt for your records.</p>
                <table class="drink-checkout-list">
                    <thead>
                    <tr>
                        <th>Drink</th>
                        <th>Number of drinks</th>
                    </tr>
                    </thead>
                    <tbody>
                    {foreach $cart as $name => $amount}
                        <tr>
                            <td>{$name}</td>
                            <td>{$amount}</td>
                        </tr>
                    {/foreach}
                    </tbody>
                </table>
            </div>
        </div>
    </div>
{/block}