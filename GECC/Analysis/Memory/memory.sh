#!/bin/sh


module load devel/anaconda/3
python memory_script.py $1
module unload devel/anaconda/3
