#!/bin/sh
make test
valgrind --leak-check=full --show-leak-kinds=all test/test 2> result.valgrind 1> /dev/null
