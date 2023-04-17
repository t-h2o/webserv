<?php
$variableName = 'CONTENT_LENGTH';
$value = getenv($variableName);
echo "Environment variable using getenv(): {$value}\n";
?>
$value = getenv($variableName);
if ($value !== false) {
    echo "Environment variable using getenv(): {$value}\n";
}
else {
    echo "Environment variable not set using getenv().\n";
}

if (isset($_ENV[$variableName])) {
    echo "Environment variable using _ENV: {$_ENV[$variableName]}\n";
}
else {
    echo "Environment variable not set using _ENV.\n";
}