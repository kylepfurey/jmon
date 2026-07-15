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
if not exist "%INTERMEDIATE%\rom" mkdir "%INTERMEDIATE%\rom"

:: Compile source
%COMPILE% %INTERMEDIATE%\main.o %SOURCE%\main.c
%COMPILE% %INTERMEDIATE%\render.o %SOURCE%\render.c
%COMPILE% %INTERMEDIATE%\sprite.o %SOURCE%\sprite.c
%COMPILE% %INTERMEDIATE%\color.o %SOURCE%\color.c
%COMPILE% %INTERMEDIATE%\input.o %SOURCE%\input.c
%COMPILE% %INTERMEDIATE%\audio.o %SOURCE%\audio.c
%COMPILE% %INTERMEDIATE%\save.o %SOURCE%\save.c
%COMPILE% %INTERMEDIATE%\rom\string.o %SOURCE%\rom\string.c
%COMPILE% %INTERMEDIATE%\rom\sprite.o %SOURCE%\rom\sprite.c
%COMPILE% %INTERMEDIATE%\rom\color.o %SOURCE%\rom\color.c
%COMPILE% %INTERMEDIATE%\rom\audio.o %SOURCE%\rom\audio.c

:: Link objects
%GBDK%\lcc -msm83:gb -Wm-yo128 -Wm-ya4 -Wm-yt0x10 -Wm-yC -Wm-yn"Jokemon" -o %BUILD%\jmon.gb ^
%INTERMEDIATE%\main.o                                                                       ^
%INTERMEDIATE%\render.o                                                                     ^
%INTERMEDIATE%\sprite.o                                                                     ^
%INTERMEDIATE%\color.o                                                                      ^
%INTERMEDIATE%\input.o                                                                      ^
%INTERMEDIATE%\audio.o                                                                      ^
%INTERMEDIATE%\save.o                                                                       ^
%INTERMEDIATE%\rom\string.o                                                                 ^
%INTERMEDIATE%\rom\sprite.o                                                                 ^
%INTERMEDIATE%\rom\color.o                                                                  ^
%INTERMEDIATE%\rom\audio.o

:: Log success
echo Build successful! See "%BUILD%\jmon.gb".
