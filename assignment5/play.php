<?php
require_once('setup.php');
require_once('./views/header.php');

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
    echo("<span class='user-choice'>User Choice: " . $userChoice . "</span>");
    echo("<div class='computer-choice'>Computer Choice: " . $computerChoice . "</div>");

    $tie = didTie($userChoice, $computerChoice);
    $userWon = didUserWin($userChoice, $computerChoice);
    if ($tie) {
        ?> Tie! <?php
    } elseif ($userWon) {
        db::save_score(1);
        ?> User won! <?php
    } else {
        db::save_score(0);
        ?> Computer won! <?php
    }
    ?> <a href="./play.php">Replay!</a><?php

} else {

    ?>
    <form action="play.php" method="POST">
        <label>
            <input type="radio" name="move" value="rock"/> Rock
        </label>
        <label>
            <input type="radio" name="move" value="paper"/> Paper
        </label>
        <label>
            <input type="radio" name="move" value="scissors"/> Scissors
        </label>
        <input type="submit"/>
    </form>

    <?php


}
require_once('./views/footer.php');
