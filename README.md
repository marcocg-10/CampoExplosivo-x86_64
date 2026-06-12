# 💣 Campo Explosivo

A multiplayer strategy game inspired by the classic Minesweeper, developed using **x86_64 Assembly**, **C++**, and **SFML**.

Campo Explosivo takes the core mechanics of Minesweeper and transforms them into a competitive experience where two players face off on separate minefields. In addition to uncovering mines, players can discover and launch missiles, creating new ways to attack, defend, and ultimately win the game.

## Overview

Traditional Minesweeper is a single-player game focused on logic, probability, and careful decision-making. Campo Explosivo builds upon those concepts and introduces new gameplay mechanics that make matches more dynamic and interactive. The project is based on three main features:

### 👥 Multiplayer Gameplay

Unlike classic Minesweeper, Campo Explosivo is designed for two players.

Each player has their own minefield represented by an independent matrix. Throughout the match, players must uncover cells, identify threats, and react to their opponent's actions. Decisions made by one player can directly affect the progress of the other, creating a competitive environment that goes beyond simply achieving the fastest completion time.

### 🚀 Missile System

Missiles introduce an offensive mechanic that does not exist in traditional Minesweeper.

By discovering a missile on the board, a player gains the ability to launch it at the opponent's field. Depending on where it lands, the missile can:

* Trigger an enemy mine and instantly win the game.
* Destroy an enemy missile before it can be used.
* Reveal an unexplored cell without triggering a mine.

Players must therefore balance exploration, risk management, and offensive strategies throughout the match.

### 🏆 Multiple Victory Conditions

Campo Explosivo offers more than one path to victory:

1. Successfully uncover all mines on your own board without triggering any of them.
2. Find a missile and use it to detonate a hidden mine on your opponent's field.

These alternative win conditions create more strategic and unpredictable matches.

## Game Rules

* The game is played in turns until a winner is determined.
* A player wins by:

  * Discovering all mines on their own field, or
  * Detonating a mine on the opponent's field using a missile.
* Missiles can:

  * Detonate an enemy mine and immediately win the game.
  * Destroy an enemy missile.
  * Reveal an empty or numbered cell.
* Players have a limited amount of time to launch a missile after obtaining it.
* The first click of each player is always safe and cannot contain mines or missiles.

## Technologies

* x86_64 Assembly
* C++
* SFML
* Makefile
* Linux

## Prerequisites

This project was developed and tested on **Linux**. If you are using **Windows**, it is recommended to compile and run the project through **Windows Subsystem for Linux (WSL)**.

### Required Software

Before compiling the project, install the following dependencies:

```bash
sudo apt update

sudo apt install build-essential
sudo apt install nasm
sudo apt install libsfml-dev
```

### Verify Installation

Make sure the required tools are available:

```bash
g++ --version
nasm --version
make --version
```

**Note:** Running the project directly from PowerShell or Command Prompt is not officially supported. The recommended environment is Linux or WSL with graphical support enabled.



## Compilation & Execution

### Option 1: Using the Makefile

From the project root directory:

```bash
make run
```

### Option 2: Manual Compilation

```bash
nasm -g -f elf64 -o build/objASM.o campo_explosivo/campoExplosivo.asm
g++ -g -Iinclude -no-pie -c -o build/objMain.o interfaz/main.cpp
g++ -g -Iinclude -no-pie -c -o build/objGame.o interfaz/Game.cpp
g++ -g -Iinclude -no-pie -c -o build/objMainMenu.o interfaz/MainMenu.cpp
g++ -g -Iinclude -no-pie -c -o build/objSettingsMenu.o interfaz/SettingsMenu.cpp
g++ -g -Iinclude -no-pie -c -o build/objRulesMenu.o interfaz/RulesMenu.cpp
g++ -g -Iinclude -no-pie -c -o build/objHowToPlayMenu.o interfaz/HowToPlayMenu.cpp
g++ -g -Iinclude -no-pie -c -o build/objMinesweeper.o interfaz/Minesweeper.cpp
g++ -g -Iinclude -no-pie -c -o build/objGameOver.o interfaz/GameOver.cpp
g++ -g -Iinclude -no-pie -c -o build/objPlayground.o campo_explosivo/Playground.cpp

g++ -g -Iinclude -no-pie -o build/CampoExplosivo \
build/objASM.o \
build/objMain.o \
build/objGame.o \
build/objMainMenu.o \
build/objSettingsMenu.o \
build/objRulesMenu.o \
build/objHowToPlayMenu.o \
build/objMinesweeper.o \
build/objGameOver.o \
build/objPlayground.o \
-lsfml-graphics -lsfml-window -lsfml-system
```

### Running the Game

```bash
./build/CampoExplosivo
```

After execution, the game window will open and display the main menu.

## Academic Context

This project was developed as part of a university course focused on low-level programming and software development using x86_64 Assembly. The objective was to combine Assembly programming with modern C++ components to create a complete and interactive application.
