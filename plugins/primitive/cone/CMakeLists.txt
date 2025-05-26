##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

message(STATUS "Bulding ConePlugin library...")
message(STATUS "Checking ConePlugin Library Dependencies...")

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS ON)

set(CONEPLUGIN_SOURCES
    Cone.cpp
)

add_library(Cone SHARED ${CONEPLUGIN_SOURCES})

target_include_directories(Cone PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Cone
    ECSLib
    EngineLib
    UtilsLib)

set_target_properties(Cone PROPERTIES
    OUTPUT_NAME "Cone"
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins
    PREFIX ""
)
