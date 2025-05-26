##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

message(STATUS "Bulding PointPlugin library...")
message(STATUS "Checking PointPlugin Library Dependencies...")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS ON)

set(POINTPLUGIN_SOURCES
    Point.cpp
)

add_library(Point SHARED ${POINTPLUGIN_SOURCES})

target_include_directories(Point PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Point
    ECSLib
    EngineLib
    UtilsLib)

set_target_properties(Point PROPERTIES
    OUTPUT_NAME "Point"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
    PREFIX ""
)
