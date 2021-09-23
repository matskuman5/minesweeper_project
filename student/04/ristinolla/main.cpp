#include <iostream>
#include <vector>
#include <board.hh>

using namespace std;

const unsigned int INIT_BOARD_SIZE = 3;

int main() {

    cout << "Start game:" << endl;

    Board b = Board(INIT_BOARD_SIZE);
    bool exit = false;
    int turn = 0;
    char player;

    while(true) {

        b.print();

        string s = b.checkEnd();
        if(s != "null") {
            if(s == "No empty spaces") {
                cout << s << endl;
                break;
            } else {
                cout << player << s << endl;
                break;
            }
        }

        if(turn % 2 == 0) {
            player = 'X';
        } else {
            player = '0';
        }

        while(true) {
            cout << "For " << player << ", enter coordinates: ";
            string input_x;
            cin >> input_x;
            if(input_x == "q") {
                cout << "Why on earth are you giving up the game?" << endl;
                exit = true;
                break;
            }
            string input_y;
            cin >> input_y;

            //if we manage to place a marker succesfully, check if the game has ended
            //if not, we repeat and change turns
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


