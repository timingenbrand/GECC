#!/bin/sh


module load devel/anaconda/3
python vd_analysis.py $1
module unload devel/anaconda/3
