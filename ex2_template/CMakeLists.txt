cmake_minimum_required(VERSION 3.14)
project(pet_module)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Python from current environment
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Ask Python (from venv) where pybind11 CMake files are
execute_process(
    COMMAND ${Python3_EXECUTABLE} -m pybind11 --cmakedir
    OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Add it to CMake search path
list(APPEND CMAKE_PREFIX_PATH ${PYBIND11_CMAKE_DIR})

# Now find pybind11
find_package(pybind11 REQUIRED)

# Build module
pybind11_add_module(pet_module pet.cpp)