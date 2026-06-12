#include "HowToPlayMenu.hpp"

HowToPlayMenu::HowToPlayMenu(sf::Vector2u windowSize) {
  backgroundTexture.loadFromFile("interfaz/textures/howToPlay.png");

  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setScale(
    float(windowSize.x) / backgroundTexture.getSize().x,
    float(windowSize.y) / backgroundTexture.getSize().y
  );

  returnButton.setSize(sf::Vector2f(64, 64));
  returnButton.setFillColor(sf::Color::Transparent);
  returnButton.setPosition(1375, 40);
}

void HowToPlayMenu::handleEvent(const sf::Event& event, std::function<void()> onReturnToMenu) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (returnButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
      onReturnToMenu();
    }
  }
}

void HowToPlayMenu::render(sf::RenderWindow& window) {
  window.draw(backgroundSprite);

  window.draw(returnButton);
}
