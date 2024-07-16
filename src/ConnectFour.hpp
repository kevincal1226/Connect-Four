#pragma once
#define _XOPEN_SOURCE_EXTENDED 1

#include <iostream>
#include <limits>
#include <string>
#include <vector>

const int BOARD_ROW_SIZE = 6;
const int BOARD_COL_SIZE = 7;
const int NUMBER_TO_WIN = 4;

enum PreviousDirection { U = 0, R, L, D, UR, UL, DR, DL };

const int NUMBER_OF_DIRECTIONS = 8;

const std::vector<std::string> PLAYERS = {"red", "yellow"};

const std::vector<std::pair<int, int>> DIRECTIONS = {{-1, 0}, {0, 1},   {0, -1}, {1, 0},
                                                     {-1, 1}, {-1, -1}, {1, 1},  {1, -1}};

class ConnectFour {
  public:
    ConnectFour();
    void run();
    void printBoard();
    bool checkWin(int row, int col, const char player, int count, const PreviousDirection dir);

  private:
    std::vector<std::vector<char>> board;
};
