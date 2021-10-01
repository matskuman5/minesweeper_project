#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <set>
#include <map>

using namespace std;

int main()
{

    cout << "Input file: ";

    string input;
    getline(cin, input);

    ifstream reader(input);

    if(reader) {

        string line;
        map<string, int> competitors;

        while(getline(reader, line)) {

            int name_length = line.find(':');

            string name = line.substr(0, name_length);

            int points = stoi(line.substr(name_length + 1, line.length() - 1 - name_length));

            if(competitors.find(name) == competitors.end()) {
                competitors.insert({name, points});
            } else {
                competitors.at(name) = competitors.at(name) + points;
            }

        }

        cout << "Final scores" << endl;

        map<string, int>::iterator i;
        i = competitors.begin();

        while(i != competitors.end()) {
            cout << i -> first << ": " << i -> second << endl;
            i++;
        }

    } else {
        cout << "Error! The file " << input << " cannot be opened.";
        return EXIT_FAILURE;
    }



}
