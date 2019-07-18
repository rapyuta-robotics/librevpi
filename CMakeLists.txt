cmake_minimum_required(VERSION 2.8)

project(librevpi)

set (librevpi_VERSION_MAJOR 1)
set (librevpi_VERSION_MINOR 0)

add_library(${PROJECT_NAME} STATIC src/revpi.c include/revpi.h)

include_directories(${PROJECT_SOURCE_DIR}/include)

install(TARGETS librevpi DESTINATION lib)
install(FILES revpi.h DESTINATION include)
