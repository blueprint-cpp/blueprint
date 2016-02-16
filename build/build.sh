#!/bin/bash

./premake5 gmake

pushd gmake > /dev/null
make
popd > /dev/null
