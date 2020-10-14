@echo off

cd /D "%~dp0"



IF exist "P:\Bounty_fix\" (
	echo Removing existing link P:\Bounty_fix
	rmdir "P:\Bounty_fix\"
)

 echo Creating link P:\Bounty_fix
 mklink /J "P:\Bounty_fix\" "%cd%\Bounty_fix\"

echo Done