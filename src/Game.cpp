#include "Game.hpp"
#include <algorithm>

Game::Game(int width, int height, int mines)
    : width(width), height(height), mines(mines), board(height, std::vector<int>(width, 0)) {
    reveal_board.resize(height);
    for (int i = 0; i < height; ++i) {
        reveal_board[i].resize(width, false);
    }
    reset();
}

void Game::reset() {
    board.assign(height, std::vector<int>(width, 0));
    placeMines();
    calculateAdjacentMines();
    gameOver = false;
}

bool Game::isRevealed(int x, int y) {
    return reveal_board[x][y];
}

bool Game::isWon() {
    for (int x=0; x<width;x++)
        for (int y=0; y<height;y++)
            if ((reveal_board[x][y]&& board[x][y]==IS_BOMB)||
                (not reveal_board[x][y]and board[x][y]!=IS_BOMB))
                return false;
    return true;
}



int Game::reveal(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) return -1;
    if (board[y][x]==IS_BOMB)
        gameOver==true;
    reveal_board[y][x]=true;
    return board[y][x];
}

void Game::placeMines() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, width * height - 1);

    int placedMines = 0;
    while (placedMines < mines) {
        int index = dis(gen);
        int x = index % width;
        int y = index / width;
        if (board[y][x] == 0) {
            board[y][x] = IS_BOMB;
            ++placedMines;
        }
    }
}

void Game::calculateAdjacentMines() {
    constexpr std::array<std::pair<int, int>, 8> directions = {{
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0},           {1, 0},
        {-1, 1},  {0, 1},  {1, 1}
    }};

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (board[y][x] == IS_BOMB) continue;

            int adjacentMines = 0;
            for (const auto& [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height && board[ny][nx] == IS_BOMB) {
                    ++adjacentMines;
                }
            }
            board[y][x] = adjacentMines;
        }
    }

}
