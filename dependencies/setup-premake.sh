#!/bin/bash

pushd $(dirname $0) > /dev/null

if [[ ! -d "store" ]]; then mkdir store; fi
cd store

premake_url="http://github.com/premake/premake-core/releases/download/v5.0.0-alpha8"
premake_src="premake-5.0.0-alpha8-src.zip"
premake_dir="premake"

if [[ $(uname) == "Darwin" ]]; then
    premake_bin="premake-5.0.0-alpha8-macosx.tar.gz"
    download_mode="binary"
else
    premake_bin="premake-5.0.0-alpha8-linux.tar.gz"
    download_mode="source"
fi

if [[ $download_mode == "binary" ]]; then

    if [[ ! -e $premake_bin ]]; then wget --no-check-certificate $premake_url/$premake_bin; fi

    if [[ ! -d $premake_dir ]]; then
        mkdir $premake_dir
        tar -xvf $premake_bin -C $premake_dir
    fi

else

    if [[ ! -e $premake_src ]]; then wget --no-check-certificate $premake_url/$premake_src; fi

    if [[ ! -d $premake_dir ]]; then
        mkdir $premake_dir
        tar -xvf $premake_src -C $premake_dir

        cd $premake_dir/premake-5.0.0-alpha8/build

        if [[ $(uname) == "Darwin" ]]; then
            cd gmake.macosx
        else
            cd gmake.unix
        fi

        make

        cp ../../..
    fi

    if [[ ! -e $premake_dir/premake5 ]]; then
        cp $premake_dir/premake-5.0.0-alpha8/bin/release/premake5 $premake_dir
    fi

fi

popd > /dev/null
