cmake_minimum_required(VERSION 3.0)
project(grantig C CXX)

set(CMAKE_CXX_STANDARD 17)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)

add_executable(grantig main.cpp Controller.cpp Controller.hpp Grain.cpp Grain.hpp Envelope.cpp Envelope.hpp Tone.cpp Tone.hpp AudioFile.h Vector2.h)
target_link_libraries(grantig PRIVATE raylib)
target_link_libraries(grantig PRIVATE SDL2)
target_link_libraries(grantig PRIVATE SDL2main)
#target_compile_definitions(remoteArena PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="relative-path-to-assets-in-the-game-package") # Set the asset path macro in release more
