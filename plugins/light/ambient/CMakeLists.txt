##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

message(STATUS "Bulding AmbientPlugin library...")
message(STATUS "Checking AmbientPlugin Library Dependencies...")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS ON)

set(AMBIENTPLUGIN_SOURCES
    Ambient.cpp
)

add_library(Ambient SHARED ${AMBIENTPLUGIN_SOURCES})

target_include_directories(Ambient PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Ambient
    ECSLib
    EngineLib
    UtilsLib)

set_target_properties(Ambient PROPERTIES
    OUTPUT_NAME "Ambient"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
    PREFIX ""
)
