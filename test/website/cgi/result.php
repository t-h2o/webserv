<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>HTML Result Page for Testing</title>
</head>
<form action="php_post.php" method="post" enctype="multipart/form-data">
<body>

<h1>Testing result</h1>

<p>content post : <?php if( isset($_POST["contentPost"]) ) {echo $_POST["contentPost"];} ?></p>
<p>content get : <?php if( isset($_GET["contentGet"]) ) {echo $_GET["contentGet"];} ?></p>

<?php

    echo '<pre>';
    var_dump($_ENV);
    echo '</pre>';

    echo '<pre>';
    var_dump($_POST);
    echo '</pre>';

    echo '<pre>';
    var_dump($_GET);
    echo '</pre>';
?>

</body>

</html>