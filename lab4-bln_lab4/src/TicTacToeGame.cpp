//
// Created by Ben Eisner on 11/5/24.
//

#include "TicTacToeGame.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iomanip>

using namespace std;

TicTacToeGame::TicTacToeGame()
    : GameBase(TICTACTOE_BOARD_DIM),
      totalMoves(0) {
    activePlayer = "X";

    // Initialize the game board with proper borders
    for (int i = 0; i < gridDimension; ++i) {
        for (int j = 0; j < gridDimension; ++j) {
            if ((i >= 1 && i <= TICTACTOE_PLAY_AREA) && (j >= 1 && j <= TICTACTOE_PLAY_AREA)) {
                gameGrid[i][j] = ' ';
            } else {
                gameGrid[i][j] = ' ';
            }
        }
    }
    symbolWidth = 1;
}


ostream& operator<<(ostream& os, const TicTacToeGame& game) {
    os << setw(game.symbolWidth) << right;

    for (int i = game.gridDimension - 1; i >= 0; --i) {
        os << i;
        for (int j = 0; j < game.gridDimension; ++j) {
            os << " " << setw(game.symbolWidth) << game.gameGrid[i][j];
        }
        os << '\n';
    }

    os << "  ";
    for (int i = 0; i < game.gridDimension; i++) {
        os << setw(game.symbolWidth) << right << i << " ";
    }
    os << "\n";

    return os;
}

bool TicTacToeGame::checkWinCondition(char symbol) const {
    // Check rows
    for (int i = 1; i <= TICTACTOE_PLAY_AREA; ++i) {
        if (gameGrid[i][1] == symbol &&
            gameGrid[i][2] == symbol &&
            gameGrid[i][3] == symbol) {
            return true;
        }
    }

    // Check columns
    for (int j = 1; j <= TICTACTOE_PLAY_AREA; ++j) {
        if (gameGrid[1][j] == symbol &&
            gameGrid[2][j] == symbol &&
            gameGrid[3][j] == symbol) {
            return true;
        }
    }

    // Check diagonals
    if ((gameGrid[1][1] == symbol &&
         gameGrid[2][2] == symbol &&
         gameGrid[3][3] == symbol) ||
        (gameGrid[1][3] == symbol &&
         gameGrid[2][2] == symbol &&
         gameGrid[3][1] == symbol)) {
        return true;
    }

    return false;
}

bool TicTacToeGame::isGameOver() const {
    return checkWinCondition(activePlayer[0]);
}

bool TicTacToeGame::isGameDraw() {
    for (int i = 1; i <= TICTACTOE_PLAY_AREA; ++i) {
        for (int j = 1; j <= TICTACTOE_PLAY_AREA; ++j) {
            if (gameGrid[i][j] == ' ') {
                return false;
            }
        }
    }
    return !isGameOver();
}

bool TicTacToeGame::getPlayerInput(unsigned int& x, unsigned int& y) const {
    string input;
    cout << "Player " << activePlayer << ", enter move ('2,2' or enter 'quit'): ";
    getline(cin, input);

    if (input == "quit") {
        return true;
    }

    replace(input.begin(), input.end(), ',', ' ');
    istringstream iss(input);

    // Create variables to store potential extra input (ex. 3, 2, 1)
    unsigned int temp_x, temp_y, extra;

    // Try to read two numbers and check if there's anything extra
    if (!(iss >> temp_x >> temp_y) || iss >> extra ||
        temp_x < 1 || temp_x > TICTACTOE_PLAY_AREA ||
        temp_y < 1 || temp_y > TICTACTOE_PLAY_AREA) {
        cout << "Invalid move (out of bounds or too many numbers). Try again.\n";
        return getPlayerInput(x, y);
        }

    if (gameGrid[temp_y][temp_x] != ' ') {
        cout << "Space already occupied. Try again.\n";
        return getPlayerInput(x, y);
    }

    x = temp_x;
    y = temp_y;
    return false;
}
bool TicTacToeGame::processMove() {
    unsigned int x, y;

    cout << "Player " << activePlayer << "'s turn.\n";

    if (totalMoves > 1) {
        cout << "Previous moves for Player " << activePlayer << ":";
        const auto& currentMoves = (activePlayer == "X") ? playerMovesX : playerMovesO; // Changed from xMoves/oMoves to playerMovesX/playerMovesO
        for (const auto& move : currentMoves) {
            cout << " (" << move.first << "," << move.second << ")";
        }
        cout << endl;
    }

    if (getPlayerInput(x, y)) {
        cout << "Game over. Player " << activePlayer << " quits.\n";
        cout << "Total moves played: " << totalMoves << endl; // Changed from moveCount to totalMoves
        return false;
    }

    ++totalMoves; // Changed from moveCount to totalMoves
    auto& currentMoves = (activePlayer == "X") ? playerMovesX : playerMovesO; // Changed from xMoves/oMoves to playerMovesX/playerMovesO
    currentMoves.push_back(make_pair(x, y));
    gameGrid[y][x] = activePlayer[0];

    displayBoard();

    if (!isGameOver() && !isGameDraw()) {
        if (activePlayer == "X") {
            activePlayer = "O";
        } else {
            activePlayer = "X";
        }
    }

    return true;
}

void TicTacToeGame::displayBoard() {
    cout << *this;
}

int TicTacToeGame::play() {
    displayBoard();
    while (true) {
        if (!processMove()) {
            return static_cast<int>(GameStatus::QUIT);
        }

        if (isGameOver()) {
            cout << "Player " << activePlayer << " wins!\n";
            return static_cast<int>(GameStatus::SUCCESS);
        }

        if (isGameDraw()) {
            cout << "Game over. It's a draw!\n";
            return static_cast<int>(GameStatus::DRAW);
        }
    }
}