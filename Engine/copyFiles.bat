@echo off

set solutiondir=%~1
set targetdir=%~2

MKDIR "%targetdir%res"
XCOPY "%solutiondir%res" "%targetdir%res" /E /Y /S
XCOPY "%solutiondir%Debug\Engine.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%libs\glew-2.1.0\bin\Release\Win32\glew32.dll" "%targetdir%" /E /Y /S