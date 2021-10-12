#!/bin/sh

sbatch --job-name=runlength --time=40:00:00 -n 1 -p single -N  1 --output=output1.job ./analysis.sh 0 0.005

sbatch --job-name=runlength --time=40:00:00 -n 1 -p single -N  1 --output=output2.job ./analysis.sh 0 0.0005

sbatch --job-name=runlength --time=40:00:00 -n 1 -p single -N  1 --output=output3.job ./analysis.sh 0 0.02

sbatch --job-name=runlength --time=40:00:00 -n 1 -p single -N  1 --output=output4.job ./analysis.sh 1 0.005

sbatch --job-name=runlength --time=40:00:00 -n 1 -p single -N  1 --output=output5.job ./analysis.sh 1 0.0005

sbatch --job-name=runlength --time=40:00:00 -n 1 -p single -N  1 --output=output6.job ./analysis.sh 1 0.02

