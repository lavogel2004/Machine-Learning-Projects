//
// Created by Ben Eisner on 11/5/24.
//

#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

#include "GameBase.h"
#include <iostream>


using namespace std;
//game constants
static const int TICTACTOE_BOARD_DIM = 5;
static const int TICTACTOE_PLAY_AREA = 3;

class TicTacToeGame : public GameBase {
private:
    //player move history
    vector<pair<unsigned int, unsigned int>> playerMovesX;
    vector<pair<unsigned int, unsigned int>> playerMovesO;
    unsigned int totalMoves = 0;
    char currentPlayer;
    char board[TICTACTOE_BOARD_DIM][TICTACTOE_BOARD_DIM];
    bool checkWinCondition(char symbol) const;

protected:
    string currentPlayerSymbol = "X";

public:
    TicTacToeGame();
    virtual int play() override;
    virtual bool isGameOver() const override;
    virtual bool isGameDraw() override;
    virtual bool getPlayerInput(unsigned int& x, unsigned int& y) const override;
    virtual bool processMove() override;
    virtual void displayBoard() override;

    friend ostream& operator<<(ostream& os, const TicTacToeGame& game);
};

#endif // TICTACTOEGAME_H