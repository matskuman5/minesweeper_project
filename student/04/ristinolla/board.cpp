#include "board.hh"
#include "iostream"
using namespace std;

Board::Board(int size):
size_(size) {

    //initialize an empty board by adding a dot to all squares
    for(int x = 0; x < size_; x++) {
        vector < char > row;
        for(int y = 0; y < size_; y++) {
            row.push_back('.');
        }
        board_.push_back(row);
    }

}

void Board::print() {

    cout << " ";

    for(int x = 0; x < size_; x++) {
        cout << " ";
        cout << x + 1;
    }

    cout << endl;

    for(int y = 0; y < size_; y++) {
        cout << y + 1;
        for(int x = 0; x < size_; x++) {
            cout << " ";
            cout << board_.at(x).at(y);
        }
        cout << endl;
    }

}

bool Board::placeMarker(int x, int y, char symbol) {



    //first, check that the input is correct


    //decrement the coordinates by one because we really index the board from 0, not 1
    --x;
    --y;

    //then, check that the square is not already filled



    //check if the board would have to be extended to place the marker

    //place the marker and check if the game has ended
    board_.at(x).at(y) = symbol;
    return true;

}
