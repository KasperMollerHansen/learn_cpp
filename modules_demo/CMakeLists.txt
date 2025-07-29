# CMakeLists.txt
cmake_minimum_required(VERSION 3.28)
set(CMAKE_C_COMPILER "clang-18" CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "clang++-18" CACHE STRING "" FORCE)

project(modules-example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_executable(demo)
target_sources(demo
    PUBLIC
    main.cpp
)
target_sources(demo
  PUBLIC
    FILE_SET all_my_modules TYPE CXX_MODULES FILES
    a.cppm
)