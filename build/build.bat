@echo off

premake5 vs2015

pushd %cd%
cd vs2015
call "%VS140COMNTOOLS%\vsvars32.bat"
devenv Blueprint.sln /Build Debug
popd
