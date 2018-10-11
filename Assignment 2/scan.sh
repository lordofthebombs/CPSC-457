#!/bin/bash
# Author: Bader Abbulwaseem
# UCID: 30023849
# Assignment 2
# Question 1
find . -type f -name "*"$1 -printf "%p %s\n"| sort -k2nr | head -$2 | awk '{x += $2; print $1" "$2} END {print "Total bytes: " x}'
