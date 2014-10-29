file(GLOB bubbles_invaders_source-files
    "include/*.h"
    "include/*.inl"
    "include/screen/*.h"
    "include/screen/*.inl"
    "include/display/*.h"
    "include/display/*.inl"
    "include/utils/*.h"
    "include/events/*.h"
    "include/effects/*.h"
#    "include/delete/*.h"
    "src/screen/*.cpp"
    "src/display/*.cpp"
    "src/utils/*.cpp"
    "src/events/*.cpp"
    "src/effects/*.cpp"
#    "src/detele/*.cpp"
    "src/*.cpp"
    "media/Shaders/*.frag"
    "media/Shaders/*.vert"
)

include_directories(
    include
    include/screen
    include/display
    include/utils
    include/events
    include/effects
#    include/delete
)

add_executable(bubbles-invaders ${bubbles_invaders_source-files})

target_link_libraries(bubbles-invaders
   sfml-system
   sfml-window
   sfml-graphics
)
