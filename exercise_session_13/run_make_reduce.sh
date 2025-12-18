#!/bin/bash
set -e

cat trump_tweets_*.csv\
| ./mapper3.py \
| sort \
| ./reducer3.py \
> local_wordcount.txt



