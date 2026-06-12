#ifndef HOWTOPLAYMENU_HPP
#define HOWTOPLAYMENU_HPP

#include <SFML/Graphics.hpp>
#include <functional>

/**
 * @class HowToPlayMenu
 * @brief Represents the "How to Play" screen where instructions for the game are displayed.
 */
class HowToPlayMenu {
 public:
  /**
   * @brief Constructs a HowToPlayMenu with a specified window size.
   * @param windowSize The size of the window to correctly position and scale the background and elements.
   */
  HowToPlayMenu(sf::Vector2u windowSize);

  /**
   * @brief Handles user input events for menu interactions.
   * 
   * Allows the user to return to the main menu by clicking the designated button.
   * @param event The SFML event object capturing user interactions.
   * @param onReturnToMenu Callback triggered when the user clicks the "Return" button.
   */
  void handleEvent(const sf::Event& event,
      std::function<void()> onReturnToMenu);

  /**
   * @brief Renders the "How to Play" menu on the specified window.
   * 
   * Draws the background, instructional text, and return button.
   * @param window The window where the "How to Play" menu will be drawn.
   */
  void render(sf::RenderWindow& window);

 private:
  sf::RectangleShape returnButton; /**< Button to return to the previous menu */

  sf::Texture backgroundTexture;   /**< Texture for the background image */
  sf::Sprite backgroundSprite;     /**< Sprite to display the background texture */
};

#endif // HOWTOPLAYMENU_HPP
