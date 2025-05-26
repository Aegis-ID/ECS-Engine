##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

message(STATUS "Bulding CameraPlugin library...")
message(STATUS "Checking CameraPlugin Library Dependencies...")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS ON)

set(CAMERAPLUGIN_SOURCES
    Camera.cpp
)

add_library(Camera SHARED ${CAMERAPLUGIN_SOURCES})

target_include_directories(Camera PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Camera
    ECSLib
    EngineLib
    UtilsLib
)

set_target_properties(Camera PROPERTIES
    OUTPUT_NAME "Camera"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
    PREFIX ""
)
