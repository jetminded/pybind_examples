cmake_minimum_required(VERSION 3.14)
project(pet_module)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Python and pybind11
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# ВАЖНО! Таргет pet_module должен совпадать с аналогичным в файле pet.cpp
pybind11_add_module(pet_module pet.cpp)