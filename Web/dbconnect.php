<?php
 
$db = "infnrcpw_wish4u";
$host = "mysql.netsons.com";
$username = "infnrcpw";
$password = "Am3Z5z0wn4";
 
if(!$conn = @mysql_connect($host,$username,$password))
{
	echo "Errore nella connessione al database";
	die;
}
 
if(!@mysql_select_db($db,$conn))
{
	echo "Impossibile selezionare il database";
	die;
}
 
?>