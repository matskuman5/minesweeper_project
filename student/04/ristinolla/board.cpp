#include "board.hh"
#include "iostream"
using namespace std;

//Square::Square(int x, int y, int drops, Board* board ):
//    x_(x), y_(y), drops_(drops), board_(board)

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
