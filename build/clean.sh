#!/bin/bash

pushd $(dirname $0) > /dev/null

if [[ -d "gmake" ]]; then
    rm -f -R gmake
fi

if [[ -d "../output" ]]; then
    rm -f -R ../output
fi

popd > /dev/null
