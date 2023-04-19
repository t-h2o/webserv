<?php
$test_cases = [
    ["key" => "AUTH_TYPE", "expected_value" => "Basic"],
    ["key" => "NON_EXISTENT_KEY", "expected_value" => ""]
];

foreach ($test_cases as $test_case) {
    $env_key = $test_case["key"];
    $expected_value = $test_case["expected_value"];
    $actual_value = exec('./webserv ' . escapeshellarg($env_key));

    if ($actual_value === $expected_value) {
        echo "Test case for key '$env_key' passed." . PHP_EOL;
    } else {
        echo "Test case for key '$env_key' failed. Expected: '$expected_value', Actual: '$actual_value'." . PHP_EOL;
    }
}
?>
38c6f45
acacffb