@echo off

pushd %~dp0

if not exist "dependencies" (mkdir "dependencies")
cd dependencies

set llvm_url="http://llvm.org/releases/3.8.0/LLVM-3.8.0-win64.exe"
set llvm_file="LLVM-3.8.0-win64.exe"
set llvm_dir="llvm"

if not exist %llvm_file% (wget --no-check-certificate %llvm_url%)

if not exist %llvm_dir% (
    7z x -r %llvm_file% $_OUTDIR

    rename $_OUTDIR %llvm_dir%
)

popd
