#!/bin/sh

sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output1.job ./memory.sh 0.01
sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output2.job ./memory.sh 0.1
sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output3.job ./memory.sh 0.5
#sbatch --job-name=m_calc --time=1:30:00 -n 1 -p single -N  1 --output=output4.job ./memory.sh 1
sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output5.job ./memory.sh 5
sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output1.job ./memory.sh 10
#sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output2.job ./memory.sh 0.02
#sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output3.job ./memory.sh 0.04
#sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output4.job ./memory.sh 0.005
#sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output5.job ./memory.sh 0.06
#sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output1.job ./memory.sh 0.008
#sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output2.job ./memory.sh 0.08

#sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output5.job ./memory.sh 0.001
#sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output1.job ./memory.sh 0.00075
#sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output2.job ./memory.sh 0.0005
#sbatch --job-name=m_calc --time=9:30:00 -n 1 -p single -N  1 --output=output2.job ./memory.sh 0.0003


