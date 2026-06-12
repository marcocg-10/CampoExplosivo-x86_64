#ifndef SETTINGSMENU_HPP
#define SETTINGSMENU_HPP

#include <SFML/Graphics.hpp>
#include <functional>

class SettingsMenu {
 public:
  /**
   * @brief Constructs a SettingsMenu with a specified window size.
   * @param windowSize The size of the window to scale the background and position elements accordingly.
   */
  SettingsMenu(sf::Vector2u windowSize);

  /**
   * @brief Handles user input events for menu interactions.
   * 
   * Triggers the appropriate callback function based on user clicks on the buttons.
   * @param event The SFML event object that captures user interactions.
   * @param onReturnToMenu Callback triggered when the user clicks the "Return to Menu" button.
   * @param onHowToPlay Callback triggered when the user clicks the "How to Play" button.
   * @param onRules Callback triggered when the user clicks the "Rules" button.
   */
  void handleEvent(const sf::Event& event, 
                    std::function<void()> onReturnToMenu, 
                    std::function<void()> onHowToPlay, 
                    std::function<void()> onRules);

  /**
   * @brief Renders the settings menu on the specified window.
   * 
   * Draws the background, return button, how-to-play button, and rules button.
   * @param window The window where the settings menu will be drawn.
   */
  void render(sf::RenderWindow& window);

 private:
  sf::RectangleShape returnButton;     /**< Button to return to main menu */
  sf::RectangleShape howToPlayButton;  /**< Button to view how-to-play instructions */
  sf::RectangleShape rulesButton;      /**< Button to view game rules */

  sf::Texture backgroundTexture;   /**< Texture for the background */
  sf::Sprite backgroundSprite;     /**< Sprite that displays the background texture */
};

#endif // SETTINGSMENU_HPP
