//
// Created by Ben Eisner on 11/5/24.
//

#ifndef GOMOKUGAME_H
#define GOMOKUGAME_H

#include "GameBase.h"
#include <ostream>
using namespace std;
static const int GOMOKU_BOARD_DIM = 19;
static const int GOMOKU_WIN_LENGTH = 5;

class GomokuGame : public GameBase {
private:
    vector<pair<unsigned int, unsigned int>> playerMovesB;
    vector<pair<unsigned int, unsigned int>> playerMovesW;
    unsigned int totalMoves = 0;
    unsigned int winLength;
    bool isGridFull() const;
    bool checkLine(int startX, int startY, int dx, int dy) const;
    bool canMakeWinningLine(char player) const;


protected:
    std::string currentPlayerSymbol = "B";

public:
    GomokuGame();
    GomokuGame(int boardSize);
    GomokuGame(int boardSize, int requiredWinLength);
    virtual int play() override;
    virtual bool isGameOver() const override;
    virtual bool isGameDraw() override;
    virtual bool getPlayerInput(unsigned int& x, unsigned int& y) const override;
    virtual bool processMove() override;
    virtual void displayBoard() override;

    friend ostream& operator<<(ostream& os, const GomokuGame& game);
};

#endif // GOMOKUGAME_H