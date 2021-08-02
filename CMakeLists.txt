cmake_minimum_required(VERSION 3.10)

project(librevpi VERSION 0.1.0 LANGUAGES CXX)

include_directories(include)

set (SRC
  src/revpi.cpp
)

add_library(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME}
        PUBLIC
                $<INSTALL_INTERFACE:include>
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
                ${CMAKE_CURRENT_SOURCE_DIR}
)
