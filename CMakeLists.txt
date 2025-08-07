cmake_minimum_required(VERSION 3.10)
project(iotSF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header location
include_directories(include)

# This is for configuration files, but for now we will skip that thing
# configure_file("${CMAKE_SOURCE_DIR}/config/interface.cfg" 
#               "${CMAKE_BINARY_DIR}/config/interface.cfg" COPYONLY)

# Source files
set(SOURCES
    src/main.cpp
)

# Compiler warnings
add_compile_options(-Wall -Wextra -Wunused -Wunused-function -Wunused-variable)

# Optional: Dead code elimination
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
add_compile_options(-ffunction-sections -fdata-sections)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")

# Output
add_executable(iotSF ${SOURCES})