#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include "SettingsMenu.hpp"
#include "HowToPlayMenu.hpp"
#include "RulesMenu.hpp"
#include "Minesweeper.hpp"
#include "GameOver.hpp"

/**
 * @class Game
 * @brief Manages the main game loop and handles different game states, including menus, gameplay, and the game over screen.
 */
class Game {
public:
  /**
   * @brief Constructs a Game instance and initializes the main game window and all game states.
   */
  Game();

  /**
   * @brief Runs the main game loop, which handles event processing, updating, and rendering.
   */
  void run();

private:
  /**
   * @brief Processes user input and updates the current state based on events.
   */
  void processEvents();

  /**
   * @brief Updates game logic based on the current state and player actions.
   */
  void update();

  /**
   * @brief Renders the appropriate screen based on the current game state.
   */
  void render();

  /**
   * @enum State
   * @brief Represents the different states or screens of the game.
   */
  enum class State { MainMenu, Settings, HowToPlay, Rules, InGame, GameOver };

  State currentState;   /**< The current state of the game, controlling the active screen */

  sf::RenderWindow window;    /**< The main window where all game elements are displayed */
  MainMenu mainMenu;          /**< The main menu screen */
  SettingsMenu settingsMenu;  /**< The settings menu screen */
  HowToPlayMenu howToPlayMenu;/**< The "How to Play" screen */
  RulesMenu rulesMenu;        /**< The rules screen */
  Minesweeper minesweeper1;   /**< The Minesweeper game for Player 1 */
  Minesweeper minesweeper2;   /**< The Minesweeper game for Player 2 */
  GameOver gameOver;          /**< The Game Over screen */

  int currentPlayer; /**< Tracks the current player's turn in the game */
};

#endif // GAME_HPP

