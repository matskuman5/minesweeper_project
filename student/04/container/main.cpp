#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
        // TODO: Implement your solution here
    }
}

// TODO: Implement your solution here

bool same_values(const std::vector<int>& ints) {

    bool b = true;

    for(unsigned long i = 0; i < ints.size() - 1; ++i) {
        if (!(ints.at(i) == ints.at(i + 1))) {
            b = false;
            break;
        }
    }

    return b;

}

bool is_ordered_non_strict_ascending(const std::vector<int>& ints) {

    bool b = true;

    for(unsigned long i = 0; i < ints.size() - 1; ++i) {
        if (ints.at(i) > ints.at(i + 1)) {
            b = false;
            break;
        }
    }

    return b;

}

bool is_arithmetic_series(const std::vector<int>& ints) {

    bool b = true;
    int difference = 0;

    for(unsigned long i = 0; i < ints.size() - 1; ++i) {
//        std::cout << "checking " << ints.at(i) << " and " << ints.at(i + 1) << std::endl;
        if (i == 0 && ints.size() > 1) {

            difference = ints.at(i + 1) - ints.at(i);
//            std::cout << "setting sum at " << difference << std::endl;
        }

        if (difference != ints.at(i + 1) - ints.at(i)) {
//            std::cout << "sum of " << ints.at(i) + ints.at(i+1) << "is not good" << std::endl;
            b = false;
            break;
        }

    }

    return b;

}

bool is_geometric_series(const std::vector<int>& ints) {

    bool b = true;
    int ratio = 0;

    for(unsigned long i = 0; i < ints.size() - 1; ++i) {

        if(ints.at(i + 1) == 0) {
            b = false; // let's not divide by 0
            break;
        }

        if (i == 0 && ints.size() > 1) {
            ratio = ints.at(i + 1) / ints.at(i);
        }

        if (ratio != ints.at(i + 1) / ints.at(i)) {
            b = false;
            break;
        }

    }

    return b;

}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}