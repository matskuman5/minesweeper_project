//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

// Jakaa annetun merkkijonon str annetun merkin delimiter erottelemiin osiin
// ja palauttaa osat vektorissa.
// Jos erotinmerkki on lainausmerkkien sisällä, erotinmerkistä ei välitetä,
// eli osaa olla erottelematta lainausmerkkien sisällä olevan tekstin.
//
// Splits the given string str into parts separated by the given delimiter
// and returns the parts in a vector.
// If the delimiter appears inside quatation, ignores delimiter,
// i.e. does not split quoted text.
std::vector<std::string> split_ignoring_quoted_delim(const std::string& str,
                                                     char delimiter)
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delimiter and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if(result.back() == "")
    {
        result.erase(--result.end());
    }
    return result;
}

void print_themes() {};

void print_courses_in_location_and_theme() {};

void print_available() {};

void print_courses_in_theme() {};

void print_courses_in_location() {};

void print_favorite_theme() {};

void cancel_course() {};

int main()
{

    cout << "Input file: ";
    string input_file;
    getline(cin, input_file);

    ifstream reader(input_file);

    if(reader) {

        //basic file structure:
        //map<struct>
        //top-level keys are strings (theme names) and values are vectors containing structs (courses)

        struct Course {
            string name;
            string location;
            int enrollments;
        };

        map<string, vector<Course>> themes;

        string line;

        while(getline(reader, line)) {

            vector<string> parts = split_ignoring_quoted_delim(line, ';');
            Course c;
            string theme = parts.at(0);
            c.name = parts.at(1);
            c.location = parts.at(2);
            if (parts.at(3) == "full") {
                c.enrollments = -1;
            } else {
                c.enrollments = stoi(parts.at(3));
            }



            bool exists = false;
            for (auto thing : themes) {
                if (thing.first == theme) {
                    exists = true;
                    break;
                }
            }

            if (exists) {
                //if the course already exists, remove the old info
                for (int i = 0; i < themes.at(theme).size(); i++) {
                    if (themes.at(theme).at(i).name == c.name && themes.at(theme).at(i).location == c.location) {
                        themes.at(theme).erase(themes.at(theme).begin() + i);
                    }
                }
                themes.at(theme).push_back(c);
            } else {
                //if the theme is new, create the associated vector and insert the pair into the map
                vector<Course> courses;
                courses.push_back(c);
                themes.insert({theme, courses});
            }

        }

        reader.close();

//        for (auto thing : themes) {
//            cout << thing.first << ": " << endl;
//            for (auto thing2 : thing.second) {
//                cout << thing2.name << ", " << thing2.location << ", " << thing2.enrollments << endl;
//            }
//            cout << endl << endl;
//        }


        while(true) {

            cout << "> ";

            string input;
            getline(cin, input);

            vector<string> parts = split_ignoring_quoted_delim(input, ' ');

            if (parts.at(0) == "quit") {
                return EXIT_SUCCESS;
            } else if (parts.at(0) == "themes") {
                print_themes();
            } else if (parts.at(0) == "courses") {
                print_courses_in_location_and_theme();
            } else if (parts.at(0) == "available") {
                print_available();
            } else if (parts.at(0) == "courses_in_theme") {
                print_courses_in_theme();
            } else if (parts.at(0) == "courses_in_location") {
                print_courses_in_location();
            } else if (parts.at(0) == "favorite_theme") {
                print_favorite_theme();
            } else if (parts.at(0) == "cancel") {
                cancel_course();
            }

        }

        return EXIT_SUCCESS;

    } else {
        cout << "Error: the input file cannot be opened" << endl;
        return EXIT_FAILURE;
    }

}

