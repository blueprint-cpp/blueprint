@echo off

pushd %~dp0

if not exist "store" (mkdir "store")
cd store

set premake_url="http://github.com/premake/premake-core/releases/download/v5.0.0-alpha11/premake-5.0.0-alpha11-windows.zip"
set premake_file="premake-5.0.0-alpha11-windows.zip"
set premake_dir="premake"

if not exist %premake_file% (wget --no-check-certificate --no-verbose %premake_url%)

if not exist %premake_dir% (
    7z x -r -o%premake_dir% %premake_file%
)

popd
