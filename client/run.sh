#!/bin/bash

scriptdir=$(realpath $(dirname $0))

if [ -n "$1" ]
then
LD_LIBRARY_PATH=${scriptdir}/../build/Debug/src/miaufts/ \
python3 ${scriptdir}/main.py "$@"
else
echo "angry miau"
fi