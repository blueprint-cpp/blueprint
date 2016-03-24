@echo off

pushd %~dp0

if not exist "dependencies" (mkdir "dependencies")
cd dependencies

set sqlite_src_url="https://www.sqlite.org/2016/sqlite-amalgamation-3110100.zip"
set sqlite_bin_url="https://www.sqlite.org/2016/sqlite-dll-win64-x64-3110100.zip"

set sqlite_src_file="sqlite-amalgamation-3110100.zip"
set sqlite_bin_file="sqlite-dll-win64-x64-3110100.zip"

set sqlite_dir="sqlite"

if not exist %sqlite_src_file% (wget --no-check-certificate %sqlite_src_url%)
if not exist %sqlite_bin_file% (wget --no-check-certificate %sqlite_bin_url%)

if not exist %sqlite_dir% (
    7z e -r -o%sqlite_dir%\include %sqlite_src_file% *.h
    7z x -r -o%sqlite_dir%\lib     %sqlite_bin_file%
)

if not exist %sqlite_dir%\lib\sqlite3.lib (
    call "%VS140COMNTOOLS%\vsvars32.bat"

    cd sqlite\lib
    lib /def:sqlite3.def /out:sqlite3.lib /MACHINE:x64
    cd ..\..
)

popd
