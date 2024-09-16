
#!/usr/bin/bash

: '

Coding Challenges | John Crickett

Author: Noa Burt
Date: 16/09/2024

This is the file to run all tests required of this coding challenge

 '

function runtest {

    # Simple function to format tests; arg 1 is test arguments, arg 2 is expected result

    printf "\n ./huff %-70s | expecting: %40s\n" "$1" "$2"
    printf "I=================================================================="
    printf "===================================================================I\n"
    printf "$(./huff $1)\n"
}

make

if [ $? -ne 0 ]; then
    exit 1
fi

echo "Beginning testing..."


