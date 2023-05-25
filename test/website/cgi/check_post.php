<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  $input = $_POST['input_field'];
  echo "Input value: " . $input;
}
?>