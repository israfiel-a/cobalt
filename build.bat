:: Build script for the Cobalt operating system.
:: Simple in nature, basically a stripped Makefile.
@echo off

echo ---
echo CobaltOS simple compile script (Unix/Linux).
echo Copyright (c) Israfil Argos 2025
echo ---
echo: 

echo|set /p=Making sure CWD is correct...
cd /D "%~dp0"
echo correct.
echo Building into '.\build'.
md "build" "build\kernel" 2>NUL
echo:

echo|set /p=Checking NASM...
where nasm 1>NUL
if %ERRORLEVEL% NEQ 0 (
    echo:
    echo NASM is not installed properly on this system.
    echo Please install NASM and re-run the build script.
    echo:
    exit /b 1
)
echo found.

echo|set /p=Checking OSCDIMG...
where oscdimg 1>NUL
if %ERRORLEVEL% NEQ 0 (
    echo:
    echo The Windows APK is not installed properly on this system.
    echo Please install the Windows APK and re-run the build script.
    echo:
    exit /b 1
)
echo found.
echo:

echo Compiling bootloader...
echo - bootloader.asm
nasm bootloader.asm -f bin -o .\build\bootloader.bin
echo Done.
echo:

echo Creating disc image.
:: Check for this instead of blind usage.
oscdimg -d -n -w4 -b.\build\bootloader.bin .\build .\build\cobalt.iso 1>NUL
echo Done. Thank you.
echo:

:: bochs -f bochs_config
qemu-system-i386 -cdrom .\build\cobalt.iso -boot d -m 512
