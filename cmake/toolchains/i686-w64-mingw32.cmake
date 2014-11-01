# Define the environment for cross compiling from Linux to Win32
SET(CMAKE_SYSTEM_NAME    Windows) # Target system name
set(CMAKE_SYSTEM_PROCESSOR i686)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_C_COMPILER     "/usr/bin/i686-w64-mingw32-gcc")
SET(CMAKE_CXX_COMPILER   "/usr/bin/i686-w64-mingw32-g++")
SET(CMAKE_ASM-ATT_COMPILER "/usr/bin/i686-w64-mingw32-as")
SET(CMAKE_RC_COMPILER    "/usr/bin/i686-w64-mingw32-windres")
SET(CMAKE_RANLIB         "/usr/bin/i686-w64-mingw32-ranlib")
SET(CMAKE_AR             "/usr/bin/i686-w64-mingw32-ar")

SET(CMAKE_C_LINK_EXECUTABLE "/usr/bin/i686-w64-mingw32-ld")
SET(CMAKE_CXX_LINK_EXECUTABLE "/usr/bin/i686-w64-mingw32-ld")

# Configure the behaviour of the find commands
SET(CMAKE_FIND_ROOT_PATH "/usr/i686-w64-mingw32")
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
