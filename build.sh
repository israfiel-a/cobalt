# Build script for the Cobalt operating system.
# Simple in nature, basically a stripped Makefile.
#!/bin/bash

echo "---"
echo "CobaltOS simple compile script (Unix/Linux)."
echo "Copyright (c) Israfil Argos 2025"
echo "---"
echo

echo "Making sure CWD is correct..."
SOURCE=${BASH_SOURCE[0]}
# Resolve $SOURCE until the file is no longer a symlink.
while [ -L "$SOURCE" ]; do
  DIR=$( cd -P "$( dirname "$SOURCE" )" 2>&1 > /dev/null && pwd )
  SOURCE=$(readlink "$SOURCE")
  # If $SOURCE was a relative symlink, we need to resolve it relative 
  # to the path where the symlink file was located.
  [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE
done
DIR=$( cd -P "$( dirname "$SOURCE" )" 2>&1 > /dev/null && pwd )
echo "In correct directory ('${DIR}')."
echo "Building into './build'."
mkdir -p ./build ./build/kernel
echo

echo "Checking NASM..."
if ! command -v nasm 2>&1 > /dev/null; then
    echo "NASM is not installed (properly) on this system."
    echo "Please install NASM and re-run the build script."
    echo
    exit 255
fi
echo "NASM found."
echo

echo "Compiling bootloader..."
echo "- bootloader.asm"
nasm bootloader.asm -f bin -o ./build/bootloader.bin
echo "Done."
echo

echo "Creating disc image."
dd status=noxfer conv=notrunc if=./build/bootloader.bin of=./build/cobalt.flp
echo "Done. Thank you."
echo

# bochs -f bochs_config
qemu-system-i386 -fda ./build/cobalt.flp
