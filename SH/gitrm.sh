#!/bin/bash

dir='/home/'`whoami`'/Github/TRASH/'`date +%F`

if [ ! -e $dir ]
then
	mkdir -p $dir
fi

for arg in $*
do 
    file=$arg'_'`date +%T`
    mv $arg $file
    mv $file $dir 
done

exit 0
