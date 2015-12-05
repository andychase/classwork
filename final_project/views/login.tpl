{extends 'base.tpl'}
{block 'content'}
    <div class="container">
        <div class="row">
            <div class="col-md-4 col-md-offset-4">
                {if $user}
                    You are logged in!
                {else}
                    <div class="alert alert-danger" role="alert" id="login-error" style="display:none;"></div>
                    <form class="form-signin" action="login.php" method="post">
                        <h2 class="form-signin-heading">Please sign in</h2>
                        <label for="username" class="sr-only">Username</label>
                        <input id="username" name="username" class="form-control" placeholder="Username" required
                               autofocus>
                        <label for="password" class="sr-only">Password</label>
                        <input type="password" name="password" id="password" class="form-control" placeholder="Password"
                               required>
                        <br/>
                        <button class="btn btn-lg btn-primary btn-block" type="submit">Sign in</button>
                    </form>
                    <form class="form-register">
                        <h2 class="form-signin-heading">Register</h2>
                        <label for="r-username" class="sr-only">Email address</label>
                        <input id="r-username" class="form-control" placeholder="Username" required>
                        <label for="r-password" class="sr-only">Password</label>
                        <input type="password" id="r-password" class="form-control" placeholder="Password" required>
                        <label for="r-password-confirm" class="sr-only">Password Confirmation</label>
                        <input type="password" id="r-password-confirm" class="form-control"
                               placeholder="Password Confirmation" required>
                        <br/>
                        <button class="btn btn-lg btn-primary btn-block" type="submit">Register</button>
                    </form>
                {/if}
            </div>
        </div>
    </div>
{/block}