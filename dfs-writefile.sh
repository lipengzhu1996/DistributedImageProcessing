#! /bin/bash

jps

hdfs dfs -rm -r ./data2.txt
hdfs dfs -rm -r ./output
hdfs dfs -put ./data2.txt ./
hdfs dfs -ls


