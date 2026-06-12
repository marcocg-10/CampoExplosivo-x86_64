#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics.hpp>
#include <functional>

/**
 * @class GameOver
 * @brief Represents the Game Over screen displayed when the game ends.
 */
class GameOver {
 public:
  /**
   * @brief Constructs a GameOver screen with a specified window size.
   * @param windowSize The size of the window to correctly position and scale the background and elements.
   */
  GameOver(sf::Vector2u windowSize);

  /**
   * @brief Handles user input events for interactions on the Game Over screen.
   * 
   * Allows the user to return to the main menu by clicking the designated button.
   * @param event The SFML event object capturing user interactions.
   * @param onReturnToMenu Callback triggered when the user clicks the "Return" button.
   */
  void handleEvent(const sf::Event& event,
      std::function<void()> onReturnToMenu);

  /**
   * @brief Renders the Game Over screen on the specified window.
   * 
   * Draws the background and return button.
   * @param window The window where the Game Over screen will be drawn.
   */
  void render(sf::RenderWindow& window);

  void setWinner(const int& winner);

 private:
  sf::RectangleShape returnButton; /**< Button to return to the main menu */

  // Background elements
  sf::Texture backgroundTextureWinnerPlayer1;   /**< Texture for the background image for winner player 1*/
  sf::Sprite backgroundSpriteWinnerPlayer1;     /**< Sprite to display the background texture for winnner player 1*/
  sf::Texture backgroundTextureWinnerPlayer2;   /**< Texture for the background image for winner player 2*/
  sf::Sprite backgroundSpriteWinnerPlayer2;     /**< Sprite to display the background texture for winnner player 2*/

  int winner;
};

#endif // GAMEOVER_HPP

