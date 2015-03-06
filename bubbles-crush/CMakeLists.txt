file(GLOB bubbles_crush_source-files
    "include/*.h"
    "include/*.inl"
    "include/screen/*.h"
    "include/screen/*.inl"
    "include/display/*.h"
    "include/display/*.inl"
    "include/utils/*.h"
    "include/events/*.h"
    "include/effects/*.h"
    "include/particles/*.h"
    "include/physics/*.h"
    "src/screen/*.cpp"
    "src/display/*.cpp"
    "src/utils/*.cpp"
    "src/utils/*.mm"
    "src/events/*.cpp"
    "src/effects/*.cpp"
    "src/particles/*.cpp"
    "src/physics/*.cpp"
    "src/*.cpp"
)

include_directories(
    include
    include/screen
    include/display
    include/utils
    include/events
    include/effects
    include/particles
    include/physics
)

if(MINGW)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -s")
endif()
if(NOT MSVC)
    add_definitions(-D__cplusplus=201103L)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -Wall -DDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=c99 -O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -Wall -DDEBUG -std=c++11")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -std=c++11")
endif()

if(APPLE)
    set(BUNDLE_NAME ${PROJECT_NAME}.app)
    set(BUNDLE_PATH "${CMAKE_INSTALL_PREFIX}/${BUNDLE_NAME}")
    set(BINDIR ${BUNDLE_NAME}/Contents/MacOS)
    set(LIBDIR ${BUNDLE_NAME}/Contents/Libraries)
    set(RLIBDIR ${BUNDLE_NAME}/Contents/Frameworks)
    set(SHAREDIR ${BUNDLE_NAME}/Contents/Resources)
    set(PLUGINSDIR ${BUNDLE_NAME}/Contents/PlugIns)
    set(IMPORTSDIR ${BINDIR})
    set(BUNDLE_BINARIES ${PROJECT_NAME})

    # Locate all recourses
#    file(GLOB copy_resources ${CMAKE_CURRENT_SOURCE_DIR}/media/*.*)
#    set_source_files_properties(
#        ${copy_resources}
#        PROPERTIES
#        MACOSX_PACKAGE_LOCATION Resources
#    )

    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${bubbles_crush_source-files} ${copy_resources})

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E make_directory
                        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SHAREDIR})

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_CURRENT_SOURCE_DIR}/media Media
                        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SHAREDIR})

#    set_target_properties(${PROJECT_NAME} PROPERTIES RESOURCE ${copy_resources})
    set_target_properties(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})

elseif(WIN32)
    message(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${bubbles_crush_source-files})
elseif(ANDROID)
    message(ANDROID)
    add_library(${PROJECT_NAME} SHARED ${bubbles_crush_source-files})
else()
    message(LINUX)
    add_executable(${PROJECT_NAME} ${bubbles_crush_source-files})

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${CMAKE_CURRENT_SOURCE_DIR}/media Media
                        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

target_link_libraries(${PROJECT_NAME}
    sfml-system
    sfml-window
    sfml-graphics
)

