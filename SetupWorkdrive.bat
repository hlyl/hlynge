@echo off

cd /D "%~dp0"



IF exist "P:\BountyHunter\" (
	echo Removing existing link P:\BountyHunter
	rmdir "P:\BountyHunter\"
)

 echo Creating link P:\BountyHunter
  mklink /J "P:\BountyHunter\" "%cd%\BountyHunter\"

echo Done