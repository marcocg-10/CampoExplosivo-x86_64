#include "SettingsMenu.hpp"

SettingsMenu::SettingsMenu(sf::Vector2u windowSize) {
  backgroundTexture.loadFromFile("interfaz/textures/settings.png");

  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setScale(
    float(windowSize.x) / backgroundTexture.getSize().x,
    float(windowSize.y) / backgroundTexture.getSize().y
  );

  returnButton.setSize(sf::Vector2f(320, 140));
  returnButton.setFillColor(sf::Color::Transparent);
  returnButton.setPosition(16, 744);

  howToPlayButton.setSize(sf::Vector2f(912, 176));
  howToPlayButton.setFillColor(sf::Color::Transparent);
  howToPlayButton.setPosition(16, 16);

  rulesButton.setSize(sf::Vector2f(500, 168));
  rulesButton.setFillColor(sf::Color::Transparent);
  rulesButton.setPosition(16, 200);
}

void SettingsMenu::handleEvent(const sf::Event& event,
    std::function<void()> onReturnToMenu, std::function<void()> onHowToPlay,
    std::function<void()> onRules) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (returnButton.getGlobalBounds().contains(event.mouseButton.x,
        event.mouseButton.y)) {
      onReturnToMenu();
    } else if (howToPlayButton.getGlobalBounds().contains(event.mouseButton.x,
        event.mouseButton.y)) {
      onHowToPlay();
    } else if (rulesButton.getGlobalBounds().contains(event.mouseButton.x,\
        event.mouseButton.y)) {
      onRules();
    }
  }
}

void SettingsMenu::render(sf::RenderWindow& window) {
  window.draw(backgroundSprite);

  window.draw(returnButton);
  window.draw(howToPlayButton);
  window.draw(rulesButton);
}
