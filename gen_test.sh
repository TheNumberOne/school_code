#/usr/bin/sh
shuf -i 1-$1 | tr '\n' ',' | head -c -1 > $2
