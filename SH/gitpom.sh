#!/bin/bash

Gdir=/home/`whoami`/Github
Fdir=`ls $Gdir`

for arg in $Fdir
do
   cd $Gdir$arg
   git add *
   git commit -a -m  `date +%F%T` 
   git push origin master
done
