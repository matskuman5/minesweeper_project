#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    int temperature = 0;
    cin >> temperature;

    double fahrenheit = temperature * 1.8 + 32;
    double celsius = (temperature - 32) / 1.8;

    cout << temperature << " degrees Celsius is " << fahrenheit << " degrees Fahrenheit";
    cout << temperature << " degrees Fahrenheit is " << celsius << " degrees Celsius";

    return 0;
}
