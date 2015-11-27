<?php
require_once('setup.php');

if ($_POST['move']) {

    function didUserWin($userChoice, $computerChoice)
    {
        if ($userChoice == "rock" && $computerChoice == "paper") {
            return false;
        } else if ($userChoice == "rock" && $computerChoice == "scissors") {
            return true;
        } else if ($userChoice == "paper" && $computerChoice == "rock") {
            return true;
        } else if ($userChoice == "paper" && $computerChoice == "scissors") {
            return false;
        } else if ($userChoice == "scissors" && $computerChoice == "rock") {
            return false;
        } else if ($userChoice == "scissors" && $computerChoice == "paper") {
            return true;
        }
        return false;
    }

    function didTie($userChoice, $computerChoice)
    {
        return ($userChoice == $computerChoice);
    }

    $choices = array("paper", "rock", "scissors");
    $computerChoice = $choices[array_rand($choices)];
    $userChoice = $_POST['move'];

    $tie = didTie($userChoice, $computerChoice);
    $userWon = didUserWin($userChoice, $computerChoice);
    if ($tie) {
    } elseif ($userWon) {
        db::save_score(1);
    } else {
        db::save_score(0);
    }

    header('Content-Type: application/json');
    echo json_encode(array(
        'userChoice' => $userChoice,
        'computerChoice' => $computerChoice,
        'tie' => $tie,
        'userWon' => $userWon,
        'scoreboard' => [0, 0]
    ));
    exit();

    /* Markup from Assignment 3 */
} else {
    require_once('./views/header.php');

    ?>
    <div class="content">
    <div class="scoreboard">
			<span class="user score"><i class="fa fa-star-o"></i>
				<span id="user-score-number">0</span>
			</span>
			<span class="computer score"><i class="fa fa-laptop"></i>
				<span id="computer-score-number">0</span>
			</span>
    </div>

    <div class="results">
        <i id="c-usr" class="choice fa fa-hand-scissors-o"></i>
        <i id="c-cmp" class="choice fa fa-hand-scissors-o"></i>
    </div>


    <i class="select fa fa-hand-rock-o rock"></i>
    <i class="select fa fa-hand-paper-o paper"></i>
    <i class="select fa fa-hand-scissors-o scissors"></i>

    <div class="instructions">
        Rocks, Paper, Scissors<br/>
        Click an action above to play. Good luck!

    </div>
    </div>

    <?php
    require_once('./views/footer.php');

}

