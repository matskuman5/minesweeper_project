#ifndef BOARD_HH
#define BOARD_HH

#include <vector>

enum Direction { UP, DOWN, LEFT, RIGHT };

class Board
{
public:

    Board(int size);

    //prints the status of the board
    void print();

    //places a cross or a naught in the selected coordinates, returns if the placing was successful
    //if placing was succesful, also calls checkEnd()
    bool placeMarker(int x, int y);

private:

    //extends the board in the specified direction
    void extend(Direction d);

    //returns true if either of the players has won or if the board is full
    bool checkEnd();

    std::vector< std::vector< char > > board_;
    int size_;

};

#endif // BOARD_HH
