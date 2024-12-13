//
// Created by Ben Eisner on 11/6/24.
//


#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <iostream>
#include <vector>
using namespace std;

//game status enum for standardized return values
enum class GameStatus {
    SUCCESS = 0,
    QUIT = 1,
    DRAW = 2,
    INVALID_ARGS = 3
};

class GameBase {
protected:
    const int gridDimension; //board size
    string activePlayer; //which player is active (whos turn is it)
    size_t symbolWidth; //max width needed to display game symbols
    mutable vector<vector<char>> gameGrid; //game baord
    void updateSymbolWidth(const string& piece); //helper function to update SymbolWidth when new pieces are added

public:
    explicit GameBase(int dimension); //Explicit constructor to prevent any implicit type conversions into consturctor
    virtual ~GameBase() = default; //virtual default destructor
    
    // Core game functions (all virtual to allow for overriding methods from base class)
    virtual int play(); //main game loop
    virtual bool isGameOver() const = 0; //checks if game state is winning
    virtual bool isGameDraw(); //checks if game is in state of draw
    virtual void displayBoard() = 0; //displayes current game state
    virtual bool processMove(); //proccesses moves and returns false if invalid move (ensures valid move before continuing with recursion)
    virtual bool getPlayerInput(unsigned int& x, unsigned int& y) const; //geta and validates player move data (const to ensure method doesnt modify class state)
    static GameBase* createGameInstance(int argc, char* argv[]); // Factory method - creates apropriate derived class based on command line args
};

#endif // GAMEBASE_H