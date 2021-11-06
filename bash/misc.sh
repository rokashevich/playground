#!/bin/bash
find ~ -type f -a -iname '*.txt' | while read filename
do echo "-->$filename"; done
