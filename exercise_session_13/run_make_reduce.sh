#!/bin/bash
set -e

DATA_DIR="data"   

cat ${DATA_DIR}/* \
| ./mapper.py \
| sort \
| ./reducer.py \
> local_wordcount.txt
