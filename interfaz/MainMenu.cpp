#include "MainMenu.hpp"
#include <iostream>

// MainMenu::MainMenu(const sf::Vector2u& windowSize) {
//   font.loadFromFile("interfaz/fonts/OpenSans-Bold.ttf");

//   titleText.setFont(font);
//   titleText.setString("Campo Explosivo");
//   titleText.setCharacterSize(50);
//   titleText.setFillColor(sf::Color::Black);
//   titleText.setPosition(windowSize.x / 2 -titleText.getLocalBounds().width / 2,
//       windowSize.y / 3);

//   playButton.setFont(font);
//   playButton.setString("Jugar");
//   playButton.setCharacterSize(30);
//   playButton.setFillColor(sf::Color::Black);
//   playButton.setPosition(50, windowSize.y - 150);

//   exitButton.setFont(font);
//   exitButton.setString("Salir");
//   exitButton.setCharacterSize(30);
//   exitButton.setFillColor(sf::Color::Black);
//   exitButton.setPosition(50, windowSize.y - 100);

//   settingsButton.setFont(font);
//   settingsButton.setString("Ajustes");
//   settingsButton.setCharacterSize(30);
//   settingsButton.setFillColor(sf::Color::Black);
//   settingsButton.setPosition(windowSize.x - 150, windowSize.y - 100);
// }

// void MainMenu::handleEvent(const sf::Event& event, 
//     const std::function<void()>& onExit, const std::function<void()>& onPlay,
//     const std::function<void()>& onSettings) {
//   if (event.type == sf::Event::MouseButtonPressed) {
//     if (playButton.getGlobalBounds().contains(event.mouseButton.x,
//         event.mouseButton.y)) {
//       onPlay();
//     } else if (exitButton.getGlobalBounds().contains(event.mouseButton.x,
//         event.mouseButton.y)) {
//       onExit();
//     } else if (settingsButton.getGlobalBounds().contains(event.mouseButton.x,
//         event.mouseButton.y)) {
//       onSettings();
//     }
//   }
// }

// void MainMenu::render(sf::RenderWindow& window) {
//   window.draw(titleText);

//   window.draw(playButton);
//   window.draw(exitButton);
//   window.draw(settingsButton);
// }

MainMenu::MainMenu(sf::Vector2u windowSize) {
  backgroundTexture.loadFromFile("interfaz/textures/mainmenu.png");

  backgroundSprite.setTexture(backgroundTexture);
  backgroundSprite.setScale(
    float(windowSize.x) / backgroundTexture.getSize().x,
    float(windowSize.y) / backgroundTexture.getSize().y
  );

  exitButton.setSize(sf::Vector2f(250, 105));
  exitButton.setFillColor(sf::Color::Transparent);
  exitButton.setPosition(32, 787);

  playButton.setSize(sf::Vector2f(265, 105));
  playButton.setFillColor(sf::Color::Transparent);
  playButton.setPosition(32, 670);

  settingsButton.setSize(sf::Vector2f(105, 105));
  settingsButton.setFillColor(sf::Color::Transparent);
  settingsButton.setPosition(290, 787);
}

void MainMenu::handleEvent(const sf::Event& event,
    std::function<void()> onExit, std::function<void()> onPlay,
    std::function<void()> onSettings) {
  if (event.type == sf::Event::MouseButtonPressed) {
    if (exitButton.getGlobalBounds().contains(event.mouseButton.x,
        event.mouseButton.y)) {
      onExit();
    } else if (playButton.getGlobalBounds().contains(event.mouseButton.x,
        event.mouseButton.y)) {
      onPlay();
    } else if (settingsButton.getGlobalBounds().contains(event.mouseButton.x,\
        event.mouseButton.y)) {
      onSettings();
    }
  }
}

void MainMenu::render(sf::RenderWindow& window) {
  window.draw(backgroundSprite);

  window.draw(exitButton);
  window.draw(playButton);
  window.draw(settingsButton);
}
