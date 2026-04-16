cmake_minimum_required(VERSION 3.22)

project("Logic-Gate-Sim")

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME}
    "src/App.cpp"
    "src/Block_container.cpp"
    "src/Block.cpp"
    "src/Connection_tracker.cpp"
    "src/main.cpp"
    "src/rendering.cpp"
    "src/User_input_handler.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)