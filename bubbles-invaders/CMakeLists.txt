file(GLOB bubbles_invaders_source-files
    "include/*.h"
    "include/*.inl"
    "include/screen/*.h"
    "include/screen/*.inl"
    "include/display/*.h"
    "include/display/*.inl"
    "include/utils/*.h"
    "include/events/*.h"
    "src/screen/*.cpp"
    "src/display/*.cpp"
    "src/utils/*.cpp"
    "src/events/*.cpp"
    "src/*.cpp"
)

include_directories(
    include
    include/screen
    include/display
    include/utils
    include/events
)

add_executable(bubbles-invaders ${bubbles_invaders_source-files})

target_link_libraries(bubbles-invaders
   sfml-system
   sfml-window
   sfml-graphics
)
