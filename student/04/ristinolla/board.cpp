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

void Board::extend(Direction d) {

}

bool Board::placeMarker(string x_string, string y_string, char symbol) {

    //first, check that the input coordinates contains only digits
    for(char c : x_string) {
        if(!isdigit(c)) {
            cout << "Coordinate outside the board" << endl;
            return false;
        }
    }

    for(char c : y_string) {
        if(!isdigit(c)) {
            cout << "Coordinate outside the board" << endl;
            return false;
        }
    }

    //once we're sure they're digit strings, convert them to integers
    int x = stoi(x_string);
    int y = stoi(y_string);

    //decrement the coordinates by one because we really index the board from 0, not 1
    --x;
    --y;

    //make sure that the requested square is either in the board...
    if(!((x < size_ && y < size_) && x != -1 && y != -1)) {


        if (y == -1 && -1 < x && x < size_) { //... one square above the board ...
            extend(UP);
        } else if (y == size_ && -1 < x && x < size_) {  //... one square below the board ...
            extend(DOWN);
        } else if (x == -1 && -1 < y && y < size_) { //... one square to the left of the board ...
            extend(LEFT);
        } else if (x == size_ && -1 < y && y < size_) { // ... or one square to the right of the board
            extend(RIGHT);
        } else {
            cout << "Coordinate outside the board" << endl;
            return false;
        }

    }

    //then, check that the square is not already filled
    if(!(board_.at(x).at(y) == '.')) {
        cout << "The given place is already occupied" << endl;
        return false;
    }

    //finally, place the marker and check if the game has ended
    board_.at(x).at(y) = symbol;

    //checkEnd();
    return true;

}


