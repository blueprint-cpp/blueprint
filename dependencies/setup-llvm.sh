#!/bin/bash

if [[ $(uname) == "Darwin" ]]; then

    package="llvm38"

    echo brew install $package
    brew install $package
    echo -en "\n"

    ln -sf /usr/local/Cellar/llvm38/3.8.0/lib/llvm-3.8/ store/llvm38

elif [[ -z ${TRAVIS} ]]; then

    packages="clang-3.8 libclang-3.8-dev"

    echo apt-get install $packages
    sudo apt-get -yq --force-yes install $packages
    echo -en "\n"

fi
