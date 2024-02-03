@REM File: config\env.bat
@REM This file is used by build.bat to set up the build environment.

set "MAIN_DIR=%cd%"

@REM Compilation settings
set PROJECT_BUILD_TYPE=Debug
set PROJECT_BUILD_ARCH=x64
set PROJECT_BUILD_GENERATOR="Visual Studio 17 2022"

@REM Project default architecture settings
set PROJECT_NAME=Mozarella
set PROJECT_BUILD_DIR=%MAIN_DIR%/build
set PROJECT_BIN_DIR=%MAIN_DIR%/bin 
set PROJECT_INCLUDE_DIR=%MAIN_DIR%/include
set PROJECT_DIR=%MAIN_DIR%

@REM Librairies
set GLFW_DIR=%MAIN_DIR%/lib/GLFW
set FREETYPE_DIR=%MAIN_DIR%/lib/freetype