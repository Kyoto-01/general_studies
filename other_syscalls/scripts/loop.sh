#!/bin/bash

function handler {
	echo "ADIÓS!!"
	exit 0
}

trap "handler" 2

i=0
while true; do
	echo "($i) MAMA MIA!"
	sleep .5
	i=$(( i + 1 ))
done
