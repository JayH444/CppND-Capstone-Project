# Udacity CPPND Capstone project - "Tyrianoid"

Created from the [Snake game starter repo](https://github.com/udacity/CppND-Capstone-Snake-Game) for the [Udacity C++ Nnanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
This is the repository of my capstone project for it.

This project is a simple endless arcade game. The player controls a spacecraft and must dodge a continuous volley of incoming asteroids.
The player scores by surviving for as long as possible. Higher scores mean a longer survival time. The game's difficulty increases the longer the player survives by slowly incrementing the number of asteroids that will appear.

## How to Play

- W: Move up
- A: Move left
- S: Move down
- D: Move right

## Project Structure

- `main.cpp` - The entry point of the program. Initializes the renderer, input manager, and game manager objects, and runs the game.
- `util.cpp/.h` - A utility file included by every other header file in the project. It contains all the standard library headers used in the project, as well as any general purpose functions, global variables, and structs.
- `gameManager.cpp/.h` - Initializes the game state and runs the game loop + its respective steps (handling inputs, updating game state, rendering).
- `inputManager.cpp/.h` - Handles inputs both for the player and for closing the application.
- `renderer.cpp/.h` - Contains and handles everything related to rendering the visual aspects of the game; Textures, sprite positions, and window title information.
- `gameEntity.cpp/.h` - The generic class that all entities in the game inherit from. Contains an assortment of functions and member variables used by them.
- `player.cpp/.h` - The player class. Contains all the functions and member variables unique to and required by the player entity.

## Rubric Points Addressed

#### 1. The project demonstrates an understanding of C++ functions and control structures.
  * Can be found throughout every file. e.g. `gameManager.cpp`.
#### 2. The project reads data from a file and process the data, or the program writes data to a file.
  * Examples in `gameManager.cpp`, with the function LoadAllGameTextures() at line 22, and in `renderer.cpp`, with the function LoadTexture() at line 28.
#### 3. The project accepts user input and processes the input.
  * Used for player inputs for the game. Seen in `inputmanager.cpp`, with the function HandleInput() at line 3. This input is processed in `player.cpp` by the Player class functions SetMovementDirection() at line 7, and Update() at line 19.
#### 4. The project uses Object Oriented Programming techniques.
  * Used extensively. Examples can be found with the Player class in `player.cpp`, GameManager class in `gameManager.cpp`, Renderer class in `renderer.cpp`, etc.
#### 5. Classes use appropriate access specifiers for class members.
  * Also used extensively. Examples can be found with the Player class in `player.cpp`, GameManager class in `gameManager.cpp`, GameEntity class in `gameEntity.cpp`, etc.
#### 6. Class constructors utilize member initialization lists.
  * Used for the Player class in `player.cpp` at line 4, GameEntity class in `gameEntity.cpp` at line 7, and GameManager class in `gameManager.cpp` at line 3.
#### 7. Classes encapsulate behavior.
  * Used extensively. Examples can be found with the Player class in `player.cpp`, GameManager class in `gameManager.cpp`, Renderer class in `renderer.cpp`, etc.
#### 8. Classes follow an appropriate inheritance hierarchy.
  * Can be seen with the Player class in `player.cpp` and the GameEntity class in `gameEntity.cpp`. GameEntity is composed entirely of overideable virtual functions, and the Player class inherits from it and overrides some of its functions.
#### 9. Overloaded functions allow the same function to operate on different parameters.
  * The Renderer class's UpdateWindowTitle() function makes use of this - lines 16 and 17 in `renderer.h` show it. UpdateWindowTitle() has an overload allowing it to take either two integers or one string and an integer as its arguments.
#### 10. Derived class functions override virtual base class functions.
  * The Player class does this in `player.h`, lines 20 and 21.
#### 11. The project makes use of references in function declarations.
  * Used extensively. E.g. GameEntity in `gameEntity.h` at lines 14 and 35, and the _texture member variable at line 45; GameManager in `gameManager.h` at line 17 and for the member variable _r at line 37.
#### 12. The project uses destructors appropriately.
  * This needed to be done for any instances of SDL_Texture, due to its lack of built-in compatibility with standard library smart pointers. GameManager destructs them in its destructor in `gameManager.cpp`, line 6.
#### 13. The project uses smart pointers instead of raw pointers.
  * Wherever possible. SDL types were omitted from using them due to the aforementioned compatibility issues, but any standard library derived classes make extensive usage of them. These can be seen in `main.cpp` at lines 17 thru 19, and in `gameManager.cpp` at line 81.

## Credits

The partial namesake and sprites used for the game come from the freeware game [Tyrian](https://www.gog.com/game/tyrian_2000). 

[The author of the game's assets](https://lostgarden.home.blog/2007/04/05/free-game-graphics-tyrian-ships-and-tiles/) has provided them available
for free for use in any derivative works (games, prototypes, animations, etc).

Additional credits to the following people for their explanations and code examples (commented in the codebase where appropriate):
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
  * For Windows, information for how to compile for SDL2 in Visual Studio 2019 can be found [here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions
### Option 1 (using CMake and GCC):

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. In the build folder, copy the textures folder in the top level directory over to the build folder: `cp -avr ../textures ./` (or simply manually copy & paste in a file manager)
5. Run it: `./Tyrianoid`.

### Option 2 (using Visual Studio):

1. Clone this repo.
2. Open the .sln file with Visual Studio 2019 (Not tested with earlier versions).
3. In `./src/util.h`, replace `#include <experimental/filesystem>` on line 8 with `#include <filesystem>`
4. In `./src/util.h`, replace `namespace FS = std::experimental::filesystem;` on line 20 with `namespace FS = std::filesystem;`
5. Verify that the required environment variables have been set. (Further instructions [here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php)).
6. Verify that the directory `C:/SDL2-2.0.12` exists, or that the location of the SDL2 install is set correctly for the project (Further instructions [here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php)).
7. Compile it.
8. Run it: `./x64/Release/CppND-Capstone-Project.exe` or `./x64/Debug/CppND-Capstone-Project.exe` (depending on the compile configuration chosen).

