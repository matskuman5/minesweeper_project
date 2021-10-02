#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main()
{
    cout << "Input file: ";

    string input;
    getline(cin, input);

    ifstream reader(input);

    if(reader) {

        vector<string> lines;
        set<string> words;

        string line;
        while(getline(reader, line)) {

            lines.push_back(line);

            while(true) {

                if(line.find(" ") == string::npos) {
                    words.insert(line);
                    break;
                } else {
                    words.insert(line.substr(0, line.find(" ")));
                    line.erase(0, line.find(" ") + 1);
                }
            }

        }

//        for (auto s : lines) {
//            cout << s << endl;
//        }

//        cout << endl;

//        for (auto s : words) {
//            cout << s << endl;
//        }

//        cout << endl;

        for (auto w : words) {

            int occurrences = 0;
            vector<int> occurrence_lines;

            for (int i = 0; i < lines.size(); i++) {

                if(lines.at(i).find(" " + w + " ") != string::npos) {
                    occurrences++;
                    occurrence_lines.push_back(i + 1);
                } else if (lines.at(i).find(w) == 0) {
                    occurrences++;
                    occurrence_lines.push_back(i + 1);
                } else if (lines.at(i).find(w) + w.length() == lines.at(i).length()){
                    occurrences++;
                    occurrence_lines.push_back(i + 1);
                }

            }

            cout << w << " " << occurrences << ": ";
            for (int i = 0; i < occurrence_lines.size(); i++) {
                if(i != occurrence_lines.size() - 1) {
                    cout << occurrence_lines.at(i) << ", ";
                } else {
                    cout << occurrence_lines.at(i);
                }
            }
            cout << endl;

        }





    } else {
        cout << "Error! The file " << input << " cannot be opened.";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
