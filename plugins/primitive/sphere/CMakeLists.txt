##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

message(STATUS "Bulding SpherePlugin library...")
message(STATUS "Checking SpherePlugin Library Dependencies...")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS ON)

set(SPHEREPLUGIN_SOURCES
    Sphere.cpp
)

add_library(Sphere SHARED ${SPHEREPLUGIN_SOURCES})

target_include_directories(Sphere PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Sphere
    ECSLib
    EngineLib
    UtilsLib
)

set_target_properties(Sphere PROPERTIES
    OUTPUT_NAME "Sphere"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
    PREFIX ""
)