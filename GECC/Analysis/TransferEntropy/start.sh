#!/bin/sh

sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output1.job ./te.sh 0.01 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output2.job ./te.sh 0.1 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output3.job ./te.sh 0.5 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output4.job ./te.sh 1 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output5.job ./te.sh 5 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output6.job ./te.sh 10 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output7.job ./te.sh 0.02 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output8.job ./te.sh 0.04 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output9.job ./te.sh 0.005 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output10.job ./te.sh 0.06 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output11.job ./te.sh 0.008 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output12.job ./te.sh 0.08 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output13.job ./te.sh 0.001 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output14.job ./te.sh 0.00075 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output15.job ./te.sh 0.0005 $1
sbatch --job-name=TE_calc --time=24:00:00 -n 1 -p single -N  1 --output=output16.job ./te.sh 0.0003 $1



