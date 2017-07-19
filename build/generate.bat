@echo off

pushd %~dp0

call "..\dependencies\store\premake\premake5.exe" %1

popd
