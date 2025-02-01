# Build script for the Cobalt operating system.
# Simple in nature, basically a stripped Makefile.
#!/bin/bash

echo
echo "=================================================="
echo "|| CobaltOS simple compile script (Unix/Linux). ||"
echo "||       Copyright (c) Israfil Argos 2025       ||"
echo "=================================================="
echo

# resolve_cwd
# Resolve the current working directory to the one we need for
# proper file operations.
# Parameters:
#   N/A
resolve_cwd() {
    echo -n "Making sure CWD is correct..."

    local SOURCE=${BASH_SOURCE[0]}
    local DIR=""
    # Resolve $SOURCE until the file is no longer a symlink.
    while [ -L "$SOURCE" ]; do
        DIR=$( cd -P "$( dirname "$SOURCE" )" 2>&1 > /dev/null && pwd )
        SOURCE=$(readlink "$SOURCE")
        # If $SOURCE was a relative symlink, we need to resolve it relative 
        # to the path where the symlink file was located.
        [[ $SOURCE != /* ]] && SOURCE=$DIR/$SOURCE
    done
    DIR=$( cd -P "$( dirname "$SOURCE" )" 2>&1 > /dev/null && pwd )

    echo "correct: $DIR"
}

# confirm
# Confirm whether or not the user wants to continue.
# Parameters:
#   1: Confirmation message.
confirm() {
    read -r -p "$1 " response
    case "$response" in
        [yY][eE][sS]|[yY]) 
            true
            ;;
        *)
            false
            ;;
    esac
}

# check_command
# Check the existence of a command on the system.
# Parameters:
#   1: The name of the command to check for.
check_command() {
    echo -n "Checking $1..."
    if ! command -v $1 2>&1 > /dev/null; then
        echo
        echo
        echo "$1 is not properly installed on this system."
        echo "Please (re)install $1 and re-run the build script."
        echo
        exit 255
    fi
    echo "found."
}

# check_build
# Check to see if the build folder exists already, in which
# case we need to delete it.
# Parameters:
#   N/A
check_build() {
    if [ -d build ] && ! confirm "Build folder already exists, overwrite it? (y/N)"; then
        echo
        echo "The program cannot continue without a build folder."
        echo "Please remedy this situation manually."
        echo
        exit 255
    elif [ -d build ]; then
        rm -rf build
    fi
}

# compile_file
# Compile a given assembly file into a flat binary.
# Parameters:
#   1: Name of file.
#   2: Output name of file.
compile_file() {
    echo "$1 --> $2"
    nasm $1 -f bin -o $2
}

resolve_cwd
echo

check_command "mkdir"
check_command "mkisofs"
check_command "nasm"
echo

echo "Building into \"build\"."
check_build
mkdir build build/kernel

compile_file bootloader/bootloader.asm build/bootloader.bin

echo
echo -n "Creating disk image..."
mkisofs --no-emul-boot -quiet -V "CobaltOS"     \
    -b bootloader.bin -o build/cobalt.iso build
echo "done."
echo

echo "Thank you."
echo

qemu-system-x86_64 -cdrom ./build/cobalt.iso
