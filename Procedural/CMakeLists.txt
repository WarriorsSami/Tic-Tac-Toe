cmake_minimum_required(VERSION 3.20)
project(Procedural C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c)
add_executable(Procedural ${SOURCE_FILES} game.h render.c logic.c game.c)

target_link_libraries(Procedural SDL2main SDL2)
