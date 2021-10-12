#!/bin/sh


sbatch --job-name=autoc --time=1:30:00 -n 1 -p single -N  1 --output=output2.job ./analysis_autoc.sh