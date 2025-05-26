##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

message(STATUS "Bulding PlanePlugin library...")
message(STATUS "Checking PlanePlugin Library Dependencies...")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS ON)

set(PLANEPLUGIN_SOURCES
    Plane.cpp
)

add_library(Plane SHARED ${PLANEPLUGIN_SOURCES})

target_include_directories(Plane PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Plane
    ECSLib
    EngineLib
    UtilsLib)

set_target_properties(Plane PROPERTIES
    OUTPUT_NAME "Plane"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
    PREFIX ""
)
