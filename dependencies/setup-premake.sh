#!/bin/bash

pushd $(dirname $0) > /dev/null

if [[ ! -d "store" ]]; then mkdir store; fi
cd store

premake_url="http://github.com/premake/premake-core/releases/download/v5.0.0-alpha8"
premake_dir="premake"

if [[ $(uname) == "Darwin" ]]; then
    premake_bin="premake-5.0.0-alpha8-macosx.tar.gz"
    download_mode="binary"
else
    premake_bin="premake-5.0.0-alpha8-linux.tar.gz"
    download_mode="source"

    echo apt-get install libssl-dev
    sudo apt-get -yq --force-yes install libssl-dev
    echo -en "\n"
fi

if [[ $download_mode == "binary" ]]; then

    if [[ ! -e $premake_bin ]]; then wget --no-check-certificate $premake_url/$premake_bin; fi

    if [[ ! -d $premake_dir ]]; then
        mkdir $premake_dir
        tar -xvf $premake_bin -C $premake_dir
    fi

else

    if [[ ! -d $premake_dir ]]; then mkdir $premake_dir; fi

    if [[ ! -d $premake_dir/premake-core ]]; then
        cd $premake_dir

        github=https://github.com/premake/premake-core.git
        branch=release

        git clone --depth=1 --recursive -b $branch --single-branch $github premake-core

        cd ..
    fi

    if [ ! -f $premake_dir/premake5 ]; then
        cd $premake_dir/premake-core

        if [[ $(uname) == "Darwin" ]]; then
            make -f Bootstrap.mak osx
        else
            make -f Bootstrap.mak linux
        fi

        cp bin/release/premake5 ..

        cd ../..
    fi

fi

popd > /dev/null
