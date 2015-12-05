$(".form-signin, .form-register").submit(function (e) {
    var data = {
        username: $("#username").val(),
        password: $("#password").val()
    };
    if (data.username == "") {
        data = {
            username: $("#r-username").val(),
            password: $("#r-password").val(),
            password_confirm: $("#r-password-confirm").val()
        };
    }
    $.post("./login.php", data, function (result) {
        if (result['success'] == "ok") {
            window.location = "..";
        } else {
            var loginError = $("#login-error");
            loginError.show();
            loginError.html(result['error']);
        }
    });

    e.preventDefault();
});

var timeout = 0;

$(".drink-btn").click(function () {
    var drink = $(this);
    drink.addClass("clicked");
    if (timeout)
        window.clearTimeout(timeout);
    timeout = window.setTimeout(function () {
        drink.removeClass("clicked");
    }, 500);
    $.post("./edit_cart.php", {add: drink.attr('id')}, function (result) {
        $("#shopping-amount").html("$" + result['amount'] + ".00");
    });
});

$(".remove-drink-button").click(function () {
    var drink = $(this);
    $.post("./edit_cart.php", {remove: drink.attr('id')}, function (result) {
        $("#shopping-amount").html("$" + result['amount'] + ".00");
        drink.parent().parent().remove();
    });
});
