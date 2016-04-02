#!/bin/bash

if [[ $(uname) == "Darwin" ]]; then

    packages="llvm38"

    echo brew install $packages
    brew install $packages
    echo -en "\n"

elif [[ -z ${TRAVIS} ]]; then

    packages="clang-3.8 libclang-3.8-dev"

    echo apt-get install $packages
    sudo apt-get -yq --force-yes install $packages
    echo -en "\n"

fi
