cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)
enable_language(CXX)

find_package(SDL_image)

add_executable(Game 
    src/main.cpp 
    src/game.cpp 
    src/controller.cpp 
    src/renderer.cpp 
    src/object2d.cpp
)
target_include_directories(Game
    PRIVATE
        src    
)

target_link_libraries(Game 
    PRIVATE    
        SDL2-static
        sdl_image::sdl_image
)
