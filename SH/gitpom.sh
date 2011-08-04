#!/bin/bash

Gdir=/home/`whoami`/Github/
Fdir=`ls $Gdir`

for arg in $Fdir
do
   echo $Gdir$arg
   cd $Gdir$arg
   git add *
   git commit -a -m `date +%F`
   git push origin master
done
