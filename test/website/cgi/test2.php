<?php
// Définir la variable PATH_INFO à une valeur spécifique
putenv("PATH_INFO=/page1");

// Exécuter le script PHP
include "script.php";
?>
