#include <iostream>
#include <vector>
#include <board.hh>

using namespace std;

const unsigned int INIT_BOARD_SIZE = 3;

int main() {

    Board b = Board(INIT_BOARD_SIZE);
    b.print();

}

bool checkInput() {
    return false;
}
