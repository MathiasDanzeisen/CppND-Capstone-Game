cmake_minimum_required(VERSION 3.7)

project(Game)
enable_language(CXX)

find_package(SDL2)
find_package(SDL2_image)

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


#target_compile_options(Game PRIVATE -Wall -Wextra -pedantic -Werror)
target_compile_options(Game PRIVATE -Wall -Wextra -pedantic )


set_property(TARGET Game PROPERTY CXX_STANDARD 17)
target_compile_features(Game PRIVATE cxx_std_17)

target_include_directories(Game
    PRIVATE
        src    
)

target_link_libraries(Game 
    PRIVATE    
        SDL2::SDL2-static
        SDL2_image::SDL2_image
        
)
