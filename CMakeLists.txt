cmake_minimum_required(VERSION 2.8)
project(BubblesFall)

set(BubblesInvaders_VERSION_MAJOR 0)
set(BubblesInvaders_VERSION_MINOR 1)

option(DEBUG_MODE "Debug or Release?" OFF)

if(DEBUG_MODE)
    add_definitions(-DDEBUG_MODE)
    set(CMAKE_BUILD_TYPE Debug)
else(DEBUG_MODE)
    set(CMAKE_BUILD_TYPE Release)
endif(DEBUG_MODE)

include_directories(
    SFML/include
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all Libraries"
   )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all Executables."
   )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
   ${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all static libraries."
   )

#link_directories(
#    ${CMAKE_BINARY_DIR}/bin
#)

if(MINGW)
    set(FREETYPE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/SFML/extlibs/headers/libfreetype/windows)
    set(OPENAL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SFML/extlibs/headers/AL)
    set(SNDFILE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SFML/extlibs/headers/libsndfile/windows)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -s")
endif()
if(NOT MSVC)
    add_definitions(-std=c++11)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -Wall -DDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -Wall -DDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=c99 -O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif()

add_subdirectory(bubbles-crush)
add_subdirectory(SFML)
