# Udacity CPPND Capstone project - "Tyrianoid"

**WIP**

Created from the [Snake game starter repo](https://github.com/udacity/CppND-Capstone-Snake-Game) for the [Udacity C++ Nnanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
This is the repository of my capstone project for it.

This project is a simple endless arcade game. The player controls a spacecraft and must dodge a continuous volley of incoming asteroids.
The player scores by surviving for as long as possible. Higher scores mean a longer survival time. The game's difficulty increases as the
player survives longer by slowly incrementing the number of asteroids that will appear.

## How to Play

- W: Move up
- A: Move left
- S: Move right
- D: Move down

## Project Structure

- main.cpp - The entry point of the program. Initializes the renderer, input manager, and game manager objects, and runs the game.
- util.cpp/.h - A utility file included by every other header file in the project. It contains all the standard library headers used in the project, as well as any general purpose functions, global variables, and structs.
- gameManager.cpp/.h - Initializes the game state and runs the game loop + its respective steps (handling inputs, updating game state, rendering).
- inputManager.cpp/.h - Handles inputs both for the player and for closing the application.
- renderer.cpp/.h - Contains and handles everything related to rendering the visual aspects of the game; Textures, sprite positions, and window title information.
- gameObject.cpp/.h - The generic class that all entities in the game inherit from. Contains an assortment of functions and member variables used by them.
- player.cpp/.h - The player class. Contains all the functions and member variables unique to and required by the player entity.

## Rubric Points Addressed:

WIP

## Credits

The namesake and sprites used for the game come from the freeware game [Tyrian](https://www.gog.com/game/tyrian_2000). 

[The author of the game's assets](https://lostgarden.home.blog/2007/04/05/free-game-graphics-tyrian-ships-and-tiles/) has provided them available
for free for use in any derivative works (games, prototypes, animations, etc).

Additional credits to the following people for their explanations and code examples:
- Lazy Foo's Tutorials
- Brandon Foltz
- "Patrick le Duc" of stackexchange/stackoverflow
- "Peter Parker" of stackoverflow

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions
### Option 1 (typical when using CMake and GCC):

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

### Option 2 (using Visual Studio):

1. Clone this repo.
2. Open the .sln file with Visual Studio 2019 (Not tested with earlier versions.)
3. Compile through the solution explorer.
4. Run it: `./x64/Release/CppND-Capstone-Project.exe` or `./x64/Debug/CppND-Capstone-Project.exe` (depending on the compile configuration chosen).