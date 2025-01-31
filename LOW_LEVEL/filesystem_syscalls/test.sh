#!/bin/bash

# NOTE: You should have a ext4 media in /dev/sdb1

# setup test environment

sudo umount /dev/sdb1 &> /dev/null
sudo mount /dev/sdb1 /mnt &> /dev/null
sudo rm -rf /mnt/bob /mnt/fs_sys_test.txt &> /dev/null
sudo umount /dev/sdb1 &> /dev/null

# execute test

gcc main.c && sudo ./a.out
errno $?
