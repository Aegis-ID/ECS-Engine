##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

message(STATUS "Bulding CylinderPlugin library...")
message(STATUS "Checking CylinderPlugin Library Dependencies...")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS ON)

set(CYLINDERPLUGIN_SOURCES
    Cylinder.cpp
)

add_library(Cylinder SHARED ${CYLINDERPLUGIN_SOURCES})

target_include_directories(Cylinder PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Cylinder
    ECSLib
    EngineLib
    UtilsLib)

set_target_properties(Cylinder PROPERTIES
    OUTPUT_NAME "Cylinder"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
    PREFIX ""
)
