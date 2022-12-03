/*
#############################################################################
# COMP.CS.110 Programming 2: Autumn 2021                                    #
# Project4: Minesweeper                                                     #
# File: gameboard.hh                                                        #
# Description: Describes the internal structure of the gameboard in         #
#       minesweeper game.                                                   #
#       Gameboard contains squares in a two-dimensional vector.             #
# Notes: * This is a part of an exercise program.                           #
#        * Student can add new methods and attributes in the class.         #
#############################################################################
*/

// MINESWEEPER GUI PROJECT
// PROGRAMMING 2 COURSE
// Author: Matias Selin
// Student number: 150181798

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "square.hh"
#include <vector>

const int MINE_PROBABALITY = 20; // in percents

class GameBoard
{
public:
    GameBoard();
    ~GameBoard();

    // Initializes a size x size board, i.e. forms square objects and calculates data
    // needed by them.
    void init(int seed, unsigned int size);

    // Prints the game board.
    void print(std::ostream& stream) const;

    // Checks if the game is over.
    bool isGameOver() const;

    // Returns the size of the game board.
    int getSize() const;

    // Returns the square object in the given location.
    Square getSquare(int x, int y) const;

    // Sets the given square object into the given location.
    void setSquare(Square sq, int x, int y);

    // Opens the square in the given location.
    bool openSquare(int x, int y);

    // Flags or deflags the square in the given location. Returns whether or not a flag was placed.
    bool flagSquare(int x, int y);

private:
    std::vector<std::vector<Square>> board_;
    unsigned int board_size_;
};

#endif // GAMEBOARD_HH
