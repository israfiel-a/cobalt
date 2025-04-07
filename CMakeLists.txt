cmake_minimum_required(VERSION 4.0.0 FATAL_ERROR)
project("cobalt" LANGUAGES C VERSION 0.1.0
    DESCRIPTION "A toy x86_64 operating system written in NASM Assembly and C.")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/cobalt")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/cobalt")

add_link_options(-nostdlib -ffreestanding -e 0)
