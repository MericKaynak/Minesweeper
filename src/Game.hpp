#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

class Game {
    friend class GameRenderer;
public:
    static constexpr int IS_A_BOMB = -1;
    bool isWon();
    Game(int width, int height, int mines);

    void reset();
    int getFieldValue(int x, int y);
    bool isRevealed(int x, int y);
    [[nodiscard]] bool isGameOver() const noexcept { return gameOver; }

    [[nodiscard]] const std::vector<std::vector<int>>& getBoard() const noexcept { return board; }

    [[nodiscard]] int getWidth() const noexcept { return width; }
    [[nodiscard]] int getHeight() const noexcept { return height; }

protected:
    void placeMines();
    void calculateAdjacentMines();
    int width;
    int height;
    int mines;
    std::vector<std::vector<int>> board;
    std::vector<std::vector<bool>> reveal_board;
    bool gameOver{false};

};

#endif // GAME_HPP
