#!/bin/bash

find . -type f -name "*"$1 -printf "%p %s\n"| sort -k2nr | head -$2 | awk '{x += $2; print $1" "$2} END {print "total bytes: " x}'
