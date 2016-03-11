#!/bin/bash

pushd $(dirname $0) > /dev/null

# build blueprint

../../../build/build.sh

# run blueprint-premake

../common/run-blueprint-premake.sh

# run blueprint

blueprint=../../../output/bin/Debug/Blueprint
workspace=../../../build/blueprint/Blueprint.wks.json

$blueprint -l -f $workspace

popd > /dev/null
