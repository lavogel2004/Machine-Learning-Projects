/**
 * Main.cpp
 * CSE 332S
 * Lab Num: 4
 * Author: Benny Eisner, Lucas Vogel, Nicholas Magnani
*/

#include <iostream>
#include <memory>
#include <stdexcept>
#include "GameBase.h"

using namespace std;

// error message
void displayUsage(const char* programName) {
    cout << "Usage: " << programName << " [TicTacToe|Gomoku]" << endl;
}

int main(int argc, char* argv[]) {
    // Runs game
    try {
        unique_ptr<GameBase> game(GameBase::createGameInstance(argc, argv));

        if (!game) {
            displayUsage(argv[0]);
            return static_cast<int>(GameStatus::INVALID_ARGS);
        }

        return (*game).play();
    }
    catch (const bad_alloc& e) {
        cerr << "Memory allocation failed: " << e.what() << endl;
        return static_cast<int>(GameStatus::INVALID_ARGS);
    }
    catch (const exception& e) {
        cerr << "error occurred: " << e.what() << endl;
        return static_cast<int>(GameStatus::INVALID_ARGS);
    }
}