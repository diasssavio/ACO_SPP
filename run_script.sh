#!/bin/bash
for i in instances/*.txt
do
	FILE=$(basename "$i" .txt)
	echo "Running $FILE..."
	for j in $(seq 10)
	do
		./ACO_SPP $i > logs/$FILE-$j.txt
		echo "$j...ok!"
	done
	echo "$FILE...ok!"
done
