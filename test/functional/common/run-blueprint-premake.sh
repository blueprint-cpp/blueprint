#!/bin/bash

# sync blueprint-premake

pushd $(dirname $0) > /dev/null

if [ ! -d "blueprint-premake" ]; then
    echo -en "\n"
    echo [ clone blueprint-premake ]
    echo -en "\n"

    github=https://github.com/eparayre/blueprint-premake.git
    git clone --depth=1 $github
else
    git pull
fi

popd > /dev/null

# run premake

premake=../../../build/buildtools-premake/bin/premake.sh
$premake blueprint
