#!/bin/bash

# Convert spaces to tabs in src/
for file in $(ls src/)
do
	unexpand -t 4 src/$file > temp
	cat temp > src/$file
done

rm temp
