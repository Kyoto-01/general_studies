#!/bin/bash

echo "abc" > test.txt

echo "========== BEFORE - test.txt =========="
cat test.txt | hexdump -c
echo "======================================="

echo -e "\n========== LOGS - a.out =========="
gcc main.c && ./a.out
echo "=================================="

echo -e "\n========== STATUS - system =========="
echo "exit status = $?" 
echo "directory status = $( ls -lh )"
echo "====================================="

echo -e "\n========== AFTER - test.txt =========="
cat test.txt | hexdump -c
echo "======================================"
