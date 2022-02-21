# CPPND: Capstone Game

- [CPPND: Capstone Game](#cppnd-capstone-game)
  - [Intro](#intro)
- [Manual](#manual)
  - [Control](#control)
  - [Behavior](#behavior)
  - [Dependencies for Running Locally](#dependencies-for-running-locally)
  - [Basic Build Instructions](#basic-build-instructions)
  - [File and folder strcuture](#file-and-folder-strcuture)
  - [Checklist](#checklist)
  - [CC Attribution-ShareAlike 4.0 International](#cc-attribution-sharealike-40-international)
  - [Attribution Freepik](#attribution-freepik)
  - [Misc Attribution](#misc-attribution)

## Intro
In this game you play a lonely animal and need to defeat yourself against all attracts to survive and be successful in the game. This is 2D shooter forked from [udacity/CppND-Capstone-Snake-Game](https://github.com/udacity/CppND-Capstone-Snake-Game) and heavily modified.

# Manual
## Control
You can control your favorite animal with the arrow keyboard keys to move it across the screen. To shoot press the space key.   
## Behavior
You can move your animal on the screen and shoot or avoid the approaching enemies. Your score is increased for each destroyed enemy and decreased for each enemy with passes you.
Once your player catches you the game is over and your score is printed on the console.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* conan binary management
  * All OSes: [instructions](https://docs.conan.io/en/latest/installation.html#)

## Basic Build Instructions

1. Clone this repo.
2. Create build directory `mkdir build && cd build`
3. Install depoendencies: `conan install -pr:b=default -s build_type=Debug ..`
4. Configure project: `cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake`
5. Compile: `cmake --build .`  # or just "`make`"
6. Run it from the workspace directory (otherwise images are not being found): `cd .. & ./build/Game`. 

## File and folder strcuture
```
.
├── .vscode         -> configuration of vscode IDE 
├── CMakeLists.txt  -> cmake file for the build    
├── CODEOWNERS  
├── conanfile.txt -> configuration file for conan dependency management 
├── data          -> images which are needed in the program
├── LICENSE.md
├── README.md     -> This readme
└── src           -> Source and header files
    ├── bullet.cpp
    ├── bullet.h
    ├── config.h
    ├── controller.cpp
    ├── controller.h
    ├── enemy.cpp
    ├── enemy.h
    ├── game.cpp
    ├── game.h
    ├── iobject2d.h
    ├── logic.cpp
    ├── logic.h
    ├── main.cpp
    ├── object2d.cpp
    ├── object2d.h
    ├── player.cpp
    ├── player.h
    ├── renderer.cpp
    └── renderer.h
```

## Checklist
| Criteria                                                                                       | Description                             |
| ---------------------------------------------------------------------------------------------- | --------------------------------------- |
| A README with instructions is included with the project                                        | ✅ this file                             |
| The README indicates which project is chosen.                                                  | ✅ [Intro](#intro)                       |
| The README includes information about each rubric point addressed.                             | ✅ this table                            |
| -----------                                                                                    | -----------                             |
| The submission must compile and run.                                                           | ✅  [howto](#basic-build-instructions)   |
| -----------                                                                                    | -----------                             |
| The project demonstrates an understanding of C++ functions and control structures.             | ✅ all sources files                     |
| The project reads data from a file and process the data, or the program writes data to a file. | ✅ read images in  renderer.cpp:104      |
| The project accepts user input and processes the input.                                        | ✅ see: controller.h/cpp                 |
| -----------                                                                                    | -----------                             |
| The project uses Object Oriented Programming techniques.                                       | ✅ see all src files                     |
| Classes use appropriate access specifiers for class members.                                   | ✅ see all headers                       |
| Class constructors utilize member initialization lists.                                        | ✅ renderer.cpp                          |
| Classes abstract implementation details from their interfaces.                                 | ✅                                       |
| Classes encapsulate behavior                                                                   | ✅ see e.g: object2d.cpp or renderer.cpp |
| Classes follow an appropriate inheritance hierarchy                                            | ✅ iobject2d.h, object2d.h, player.h     |
| Overloaded functions allow the same function to operate on different parameters.               | ✅ renderer.h:65&67                      |
| Derived class functions override virtual base class functions.                                 | ✅ player.h:16                           |
| -----------                                                                                    | -----------                             |
| The project makes use of references in function declarations.                                  | ✅ object2d.h:53&59                      |
| The project uses destructors appropriately.                                                    | ✅ renderer.cpp:49                       |
| The project uses move semantics to move data, instead of copying it, where possible.           | ✅ game.cpp:102                          |
| The project uses smart pointers instead of raw pointers.                                       | ✅ logic.h                               |
| -----------                                                                                    | -----------                             |




## CC Attribution-ShareAlike 4.0 International
Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

## Attribution Freepik
player_skunk.png: Icons made by <a href="https://www.freepik.com" title="Freepik">Freepik</a> from <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a>
player_cat*.png: <div>Icons made by <a href="https://www.flaticon.com/authors/iconfield" title="iconfield">iconfield</a> from <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a></div>

## Misc Attribution

background_alley-gceda_1920.jpg https://pixabay.com/images/id-89197/
