<?php
ob_start(); // Mise en memoire tampon de la sortie
phpinfo();
$info = ob_get_contents(); // Recuperation de la sortie mise en memoire tampon
ob_end_clean(); // Effacement de la memoire tampon

$file = 'info.html';
file_put_contents($file, $info); // Ecriture du contenu dans le fichier

echo "le contenu de phpinfo() a été copié dans $file";
?>
