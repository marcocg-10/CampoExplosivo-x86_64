#include "GameOver.hpp"
#include <iostream>

GameOver::GameOver(sf::Vector2u windowSize) {
  backgroundTextureWinnerPlayer1.loadFromFile("interfaz/textures/winnerPlayer1.png");
  backgroundSpriteWinnerPlayer1.setTexture(backgroundTextureWinnerPlayer1);
  backgroundSpriteWinnerPlayer1.setScale(
    float(windowSize.x) / backgroundTextureWinnerPlayer1.getSize().x,
    float(windowSize.y) / backgroundTextureWinnerPlayer1.getSize().y
  );

  backgroundTextureWinnerPlayer2.loadFromFile("interfaz/textures/winnerPlayer2.png");
  backgroundSpriteWinnerPlayer2.setTexture(backgroundTextureWinnerPlayer2);
  backgroundSpriteWinnerPlayer2.setScale(
    float(windowSize.x) / backgroundTextureWinnerPlayer2.getSize().x,
    float(windowSize.y) / backgroundTextureWinnerPlayer2.getSize().y
  );

  returnButton.setSize(sf::Vector2f(350, 150));
  returnButton.setFillColor(sf::Color::Transparent);
  returnButton.setPosition(630, 735);
}

void GameOver::handleEvent(const sf::Event& event, std::function<void()> onReturnToMenu) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (returnButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
      onReturnToMenu();
    }
  }
}

void GameOver::render(sf::RenderWindow& window) {
  if (this->winner == 1) {
    window.draw(backgroundSpriteWinnerPlayer1);
  } else {
    window.draw(backgroundSpriteWinnerPlayer2);
  }
  window.draw(returnButton);
}

void GameOver::setWinner(const int& winner) {
  this->winner = winner;
}

