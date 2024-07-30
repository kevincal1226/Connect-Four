#include "ConnectFour.hpp"

ConnectFour::ConnectFour()
    : board(std::vector<std::vector<char>>(BOARD_ROW_SIZE, std::vector<char>(BOARD_COL_SIZE, ' '))) {}

void ConnectFour::run() {
    bool end = false;
    int roundNumber = 0;
    while (!end && roundNumber < BOARD_ROW_SIZE * BOARD_COL_SIZE) {
        std::cout << "Drop a " << PLAYERS[roundNumber % PLAYERS.size()] << " disc at column (0 - " << BOARD_COL_SIZE - 1
                  << ") : ";
        int dropCol = -1;
        std::cin >> dropCol;
        if (std::cin.fail()) {
            std::cout << "\nFailed to read type integer from stream.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (dropCol < 0 || dropCol >= BOARD_COL_SIZE) {
            std::cout << "\nInvalid number. Must be in the range 0 to " << BOARD_COL_SIZE - 1 << " inclusive.\n\n";
            continue;
        }
        int dropRow = BOARD_ROW_SIZE;
        for (int i = BOARD_ROW_SIZE - 1; i >= 0; --i) {
            if (board[i][dropCol] == ' ') {
                dropRow = i;
                break;
            }
        }
        if (dropRow == BOARD_ROW_SIZE) {
            std::cout << "\nColumn already full.\n\n";
            continue;
        }
        board[dropRow][dropCol] = static_cast<char>(toupper(PLAYERS[roundNumber % PLAYERS.size()][0]));
        ConnectFour::printBoard();
        for (int i = 0; i < NUMBER_OF_DIRECTIONS; ++i) {
            end = end || ConnectFour::checkWin(dropRow + DIRECTIONS[i].first, dropCol + DIRECTIONS[i].second,
                                               board[dropRow][dropCol], 1, static_cast<PreviousDirection>(i));
        }
        if (!end)
            ++roundNumber;
    }
    if (end) {
        std::cout << "The " << PLAYERS[roundNumber % PLAYERS.size()] << " player won. Congratulations.\n";
    }
    else {
        std::cout << "Tie. Neither player wins.\n";
    }
}

void ConnectFour::printBoard() {
    std::cout << ' ';
    for (int i = 0; i < BOARD_COL_SIZE; ++i) {
        std::cout << i << ' ';
    }
    std::cout << "\n";
    for (const std::vector<char> &vec : board) {
        std::cout << std::string(BOARD_COL_SIZE * 2, '-') << "\n|";
        for (const char c : vec) {
            std::cout << c << '|';
        }
        std::cout << '\n';
    }
    std::cout << std::string(BOARD_COL_SIZE * 2, '-') << "\n\n";
}

bool ConnectFour::checkWin(int row, int col, const char player, int count, const PreviousDirection dir) {
    if (row < 0 || col < 0 || row >= BOARD_ROW_SIZE || col >= BOARD_COL_SIZE || board[row][col] != player) {
        return false;
    }
    ++count;
    if (count >= NUMBER_TO_WIN) {
        return true;
    }
    return ConnectFour::checkWin(row + DIRECTIONS[dir].first, col + DIRECTIONS[dir].second, player, count, dir);
}
