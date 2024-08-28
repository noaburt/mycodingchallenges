
#!/usr/bin/bash

: '

Coding Challenges | John Crickett

Author: Noa Burt
Date: 22/08/2024

This is the file to run all tests required of this coding challenge

 '

function runtest {

    # Simple function to format tests; argument 1 is test arguments, argument 2 is expected result
    
    printf "\n> ./main %-50s | expecting: %40s" "$1" "$2"
    printf "$(./main $1)\n"
}

make

if [ $? -ne 0 ]; then
    exit 1
fi

echo "Beginning testing..."

runtest "-c ChallengeFiles/test.txt" "342190 ChallengeFiles/test.txt"
runtest "-l ChallengeFiles/test.txt" "7145 ChallengeFiles/test.txt"
runtest "-w ChallengeFiles/test.txt" "58164 ChallengeFiles/test.txt"
