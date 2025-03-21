# Army Moves MSX

Remake of Army Moves MSX (phase 1 & 2) using C++ and [SFML](https://www.sfml-dev.org/) library.

### Software used:

* [Ubuntu 16.04](https://www.ubuntu.com/) (recommended)
* [Code::Blocks](http://www.codeblocks.org/)
* GNU GCC Compiler
* [SFML 2.X](https://www.sfml-dev.org/)

### Set up the enviroment:

1. install **OpenGL**:
 ```
 sudo apt-get install mesa-common-dev
 sudo apt-get install freeglut3-dev
 ```

2. install **C++ compilator** (in case it doesn't):
 ```
 sudo apt-get install build-essential
 ```

3. install **SFML** for Linux:
 ```
 sudo apt-get install libsfml-dev
 sudo dpkg -L libsfm-dev
 ```

4. install **CodeBlocks (v.13)** [ if a **newer version** is wanted go to point 5 directly ]
 ```
 sudo apt-get install codeblocks
 ```

5. intall CodeBlocks (v. 16)
 ```
 sudo add-apt-repository ppa:damien-moore/codeblocks-stable
 sudo apt-get update
 sudo apt-get install codeblocks codeblocks-contrib
 ```

---

### Project execution:

1. Open codeblocks

2. Open project
 - File > Open > {folderPath}/Army-moves/Army-moves.cbp
 - Project mode: DEBUG (Build target)
 - Settings > Compiler > Compiler flags > **activate C++11**
 - Compile, execute and have fun ^^

---

### Controls:
 - Start directly a concrete phase: **F1** for phase 1, **F2** for phase 2
 - See player and enemies colliders: **F3**
 - Toggle info panel: **F4**
 - Q: exit game

 - Phase 1:
   - Arrow keys: Up -> jump, Left -> car reverse, Right -> car forward
   - Z -> shoot above, X -> shoot straight

 - Phase 2:
   - Arrow keys: Up, Down, Left, Right -> move helicopter
   - Z/X -> shoot straight and below at the same time
