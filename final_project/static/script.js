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
