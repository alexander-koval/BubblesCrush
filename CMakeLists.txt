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

set(MINGW_ROOT c:/Qt/Tools/mingw482_32)

set(MINGW_RUNTIME_FILES
    ${MINGW_ROOT}/bin/libgcc_s_dw2-1.dll
    ${MINGW_ROOT}/bin/libwinpthread-1.dll
    ${MINGW_ROOT}/bin/libstdc++-6.dll
)

include_directories(
    SFML/include
)

link_directories(
    ${CMAKE_BINARY_DIR}/SFML/lib
)

add_definitions(-DSFML_STATIC)

if(MINGW)
     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
     set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
     set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
endif()
if(NOT MSVC)
    add_definitions(-std=c++11)
    set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
    set(CMAKE_C_FLAGS "-std=c99")
endif()

add_subdirectory(bubbles-fall)
add_subdirectory(SFML)

