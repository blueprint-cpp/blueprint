@echo off

pushd %~dp0

call "dependencies\premake\premake5.exe" vs2015

popd
