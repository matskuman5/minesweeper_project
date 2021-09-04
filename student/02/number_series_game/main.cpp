#include <iostream>
using namespace std;


int main()
{
    std::cout << "How many numbers would you like to have? ";

    int numerojen_maara = 0;
    cin >> numerojen_maara;

    for (int i = 1; i <= numerojen_maara; ++i) {
        cout << i << endl;
    }

}
