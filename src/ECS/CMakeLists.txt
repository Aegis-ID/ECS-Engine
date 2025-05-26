##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

message(STATUS "Building ECS Library...")

set(ECS_SOURCES
    Entity.cpp
    EntityManager.cpp
    SystemManager.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(ECSLib STATIC ${ECS_SOURCES})

target_include_directories(ECSLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
