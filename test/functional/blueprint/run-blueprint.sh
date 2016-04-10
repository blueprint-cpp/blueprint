#!/bin/bash

pushd $(dirname $0) > /dev/null

root=../../..

# build blueprint

$root/build/build.sh

if [[ $? -ne 0 ]]; then
    exit $?
fi

# run blueprint-premake

../common/run-blueprint-premake.sh

# run blueprint

blueprint=$root/output/bin/Debug/Blueprint
workspace=$root/build/blueprint/Blueprint.wks.json
outputdir=../../output/blueprint

$blueprint -l -f $workspace -o $outputdir

popd > /dev/null
