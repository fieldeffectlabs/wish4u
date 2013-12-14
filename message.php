<?php 

header("Access-Control-Allow-Origin: *");
header("Content-type: */*; charset=utf-8");

include "dbconnect.php";


$get = $_GET;   //parametri ricevuti dalla richiesta GET

$sql = "SELECT testo FROM auguri WHERE id_utente = 3 ORDER BY id DESC LIMIT 0,1 ";

$res = mysql_query($sql, $conn);

$riga = mysql_fetch_array($res);

echo $riga;


echo '$';
echo $riga[testo];
//echo '#';


?>
