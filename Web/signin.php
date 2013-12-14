<?php
include "dbconnect.php";


$sql = "INSERT INTO auguri  (id_utente, testo) VALUES ('".$_POST[id]."','".$_POST[testo]."')";
$res = mysql_query($sql, $conn);
header("Location: index.php");
?>