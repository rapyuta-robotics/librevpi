cmake_minimum_required(VERSION 2.8)

project(librevpi)

set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/revpi.h.in"
  "${PROJECT_BINARY_DIR}/revpi.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

add_library(${PROJECT_NAME} SHARED "revpi.c")

