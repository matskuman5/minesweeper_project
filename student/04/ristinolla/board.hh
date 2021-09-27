#ifndef BOARD_HH
#define BOARD_HH

#include <vector>
#include <string>

enum Direction { NW, SE };

class Board
{
public:

    //constructor function, creates an empty board with the specified amount of rows and columns
    Board(const int size);

    //prints the status of the board
    void print() const;

    //attempts to place a given symbol (cross or naught) in the selected coordinates
    //first checks the input to make sure it can be used (the inputs are integers and within the board)
    //then checks whether the square is already filled
    //if placement would extend the board in one direction, calls extend()
    //returns whether the placement was successful or not
    bool placeMarker(const std::string& x, const std::string& y, const char symbol);

    //returns a string describing how the game ended (victory or draw)
    //if the game has not ended, returns "null"
    std::string checkEnd() const;

private:

    //extends the board by one in the specified direction
    void extend(const Direction d);

    std::vector< std::vector< char > > board_;
    int size_;

};

#endif // BOARD_HH
