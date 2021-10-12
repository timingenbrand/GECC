#!/bin/sh

make out=snm.exe target

for i in {0..9}
do
  ran=$RANDOM
  echo "Run number $i, vol $1"
  sbatch --job-name=snm_$i --time=30:00:00 -n 1 -p single -N 1 --output=outputs/out$i.job ./run.sh $i $ran $1
done