<?php
if (isset($_SERVER['GATEWAY_INTERFACE'])) {
    echo 'GATEWAY_INTERFACE: ' . $_SERVER['GATEWAY_INTERFACE'] . '<br>';
} else {
    echo 'GATEWAY_INTERFACE: undefined<br>';
}


?>
