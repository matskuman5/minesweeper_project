#include <iostream>
#include <cmath>

using namespace std;

int main()
{

    cout << "Enter a number:";
    int luku = 0;
    cin >> luku;

    int tulos = 0;
    tulos = pow(luku,3);

    if ((tulos / luku) / luku == luku) {
        cout << "The cube of " << luku << " is " << tulos << ".";
    } else {
        cout << "Error! The cube of " << luku << " is not " << tulos << ".";
    }

}
