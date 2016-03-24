@echo off

pushd %~dp0

call "setup-dependency-llvm.bat"
call "setup-dependency-premake.bat"

popd
