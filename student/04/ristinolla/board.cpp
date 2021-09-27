#include "board.hh"
#include "iostream"
using namespace std;

Board::Board(const int size):
size_(size) {

    //initialize an empty board by adding a dot to all squares
    for(int x = 0; x < size_; x++) {
        vector < char > column;
        for(int y = 0; y < size_; y++) {
            column.push_back('.');
        }
        board_.push_back(column);
    }

}

void Board::print() const {

    cout << " ";

    for(int x = 0; x < size_; x++) {
        cout << " ";
        if (x + 1 >= 10) {
            cout << (x + 1) % 10;
        } else {
            cout << x + 1;
        }
    }

    cout << endl;

    for(int y = 0; y < size_; y++) {

        if (y + 1 >= 10) {
            cout << (y + 1) % 10;
        } else {
            cout << y + 1;
        }

        for(int x = 0; x < size_; x++) {
            cout << " ";
            cout << board_.at(x).at(y);
        }
        cout << endl;
    }

}

void Board::extend(const Direction d) {

    //first, expand the board by one column...
    vector < char > column;
    for (int y = 0; y < size_; y++) {
        column.push_back('.');
    }
    board_.push_back(column);

    //... increase the size of the board ...
    size_++;

    //... then, extend all columns by one
    for (int x = 0; x < size_; x++) {
        board_.at(x).push_back('.');
    }

    //if we're extending north-west, we need to move the markers
    if(d == NW) {

        //create a new board with the new size
        std::vector< std::vector< char > > new_board;

        for(int x = 0; x < size_; x++) {
            vector < char > column;
            for(int y = 0; y < size_; y++) {
                column.push_back('.');
            }
            new_board.push_back(column);
        }

        //move all the markers from the old board to the new board, just one square to the south-east
        for(int x = 0; x < size_ - 1; x++) {
            for(int y = 0; y < size_ - 1; y++) {
                new_board.at(x + 1).at(y + 1) = board_.at(x).at(y);
            }
        }

        //replace the old board with the new board
        board_ = new_board;

    }



}

bool Board::placeMarker(const string& x_string, const string& y_string, const char symbol) {

    //first, check that the input coordinates contain only digits
    for(const auto& s : {x_string, y_string}) {
        for(char c : s) {
            if(!isdigit(c)) {
                cout << "Coordinate outside the board" << endl;
                return false;
            }
        }
    }

    //once we're sure they're digit strings, convert them to integers
    int x = stoi(x_string);
    int y = stoi(y_string);

    //decrement the coordinates by one because we really index the board from 0, not 1
    --x;
    --y;

    //check that the coordinates are within the board or in expandable range
    if(!((x < size_ && y < size_) && x != -1 && y != -1)) {

        if ((x == size_ && -1 < y && y <= size_) || (y == size_ && -1 < x && x <= size_)) {
            extend(SE);
        } else if ((x == -1 && -1 <= y && y < size_) || (y == -1 && -1 <= x && x < size_)) {
            extend(NW);
            x++;
            y++;
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

    //finally, place the marker
    board_.at(x).at(y) = symbol;
    return true;

}

string Board::checkEnd() const {

    //check columns first
    for(int x = 0; x < size_; x++) {

        bool victory = true;
        char to_check = board_.at(x).at(0);

        if(to_check == '.') {
            continue;
        }

        for(int y = 0; y < size_; y++) {
            if(board_.at(x).at(y) != to_check) {
                victory = false;
                break;
            }
        }

        if(victory) {
            return " won vertically";
        }

    }

    //then check rows
    for(int y = 0; y < size_; y++) {

        bool victory = true;
        char to_check = board_.at(0).at(y);

        if(to_check == '.') {
            continue;
        }

        for(int x = 0; x < size_; x++) {
            if(board_.at(x).at(y) != to_check) {
                victory = false;
                break;
            }
        }

        if(victory) {
            return " won horizontally";
        }

    }

    //then check diagonals, first top left to bottom right

    char to_check = board_.at(0).at(0);

    bool victory = true;

    if(to_check != '.') {
        for(int x_y = 0; x_y < size_; x_y++) {
            if(board_.at(x_y).at(x_y) != to_check) {
                victory = false;
            }
        }
    } else {
        victory = false;
    }

    if(victory) {
        return " won diagonally";
    }


    //then bottom left to top right
    victory = true;
    to_check = board_.at(0).at(size_ - 1);

    if(to_check != '.') {
        for(int x_y = 0; x_y < size_; x_y++ ) {
            if(board_.at(x_y).at(size_ - 1 - x_y) != to_check) {
                victory = false;
            }
        }
    } else {
        victory = false;
    }


    if(victory) {
        return " won diagonally";
    }

    //finally, we check if the board is full or not (i.e. whether there any squares that are empty)
    bool full = true;

    for(int x = 0; x < size_; x++) {
        for(int y = 0; y < size_; y++) {
            if(board_.at(x).at(y) == '.') {
                full = false;
                break;
            }
        }
    }

    if(full) {
        return "No empty places";
    }

    return "null";
}


