// Util
// Returns a random integer between min (included) and max (excluded)
// Using Math.round() will give you a non-uniform distribution!
// Source: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Math/random
function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min)) + min;
}

// Calculate results
// true if user won, false if not, undefined if tie
function didUserWin(userChoice, computerChoice) {
    if (userChoice == "rock" && computerChoice == "paper") {
        return false;
    } else if (userChoice == "rock" && computerChoice == "scissors") {
        return true;
    } else if (userChoice == "paper" && computerChoice == "rock") {
        return true;
    } else if (userChoice == "paper" && computerChoice == "scissors") {
        return false;
    } else if (userChoice == "scissors" && computerChoice == "rock") {
        return false;
    } else if (userChoice == "scissors" && computerChoice == "paper") {
        return true;
    }
}

// Update Score
function updateScoreboard(userWon) {
    var score;
    if (userWon) {
        score = document.getElementById("user-score-number");
    } else {
        score = document.getElementById("computer-score-number");
    }
    score.innerHTML = parseInt(score.innerHTML) + 1;
}

// Show results
function getComputerResult() {
    switch (getRandomInt(0, 3)) {
        case 0:
            return "rock";
        case 1:
            return "paper";
        case 2:
            return "scissors";
    }
}

// Show results
var showTimerUsr;
var showTimerCmp;
var resultsTime = 2000;
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

//
// Main game code
document.addEventListener("DOMContentLoaded", function (event) {
    var select = document.getElementsByClassName('select');
    var s;
    for (s in select) if (select.hasOwnProperty(s)) {
        select[s].addEventListener("click", function (event) {
            var computerChoice = getComputerResult();
            var userWon;
            if (event.target.classList.contains("rock")) {
                userWon = didUserWin("rock", computerChoice);
                showResult("rock", computerChoice, userWon);
            } else if (event.target.classList.contains("paper")) {
                userWon = didUserWin("paper", computerChoice);
                showResult("paper", computerChoice, userWon);
            } else {
                userWon = didUserWin("scissors", computerChoice);
                showResult("scissors", computerChoice, userWon);
            }
            if (userWon != undefined)
                updateScoreboard(userWon);
        });
    }
});