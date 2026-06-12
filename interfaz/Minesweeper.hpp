#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include "../campo_explosivo/Playground.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @class Minesweeper
 * @brief Manages the Minesweeper game logic and rendering.
 */
class Minesweeper {
 public:
  /**
   * @brief Constructs a Minesweeper game with a specified window size.
   * @param windowSize Size of the game window.
   */
  Minesweeper(sf::Vector2u windowSize);

  /**
   * @brief Handles user input and game events.
   * @param event Event to process.
   * @param window The main render window.
   * @param currentPlayer The current player's turn.
   * @param launchingMissile Indicates if a missile is being launched.
   */
  void handleEvent(const sf::Event& event, sf::RenderWindow& window, int& currentPlayer, bool& launchingMissile);

  /**
   * @brief Renders the Minesweeper board.
   * @param window The window where the board will be displayed.
   * @param player The current player being rendered.
   */
  void render(sf::RenderWindow& window, int player);

  /**
   * @brief Checks if the game is over.
   * @return True if the game is over, false otherwise.
   */
  bool isGameOver() const;

  /**
   * @brief Returns whether a missile is set to be launched.
   * @return Reference to the launch missile status.
   */
  bool& hasToLaunchMissile();

  /**
   * @brief Sets the missile launch status.
   * @param state True to set missile launch, false to reset.
   */
  void setLaunchMissile(bool state);

  /**
   * @brief Checks if the board is being bombed.
   * @return True if the board is being bombed, false otherwise.
   */
  bool isBeingBombed() const;

  /**
   * @brief Sets the bomb status.
   * @param state True if being bombed, false otherwise.
   */
  void setBeingBombed(bool state);

  /**
   * @brief Resets the game state for a new session.
   */
  void reset();

 private:
  /**
   * @brief Initializes the Minesweeper board with bombs and numbers.
   */
  void initializeBoard();

  /**
   * @brief Reveals the cell at the specified position.
   * @param row The row of the cell.
   * @param col The column of the cell.
   */
  void revealCell(int row, int col);

  void revealAdjacentCells(int row, int col);

  /**
   * @brief Handles the effects of bombing a cell.
   * @param row The row of the cell.
   * @param col The column of the cell.
   */
  void handleBombing(int row, int col);

  /**
   * @brief Draws the board onto the provided window.
   * @param window The window where the board will be drawn.
   */
  void drawBoard(sf::RenderWindow& window);

  /**
   * @brief Toggles a flag on a cell.
   * @param row The row of the cell.
   * @param col The column of the cell.
   */
  void toggleFlag(int row, int col);

  /**
   * @brief Checks for victory conditions.
   */
  void checkVictory();

  sf::RectangleShape cellShape;               /**< Shape for each cell on the board */
  std::vector<std::vector<int>> board;        /**< 2D vector representing bombs and numbers */
  std::vector<std::vector<bool>> revealed;    /**< Tracks revealed cells */
  std::vector<std::vector<bool>> flagged;     /**< Tracks flagged cells */
  std::vector<std::vector<bool>> bombed;     /**< Tracks bombed cells */

  sf::Font font;                              /**< Font used for displaying numbers */
  sf::Texture flagTexture;                    /**< Texture for flags */
  sf::Texture rocketTexture;                  /**< Texture for rockets */
  sf::Texture dirtTexture;                    /**< Texture for dirt */
  sf::Texture explosionTexture;                    /**< Texture for explosion */

  sf::Texture backgroundTexturePlayer1;       /**< Background texture for Player 1 */
  sf::Sprite backgroundSpritePlayer1;         /**< Background sprite for Player 1 */
  sf::Texture backgroundTexturePlayer2;       /**< Background texture for Player 2 */
  sf::Sprite backgroundSpritePlayer2;         /**< Background sprite for Player 2 */

  sf::Texture backgroundBombingTexturePlayer1;       /**< Background bombing texture for Player 1 */
  sf::Sprite backgroundBombingSpritePlayer1;         /**< Background bombing sprite for Player 1 */
  sf::Texture backgroundBombingTexturePlayer2;       /**< Background bombing texture for Player 2 */
  sf::Sprite backgroundBombingSpritePlayer2;         /**< Background bombing sprite for Player 2 */

  float cellSize;                             /**< Size of each cell */
  bool gameOver;                              /**< Tracks if the game is over */
  bool launchMissile;                         /**< Indicates if a missile should be launched */
  bool beingBombed;                           /**< Indicates if the board is being bombed */
  int clickCount;                             /**< Tracks the number of clicks */
};

#endif // MINESWEEPER_HPP

