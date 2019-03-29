#!/bin/bash

./rshell <<< "echo brandon
 ls -a; echo hello || echo world; git status
 fail && fail
 echo brandon && echo bryan
 exit"
