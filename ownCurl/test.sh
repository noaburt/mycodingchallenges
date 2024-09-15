
#!/usr/bin/bash

: '

Coding Challenges | John Crickett

Author: Noa Burt
Date: 06/09/2024

This is the file to run all tests required of this coding challenge

 '

function runtest {

    # Simple function to format tests; arg 1 is test arguments, arg 2 is expected result, arg 3 is show tests [0 - no, 1 - yes]

    printf "\n ./cccurl %-70s | expecting: %40s\n" "$1" "$2"
    printf "I=================================================================="
    printf "===================================================================I\n"
    printf "$(./cccurl $1)\n"
}

make

if [ $? -ne 0 ]; then
    exit 1
fi

echo "Beginning testing..."

runtest "http://eu.httpbin.org/get" "Header contents only"
runtest "-v http://eu.httpbin.org/get" "Connection & header contents"
runtest "-X DELETE http://eu.httpbin.org/delete" "args, data, etc should be empty"
runtest "-X POST http://eu.httpbin.org/post"
