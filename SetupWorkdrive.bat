@echo off

cd /D "%~dp0"



IF exist "P:\DaySEditor\" (
	echo Removing existing link P:\DaySEditor
	rmdir "P:\DaySEditor\"
)

Rem echo Creating link P:\DayZEditor
Rem  mklink /J "P:\DayZEditor\" "%cd%\DayZEditor\"

echo Done