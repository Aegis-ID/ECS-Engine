##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

message(STATUS "Bulding DiffusePlugin library...")
message(STATUS "Checking DiffusePlugin Library Dependencies...")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS ON)

set(DIFFUSEPLUGIN_SOURCES
    Diffuse.cpp
)

add_library(Diffuse SHARED ${DIFFUSEPLUGIN_SOURCES})

target_include_directories(Diffuse PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Diffuse
    ECSLib
    EngineLib
    UtilsLib)

set_target_properties(Diffuse PROPERTIES
    OUTPUT_NAME "Diffuse"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
    PREFIX ""
)
