{extends 'base.tpl'}
{block 'content'}
    <div class="container">
        <div class="row">
            <div class="col-md-6 col-md-offset-4">
                <h2>Past Orders</h2>
                {foreach $orders as $order}
                    <h3>Order #{$order.number}</h3>
                    <table class="drink-checkout-list">
                        <thead>
                        <tr>
                            <th>Drink</th>
                            <th>Number of drinks</th>
                        </tr>
                        </thead>
                        <tbody>
                        {foreach $order.order as $name => $amount}
                            <tr>
                                <td>{$name}</td>
                                <td>{$amount}</td>
                            </tr>
                        {/foreach}
                        </tbody>
                    </table>
                {/foreach}
            </div>
        </div>
    </div>
{/block}