// Show results
var showTimerUsr;
var showTimerCmp;
var resultsTime = 2000;
/* from Assignment 3 */
function showResult(userChoice, computerChoice, userWon) {
    // Update the user result
    document.getElementById("c-usr").className =
        "choice fa show fa-hand-" + userChoice + "-o " + userWon;

    // Fade out user result
    if (typeof showTimerUsr != "undefined")
        window.clearTimeout(showTimerUsr);
    showTimerUsr = window.setTimeout(function () {
        document.getElementById("c-usr").className =
            "choice fa fa-hand-" + userChoice + "-o";
    }, resultsTime);

    // Update the computer result
    document.getElementById("c-cmp").className =
        "choice fa show fa-hand-" + computerChoice + "-o " + userWon;
    // Fade out computer result
    if (typeof showTimerCmp != "undefined")
        window.clearTimeout(showTimerCmp);
    showTimerCmp = window.setTimeout(function () {
        document.getElementById("c-cmp").className =
            "choice fa fa-hand-" + computerChoice + "-o";
    }, resultsTime);
}

// Reference used: http://stackoverflow.com/a/18995200/134730
// Modified
function callAjax(url, data, callback) {
    var ajaxRequest = new XMLHttpRequest();
    ajaxRequest.open('POST', url, true);
    ajaxRequest.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    ajaxRequest.onreadystatechange = function() {
        if (ajaxRequest.readyState === 4 && ajaxRequest.status === 200) {
            callback(JSON.parse(ajaxRequest.response));
        }
    };
    ajaxRequest.send(data);
}

function sendChoice(userChoice) {
    callAjax("/play.php", "move=" + userChoice, function (data) {
        showResult(userChoice, data.computerChoice, data.userWon)
    });
}

document.addEventListener("DOMContentLoaded", function (event) {
    var select = document.getElementsByClassName('select');
    var s;
    for (s in select) if (select.hasOwnProperty(s)) {
        select[s].addEventListener("click", function (event) {
            if (event.target.classList.contains("rock")) {
                sendChoice("rock");
            } else if (event.target.classList.contains("paper")) {
                sendChoice("paper");
            } else {
                sendChoice("scissors");
            }
        });
    }
});