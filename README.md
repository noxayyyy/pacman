# Pac-Man Clone

A 2D Pac-Man clone featuring procedural level generation, built from scratch using C++ and the custom **Nox Engine**.

## ✨ Features
* **Procedural Map Generation:** Levels are procedurally generated using autonomous "Builder" agents that carve out valid paths, ensuring a unique layout.
* **Custom ECS Engine:** Built entirely on top of Nox Engine's Entity-Component-System architecture.
* **State Machine Animations:** Smooth, direction-based Sprite animations using Nox Engine's Animator component.
* **Dynamic Scoring:** Pellet collection and automatic UI updates.

## 📦 Project Structure
This project uses the `Nox Engine` as a Git submodule. 
* `src/` & `include/`: Game-specific logic (Map Generation, Gameplay Scene).
* `engine/`: The ECS engine submodule.
* `sprites/` & `fonts/`: Game assets.

## 🛠️ Prerequisites
You will need `clang++`, `make`, and the SDL2 suite.

**Ubuntu/Debian:**
```bash
sudo apt-get install clang make libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```
**macOS (Homebrew):**
```bash
brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer
```

## 🚀 Building and Running
**Important:** Because the engine is a submodule, you must clone the repository recursively.

```bash
# 1. Clone the repository with its submodules
git clone --recurse-submodules https://github.com/noxayyyy/pacman.git
cd pacman

# (If you already cloned without submodules, run: git submodule update --init --recursive)

# 2. Build the game
# The Makefile is configured to automatically build the Engine library first!
make

# 3. Run the game
./bin
```

### Make Commands
* `make`: Compiles both the engine and the game, producing the `./bin` executable.
* `make clean`: Removes all compiled objects, binaries, and cleans the engine submodule.

## 📚 Documentation
This project uses automated Doxygen documentation deployed via GitHub Actions. Game documentation seamlessly cross-links to the Engine documentation via Doxygen tag files.

**[View the Live Game Documentation Here](https://noxayyyy.github.io/pacman)**
