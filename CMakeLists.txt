####################################################################
## PROJECT CONFIGURATION FILE
## SINCE 0.1.0
## UPDATED 0.1.0
## This file contains the CMake script for compiling and linking
## the OS.
##
## Copyright (c) 2025 Israfil Argos
## This file is under the AGPLv3. For information on what that 
## entails, see the attached LICENSE.md file or 
## https://www.gnu.org/licenses/agpl-3.0.en.html.
####################################################################

cmake_minimum_required(VERSION 4.0.1 FATAL_ERROR)
project("Cobalt" LANGUAGES C VERSION 0.1.0 DESCRIPTION 
    "A toy text-based x86_64 operating system written in C.")

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Please supply CMake with the toolchain.")
endif()

####################################################################
## OUTPUT INITIALIZATION
####################################################################
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
# Create a commands.json file for analysis tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

####################################################################
## FLAG INITIALIZATION
####################################################################
set(CMAKE_C_STANDARD_REQUIRED YES)
set(CMAKE_C_STANDARD 23)

add_compile_definitions(EFI_FUNCTION_WRAPPER)

include_directories(/usr/include/efi /usr/include/efi/x86_64)

####################################################################
## TARGET INITIALIZATION
####################################################################
add_executable(${PROJECT_NAME} Source/Initialization.c)
target_link_libraries(${PROJECT_NAME} gcc)
