@echo off

CALL Exit.bat

cd /D "%~dp0"

set /a failed=0

if exist ../project.cfg (
	echo Found the project.cfg
) else (
	echo Failed to find the project.cfg file, exitting.
	set /a failed=1
)

if exist ../user.cfg (
	echo Found the user.cfg
) else (
	echo Failed to find the user.cfg file, exitting.
	set /a failed=1
)

if %failed%==1 (
	endlocal

	echo Failed to package the mod.
	goto:eof
)

set serverProfileDirectory=
set serverDirectory=

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ServerProfileDirectory') do (
	set serverProfileDirectory=%%a
)

for /f "delims=" %%a in ('call ExtractData.bat ../project.cfg ../user.cfg ServerDirectory') do (
    set serverDirectory=%%a
)


echo ServerDirectory is: "%serverDirectory%"
if "%serverDirectory%"=="" (
    set /a failed=1
    echo ServerDirectory parameter was not set in the project.cfg
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
del /s /q /f %serverDirectory%%serverProfileDirectory%*.rpt
del /s /q /f %serverDirectory%%serverProfileDirectory%*.log
del /s /q /f %serverDirectory%%serverProfileDirectory%*.mdmp
del /s /q /f %serverDirectory%%serverProfileDirectory%*.ADM

del /s /q /f %localappdata%\DayZ\*.rpt
del /s /q /f %localappdata%\DayZ\*.log
del /s /q /f %localappdata%\DayZ\*.mdmp
del /s /q /f %localappdata%\DayZ\*.ADM

del /s /q /f "%localappdata%\DayZ Exp\*.rpt"
del /s /q /f "%localappdata%\DayZ Exp\*.log"
del /s /q /f "%localappdata%\DayZ Exp\*.mdmp"
del /s /q /f "%localappdata%\DayZ Exp\*.ADM"

cmd /k