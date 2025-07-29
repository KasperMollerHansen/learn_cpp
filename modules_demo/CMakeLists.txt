cmake_minimum_required(VERSION 3.28)

project(my_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
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