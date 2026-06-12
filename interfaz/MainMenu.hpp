#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>
#include <functional>

/**
 * @class MainMenu
 * @brief Represents the main menu screen with options to play, access settings, or exit.
 */
class MainMenu {
 public:
  /**
   * @brief Constructs a MainMenu with a specified window size.
   * @param windowSize The size of the window to properly position and scale elements.
   */
  MainMenu(sf::Vector2u windowSize);

  /**
   * @brief Handles user input events for menu interactions.
   * 
   * Triggers the appropriate callback function based on which button the user clicks.
   * @param event The SFML event object capturing user interactions.
   * @param onExit Callback triggered when the user clicks the "Exit" button.
   * @param onPlay Callback triggered when the user clicks the "Play" button.
   * @param onSettings Callback triggered when the user clicks the "Settings" button.
   */
  void handleEvent(const sf::Event& event, 
                    std::function<void()> onExit, 
                    std::function<void()> onPlay, 
                    std::function<void()> onSettings);

  /**
   * @brief Renders the settings menu on the specified window.
   * 
   * Draws the background, return button, how-to-play button, and rules button.
   * @param window The window where the settings menu will be drawn.
   */
  void render(sf::RenderWindow& window);

 private:
  sf::RectangleShape exitButton;     /**< Button to return to main menu */
  sf::RectangleShape playButton;  /**< Button to star playing */
  sf::RectangleShape settingsButton;      /**< Button to view the settings */

  sf::Texture backgroundTexture;   /**< Texture for the background */
  sf::Sprite backgroundSprite;     /**< Sprite that displays the background texture */
};

#endif // MAINMENU_HPP