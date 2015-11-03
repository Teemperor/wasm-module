#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Expected single directory as parameter"
fi

for f in "$1/*.wast"; do
    ./testsuite-converter "$f"
done