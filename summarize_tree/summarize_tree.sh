#!/bin/bash

echo "This is number of directories:" 
find $1 -type d -print | wc -l
echo "This is number of files:" 
find $1 -type f -print| wc -l
