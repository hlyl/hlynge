@echo off

CALL Exit.bat

cd /D "%~dp0"

set /a failed=0

set modName=
set modPath=

if exist ../../user.cfg (
	echo HLYL Found the user.cfg
) else (
	echo Failed to find the user.cfg file, exitting.
	set /a failed=1
)

for /f "delims=" %%a in ('call ExtractData.bat dummy.cfg ../../user.cfg ModName') do (
    set modName=%%a
)

echo %modName%
set modPath=%modName:~1%
echo %modPath%


if exist ../../%modPath%/project.cfg (
	echo HLYL Found the project.cfg
	
) else (
	echo Failed to find the project.cfg file, exitting.
	set /a failed=1
)

if %failed%==1 (
	endlocal

	echo Failed to package the mod.
	goto:eof
)

set serverProfileDirectory=

for /f "delims=" %%a in ('call ExtractData.bat ../../%modPath%/project.cfg ../../user.cfg ServerProfileDirectory') do (
	set serverProfileDirectory=%%a
)

echo ServerProfileDirectory is: "%serverProfileDirectory%"
if "%serverProfileDirectory%"=="" (
	set /a failed=1
	echo ServerProfileDirectory parameter was not set in the project.cfg
)

if %failed%==1 (
	endlocal

	echo Failed to package the mod.
	goto:eof
)

del /s /q /f %serverProfileDirectory%\*.rpt
del /s /q /f %serverProfileDirectory%\*.log
del /s /q /f %serverProfileDirectory%\*.mdmp
del /s /q /f %serverProfileDirectory%\*.ADM

del /s /q /f %localappdata%\DayZ\*.rpt
del /s /q /f %localappdata%\DayZ\*.log
del /s /q /f %localappdata%\DayZ\*.mdmp
del /s /q /f %localappdata%\DayZ\*.ADM

del /s /q /f "%localappdata%\DayZ Exp\*.rpt"
del /s /q /f "%localappdata%\DayZ Exp\*.log"
del /s /q /f "%localappdata%\DayZ Exp\*.mdmp"
del /s /q /f "%localappdata%\DayZ Exp\*.ADM"