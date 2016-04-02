@echo off

pushd %~dp0

call "setup-llvm.bat"
call "setup-premake.bat"
call "setup-sqlite.bat"

popd
