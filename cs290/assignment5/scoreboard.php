<?php
require_once('setup.php');

require_once('./views/header.php');

?>
    <table>
        <thead>
        <tr>
            <th>First</th>
            <th>Last</th>
            <th>Score</th>
        </tr>
        </thead>
        <tbody>
        <?php
        foreach (DB::scoreboard() as $row) { ?>
            <tr>
                <td><?php echo($row['first']); ?></td>
                <td><?php echo($row['last']); ?></td>
                <td><?php echo($row['won']); ?></td>
            </tr>
        <?php } ?>
        </tbody>
    </table>

<?php
require_once('./views/footer.php');
