@echo off

cd /D "%~dp0"



IF exist "P:\testHlyl\" (
	echo Removing existing link P:\testHlyl
	rmdir "P:\testHlyl\"
)

echo Creating link P:\testHlyl
mklink /J "P:\testHlyl\" "%cd%\testHlyl\"

echo Done