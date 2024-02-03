@echo off

set CURRENT_DIR=%~dp0

@REM Check if config/env.bat exists
if not exist config\env.bat (
    echo config\env.bat not found.
    echo Please copy config\env_example.bat to config\env.bat and edit it.
    goto :EOF
)

@REM Load config/env.bat
call config\env.bat
@REM We create the build directory if it doesn't exist
if not exist %PROJECT_BUILD_DIR% mkdir %PROJECT_BUILD_DIR% 

echo [CMake] Generating project
cmake -S %PROJECT_DIR% -B %PROJECT_BUILD_DIR% -G %PROJECT_BUILD_GENERATOR% -A %PROJECT_BUILD_ARCH% ^
-DCMAKE_BUILD_TYPE=%PROJECT_BUILD_TYPE% ^
-DPROJECT_INCLUDE_DIR=%PROJECT_INCLUDE_DIR% ^
-DCMAKE_INSTALL_PREFIX=%PROJECT_BIN_DIR% ^
-DGLFW_DIR=%GLFW_DIR% ^
-DFREETYPE_DIR=%FREETYPE_DIR%


cd %PROJECT_BUILD_DIR%
echo [CMake] Building project
cmake --build . -j 8 --config %PROJECT_BUILD_TYPE% 
echo [CMake] Installing project
cmake --install . --config %PROJECT_BUILD_TYPE% 
cd %CURRENT_DIR%