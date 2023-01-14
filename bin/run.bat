@echo off
@title Falcon is running

echo Current dir is %~dp0%
::cd /D %~dp0%\base
::Client.exe
%~dp0%\base\Client.exe

pause
