@echo off
setlocal enabledelayedexpansion

echo ========================================================
echo Exporting BMS Firmware Decompiled C Code
echo ========================================================

:: 1. Ensure JAVA_HOME is configured
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
    echo [!] Warning: JAVA_HOME not detected.
)

:: 2. Locate Ghidra installation
set GHIDRA_HEADLESS=
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
    exit /b 1
)

pushd "%~dp0.."
set "ROOT_DIR=%CD%"
popd

set "PROJECT_DIR=%ROOT_DIR%\ghidra_project"
set "SCRIPTS_DIR=%ROOT_DIR%\scripts"

echo [+] Project: "%PROJECT_DIR%\BMS_Project.gpr"
echo [+] Running Ghidra decompiler exporter...
echo.

call "%GHIDRA_HEADLESS%" "%PROJECT_DIR%" BMS_Project -process "firmware_app_0x08008000.ihex" -noanalysis -scriptPath "%SCRIPTS_DIR%" -postScript "ExportBmsDecompiled.java"

echo.
echo ========================================================
echo Export complete!
echo ========================================================
