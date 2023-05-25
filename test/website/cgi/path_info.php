<?php
// Récupérer le chemin d'accès à partir de PATH_INFO
$path = $_SERVER['PATH_INFO'];

// Générer une réponse en fonction du chemin d'accès
if ($path == '') {
    echo "Bienvenue sur mon site !";
} else {
    header("HTTP/1.0 404 Not Found");
    echo "404 - Page non trouvée";
}
?>
