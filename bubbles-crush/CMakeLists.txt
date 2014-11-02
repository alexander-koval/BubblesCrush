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
    "src/screen/*.cpp"
    "src/display/*.cpp"
    "src/utils/*.cpp"
    "src/events/*.cpp"
    "src/effects/*.cpp"
    "src/particles/*.cpp"
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
)

add_executable(bubbles-crush ${bubbles_crush_source-files})

target_link_libraries(bubbles-crush
    sfml-system
    sfml-window
    sfml-graphics
)

add_custom_command(TARGET bubbles-crush PRE_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_CURRENT_SOURCE_DIR}/media Media
                    WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
