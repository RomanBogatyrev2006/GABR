@echo off
setlocal enabledelayedexpansion

echo STAGE 1: Checking for CMake...
where cmake >nul 2>nul
if %errorlevel% neq 0 (
	echo Error: CMake not found in PATH!
	echo Please install CMake or add it to your system PATH
	pause
	exit /b 1
)
echo STAGE 1 DONE!

echo STAGE 2: Creating build directory...
if not exist "build" (
	mkdir build
)

cd build

echo STAGE 2: and cleaning previous configuration...
if exist "CMakeCache.txt" (
	del CMakeCache.txt
)
if exist "CMakeFiles" (
	rmdir /s /q CMakeFiles
)
echo STAGE 2 DONE!

echo STAGE 3: configuration project with CMake...
cmake ..

if %errorlevel% neq 0 (
	echo CMake configuration failed!
	echo Please check your CMake installation and project configuration
	pause
	exit /b 1
)
echo STAGE 3 DONE!

echo Configuration completed successfully!
echo You can now open the generated solution file in the build directory
cd ..
pause