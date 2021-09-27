//Naughts and Crosses
//
//This program implements the classic game Naughts and Crosses.
//The game begins with an empty 3x3 grid. Two players take turns drawing symbols
//on specific squares on the grid. The player wins by having covered a full row, column or diagonal
//with their own symbol. The game ends in a draw if all squares are covered and no players has won.
//A player can also exit the game at any time by inputting "q".
//The game also supports extending the board. If a player chooses to draw a symbol one square away
//from the grid, the grid expands in the corresponding direction.
//
//Implementation details:
//The program works by largely using one class named Board. The main.cpp file is used for
//printing the starting and ending messages, reading input, and changing player turns. The rest is handled in board.cpp,
//including checking coordinates, placing the markers, extending the board if necessary and checking for the end of the game.
//See board.hh for more details about class functions and variables.
//
//Code author:
//Name: Matias Selin
//Student Number: 150181798
//Username: vxmase
//E-Mail: matias.selin@tuni.fi

#include <iostream>
#include <vector>
#include <board.hh>

using namespace std;

const unsigned int INIT_GRID_SIZE = 3;

int main() {

    cout << "Start game:" << endl;

    Board b = Board(INIT_GRID_SIZE);
    bool exit = false;
    int turn = 0;
    char player = 'X';

    while(true) {

        b.print();

        string s = b.checkEnd();
        if(s != "null") {
            if(s == "No empty places") {
                cout << s << endl;
                break;
            } else {
                string winner;
                if (player == 'X') {
                    winner = "Cross";
                } else {
                    winner = "Nought";
                }
                cout << winner << s << endl;
                break;
            }
        }

        if(turn % 2 == 0) {
            player = 'X';
        } else {
            player = '0';
        }

        while(true) {
            cout << "For " << player << ", enter coordinates: x y> ";
            string input_x;
            cin >> input_x;
            if(input_x == "q") {
                cout << "Why on earth are you giving up the game?" << endl;
                exit = true;
                break;
            }
            string input_y;
            cin >> input_y;

            if (b.placeMarker(input_x, input_y, player)) {
                break;
            }
        }

        if(exit) {
            break;
        }

        turn++;

    }

    cout << "Game over!" << endl;
    return EXIT_SUCCESS;


}


