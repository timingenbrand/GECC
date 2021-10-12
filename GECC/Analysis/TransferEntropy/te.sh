#!/bin/sh


module load devel/anaconda/3
source activate py38
python te_kraskov.py $1 $2
conda deactivate
module unload devel/anaconda/3
