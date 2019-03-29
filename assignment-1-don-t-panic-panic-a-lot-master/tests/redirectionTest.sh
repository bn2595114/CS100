#!/bin/bash

./rshell <<< "cat < input.txt

echo hello > output.txt

echo world >> output.txt

cat < output.txt

echo replace this whole file with what i'm writing now > output.txt

cat < output.txt

cat < input.txt

cat < output.txt

exit
"
