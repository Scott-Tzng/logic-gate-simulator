cmake_minimum_required(VERSION 3.29)

project(Sorting-Visualizer
    LANGUAGES C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib CONFIG REQUIRED)

add_executable(Sorting-Visualizer
    "src/main.c"
    "src/algorithms.c"
    "src/elements.c"
    "src/input.c"
    "src/timer.c"
    "src/ui.c")

target_link_libraries(Sorting-Visualizer PRIVATE raylib)
