##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

message(STATUS "Bulding DirectionalPlugin library...")
message(STATUS "Checking DirectionalPlugin Library Dependencies...")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS ON)

set(DIRECTIONALPLUGIN_SOURCES
    Directional.cpp
)

add_library(Directional SHARED ${DIRECTIONALPLUGIN_SOURCES})

target_include_directories(Directional PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Directional
    ECSLib
    EngineLib
    UtilsLib)

set_target_properties(Directional PROPERTIES
    OUTPUT_NAME "Directional"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
    PREFIX ""
)
