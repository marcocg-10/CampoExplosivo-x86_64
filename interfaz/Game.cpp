#include "Game.hpp"
#include <iostream>

Game::Game() 
    : window(sf::VideoMode(1600, 900), "Campo Explosivo"), 
    mainMenu(window.getSize()), 
    settingsMenu(window.getSize()),
    howToPlayMenu(window.getSize()),
    rulesMenu(window.getSize()),
    minesweeper1(window.getSize()),
    minesweeper2(window.getSize()),
    gameOver(window.getSize()) {
  this->currentState = State::MainMenu;
  this->currentPlayer = 1;
}

void Game::run() {
  while (window.isOpen()) {
    this->processEvents();
    this->render();
  }
}

void Game::processEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    } else if (currentState == State::MainMenu) {
      mainMenu.handleEvent(event, 
        [this]() { window.close(); },
        [this]() { this->currentState = State::InGame; },
        [this]() { this->currentState = State::Settings; }
      );
    } else if (currentState == State::Settings) {
      settingsMenu.handleEvent(event, 
        [this]() { this->currentState = State::MainMenu; },
        [this]() { this->currentState = State::HowToPlay; },
        [this]() { this->currentState = State::Rules; }
      );
    } else if (currentState == State::HowToPlay) {
      howToPlayMenu.handleEvent(event, [this]() {
        this->currentState = State::Settings; });
    } else if (currentState == State::Rules) {
      rulesMenu.handleEvent(event, [this]() {
        this->currentState = State::Settings; });
    } else if (currentState == State::InGame) {
      if (currentPlayer == 1) {
        minesweeper1.handleEvent(event, window, currentPlayer,
            minesweeper2.hasToLaunchMissile());
      } else {
        minesweeper2.handleEvent(event, window, currentPlayer,
            minesweeper1.hasToLaunchMissile());
      }
        
      window.setTitle("Campo Explosivo - Jugador " +
          std::to_string(currentPlayer));

      if (minesweeper1.hasToLaunchMissile()) {
        minesweeper2.setBeingBombed(true);
      } else if (minesweeper2.hasToLaunchMissile()) {
        minesweeper1.setBeingBombed(true);
      }

      if (minesweeper1.isBeingBombed()) {
        currentPlayer = 1;
      } else if (minesweeper2.isBeingBombed()) {
        currentPlayer = 2;
      }

      if (minesweeper1.isGameOver() || minesweeper2.isGameOver()) {
        currentState = State::GameOver;
        if (minesweeper1.isGameOver()) {
          currentPlayer = 2;
        } else {
          currentPlayer = 1;
        }
      }
      

    } else if (currentState == State::GameOver) {
      gameOver.setWinner(currentPlayer);
      gameOver.handleEvent(event, [this]() { 
        currentState = State::MainMenu;
        minesweeper1.reset();
        minesweeper2.reset();
        currentPlayer = 1;
      });
    }
  }
}

void Game::render() {
  window.clear(sf::Color::White);
  if (currentState == State::MainMenu) {
    mainMenu.render(window);
  } else if (currentState == State::Settings) {
    settingsMenu.render(window);
  } else if (currentState == State::HowToPlay) {
    howToPlayMenu.render(window);
  } else if (currentState == State::Rules) {
    rulesMenu.render(window);
  } else if (currentState == State::InGame) {
    if (currentPlayer == 1) {
      minesweeper1.render(window, 1);
    } else {
      minesweeper2.render(window, 2);
    }
  } else if (currentState == State::GameOver) {
    gameOver.render(window);  // Mostrar la pantalla GameOver
  }
  window.display();
}
