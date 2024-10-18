# Maze Game Project

<div align="center">
  <img src=![image](https://github.com/user-attachments/assets/0d9672da-2368-4129-bce5-bb2157428fbe)
alt="Game Logo" width="200"/>
</div>

## 🏁 Introduction

Welcome to the **Maze Game Project**! This is a console-based maze game built using C++ and the `ncurses` library. The game features a grid-based maze with various items (coins, bombs, keys, doors) and a player that can move around, collect items, and avoid obstacles. The player can also undo moves, making it a strategic puzzle-solving experience.

## 🚀 Features

- **Dynamic Grid Creation**: The game generates a dynamic grid based on the selected difficulty level.
- **Linked List Data Structures**: Efficiently manage player positions, coins collected, and more.
- **Undo Mechanism**: Limited undo moves for strategic gameplay.
- **Random Item Placement**: Items like bombs, coins, keys, and doors are placed at random positions.

## 📜 How It Works

1. **Linked List Management**: 
    - Utilizes custom linked list classes (`List` and `Node`) to manage player movements, item placements, and more.
2. **Grid System**: 
    - Implements a 2D grid using linked lists, where each cell is a `Cell` object connected to its adjacent cells (up, down, left, right).
3. **Player Class**: 
    - Manages player movement, collection of items, and collision checks.
4. **Maze Class**: 
    - Integrates everything together, initializes the maze, and handles game logic.

## 🎮 Game Controls

| Key | Action       |
|-----|--------------|
| `W` | Move Up      |
| `S` | Move Down    |
| `A` | Move Left    |
| `D` | Move Right   |
| `U` | Undo Last Move |

## 🛠️ Setup and Installation

### Prerequisites

- Ensure you have `g++` installed on your system.
- Install `ncurses` library: 
    ```bash
    sudo apt-get install libncurses5-dev libncursesw5-dev
    ```

### Compilation

To compile the game, use the following command:
```bash
g++ -o MazeGame main.cpp -lncurses
```
