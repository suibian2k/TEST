#!/bin/bash

file=./t1.sh

{
read line1
read line2
}<$file

echo "First line in $file is: "
echo "$line1"
echo "Second line in $file is: "
echo "$line2"

exit 0
