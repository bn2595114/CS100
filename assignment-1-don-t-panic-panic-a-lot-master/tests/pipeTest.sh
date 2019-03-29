#!/bin/bash

./rshell <<< "cat input.txt | tr a-z A-Z

cat input.txt

ls | tail | tr a-z A-Z

input.txt | tr A-Z a-z | tee newfile

exit
"
