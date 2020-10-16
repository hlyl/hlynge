@echo off

cd /D "%~dp0"



IF exist "P:\BountyHunter" (
Rem	echo Removing existing link P:\BountyHunter
	rmdir "P:\BountyHunter"
)

Rem echo Creating link P:\BountyHunter
Rem mklink /J "P:\BountyHunter\" "%cd%\BountyHunter\"

echo Done