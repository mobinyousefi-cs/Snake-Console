# Snake Game in Console (C)

A fully implemented, terminal-based **Snake Game** written in the C programming language, structured at a professional graduate-level standard. This project demonstrates data structures (linked lists), low-level input handling, game loop design, and clean modular architecture. It is designed to be cross-platform (Linux/macOS/Windows) with platform-specific terminal utilities.

---

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Project Structure](#project-structure)
4. [Build Instructions](#build-instructions)
5. [Gameplay Instructions](#gameplay-instructions)
6. [Technical Architecture](#technical-architecture)
7. [Data Structures](#data-structures)
8. [Core Algorithms](#core-algorithms)
9. [Cross-Platform Terminal Handling](#cross-platform-terminal-handling)
10. [Future Improvements](#future-improvements)
11. [License](#license)

---

## Overview

The **Snake Game in Console** recreates the classic retro Snake game inside a terminal window. The implementation avoids external libraries and relies purely on standard C and platform-specific system calls.

The design emphasizes clarity, maintainability, modularity, and academic-level correctness. The snake is modeled as a **linked list**, the game board is dynamically generated, and the core loop uses **non-blocking input** and millisecond-level timing.

---

## Features

* Fully playable console Snake Game
* Cross-platform: works on Linux, macOS, and Windows
* Clean modular architecture
* Non-blocking keyboard input
* Linked list implementation of the snake body
* Randomized food placement avoiding collisions
* Variable board dimensions (modifiable in `config.h`)
* Smooth game loop with fixed tick timing
* High-quality professional code structure

---

## Project Structure

```text
snake-console/
├─ src/
│  ├─ main.c            # Entry point
│  ├─ game.c            # Game logic and update loop
│  ├─ snake.c           # Snake linked-list implementation
│  ├─ board.c           # Board, food placement
│  ├─ input.c           # Key input mapping
│  └─ utils.c           # Terminal control, timing
│
├─ game.h
├─ snake.h
├─ board.h
├─ input.h
├─ config.h
├─ utils.h
│
├─ Makefile
├─ LICENSE (MIT)
└─ README.md
```

---

## Build Instructions

### Linux / macOS

```bash
make
./snake_game
```

### Windows (MinGW or similar)

```bash
mingw32-make
snake_game.exe
```

### Cleanup

```bash
make clean
```

---

## Gameplay Instructions

Use the following controls while playing:

| Key | Action        |
| --- | ------------- |
| W   | Move Up       |
| S   | Move Down     |
| A   | Move Left     |
| D   | Move Right    |
| Q   | Quit the Game |

The game ends when:

* The snake hits a wall
* The snake bites itself
* The player presses `Q`

Each eaten food (`*`) gives **+10 points**.

---

## Technical Architecture

The program is divided into distinct, reusable modules:

### 1. `game.c` — Core Game Engine

Handles the game loop, updates, score management, collision detection, and rendering.

### 2. `snake.c` — Snake Data Structure

Implements a linked-list representation of the snake. Supports movement, growing, and occupancy checks.

### 3. `board.c` — Board Representation

Defines board boundaries and randomized food placement that avoids the snake.

### 4. `input.c` — Raw Input Processing

Maps raw keystrokes (non-blocking) to semantic input actions.

### 5. `utils.c` — Cross-Platform Terminal Tools

Provides:

* Raw terminal mode (POSIX)
* Non-blocking `kbhit` implementations
* Screen clearing
* Millisecond sleep

---

## Data Structures

### Snake Linked List

```c
typedef struct SnakeNode {
    Position pos;
    struct SnakeNode* next;
} SnakeNode;

typedef struct Snake {
    SnakeNode* head;
    SnakeNode* tail;
    Direction dir;
    int length;
} Snake;
```

### Board

```c
typedef struct Board {
    int width;
    int height;
    Position food;
} Board;
```

---

## Core Algorithms

### 1. Snake Movement

* Compute next head position
* Insert new head node
* If not growing, remove tail

This yields O(n) movement behavior (due to linked list traversal on tail removal) but is perfectly adequate for typical board sizes.

### 2. Food Placement

Food positions are generated randomly and validated to avoid overlap with the snake.

### 3. Collision Detection

Checks include:

* Hitting walls
* Hitting own body
* Eating food

### 4. Game Loop

Pseudocode:

```text
while (game_running):
    read_input()
    update_snake_direction()
    compute_next_position()
    if collision: end_game
    if food eaten: grow snake, increase score
    render_board()
    sleep(GAME_TICK_MS)
```

---

## Cross-Platform Terminal Handling

* **Windows:** Uses `conio.h`, `_kbhit()`, `_getch()`, and `cls` commands.
* **Linux/macOS:** Uses `termios`, `select()`, `nanosleep()`, and ANSI escape sequences.

This ensures consistent behavior across all systems.

---

## Future Improvements

Here are several extensions you may add:

### Gameplay Enhancements

* Increasing speed as snake grows
* Obstacles or walls
* Score multipliers
* Pausing functionality

### Rendering Improvements

* Colored output using ANSI codes
* Double-buffered rendering to eliminate flickering

### Structural Enhancements

* Add unit tests
* Add configuration file loader
* Make board size CLI parameters

### Platform Ports

* Windows console colors
* ncurses-based advanced version
* SDL2 graphical port

---

## License

This project is released under the **MIT License**. See the `LICENSE` file for full details.

---

## Author

**Mobin Yousefi**
GitHub: [github.com/mobinyousefi-cs](https://github.com/mobinyousefi-cs)
