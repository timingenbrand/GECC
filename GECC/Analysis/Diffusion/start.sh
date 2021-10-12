#!/bin/sh


#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 0.000001
#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 0.00001
#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 0.0001
#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 0.001
#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 0.01
#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 0.1

#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 10
#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 100

sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 10000
sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 100000

#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 1
#sbatch --job-name=diff_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./diff.sh 1000



