# CPPND: Capstone Game
In this game you play a lonely animal and need to defeat yourself against all attracts to survive and be successful in the game.


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
6. Run it from the workspace directory (otherwise images are not beeing found): `cd .. & ./build/Game`. 

## File and folder strcuture
.
├── .vscode         -> configuration of vscode IDE 
├── CMakeLists.txt  -> cmake file fot the build    
├── CODEOWNERS  
├── conanfile.txt -> configuration file for conan dependency management 
├── data          -> files like images which are needed in the program
├── LICENSE.md
├── README.md     -> This readme
└── src           -> Source and header files
    ├── controller.cpp
    ├── controller.h
    ├── game.cpp
    ├── game.h
    ├── logic.cpp
    ├── logic.h
    ├── main.cpp
    ├── object2d.cpp
    ├── object2d.h
    ├── renderer.cpp
    └── renderer.h

## checklist
* Compiling and Testing 
  * ✓ The submission must compile and run.
* Loops, Functions, I/O
  1. The project demonstrates an understanding of C++ functions and control structures.
  2. The project accepts user input and processes the input.
* 
   



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
