cmake_minimum_required(VERSION 3.28)
set(CMAKE_C_COMPILER "clang-18" CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "clang++-18" CACHE STRING "" FORCE)

get_filename_component(PROJECT_NAME "${CMAKE_SOURCE_DIR}" NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Collect all .cpp files
file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/*.cpp")

# Collect all .cppm files for modules
file(GLOB MODULE_FILES "${CMAKE_SOURCE_DIR}/*.cppm")

add_executable(${PROJECT_NAME} ${SRC_FILES})

if(MODULE_FILES)
  target_sources(${PROJECT_NAME}
    PUBLIC
      FILE_SET all_my_modules TYPE CXX_MODULES FILES
      ${MODULE_FILES}
  )
endif()