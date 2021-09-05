#include <iostream>


using namespace std;

unsigned long int kertoma(int i) {
    unsigned long tulos = 1;
    while(i > 0) {
        tulos *= i;
        i--;
    }
    return tulos;
}

unsigned long int lottorivien_maara(int pallot, int arvottavat) {
    unsigned long int tulos = kertoma(pallot) / (kertoma(pallot - arvottavat) * kertoma(arvottavat));
    return tulos;
}

int main()
{

    int pallot = 0;
    int arvottavat = 0;

    cout << "Enter the total number of lottery balls: ";
    cin >> pallot;
    cout << "Enter the number of drawn balls: ";
    cin >> arvottavat;

    if (pallot < 0 || arvottavat < 0) {
        cout << "The number of balls must be a positive number.";
    } else {
        cout << "The probability of guessing all " << arvottavat << " balls correctly is 1/" << lottorivien_maara(pallot,arvottavat);
    }



}
