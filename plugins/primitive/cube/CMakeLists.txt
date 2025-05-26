##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

message(STATUS "Bulding CubePlugin library...")
message(STATUS "Checking CubePlugin Library Dependencies...")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS ON)

set(CUBEPLUGIN_SOURCES
    Cube.cpp
)

add_library(Cube SHARED ${CUBEPLUGIN_SOURCES})

target_include_directories(Cube PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Cube
    ECSLib
    EngineLib
    UtilsLib)

set_target_properties(Cube PROPERTIES
    OUTPUT_NAME "Cube"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
    PREFIX ""
)
