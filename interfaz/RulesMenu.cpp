#include "RulesMenu.hpp"

RulesMenu::RulesMenu(sf::Vector2u windowSize) {
  backgroundTexture.loadFromFile("interfaz/textures/rules.png");

  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setScale(
    float(windowSize.x) / backgroundTexture.getSize().x,
    float(windowSize.y) / backgroundTexture.getSize().y
  );

  returnButton.setSize(sf::Vector2f(64, 64));
  returnButton.setFillColor(sf::Color::Transparent);
  returnButton.setPosition(1375, 40);
}

void RulesMenu::handleEvent(const sf::Event& event, std::function<void()> onReturnToMenu) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (returnButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
      onReturnToMenu();
    }
  }
}

void RulesMenu::render(sf::RenderWindow& window) {
  window.draw(backgroundSprite);

  window.draw(returnButton);
}

