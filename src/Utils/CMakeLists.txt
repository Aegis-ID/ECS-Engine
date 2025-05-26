##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

message(STATUS "Bulding Utils library...")

set(UTILS_SOURCES
    Logger.cpp
    DynamicLoader.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(UtilsLib STATIC ${UTILS_SOURCES})

target_include_directories(UtilsLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)