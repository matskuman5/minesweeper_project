#include "board.hh"

//Square::Square(int x, int y, int drops, Board* board ):
//    x_(x), y_(y), drops_(drops), board_(board)

Board::Board(int size) {

    //initialize an empty board by adding a dot to all squares
    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            board_.at(x).at(y) = '.';
        }
    }

}
