# The Data Maze

Project developed in C for a Data Structures course.

The system simulates a character exploring a maze in search of the exit using the Backtracking algorithm. During the journey, the character collects treasures, encounters traps, and stores the collected values in an ordered backpack structure.

## Features

* Maze loading from a `.txt` file
* Automatic pathfinding using Backtracking
* Stack structure to store the explored path
* Ordered linked list representing the backpack
* Random treasure values between 1 and 100 coins
* Traps that remove the smallest treasure from the backpack
* Real-time maze visualization in the terminal
* Generation of a `saida.txt` file containing the final solution path

## Data Structures Used

* Stack
* Ordered Linked List
* One-dimensional array
* Recursion

## Project Structure

```bash
main.c
labirinto.c
labirinto.h
mochila.c
mochila.h
arquivo.c
arquivo.h
labirinto.txt
saida.txt
integrantes.txt
```

## How to Compile

### Windows (GCC / MinGW)

```bash
gcc main.c labirinto.c mochila.c arquivo.c -o labirinto
```

## How to Run

```bash
labirinto.exe
```

## Maze Legend

* `P` → player
* `S` → exit
* `#` → wall
* `T` → treasure
* `A` → trap
* empty space → free path
