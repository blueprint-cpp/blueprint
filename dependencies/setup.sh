#!/bin/bash

pushd $(dirname $0) > /dev/null

if [[ $(uname) == "Darwin" ]]; then
    echo brew update
    brew update
    echo -en "\n"
fi

./setup-premake.sh
./setup-sqlite.sh skip-update
./setup-llvm.sh   skip-update

popd > /dev/null
