@echo off
@title Qt Auto Packing up by Ed

::获取QT路径
IF NOT EXIST package.txt (
   setlocal EnableDelayedExpansion
   set /p var=Where is QT :
   ::echo !var! 
   echo !var!>>package.txt
   set /p qml=Where is Custom QML :
   ::echo !qml! 
   echo !qml!>>package.txt) ELSE (
      @echo off & setlocal enabledelayedexpansion
      set lineFlag=0
      for /f "delims=*" %%i in (package.txt) do (
         set /a lineFlag+=1
         if !lineFlag!==1 (
            set var=%%i
            echo !var!
         )
         if !lineFlag!==2 (
            set qml=%%i
            echo !qml!
         )
      )
   )

::QT的脚本，Qt\5.15.2\msvc2019\bin下的qtenv2.bat
echo Setting up environment for Qt usage...
::echo %var% 
set PATH=%var%\bin;%PATH%
cd /D %var%
::echo %PATH%
echo Remember to call vcvarsall.bat to complete environment setup!

::使用Qt命令自动抓取所依赖的环境，依次使用Falcon.exe和各个DLL生成依赖，DLL先复制到base，生成依赖后删除
echo Current dir is %~dp0%
cd /D %~dp0%\base
windeployqt -force Client.exe --qmldir %qml%
::%var%\qml
windeployqt -force Core.exe
windeployqt -force grSim.exe

::结束时可以暂停一下
pause
