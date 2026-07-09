:: .bat
:: Jokémon Build Batch Script
:: by Kyle Furey
:: Requires Windows and gbdk-2020

@echo off

:: Set variables
set GBDK=extern\gbdk\bin
set BUILD=bin
set INTERMEDIATE=obj
set INCLUDE=include
set SOURCE=src\jmon
set COMPILE=%GBDK%\lcc -c -I%INCLUDE% -o

:: Make directories
if not exist "%BUILD%" mkdir "%BUILD%"
if not exist "%INTERMEDIATE%" mkdir "%INTERMEDIATE%"

:: Compile source
%COMPILE% %INTERMEDIATE%\main.o %SOURCE%\main.c

:: Link objects
%GBDK%\lcc -o %BUILD%\jmon.gb ^
              %INTERMEDIATE%\main.o

:: Log success
echo Build successful! See "%BUILD%\jmon.gb".
