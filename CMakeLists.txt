cmake_minimum_required(VERSION 2.8)
project(BubblesFall)

set(BubblesInvaders_VERSION_MAJOR 0)
set(BubblesInvaders_VERSION_MINOR 1)

option(DEBUG_MODE "Debug or Release?" ON)

if(DEBUG_MODE)
    set(CMAKE_BUILD_TYPE Debug)
else(DEBUG_MODE)
    set(CMAKE_BUILD_TYPE Release)
endif(DEBUG_MODE)

include_directories(
    SFML/include
)

if(NOT MSVC)
    add_definitions(-std=c++11)
    set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
    set(CMAKE_C_FLAGS "-std=c99 -fno-stack-protector")
endif()

add_subdirectory(bubbles-fall)
add_subdirectory(SFML)

