@echo off
.\tools\premake\premake5.exe vs2022
if %ERRORLEVEL% neq	0 (
	pause
)