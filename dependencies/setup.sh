#!/bin/bash

pushd $(dirname $0) > /dev/null

if [[ $(uname) == "Darwin" ]]; then

    echo brew update
    brew update
    echo -en "\n"

elif [[ -z ${TRAVIS} ]]; then

    echo "deb http://llvm.org/apt/wily/ llvm-toolchain-wily-3.8 main"     | sudo tee    /etc/apt/sources.list.d/llvm.list
    echo "deb-src http://llvm.org/apt/wily/ llvm-toolchain-wily-3.8 main" | sudo tee -a /etc/apt/sources.list.d/llvm.list
    echo -en "\n"

    echo apt-get update
    sudo apt-get update
    echo -en "\n"

fi

./setup-premake.sh
./setup-sqlite.sh
./setup-llvm.sh

popd > /dev/null
