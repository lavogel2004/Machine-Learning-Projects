//
// Created by Ben Eisner on 11/5/24.
//

#include "GameBase.h"


#include "GameBase.h"
#include "TicTacToeGame.h"
#include "GomokuGame.h"
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

// Creates gameBase instance
GameBase::GameBase(int dimension) :
    gridDimension(dimension),
    symbolWidth(3) {
    gameGrid = vector<vector<char>>(dimension, vector<char>(dimension, ' '));
}

void GameBase::updateSymbolWidth(const string& piece) {
    symbolWidth = max(symbolWidth, piece.length());
}

bool GameBase::getPlayerInput(unsigned int& x, unsigned int& y) const {
    string userInput;
    cout << "Player " << activePlayer << ", enter your move or quit game ('1,3'/'quit'): ";
    getline(cin, userInput);

    if (userInput == "quit") {
        return true;
    }

    replace(userInput.begin(), userInput.end(), ',', ' ');
    istringstream inputStream(userInput);

    if (!(inputStream >> x >> y) ||
        y >= gridDimension ||
        x >= gridDimension ||
        gameGrid[y][x] != ' ') {
        cout << "That is not a valid move. Enter a valid move!\n";
        return getPlayerInput(x, y);
    }
    return false; //only hits when valid input is given and function isnt recursivley called
}
// plays the game
int GameBase::play() {
    displayBoard();

    while (true) {
        if (!processMove()) { //game is quit
            return static_cast<int>(GameStatus::QUIT);
        }

        if (isGameOver()) { //one player has won
            cout << "Player " << activePlayer << " wins!\n";
            return static_cast<int>(GameStatus::SUCCESS);
        }

        if (isGameDraw()) { //game is drawn
            cout << "Game ends in a draw!\n";
            return static_cast<int>(GameStatus::DRAW);
        }
    }
}

bool GameBase::isGameDraw() {
    if (isGameOver()) { //first checks if the game is over -> cant draw if game is over
        return false;
    }

    for (size_t row = 0; row < gridDimension; ++row) {
        for (size_t col = 0; col < gridDimension; ++col) {
            if (gameGrid[row][col] == ' ') { //checks for an empty space anywhere on the grid
                return false;
            }
        }
    }
    return true;
}

bool GameBase::processMove() {
    unsigned int x, y;
    cout << "Player " << activePlayer << "'s turn\n";

    if (getPlayerInput(x, y)) {
        cout << "Player " << activePlayer << " quits. Game finished. \n";
        return false;
    }
    gameGrid[y][x] = activePlayer[0]; //check if specific move is valid
    displayBoard(); //updates board display

    //If player = X switch to O, else switch to X
    if (activePlayer == "X") {
        activePlayer = "O";
    } else {
        activePlayer = "X";
    }
    return true;
}

GameBase* GameBase::createGameInstance(int argc, char* argv[]) {
    if (argc >= 2) {
        std::string gameType = argv[1];

        if (gameType == "TicTacToe") {
            return new TicTacToeGame();
        }
        else if (gameType == "Gomoku") {
            try {
                // Parse additional arguments for Gomoku
                if (argc == 2) {
                    // Default 19x19 board with win length 5
                    return new GomokuGame();
                }
                else if (argc == 3) {
                    // Custom board size
                    int boardSize = std::stoi(argv[2]);
                    if (boardSize < 3) {
                        std::cerr << "Board size must be at least 3x3\n";
                        return nullptr;
                    }
                    return new GomokuGame(boardSize);
                }
                else if (argc == 4) {
                    // Custom board size and win length
                    int boardSize = std::stoi(argv[2]);
                    int winLength = std::stoi(argv[3]);
                    if (boardSize < 3) {
                        std::cerr << "Board size must be at least 3x3\n";
                        return nullptr;
                    }
                    if (winLength < 3 || winLength > boardSize) {
                        std::cerr << "Win length must be between 3 and board size\n";
                        return nullptr;
                    }
                    return new GomokuGame(boardSize, winLength);
                }
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid number format in arguments\n";
                return nullptr;
            }
        }
    }
    return nullptr;
}