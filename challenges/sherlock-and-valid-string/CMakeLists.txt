# Copyright (C) 2018 Albert Farres - All Rights Reserved
# You may use, distribute and modify this code under the terms of the MIT
# license, which unfortunately won't be written for another century.
#
# You should have received a copy of the MIT license with this file. If not,
# please write to: albertfc@gmail.com.

cmake_minimum_required(VERSION 2.8.11)

project(poc)

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS_DEBUG "-g -Wall -O0" )

# https://stackoverflow.com/a/40947954/3660282
# The additional / is important to remove the last character from the path.
# Note that it does not matter if the OS uses / or \, because we are only
# saving the path size.
string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)
add_definitions("-DSOURCE_PATH_SIZE=${SOURCE_PATH_SIZE}")

# Make libcommon visible
#include_directories( "${PROJECT_SOURCE_DIR}/common" )
#add_subdirectory( common )

# Tell CMake to create the executable
add_executable(main sherlock-and-valid-string.cpp)

# linker
#target_link_libraries(poc common)
