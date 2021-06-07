@echo off
set CommonCompilerFlags=-diagnostics:column -MTd -nologo -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4456 -wd4505 -FAsc -Z7 -utf-8
set CommonLinkerFlags=-incremental:no -opt:ref user32.lib

IF NOT EXIST ..\build mkdir ..\build
IF NOT EXIST ..\rundata mkdir ..\rundir
pushd ..\build

REM 64-bit build
cl %CommonCompilerFlags% ..\code\main.cpp -Fmmain.map /link %CommonLinkerFlags%
popd

