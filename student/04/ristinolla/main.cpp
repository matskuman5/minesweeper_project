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

        while(true) {
            cout << "For X, enter coordinates: ";
            int input_x;
            cin >> input_x;
//            if(input_x == 'q') {
//                cout << "Why on earth are you giving up the game?";
//                exit = true;
//                break;
//            }
            int input_y;
            cin >> input_y;

            if (b.placeMarker(input_x, input_y, 'X')) {
                break;
            }
        }

        if(exit) {
            break;
        }



    }

    cout << "Game over!";
    return EXIT_SUCCESS;


}


