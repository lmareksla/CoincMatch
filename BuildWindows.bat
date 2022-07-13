@ECHO OFF
SET BUILD_DIR="_Build"
SET MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\amd64\MSBuild.exe"

SET ARG_COUNT=0
FOR %%X IN (%*) DO (
   SET /A ARG_COUNT+=1
)

IF %ARG_COUNT% LSS 1 (
   ECHO. 
   ECHO "Usage %0 [clean][debug|release]"
   ECHO.
   GOTO :EOF
)

SETLOCAL enabledelayedexpansion
SETLOCAL enableextensions

SET DO_CLEAN=false
SET DO_TEST=false
SET RELEASE=
SET OUT_DIR=

FOR %%X IN (%*) DO (
    IF [%%X] == [clean] (
        SET DO_CLEAN=true
    ) ELSE (
    IF [%%X] == [debug] (
        SET RELEASE=Debug
        SET OUT_DIR=Debug
    ) ELSE (
    IF [%%X] == [release] (
        SET RELEASE=Release
        SET OUT_DIR=Release
        ECHO "Releas is not supported"
        GOTO :EOF
    ) ELSE (
    IF [%%X] == [test] (
         SET DO_TEST=true
    ) ELSE (
       ECHO "Option %%X not recognized."
       GOTO :EOF
    ) ) ) )   
)

IF [%DO_CLEAN%] == [true] (
   ECHO Cleaning build directory...
   IF EXIST %BUILD_DIR%\install_manifest.txt ( 
      CD %BUILD_DIR%
      FOR /f "delims=" %%F IN (install_manifest.txt) DO (
         SET OLD=%%F
         SET R=!OLD:/=\!
         DEL !R!
      )
      CD ..   
   )
   RMDIR /s /q %BUILD_DIR%
)

IF NOT [%RELEASE%] == [] (
      if NOT EXIST %BUILD_DIR% (
         MKDIR %BUILD_DIR%   
      )
      CD %BUILD_DIR%
      ECHO %RELEASE%
      cmake .. -DCMAKE_INSTALL_PREFIX=..  -DBLD_DIR=%BUILD_DIR% -DCMAKE_BUILD_TYPE=%RELEASE% -A x64
      %MSBUILD% -m /p:Configuration=%RELEASE% GenFunc.sln
      %MSBUILD% /P:Configuration=%RELEASE% INSTALL.vcxproj
)      

IF [%DO_TEST%] == [true] (
   ECHO Running Tests...
   CD ..
   echo %BUILD_DIR%\%OUT_DIR%
   python tests\tests.py -b %BUILD_DIR%\%OUT_DIR%
)
