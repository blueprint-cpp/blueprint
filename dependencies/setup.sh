#!/bin/bash

pushd $(dirname $0) > /dev/null

./setup-premake.sh

popd > /dev/null
