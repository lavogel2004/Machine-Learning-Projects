//
// Created by Ben Eisner on 11/5/24.
//

#include "GomokuGame.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

GomokuGame::GomokuGame()
    : GameBase(GOMOKU_BOARD_DIM),  // default 19x19 board
      totalMoves(0),
      winLength(GOMOKU_WIN_LENGTH) {  // Default 5 in a row
    activePlayer = "B"; //always start w black
    symbolWidth = 1; //all symbols width 1

    for (int i = 0; i < gridDimension; ++i) {
        for (int j = 0; j < gridDimension; ++j) {
            gameGrid[i][j] = ' ';
        }
    }
}

//Extra Credit board size constructor
GomokuGame::GomokuGame(int boardSize)
    : GameBase(boardSize),
      totalMoves(0),
      winLength(min(5, boardSize)) {  //accounts for if board size < 5 so wins are possible
    activePlayer = "B";
    symbolWidth = 1;

    for (int i = 0; i < gridDimension; ++i) {
        for (int j = 0; j < gridDimension; ++j) {
            gameGrid[i][j] = ' ';
        }
    }
}

GomokuGame::GomokuGame(int boardSize, int requiredWinLength)
    : GameBase(boardSize),
      totalMoves(0),
      winLength(requiredWinLength) {
    activePlayer = "B";
    symbolWidth = 1;

    for (int i = 0; i < gridDimension; ++i) {
        for (int j = 0; j < gridDimension; ++j) {
            gameGrid[i][j] = ' ';
        }
    }
}


bool GomokuGame::getPlayerInput(unsigned int& x, unsigned int& y) const {
    string input;
    while (true) {
        cout << "Enter your move ('2,1'/'quit'): ";
        getline(cin, input);

        if (input == "quit") {
            cout << "Game is over - Player " << activePlayer << " quits\n";
            cout << "Moves played this game: " << totalMoves << endl;
            return true;
        }

        size_t comma_position = input.find(',');
        if (comma_position != string::npos) {
            try {
                x = stoi(input.substr(0, comma_position));
                y = stoi(input.substr(comma_position + 1));

                //cnvert from 1-based to 0-based indexing
                if (x >= 1 && x <= GOMOKU_BOARD_DIM && y >= 1 && y <= GOMOKU_BOARD_DIM &&
                    gameGrid[y-1][x-1] == ' ') {
                    return false;  // Valid move
                    }

                if (x < 1 || x > GOMOKU_BOARD_DIM || y < 1 || y > GOMOKU_BOARD_DIM) {
                    cout << "You cannot make that move. Try again.\n";
                } else {
                    cout << "You cannot move in a space that is already occupied. Try again\n";
                }
            }
            catch (...) {
                cout << "Invalid input. Use two numbers separated by comma ('1,2' for example) \n";
            }
        } else {
            cout << "Invalid input. '1,2' is a valid input for example.\n";
        }
    }
}


int GomokuGame::play() {
    displayBoard();
    while (true) {
        if (!processMove()) {
            return static_cast<int>(GameStatus::QUIT);
        }

        if (isGameDraw()) {
            cout << "Game over. It's a draw!\n";
            return static_cast<int>(GameStatus::DRAW);
        }

        if (isGameOver()) {
            cout << "Player " << activePlayer << " wins!\n";
            return static_cast<int>(GameStatus::SUCCESS);
        }
    }
}

ostream& operator<<(ostream& os, const GomokuGame& game) {
    // determin width needed for row numbers (y-axis)
    int yAxisWidth = to_string(game.gridDimension).length();

    // Print board rows (y-axis)
    for (int i = game.gridDimension - 1; i >= 0; --i) {
        //align row numbers with proper width
        os << setw(yAxisWidth) << right << (i + 1) << " ";

        //print pieces with consistent spacing
        for (int j = 0; j < game.gridDimension; ++j) {
            os << game.gameGrid[i][j];
            //add space between pieces, but handle spacing for last piece
            if (j < game.gridDimension - 1) {
                os << " ";
            }
        }
        os << '\n';
    }

    // Print x-axis numbers
    os << string(yAxisWidth + 1, ' ');

    // Print column numbers
    for (int i = 1; i <= game.gridDimension; i++) {
        if (i < 10) {
            os << i << " ";  // single digit board labels -  add space
        } else {
            os << i;         // Double digit board labels -  no extra space
            if (i < game.gridDimension) {
                os << " ";   //add space between numbers unless it's the last one
            }
        }
    }
    os << "\n";

    return os;
}

bool GomokuGame::processMove() {
    unsigned int x, y;
    cout << "Player " << activePlayer << "'s turn.\n";

    if (totalMoves > 1) {
        cout << "Previous moves for Player " << activePlayer << ":";
        const auto& moves = (activePlayer == "B") ? playerMovesB : playerMovesW;
        for (const auto& move : moves) {
            cout << " (" << move.first << "," << move.second << ")";
        }
        cout << endl;
    }

    if (getPlayerInput(x, y)) {
        return false;
    }

    ++totalMoves;
    auto& currentMoves = (activePlayer == "B") ? playerMovesB : playerMovesW;
    currentMoves.push_back(make_pair(x, y));

    // Convert from 1-based to 0-based indexing
    gameGrid[y-1][x-1] = activePlayer[0];

    displayBoard();

    if (!isGameOver() && !isGameDraw()) {
        if (activePlayer == "B") {
            activePlayer = "W";
        } else {
            activePlayer = "B";
        }
    }

    return true;
}

void GomokuGame::displayBoard() {
    cout << *this << endl;
}

bool GomokuGame::checkLine(int startX, int startY, int dx, int dy) const {
    char piece = gameGrid[startY][startX];
    if (piece == ' ') return false;

    for (int i = 1; i < winLength; ++i) {
        int newX = startX + dx * i;
        int newY = startY + dy * i;
        if (newX < 0 || newX >= gridDimension ||
            newY < 0 || newY >= gridDimension ||
            gameGrid[newY][newX] != piece) {
            return false;
            }
    }
    return true;
}

bool GomokuGame::isGameOver() const {
    //check horizontal, vertical and diagonal lines
    for (int i = 0; i < gridDimension; ++i) {
        for (int j = 0; j < gridDimension; ++j) {
            if (checkLine(j, i, 1, 0) || // Horizontal
                checkLine(j, i, 0, 1) || // Vertical
                checkLine(j, i, 1, 1) || // Diagonal
                checkLine(j, i, 1, -1))  // Other  Diagonal
            {
                return true;
            }
        }
    }
    return false;
}

bool GomokuGame::isGridFull() const {
    return totalMoves == GOMOKU_BOARD_DIM * GOMOKU_BOARD_DIM && !isGameOver();
}

bool GomokuGame::canMakeWinningLine(char player) const {
    // Check for potential winning lines in all directions
    for (int i = 0; i < gridDimension; ++i) {
        for (int j = 0; j < gridDimension; ++j) {
            if (gameGrid[i][j] != ' ' && gameGrid[i][j] != player) {
                continue;  // Skip opponent's pieces
            }

            // Check all directions
            const int directions[4][2] = {{1,0}, {0,1}, {1,1}, {1,-1}};  // horizontal, vertical, diagonal

            for (const auto& dir : directions) {
                int dx = dir[0], dy = dir[1];
                int count = 0;
                bool blocked = false;

                // Count potential line length including empty spaces
                for (int step = 0; step < winLength; ++step) {
                    int newX = j + dx * step;
                    int newY = i + dy * step;

                    if (newX < 0 || newX >= gridDimension ||
                        newY < 0 || newY >= gridDimension) {
                        blocked = true;
                        break;
                    }

                    if (gameGrid[newY][newX] == ' ' || gameGrid[newY][newX] == player) {
                        count++;
                    } else {
                        blocked = true;
                        break;
                    }
                }

                if (!blocked && count >= winLength) {
                    return true;  // Found potential winning line
                }
            }
        }
    }
    return false;
}

bool GomokuGame::isGameDraw() {
    // If someone has already won, it's not a draw
    if (isGameOver()) {
        return false;
    }

    // If the board is full, it's a draw
    if (isGridFull()) {
        return true;
    }

    // If neither player can make a winning line, it's a draw
    bool blackCanWin = canMakeWinningLine('B');
    bool whiteCanWin = canMakeWinningLine('W');

    // If neither player can possibly win, it's a draw
    if (!blackCanWin && !whiteCanWin) {
        return true;
    }

    return false;
}

