//Code author:
//Name: Matias Selin
//Student Number: 150181798
//Username: vxmase
//E-Mail: matias.selin@tuni.fi

#ifndef BOARD_HH
#define BOARD_HH

#include <vector>
#include <string>

enum Direction { NW, SE };

class Board
{
public:

    //constructor function, creates an empty grid with the specified amount of rows and columns
    Board(const int size);

    //prints the status of the board
    void print() const;

    //attempts to place a given symbol (cross or naught) in the selected coordinates
    //first checks the input to make sure it can be used
    //(the inputs are integers, and either within the grid or in expandable range)
    //if coordinates are one square away from the grid, calls extend() in the appropriate direction
    //then checks whether the square is already filled
    //returns whether the placement was successful or not
    bool placeMarker(const std::string& x_string, const std::string& y_string, const char symbol);

    //returns a string describing how the game ended (victory or draw)
    //if the game has not ended, returns "null"
    std::string checkEnd() const;

private:

    //extends the grid by one in the specified direction
    void extend(const Direction d);

    //the actual grid that the markers are drawn on
    std::vector< std::vector< char > > grid_;

    //the size of the square grid (e.g. a 3x3 grid would have a grid_size_ of 3)
    int grid_size_;

};

#endif // BOARD_HH
