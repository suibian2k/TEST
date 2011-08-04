#!/bin/bash

Hide='.'
Dat='_vimdat'
Temp=$Hide$Dat
nfile=
sfile=
cfile=

for arg in $*
do
    if [ ! -e $arg ]
    then
        nfile=$nfile$arg' '
    else
        sfile=$sfile$arg' '
    fi    
done

for arg in $sfile
do
    cat $arg > $Hide$arg$Dat    
done

vim $*

for arg in $nfile
do
    if [ -e $arg ]
    then
        echo $nfile
        cfile=$cfile$arg'\'
        git add $arg 
    fi
done

for arg in $sfile
do
    diff $arg  $Hide$arg$Dat > $Temp
    if [ $? != 0 ]
    then
        cfile=$cfile$arg'\'
    fi
done

if [ "$cfile" != "" ]
then
    git ci $cfile
fi
