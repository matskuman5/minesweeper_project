#ifndef BOARD_HH
#define BOARD_HH

#include <vector>
#include <string>

enum Direction { UP, DOWN, LEFT, RIGHT };

class Board
{
public:

    //constructor function, creates an empty board with the specified amount of rows and columns
    Board(int size);

    //prints the status of the board
    void print();

    //attempts to place a given symbol (cross or naught) in the selected coordinates
    //first checks the input to make sure it can be used (the inputs are integers and within the board)
    //then checks whether the square is already filled
    //if placement would extend the board in one direction, calls extend()
    //if placing was succesful, also calls checkEnd()
    //returns whether the placement was succesful or not
    bool placeMarker(std::string x, std::string y, char symbol);

private:

    //extends the board by one in the specified direction
    void extend(Direction d);

    //returns true if either of the players has won or if the board is full
    bool checkEnd();

    std::vector< std::vector< char > > board_;
    int size_;

};

#endif // BOARD_HH
