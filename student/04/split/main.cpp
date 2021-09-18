#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function

std::vector< std::string > split(std::string string, char separator, bool skip_empty = false) {

    std::vector< std::string > group;

    int amount = 1;
    int last_separator_index = -1;



    for(std::string::size_type i = 0; i < string.size(); ++i) {

//        std::cout << "last_separator_index: " << last_separator_index << std::endl;
//        std::cout << "amount to snip: " << i - last_separator_index - 1 << std::endl;
//        std::cout << "i: " << i << std::endl;

//        std::cout << "checking char: " << string.at(i) << std::endl;

        if(string.at(i) == separator) {
//            std::cout << "snipping from " << last_separator_index + 1 << " with amount " << i - last_separator_index - 1 << std::endl;
            std::string string_to_be_added = (string.substr(last_separator_index + 1, i - last_separator_index - 1));
            if (string_to_be_added.size() == 0) {
                if (!skip_empty) {
//                    std::cout << "adding empty part" << std::endl;
                    group.push_back("");
                }

            } else {
                group.push_back(string.substr(last_separator_index + 1, i - last_separator_index - 1));
            }

            amount = 1;
            last_separator_index = i;

        } else if (amount != 1) {
            amount++;
        }

//        std::cout << std::endl;




    }

//    std::cout << "finally adding the rest of the string: from " << last_separator_index + 1 << " with amount " << string.size() - last_separator_index - 1 << std::endl;
    std::string string_to_be_added = (string.substr(last_separator_index + 1, string.size() - last_separator_index - 1));
    if (string_to_be_added.size() == 0) {
        if (!skip_empty) {
//            std::cout << "adding empty part" << std::endl;
            group.push_back("");
        }

    } else {
        group.push_back(string.substr(last_separator_index + 1, string.size() - last_separator_index - 1));
    }

//    std::cout << std::endl;
//    std::cout << std::endl;

    return group;

}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
