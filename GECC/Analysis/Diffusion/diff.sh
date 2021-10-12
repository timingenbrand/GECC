#!/bin/sh


module load devel/anaconda/3
source activate py38
python diffusion.py $1
conda deactivate
module unload devel/anaconda/3
