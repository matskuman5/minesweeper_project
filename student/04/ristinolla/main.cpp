#include <iostream>
#include <vector>
#include <board.hh>

using namespace std;

const unsigned int INIT_BOARD_SIZE = 3;

int main() {

    cout << "Start game:" << endl;

    Board b = Board(INIT_BOARD_SIZE);
    bool exit = false;

    while(true) {

        b.print();

        string s = b.checkEnd();
        if(s != "null") {
            if(s == "No empty spaces") {
                cout << s << endl;
                break;
            } else {
                cout << "X" << s << endl;
                break;
            }
        }

        while(true) {
            cout << "For X, enter coordinates: ";
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
            if (b.placeMarker(input_x, input_y, 'X')) {                
                break;
            }
        }

        if(exit) {
            break;
        }



    }

    cout << "Game over!" << endl;
    return EXIT_SUCCESS;


}


