#!/bin/bash

#Issue a regular shell command
ls *

#Use a for loop
for i in `ls *`
do
  echo "$i.png"
done

#Loop over datafiles and call gnuplot
mkdir -p figures
for i in `ls *_*.dat`
do
  echo $i
  gnuplot -e "filename='$i'" -e "outputfile='figures/$i.png'" project.gplot
done
