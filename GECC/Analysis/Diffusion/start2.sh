#!/bin/sh

sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 1
#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 1000
