#!/bin/bash

pushd $(dirname $0) > /dev/null

../dependencies/store/premake/premake5 --version
../dependencies/store/premake/premake5 gmake

popd > /dev/null
