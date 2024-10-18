<h1 style="color: rgb(118, 152, 245)", align="left">
  <img src="https://emojis.slackmojis.com/emojis/images/1531849430/4246/blob-sunglasses.gif?1531849430" width="50"/>
  Maze Game
  <img src="https://i.pinimg.com/originals/d2/85/ba/d285ba2cc51a540ad5d5e06c489ce121.gif" alt="GIF Title" width="70"/>
</h1>

<h3 align="left">
  Made With Ncurses and 
  <img src="https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="GIF Title" width="80"/>
</h3>




  <div align="center">
  <img src="https://github.com/user-attachments/assets/0d9672da-2368-4129-bce5-bb2157428fbe" alt="Game Screenshot" width="400"/>
</div>


## <img src="https://media.giphy.com/media/VgCDAzcKvsR6OM0uWg/giphy.gif" width="50"> Introduction

Welcome to the **Maze Game Project**! This is a console-based maze game built using C++ and the `ncurses` library. The game features a grid-based maze with various items (coins, bombs, keys, doors) and a player that can move around, collect items, and avoid obstacles. The player can also undo moves, making it a strategic puzzle-solving experience.

## <img src="https://media.giphy.com/media/VbK2YCQFWdg5nvH5wa/giphy.gif" width="30"> Features

- **Dynamic Grid Creation**: The game generates a dynamic grid based on the selected difficulty level.
- **Linked List Data Structures**: Efficiently manage player positions, coins collected, and more.
- **Undo Mechanism**: Limited undo moves for strategic gameplay.
- **Random Item Placement**: Items like bombs, coins, keys, and doors are placed at random positions.

##  <img src="https://media.giphy.com/media/JoaeMGYYkHpC/giphy.gif" width="50"> How It Works

1. **Linked List Management**: 
    - Utilizes custom linked list classes (`List` and `Node`) to manage player movements, item placements, and more.
2. **Grid System**: 
    - Implements a 2D grid using linked lists, where each cell is a `Cell` object connected to its adjacent cells (up, down, left, right).
3. **Player Class**: 
    - Manages player movement, collection of items, and collision checks.
4. **Maze Class**: 
    - Integrates everything together, initializes the maze, and handles game logic.

## <img src="https://media.giphy.com/media/KOLIHpiF4BVzQBUYUt/giphy.gif" width="50"> Game Controls 🎮

| Key | Action         |
|-----|----------------|
| `W` | Move Up        |
| `S` | Move Down      |
| `A` | Move Left      |
| `D` | Move Right     |
| `U` | Undo Last Move |

## Setup and Installation  <img src="https://media.giphy.com/media/3oKIPnAiaMCws8nOsE/giphy.gif" width="100"> 

### <img src="https://media.giphy.com/media/Ll22OhMLAlVDb8UQWe/giphy.gif" width="50">  Prerequisites

- Ensure you have `g++` installed on your system.
- Install `ncurses` library: 
    ```bash
    sudo apt-get install libncurses5-dev libncursesw5-dev
    ```

### Compilation <img src="https://media.giphy.com/media/kG9DITGH0UTsnFacyV/giphy.gif" width="70" style="float: center; margin-left: 10px;">


To compile the game, use the following command:
```bash
g++ -o MazeGame game.cpp -lncurses
```
# Sample Screenshots <img src="https://media.giphy.com/media/WnCTbHZRwNXS6YtGXv/giphy.gif" width="100"> 
### Game Menu
![image](https://github.com/user-attachments/assets/ed2887ea-66bc-45b8-b505-d5b034d89191)

### Level 1
![image](https://github.com/user-attachments/assets/5f9b7053-660c-4a4a-84ee-8cfe929e54f5)
getting warmer:
![image](https://github.com/user-attachments/assets/fc55463e-f28e-4920-8af4-7e12edc9ce7e)
getting colder:
![image](https://github.com/user-attachments/assets/e38a76d3-1b72-4fac-b021-6caa1f1998b3)

### Level 2
![image](https://github.com/user-attachments/assets/58aa57cb-01bb-4241-9bc6-fb3d67ba22d6)

### Level 3
![image](https://github.com/user-attachments/assets/ab98debc-b9dc-40a6-a49c-33b2ff5357b1)

