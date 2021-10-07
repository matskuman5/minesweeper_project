#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void store(std::string id1, std::string id2, std::vector<std::string>& recruitments) {

    recruitments.push_back(id1 + " " + id2);

}

void print(std::string id, const std::vector<std::string> recruitments, int level = 0) {

    for(int i = 0; i < level; i++) {
        std::cout << "..";
    }

    std::cout << id << std::endl;

    for(std::string s : recruitments) {

        std::vector<std::string> parts = split(s, ' ', true);

        if(parts.at(0) == id) {
            int new_level = level + 1;
            print(parts.at(1), recruitments, new_level);
        }

    }

}

int count(std::string id, const std::vector<std::string> recruitments) {

    int i = 0;

    for(std::string s : recruitments) {

        std::vector<std::string> parts = split(s, ' ', true);

        if(parts.at(0) == id) {
            i++;
            i = i + count(parts.at(1), recruitments);
        }

    }

    return i;

}

int depth(std::string id, const std::vector<std::string> recruitments) {

    bool empty = true;
    std::vector<int> depths;

//    std::cout << "beginning function with id: " << id << std::endl;

    for(std::string s : recruitments) {

        std::vector<std::string> parts = split(s, ' ', true);

        if(parts.at(0) == id) {
            empty = false;
//            std::cout << parts.at(0) << " has child node: " << parts.at(1) << std::endl;
            int value = depth(parts.at(1), recruitments);
//            std::cout << "storing value: " << value << std::endl;
            depths.push_back(value);
        }

    }

    if(empty) {
//        std::cout << "node " << id << " is empty, returning 1" << std::endl;
        return 1;
    }

    int greatest_depth = 0;
    for(int i : depths) {
        if(i > greatest_depth) {
            greatest_depth = i;
        }
    }
//    std::cout << std::endl;
//    std::cout << "node: " << id << ", returning greatest depth: " << greatest_depth << std::endl;
    return greatest_depth + 1;



}

int main()
{

    std::vector<std::string> recruitments;


    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            store(id1, id2, recruitments);

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print(id, recruitments);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << count(id, recruitments) << std::endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << depth(id, recruitments) << std::endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
