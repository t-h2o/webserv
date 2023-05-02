<?php
$test_cases = [
    ["key" => "SCRIPT_FILENAME", "expected_value" => "test/src/cgi/env.php"],
    ["key" => "REDIRECT_STATUS", "expected_value" => "200"],
];

foreach ($test_cases as $test_case) {
    $env_key = $test_case["key"];
    $expected_value = $test_case["expected_value"];
    $actual_value = getenv($env_key);

    if ($actual_value == $expected_value) {
       echo "Test case for key '$env_key' passed." . PHP_EOL;
    } else {
        echo "Test case for key '$env_key' failed. Expected: '$expected_value', Actual: '$actual_value'." . PHP_EOL;
    }
}
?>
