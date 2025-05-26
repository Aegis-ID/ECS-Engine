##
## EPITECH PROJECT, 2025
## CMakeLists.txt
## File description:
## CMakeLists
##

message(STATUS "Bulding Engine library...")
message(STATUS "Checking Engine Library Dependencies...")

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)
find_library(LIBCONFIG_LIBRARY NAMES config++ libconfig++)
find_path(LIBCONFIG_INCLUDE_DIR libconfig.h++)

if (NOT LIBCONFIG_LIBRARY OR NOT LIBCONFIG_INCLUDE_DIR)
    message(FATAL_ERROR "libconfig++ is missing")
endif() 

set(ENGINE_SOURCES
    Core.cpp
    Scene.cpp
    SceneManager.cpp
    PluginManager.cpp
    SceneParser.cpp
    RTConverter.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(EngineLib STATIC ${ENGINE_SOURCES})

target_include_directories(EngineLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(EngineLib
    PUBLIC
    ECSLib
    UtilsLib
    PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    config++
)
