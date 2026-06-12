#ifndef RULESMENU_HPP
#define RULESMENU_HPP

#include <SFML/Graphics.hpp>
#include <functional>

/**
 * @class RulesMenu
 * @brief Represents the rules menu screen with an option to return to the main menu.
 */
class RulesMenu {
 public:
  /**
   * @brief Constructs a RulesMenu with a specified window size.
   * @param windowSize The size of the window to scale the background and position elements accordingly.
   */
  RulesMenu(sf::Vector2u windowSize);

  /**
   * @brief Handles user input events for menu interactions.
   * 
   * Triggers the callback function when the user clicks the "Return to Menu" button.
   * @param event The SFML event object that captures user interactions.
   * @param onReturnToMenu Callback triggered when the user clicks the "Return to Menu" button.
   */
  void handleEvent(const sf::Event& event,
      std::function<void()> onReturnToMenu);

  /**
   * @brief Renders the rules menu on the specified window.
   * 
   * Draws the background and return button.
   * @param window The window where the rules menu will be drawn.
   */
  void render(sf::RenderWindow& window);

 private:
  sf::RectangleShape returnButton;  /**< Button to return to the main menu */

  sf::Texture backgroundTexture;    /**< Texture for the background */
  sf::Sprite backgroundSprite;      /**< Sprite that displays the background texture */
};

#endif // RULESMENU_HPP
