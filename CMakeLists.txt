cmake_minimum_required(VERSION 3.7)

project(Game)
enable_language(CXX)


INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})


add_executable(Game 
    src/main.cpp 
    src/game.cpp 
    src/controller.cpp 
    src/renderer.cpp
    src/logic.cpp 
    src/object2d.cpp
    src/player.cpp
    src/bullet.cpp
    src/enemy.cpp
)

target_compile_options(Game PRIVATE -Wall -Wextra -pedantic)

set_property(TARGET Game PROPERTY CXX_STANDARD 17)
target_compile_features(Game PRIVATE cxx_std_17)

target_include_directories(Game
    PRIVATE
        src    
)

# for build with sys libs
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})