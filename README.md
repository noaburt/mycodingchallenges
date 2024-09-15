
# My Coding Challenges

This is a place for me to store my attempts and solutions to John Crickett's Coding Challenges

These are found at https://codingchallenges.fyi/challenges/


## Trying for yourself

Each coding challenge folder has it's own Makefile and automated testing script

The automated tests are based on each coding challenge's "steps"

### Automated tests
Run ```chmod +x test.sh``` and then ```./test.sh``` to run the automated tests

### User tests
Some coding challenges are basically a command line tool, this means user tests can be run too

Run ```make``` in the chosen challenge folder, for example 'cccurl', the 'Build Your Own curl' challenge

Interact with the compiled binary, in this example ```./cccurl```, as with any other CLI tool

Every challenge that allows for user interaction will support ```--help / -h```
