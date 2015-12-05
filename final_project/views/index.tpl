{extends 'base.tpl'}
{block 'content'}
    <div class="jumbo-wrapper">
        <div class="jumbotron">
            <div class="container">
                <h1>Who says you can't buy drinks online?</h1>

                <p><a class="btn btn-primary btn-lg" href="learnmore.php" role="button">Learn more</a>
            </div>
        </div>
    </div>
    <div class="container">
        <div class="row">
            {foreach $drinks as $drink}
                <div class="panel panel-default drink-panel">
                    <div class="panel-body">
                        <img src="./static/drinks/{$drink.0}.png"/>
                    </div>
                    <div class="panel-footer drink-footer">
                        <span class="badge">${$drink.2}</span>
                        <span class="drink">{$drink.1}</span>
                        <button class="btn btn-default drink-btn" id="{$drink.1|lower}" type="submit">+</button>
                    </div>
                </div>
            {/foreach}
        </div>
    </div>
{/block}