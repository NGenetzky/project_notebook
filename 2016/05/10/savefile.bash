#!/bin/bash

# Assumes file is passed in as arg.
file=$1
sha1sum_out=$(sha1sum $file)
# Get the sha1 hash but leave filename
file_sha1=$(echo $sha1sum_out |  cut -d ' ' -f 1)
dest="./file/$file_sha1"
if [ -f "$dest" ]
then
    echo "File is already saved."
else
    cp $file $dest
    echo "cp $file $dest"
fi
