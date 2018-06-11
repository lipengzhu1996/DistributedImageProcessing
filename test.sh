#! /bin/bash

hdfs dfs -rm -r ./output

hadoop jar $HADOOP_HOME/share/hadoop/tools/lib/hadoop-streaming*.jar \
-files mapper.py,reducer.py \
-mapper mapper.py \
-reducer reducer.py \
-input /user/hadoop/data.txt -output /user/hadoop/output


