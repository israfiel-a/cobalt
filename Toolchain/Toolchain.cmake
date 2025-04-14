####################################################################
## PROJECT TOOLCHAIN
## SINCE 0.1.0
## UPDATED 0.1.0
## This file contains the definition for the toolchain CMake will
## use to take the OS from source to binary. It includes
## definitions for things like the compiler and linker.
##
## Copyright (c) 2025 Israfil Argos
## This file is under the AGPLv3. For information on what that 
## entails, see the attached LICENSE.md file or 
## https://www.gnu.org/licenses/agpl-3.0.en.html.
####################################################################

set(CMAKE_SYSTEM_NAME "Generic") ## NO UNDERLYING OS!
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER x86_64-elf-gcc)
set(CMAKE_LINKER x86_64-elf-ld)
set(CMAKE_OBJCOPY x86_64-elf-objcopy)

set(CMAKE_C_COMPILER_TARGET x86_64-none-elf)
set(CMAKE_C_FLAGS "-ffreestanding -fpic -fno-stack-protector     \
    -fshort-wchar -mno-red-zone -Wall -Wextra -Werror -Wpedantic \
    -Ofast -mgeneral-regs-only -mabi=ms")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -shared                    \
    -Wl,-T,${CMAKE_SOURCE_DIR}/Toolchain/Linkscript.lds          \
    -Wl,-Bsymbolic -Wl,-znocombreloc")
