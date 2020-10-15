@echo off

cd /D "%~dp0"



IF exist "P:\Master\" (
	echo Removing existing link P:\Master
	rmdir "P:\Master\"
)

 echo Creating link P:\Master
  mklink /J "P:\Master\" "%cd%\Master\"

echo Done