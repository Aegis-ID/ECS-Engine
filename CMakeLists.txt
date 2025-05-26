##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

cmake_minimum_required(VERSION 3.15)

set(EXECUTABLE_NAME "raytracer")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}")
add_compile_options(-Wall -Wextra -Werror)
project(${EXECUTABLE_NAME} VERSION 0.0.1 LANGUAGES CXX)

option(BUILD_DEBUG "Build with debug symbols" OFF)
if(BUILD_DEBUG)
    add_compile_options(-g3)
endif()

include_directories(include)

set(SOURCES
    src/main.cpp
)

add_subdirectory(src/ECS)
add_subdirectory(src/Engine)
add_subdirectory(src/Utils)
#add_subdirectory(plugins)

message(STATUS "Bulding main executable...")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME}
    ECSLib
    EngineLib
    UtilsLib
)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
