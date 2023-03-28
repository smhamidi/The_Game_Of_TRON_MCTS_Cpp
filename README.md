# THE_GAME_OF_TRON

Tron is a two-player arcade game in which each player controls a light cycle, leaving a wall behind them as they move. The objective of the game is to survive longer than the other player by avoiding the walls and the opponent's path while trying to trap the opponent with your own wall.

In this project, we implemented the game of Tron using C++ programming language and used the MCTS algorithm to create an AI player to play the game against a human player or another AI player.

</br>
<p align="center">
<img src="TRON_Main_Game_GUI/resources/Tron.png" alt="Tron"
title="Tron" width="1000" align="middle" />
</p>
</br>

## Game of Tron Implementation

Our implementation of the game of Tron involves creating a 2D grid, where each cell in the grid represents a position on the game board. We then represent the player's light cycle by a series of connected cells on the grid, which are updated every time the player moves. The game is played until one player collides with the wall or the opponent's path, and the other player wins.

The game can be played in two modes: human vs. human or human vs. AI. In the human vs. AI mode, the AI player is created using the MCTS algorithm, which we will discuss in the next section.

## Monte Carlo Tree Search Algorithm

The Monte Carlo Tree Search algorithm is a popular technique used in artificial intelligence for decision-making processes. It is particularly useful for games with high branching factors, where a brute-force search is not feasible.

The MCTS algorithm works by simulating the game repeatedly from the current state until a terminal state is reached. The algorithm then updates the statistics of each node in the search tree and selects the best node to explore in the next iteration. This process is repeated until a certain time limit or a maximum number of iterations is reached.

In our implementation, we used the MCTS algorithm to create an AI player for the game of Tron. The algorithm starts by creating a root node representing the current state of the game. It then repeatedly performs the following steps:

> **Selection: Starting from the root node, the algorithm selects the child node with the highest upper confidence bound (UCB) score, balancing between exploitation and exploration.**

> **Expansion: If the selected node has not been visited before, the algorithm expands it by adding all possible child nodes to the search tree.**

> **Simulation: The algorithm plays a game from the current state by selecting moves randomly until a terminal state is reached.**

> **Backpropagation: The algorithm updates the statistics of each node in the path from the root to the terminal node, including the number of visits and the total reward obtained.**

Once the time limit or maximum number of iterations is reached, the algorithm selects the best move by choosing the child node with the highest number of visits from the root node.

## **Requirements**

- CMake: This is an open-source, cross-platform build system that you can use to build, test, and package software. You can download CMake from the official website: https://cmake.org/.

- g++12: This is a C++ compiler that supports C++20, which is required for your Tron game implementation. You can install g++12 on Linux by running the following command in the terminal:

```bash
$ sudo apt-get install g++-12
```

- Qt framework version 6: This is a cross-platform application framework that provides a comprehensive set of libraries and tools for developing graphical user interfaces (GUIs) and other applications. You can download Qt 6 from the official website: https://www.qt.io/download.

**Once you have installed all the necessary requirements, you can build and run your Tron game implementation using CMake.**

```bash
$ cmake . -DCMAKE_PREFIX_PATH:PATH=/home/{userName}/Qt/6.4.2/gcc_64
```

Replace your username with {userName}

**_I am using ubuntu 22.04 by the way._**
