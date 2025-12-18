#!/bin/bash
set -e

cat trump_tweets_*.csv\
| ./mapper.py \
| sort \
| ./reducer.py \
> local_wordcount.txt



