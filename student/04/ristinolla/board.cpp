#include "board.hh"
#include "iostream"
using namespace std;

Board::Board(int size):
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

void Board::print() {

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

void Board::extend(Direction d) {

    //first, expand the board by one column...
    //TODO CLEAN THIS UP
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

    //if we're extending NW, we need to move the markers
    if(d == NW) {

        //then, compile a list of the coordinates of the markers we have to move and erase them
        vector< string > to_move;
        for(int x = 0; x < size_; x++) {
            for(int y = 0; y < size_; y++) {
                if (board_.at(x).at(y) != '.') {
                    to_move.push_back(to_string(x) + " " + to_string(y) + " " + to_string(board_.at(x).at(y)));
                    board_.at(x).at(y) = '.';
                }
            }
        }

        //generate new coordinates for the markers depending on the direction they should move
        for(string s : to_move) {

            //first, turn the strings into two integers and a character
            //spaghet
            int space_index_1 = s.find(" ");
            int space_index_2 = s.substr(space_index_1 + 1).find(" ") + space_index_1 + 1;
            int x = stoi(s.substr(0,space_index_1));
            int y = stoi(s.substr(space_index_1 + 1, space_index_2 - 1 - space_index_1));
            s.erase(0, space_index_2 + 1);
            char marker = stoi(s);

            //then, modify the integers depending on the direction the markers should move
            if(d == NW) {
                x++;
                y++;
            } else {
                x--;
                y--;
            }

            //finally, place the markers in their new coordinates
            board_.at(x).at(y) = marker;

        }

    }



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

        if ((y == -1 && -1 < x && x < size_)) { //... one square above the board ...
            extend(NW);
            x++;
            y++;
        } else if (y == size_ && -1 < x && x < size_) {  //... one square below the board ...
            extend(SE);
        } else if (x == -1 && -1 < y && y < size_) { //... one square to the left of the board ...
            extend(NW);
            x++;
            y++;
        } else if (x == size_ && -1 < y && y < size_) { // ... or one square to the right of the board
            extend(SE);
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

string Board::checkEnd() {

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


