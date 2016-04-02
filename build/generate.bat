@echo off

pushd %~dp0

call "..\dependencies\store\premake\premake5.exe" vs2015

popd
