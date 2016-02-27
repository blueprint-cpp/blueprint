#!/bin/bash

pushd $(dirname $0) > /dev/null

./clean.sh
./build.sh

popd > /dev/null
