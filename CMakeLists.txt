cmake_minimum_required(VERSION 3.16)
project(chip8_emulator)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
find_package(glfw3 REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    PRIVATE
    include
)
link_directories(${SDL2_LIBRARY_DIRS})

set(SOURCES
    src/chip8.cpp
    src/main.cpp
    src/gl.c
)

add_executable(chip8 ${SOURCES})

target_link_libraries(chip8
    ${SDL2_LIBRARIES}
    glfw
)