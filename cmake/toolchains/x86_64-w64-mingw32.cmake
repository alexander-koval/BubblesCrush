## Define the environment for cross compiling from Linux to Win32
#SET(CMAKE_SYSTEM_NAME    Windows) # Target system name
#set(CMAKE_SYSTEM_PROCESSOR i686)
#SET(CMAKE_SYSTEM_VERSION 1)
#SET(CMAKE_C_COMPILER     "x86_64-w64-mingw32-gcc")
#SET(CMAKE_CXX_COMPILER   "x86_64-w64-mingw32-g++")
#SET(CMAKE_ASM-ATT_COMPILER "x86_64-w64-mingw32-as")
#SET(CMAKE_RC_COMPILER    "x86_64-w64-mingw32-windres")
#SET(CMAKE_RANLIB         "x86_64-w64-mingw32-ranlib")
#SET(CMAKE_AR             "x86_64-w64-mingw32-ar")

#SET(CMAKE_C_LINK_EXECUTABLE "x86_64-w64-mingw32-ld")
#SET(CMAKE_CXX_LINK_EXECUTABLE "x86_64-w64-mingw32-ld")

## Configure the behaviour of the find commands
#SET(CMAKE_FIND_ROOT_PATH "/usr/x86_64-w64-mingw32" "/usr/bin")
#SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


SET(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
#SET(CMAKE_MAKE_PROGRAM /usr/bin/make)

# here is the target environment located
SET(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

#set(FREETYPE_INCLUDE_DIRS /usr/x86_64-w64-mingw32/include/freetype2)
#set(OPENAL_INCLUDE_DIR /usr/x86_64-w64-mingw32/include/AL)

#set(FREETYPE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/SFML/extlibs/headers/libfreetype/windows/freetype)
#set(OPENAL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/SFML/extlibs/headers/AL)
#set(SNDFILE_INCLDE_DIR ${CMAKE_SOURCE_DIR}/SFML/extlibs/headers/libsndfile/windows)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
