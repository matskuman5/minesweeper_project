//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

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

struct Course {
    string name;
    string location;
    int enrollments;
};

void print_themes(const map<string, vector<Course>>& themes) {

    vector<string> theme_names;

    for (auto& theme : themes) {
        theme_names.push_back(theme.first);
    }

    sort(theme_names.begin(), theme_names.end());

    for (auto& s : theme_names) {
        cout << s << endl;
    }

}

void print_courses_in_location_and_theme(const map<string, vector<Course>>& themes, const string location, const string theme_name) {

    vector<Course> courses;
    bool location_found = false;
    bool theme_found = false;

    for (auto& theme: themes) {
        if (theme.first == theme_name) {
            theme_found = true;
            for (auto& course : theme.second) {
                if (course.location == location) {
                    location_found = true;
                    courses.push_back(course);
                }
            }
        }
    }

    if (!theme_found) {
        cout << "Error: unknown theme" << endl;
        return;
    }

    if (!location_found) {
        cout << "Error: unknown location" << endl;
        return;
    }

    sort(courses.begin(), courses.end(), [](Course a, Course b) {
        return a.name < b.name;
    });

    for (auto& course : courses) {
        if (course.enrollments == -1) {
            cout << course.name << " --- full" << endl;
        } else {
            cout << course.name << " --- " << course.enrollments << " enrollments" << endl;
        }
    }

}

void print_available(const map<string, vector<Course>>& themes) {

    struct Line {
        string theme;
        string location;
        string course;
    };

    vector<Line> lines;

    for (auto& theme : themes) {
        for (auto& course : theme.second) {
            if (course.enrollments != -1) {
                Line l;
                l.theme = theme.first;
                l.location = course.location;
                l.course = course.name;
                lines.push_back(l);
            }
        }
    }

    sort(lines.begin(), lines.end(), [](Line a, Line b) {
        if (a.theme == b.theme) {
            if (a.location == b.location) {
                return a.course < b.course;
            }
            return a.location < b.location;
        }
        return a.theme < b.theme;
    });

    for (Line& l : lines) {
        cout << l.theme << " : " << l.location << " : " << l.course << endl;
    }

}

void print_courses_in_theme(const map<string, vector<Course>>& themes, const string theme_name) {

    vector<Course> courses;
    bool theme_found = false;

    for (auto& theme: themes) {
        if (theme.first == theme_name) {
            theme_found = true;
            for (auto& course : theme.second) {
                courses.push_back(course);
            }
        }
    }

    if (!theme_found) {
        cout << "Error: unknown theme" << endl;
        return;
    }

    sort(courses.begin(), courses.end(), [](Course a, Course b) {
        return a.location < b.location;
    });

    for (Course& c : courses) {
        cout << c.location << " : " << c.name << endl;
    }

}

void print_courses_in_location(const map<string, vector<Course>>& themes, const string location_name) {

    vector<string> course_names;
    bool location_found = false;

    for (auto& theme : themes) {
        for (auto &course : theme.second) {
            if (course.location == location_name) {
                location_found = true;
                course_names.push_back(course.name);
            }
        }
    }

    if (!location_found) {
        cout << "Error: unknown location" << endl;
        return;
    }

    sort(course_names.begin(), course_names.end());

    for (string& s : course_names) {
        cout << s << endl;
    }

}

void print_favorite_theme(const map<string, vector<Course>>& themes) {

    int most_enrollments = 0;

    for (auto& theme : themes) {
        int enrollments_in_theme = 0;
        for (auto& course : theme.second) {
            if (course.enrollments == -1) {
                enrollments_in_theme = enrollments_in_theme + 50;
            } else {
                enrollments_in_theme = enrollments_in_theme + course.enrollments;
            }
        }
        if (enrollments_in_theme > most_enrollments) {
            most_enrollments = enrollments_in_theme;
        }
    }

    vector<string> most_popular_themes;

    for (auto& theme : themes) {
        int enrollments_in_theme = 0;
        for (auto& course : theme.second) {
            if (course.enrollments == -1) {
                enrollments_in_theme = enrollments_in_theme + 50;
            } else {
                enrollments_in_theme = enrollments_in_theme + course.enrollments;
            }
        }
        if (enrollments_in_theme == most_enrollments) {
            most_popular_themes.push_back(theme.first);
        }
    }

    sort(most_popular_themes.begin(), most_popular_themes.end());

    cout << most_enrollments << " enrollments in themes" << endl;

    for (string& s : most_popular_themes) {
        cout << "--- " << s << endl;
    }

}

void cancel_course(map<string, vector<Course>>& themes, const string course_name) {

    bool course_found = false;

    for (auto& theme : themes) {
        vector<Course> new_theme = theme.second;
        vector<int> indexes_to_delete;
        for (unsigned long int i = 0; i < theme.second.size(); i++) {
            if (theme.second.at(i).name == course_name) {
                course_found = true;
                indexes_to_delete.push_back(i);
            }
        }

        if (indexes_to_delete.size() > 0) {
            int deleted_indexes = 0;
            for (int i : indexes_to_delete) {
                new_theme.erase(new_theme.begin() + i - deleted_indexes);
                deleted_indexes++;
            }
        }

        themes.erase(theme.first);
        themes.insert({theme.first, new_theme});

    }

    if (!course_found) {
        cout << "Error: unknown course" << endl;
        return;
    }

    cout << course_name << " cancelled in all locations" << endl;

}

bool read_file_and_store_data(map<string, vector<Course>>& themes) {

    cout << "Input file: ";
    string input_file;
    getline(cin, input_file);

    ifstream reader(input_file);

    if(reader) {

        string line;

        //basic file structure:
        //keys are strings (theme names) and values are vectors containing structs (courses)

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
            for (auto& thing : themes) {
                if (thing.first == theme) {
                    exists = true;
                    break;
                }
            }

            if (exists) {
                //if the course already exists, remove the old info
                for (unsigned long int i = 0; i < themes.at(theme).size(); i++) {
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
        return true;

    } else {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }

}

bool process_input(map<string, vector<Course>>& themes, const string input) {

    vector<string> parts = split_ignoring_quoted_delim(input, ' ');

    vector<string> accepted_commands = {"quit",
                                       "themes",
                                       "courses",
                                       "available",
                                       "courses_in_theme",
                                       "courses_in_location",
                                       "favorite_theme",
                                       "cancel"};

    if (find(accepted_commands.begin(), accepted_commands.end(), parts.at(0)) != accepted_commands.end()) {

        if (parts.at(0) == "quit" && parts.size() == 1) {
            return true;
        } else if (parts.at(0) == "themes" && parts.size() == 1) {
            print_themes(themes);
        } else if (parts.at(0) == "courses" && parts.size() == 3) {
            print_courses_in_location_and_theme(themes, parts.at(1), parts.at(2));
        } else if (parts.at(0) == "available" && parts.size() == 1) {
            print_available(themes);
        } else if (parts.at(0) == "courses_in_theme" && parts.size() == 2) {
            print_courses_in_theme(themes, parts.at(1));
        } else if (parts.at(0) == "courses_in_location" && parts.size() == 2) {
            print_courses_in_location(themes, parts.at(1));
        } else if (parts.at(0) == "favorite_theme" && parts.size() == 1) {
            print_favorite_theme(themes);
        } else if (parts.at(0) == "cancel" && parts.size() == 2) {
            cancel_course(themes, parts.at(1));
        } else {
            cout << "Error: error in command " << parts.at(0) << endl;
        }

    } else {
        cout << "Error: Unknown command: " << parts.at(0) << endl;
    }

    return false;

}

int main() {

    map<string, vector<Course>> themes;

    if (read_file_and_store_data(themes)) {

        while(true) {

            cout << "> ";

            string input;
            getline(cin, input);

            if (process_input(themes, input)) {
                return EXIT_SUCCESS;
            }
        }

    } else {
        return EXIT_FAILURE;
    }

}

