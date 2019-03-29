#!/bin/bash

./rshell <<<  "test -e test/file/path
test -e src/
test -f src/
test -d src/
test -f src/main.cpp
test -e doesnotexist.cpp
test -e src/ && echo exists
test -e || echo does not exist
[src/]
[src/] && []
[] && [src/]
test -e src/ ; test -f src/ ;test -d src/
(ec && ec) || echo hello
(echo pass && echo pass) && echo pass
(fail && fail) && (fail && fail)
exit
"
