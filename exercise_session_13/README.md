Exercise 1
------------

Added an SSH config entry with port forwarding so the Hadoop web UIs are reachable locally. 

Started Hadoop services inside the VM:
start-dfs.sh (HDFS)
start-yarn.sh (YARN)

Files: run_make_reduce.sh, local_wordcount.txt

Exercise 2
-------------
1) Local  MapReduce
I ran a local MapReduce-style pipeline on the trump_tweets_*.csv files and saved the word counts to local_wordcount.txt.
This result is comparable to Hadoop streaming because both do the same “map → sort/group → reduce” logic.

2) HDFS input directory
Created a directory on HDFS called DonaldTrump and copied the CSV files into it. 

3) Hadoop Streaming run
Ran Hadoop Streaming using mapper3.py and reducer3.py on DonaldTrump/* and wrote results to output/. 
	Launched map tasks=7
	Launched reduce tasks=1
Lines treated: the input contained 35,370 total lines.

Hadoop created the HDFS output directory output/ containing:
output/_SUCCESS
output/part-00000

In the YARN UI (localhost:8088) I can see the application and its status, but the actual result file is stored in HDFS.

Files: hdfs_output/*

