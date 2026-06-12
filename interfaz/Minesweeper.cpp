#include "Minesweeper.hpp"
#include <SFML/Graphics.hpp>

Minesweeper::Minesweeper(sf::Vector2u windowSize)
    : cellSize(windowSize.x / 30),
    gameOver(false), 
    launchMissile(false),
    beingBombed(false) {
  board.resize(15, std::vector<int>(15, 0));
  revealed.resize(15, std::vector<bool>(15, false));
  flagged.resize(15, std::vector<bool>(15, false));
  bombed.resize(15, std::vector<bool>(15, false));


  backgroundTexturePlayer1.loadFromFile("interfaz/textures/minesweeperPlayer1.png");
  backgroundSpritePlayer1.setTexture(backgroundTexturePlayer1);
  backgroundSpritePlayer1.setScale(
    float(windowSize.x) / backgroundTexturePlayer1.getSize().x,
    float(windowSize.y) / backgroundTexturePlayer1.getSize().y
  );

  backgroundTexturePlayer2.loadFromFile("interfaz/textures/minesweeperPlayer2.png");
  backgroundSpritePlayer2.setTexture(backgroundTexturePlayer2);
  backgroundSpritePlayer2.setScale(
    float(windowSize.x) / backgroundTexturePlayer2.getSize().x,
    float(windowSize.y) / backgroundTexturePlayer2.getSize().y
  );

  backgroundBombingTexturePlayer1.loadFromFile("interfaz/textures/bombingPlayer2.png");
  backgroundBombingSpritePlayer1.setTexture(backgroundBombingTexturePlayer1);
  backgroundBombingSpritePlayer1.setScale(
    float(windowSize.x) / backgroundBombingTexturePlayer1.getSize().x,
    float(windowSize.y) / backgroundBombingTexturePlayer1.getSize().y
  );

  backgroundBombingTexturePlayer2.loadFromFile("interfaz/textures/bombingPlayer1.png");
  backgroundBombingSpritePlayer2.setTexture(backgroundBombingTexturePlayer2);
  backgroundBombingSpritePlayer2.setScale(
    float(windowSize.x) / backgroundBombingTexturePlayer2.getSize().x,
    float(windowSize.y) / backgroundBombingTexturePlayer2.getSize().y
  ); 
  
  clickCount = 0;
  font.loadFromFile("interfaz/fonts/OpenSans-Bold.ttf");
  flagTexture.loadFromFile("interfaz/textures/flag.png");
  rocketTexture.loadFromFile("interfaz/textures/rocket.png");
  dirtTexture.loadFromFile("interfaz/textures/dirt.png");
  explosionTexture.loadFromFile("interfaz/textures/explosion.png");

  initializeBoard();
}

bool Minesweeper::isGameOver() const {
  return gameOver;
}

bool& Minesweeper::hasToLaunchMissile() {
  return launchMissile;
}

void Minesweeper::setLaunchMissile(bool state) {
  launchMissile = state;
}

bool Minesweeper::isBeingBombed() const {
  return beingBombed;
}

void Minesweeper::setBeingBombed(bool state) {
  beingBombed = state;
}

void Minesweeper::reset() {
  gameOver = false;
  beingBombed = false;
  launchMissile = false;

  for (int i = 0; i < 15; ++i) {
    for (int j = 0; j < 15; ++j) {
      board[i][j] = 0;
      revealed[i][j] = false;
      flagged[i][j] = false;
      bombed[i][j] = false;
    }
  }
  clickCount = 0;
  initializeBoard();
}

void Minesweeper::initializeBoard() {
  Playground playground(15, 15, 40, 5);
  playground.iniciarTablero();

  for (int i = 0; i < 15; ++i) {
    for (int j = 0; j < 15; ++j) {
      board[i][j] = playground.tablero[i * 15 + j];
    }
  }
  playground.mostrarTablero();
}

void Minesweeper::handleEvent(const sf::Event& event, sf::RenderWindow& window,
    int& currenPlayer, bool& launchingMissile) {
  if (event.type == sf::Event::MouseButtonPressed) {
    int row = event.mouseButton.y / cellSize;
    int col = event.mouseButton.x / cellSize;

    if (row >= 0 && row < 15 && col >= 0 && col < 15 && !beingBombed) {
      if (event.mouseButton.button == sf::Mouse::Left) {
        if (!revealed[row][col]) {
          ++clickCount;
        }
        revealCell(row, col);
      } else if (event.mouseButton.button == sf::Mouse::Right) {
        if (!flagged[row][col]) {
          ++clickCount;
        }
        toggleFlag(row, col);
      }
      render(window, currenPlayer);
      if (clickCount >= 5) {
        currenPlayer = (currenPlayer == 1) ? 2 : 1;
        clickCount = 0;
      }
      checkVictory();
    } else if (row >= 0 && row < 15 && col >= 0 && col < 15 && beingBombed) {
      handleBombing(row, col);
      beingBombed = false;
      launchingMissile = false;
      currenPlayer = (currenPlayer == 1) ? 2 : 1;
    }
  }
}

void Minesweeper::revealCell(int row, int col) {
  if (!revealed[row][col] && !flagged[row][col]) {
    revealed[row][col] = true;
    
    if (board[row][col] == -1) {
        gameOver = true;
        cellShape.setFillColor(sf::Color::Red);
    } else {
      if (board[row][col] == 9) {
        launchMissile = true;
      } else if (board[row][col] == 0) {
        revealAdjacentCells(row, col);
      }
      cellShape.setFillColor(sf::Color::White);
    }
  }
}

void Minesweeper::revealAdjacentCells(int row, int col) {
  for (int i = row - 1; i <= row + 1; ++i) {
    for (int j = col - 1; j <= col + 1; ++j) {
      if (i >= 0 && i < 15 && j >= 0 && j < 15 && !revealed[i][j] && !flagged[i][j]) {
        if (board[i][j] == 9) {
          continue;
        }
        
        revealed[i][j] = true;

        if (board[i][j] == -1) {
          gameOver = true;
          cellShape.setFillColor(sf::Color::Red);
        } else {
          cellShape.setFillColor(sf::Color::White);
        }

        if (board[i][j] == 0) {
          revealAdjacentCells(i, j);
        }
      }
    }
  }
}

void Minesweeper::handleBombing(int row, int col) {
  for (int i = row - 1; i < row + 2; ++i) {
    for (int j = col - 1; j < col + 2; ++j) {
      if (i >= 0 && i <= 14 && j >= 0 && j <= 14) {
        bombed[i][j] = true;
        if (board[i][j] == -1) {
          gameOver = true;
          cellShape.setFillColor(sf::Color::Red);
        } else {
          cellShape.setFillColor(sf::Color::White);
        }
      }
    }
  }
}

void Minesweeper::toggleFlag(int row, int col) {
  if (!revealed[row][col]) {
    flagged[row][col] = !flagged[row][col];
  }
}

void Minesweeper::render(sf::RenderWindow& window, int player) {
  if (player == 1) {
    if (this->beingBombed) {
      window.draw(backgroundBombingSpritePlayer1);
    } else {
      window.draw(backgroundSpritePlayer1);
    }
  } else {
    if (this->beingBombed) {
      window.draw(backgroundBombingSpritePlayer2);
    } else {
      window.draw(backgroundSpritePlayer2);
    }
  }
  drawBoard(window);
}

void Minesweeper::drawBoard(sf::RenderWindow& window) {
  for (int i = 0; i < 15; ++i) {
    for (int j = 0; j < 15; ++j) {
      cellShape.setPosition(j * cellSize, i * cellSize);
      if (!this->beingBombed) {
        if (revealed[i][j]) {
          if (board[i][j] == -1) {
            cellShape.setFillColor(sf::Color::Red);
            window.draw(cellShape);
          } else {
            if (board[i][j] > 0 && board[i][j] < 9) {
              sf::Text cellText;
              cellText.setFont(font);
              cellText.setString(std::to_string(board[i][j]));
              cellText.setCharacterSize(30);
              cellText.setFillColor(sf::Color::Black);
              cellText.setPosition(j * cellSize + cellSize / 4, i * cellSize +
                  cellSize / 6);

              window.draw(cellText);
            } else if (board[i][j] == 9) {
              sf::Sprite rocketSprite(rocketTexture);
              rocketSprite.setPosition(j * cellSize - cellSize / 3, i * cellSize -
                  cellSize / 2);
              window.draw(rocketSprite);
            }
          }
        } else {
          if (flagged[i][j]) {
            sf::Sprite flagSprite(flagTexture);
            flagSprite.setPosition(j * cellSize - cellSize / 3, i * cellSize -
                cellSize / 2);
            window.draw(flagSprite);
          } else {
            sf::Sprite dirtSprite(dirtTexture);
            dirtSprite.setPosition(j * cellSize, i * cellSize);
            window.draw(dirtSprite);
          }
        }
      } else {
        if (bombed[i][j]) {
          sf::Sprite explosionSprite(explosionTexture);
          explosionSprite.setPosition(j * cellSize, i * cellSize);
          window.draw(explosionSprite);
        } else {
          sf::Sprite dirtSprite(dirtTexture);
          dirtSprite.setPosition(j * cellSize, i * cellSize);
          window.draw(dirtSprite);
        }
      }
    }
  }
}

void Minesweeper::checkVictory() {
  for (int i = 0; i < 15; ++i) {
    for (int j = 0; j < 15; ++j) {
      if (this->board[i][j] == -1 && !this->flagged[i][j]) return;
      if (this->board[i][j] != -1 && !this->revealed[i][j]) return;
    }
  }
  gameOver = true;
}
