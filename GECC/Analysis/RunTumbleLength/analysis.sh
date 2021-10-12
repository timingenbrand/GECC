#!/bin/sh


module load devel/anaconda/3
python avg_runlength.py $1 $2
module unload devel/anaconda/3
