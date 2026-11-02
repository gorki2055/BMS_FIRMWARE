@echo off
setlocal enabledelayedexpansion

echo ========================================================
echo Running Ghidra Headless Auto-Analysis on BMS Firmware
echo ========================================================
echo.

:: 1. Ensure JAVA_HOME is configured for JDK 21/25+
if not defined JAVA_HOME (
    for /d %%J in ("C:\Program Files\Eclipse Adoptium\jdk-25*" "C:\Program Files\Java\jdk-25*" "C:\Program Files\Eclipse Adoptium\jdk-21*") do (
        if exist "%%J\bin\java.exe" (
            set "JAVA_HOME=%%J"
            set "PATH=%%J\bin;!PATH!"
        )
    )
)

if defined JAVA_HOME (
    echo [+] Using Java at: "%JAVA_HOME%"
) else (
    echo [!] Warning: JAVA_HOME not detected. Ghidra will attempt system default.
)

:: 2. Locate Ghidra installation
set GHIDRA_HEADLESS=

if defined GHIDRA_HOME (
    if exist "%GHIDRA_HOME%\support\analyzeHeadless.bat" set GHIDRA_HEADLESS=%GHIDRA_HOME%\support\analyzeHeadless.bat
)

if not defined GHIDRA_HEADLESS (
    for /d %%D in (
        "C:\ProgramData\chocolatey\lib\ghidra\tools\ghidra*"
        "C:\ProgramData\chocolatey\lib\ghidra*"
        "C:\tools\ghidra*"
        "D:\tools\ghidra*"
    ) do (
        if exist "%%D\support\analyzeHeadless.bat" set GHIDRA_HEADLESS=%%D\support\analyzeHeadless.bat
    )
)

if not defined GHIDRA_HEADLESS (
    echo [ERROR] Could not find Ghidra installation.
    pause
    exit /b 1
)

echo [+] Found Ghidra at: "%GHIDRA_HEADLESS%"
echo.

:: 3. Resolve clean absolute paths without trailing slashes or relative dots
pushd "%~dp0.."
set "ROOT_DIR=%CD%"
popd

set "PROJECT_DIR=%ROOT_DIR%\ghidra_project"
set "SCRIPTS_DIR=%ROOT_DIR%\scripts"
set "IHEX_FILE=%ROOT_DIR%\output\firmware_app_0x08008000.ihex"

if not exist "%PROJECT_DIR%" mkdir "%PROJECT_DIR%"

echo [+] Project Directory : "%PROJECT_DIR%"
echo [+] Firmware Image    : "%IHEX_FILE%"
echo [+] Scripts Directory : "%SCRIPTS_DIR%"
echo.
echo Running analysis... This may take 1-2 minutes.
echo.

call "%GHIDRA_HEADLESS%" "%PROJECT_DIR%" BMS_Project -overwrite -import "%IHEX_FILE%" -processor "ARM:LE:32:Cortex" -cspec "default" -scriptPath "%SCRIPTS_DIR%" -preScript "GhidraSetupBms.java"

echo.
echo ========================================================
echo Headless Analysis Complete!
echo You can now open the project in Ghidra GUI:
echo Project Path: %PROJECT_DIR%\BMS_Project.gpr
echo ========================================================
pause
