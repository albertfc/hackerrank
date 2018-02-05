cmake_minimum_required(VERSION 2.8.11)

project(poc)

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_FLAGS_DEBUG "-g -Wall -O0" )

# Make libcommon visible
#include_directories( "${PROJECT_SOURCE_DIR}/common" )
#add_subdirectory( common )

# Tell CMake to create the executable
add_executable(cg main.cpp)

# linker
#target_link_libraries(poc common)
