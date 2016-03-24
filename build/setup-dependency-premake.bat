@echo off

pushd %~dp0

if not exist "dependencies" (mkdir "dependencies")
cd dependencies

set premake_url="https://github.com/premake/premake-core/releases/download/v5.0.0-alpha8/premake-5.0.0-alpha8-windows.zip"
set premake_file="premake-5.0.0-alpha8-windows.zip"
set premake_dir="premake"

if not exist %premake_file% (wget --no-check-certificate %premake_url%)

if not exist %premake_dir% (
    7z x -r -o%premake_dir% %premake_file%
)

popd
