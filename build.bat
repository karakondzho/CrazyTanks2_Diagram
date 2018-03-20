@echo off
cls

cl -nologo /EHsc -WX -W2 -Z7 crazytanks.cpp /link -incremental:no -opt:ref

IF %ERRORLEVEL% EQU 0 (echo.
                       echo Compilation finished successfully)
