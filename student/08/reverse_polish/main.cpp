#include <iostream>
#include <string>

int main()
{

    std::cout << "Input an expression in reverse Polish notation (end with #):" << std::endl;
    std::cout << "EXPR>";

    char char_array[80];

    char to_check;

    int size = 0;

    for (int i = 0; i < 80; ++i) {
        std::cin >> to_check;
        if (i == 0) {
            if (!isdigit(to_check)) {
                std::cout << "Error: Expression must start with a number" << std::endl;
                return EXIT_FAILURE;
            }
        }

        if (to_check == '#') {
            break;
        }

        char_array[i] = to_check;
        size = i;
    }

    std::string input = "";
    for (int i = 0; i <= size; ++i) {
        input = input + char_array[i];
    }

//    //remove spaces from input
//    for (unsigned long i = 0; i < input.length(); ++i) {
//        std::cout << "index: " << i << ", input.at(i): " << input.at(i) << std::endl;
//        if (input.at(i) == ' ') {
//            input.erase(i, 1);
//            --i;
//        }
//    }

//    //std::cout << "your input without spaces: " << input << std::endl;

    int array[input.length()];

    int* pointer = array - 1;

//    if (!isdigit(input.at(0))) {
//        std::cout << "Error: Expression must start with a number" << std::endl;
//        return EXIT_FAILURE;
//    }

    for (unsigned long i = 0; i < input.length(); ++i) {

//        std::cout << "input.at(i) = " << input.at(i) << std::endl;

        if (input.at(i) == '#') {
            break;
        }

        if (input[i] == '+') {
            int result = 0;
            result = *pointer + *(pointer - 1);
//            std::cout << "pointer: " << *pointer << std::endl;
//            std::cout << "pointer - 1: " << *(pointer - 1) << std::endl;
//            std::cout << "adding " << result <<" to " << pointer - 1 << std::endl;
            *(pointer - 1) = result;
        } else if (input[i] == '-') {
            int result = 0;
            result = *(pointer - 1) - *pointer;
//            std::cout << "pointer: " << *pointer << std::endl;
//            std::cout << "pointer - 1: " << *(pointer - 1) << std::endl;
//            std::cout << "adding " << result <<" to " << pointer - 1 << std::endl;
            *(pointer - 1) = result;
        } else if (input[i] == '*') {
            int result = 0;
            result = *pointer * *(pointer - 1);
//            std::cout << "pointer: " << *pointer << std::endl;
//            std::cout << "pointer - 1: " << *(pointer - 1) << std::endl;
//            std::cout << "adding " << result <<" to " << pointer - 1 << std::endl;
            *(pointer - 1) = result;
        } else if (input[i] == '/') {

            if (*pointer == 0) {
                std::cout << "Error: Division by zero" << std::endl;
                return EXIT_FAILURE;
            }

            int result = 0;
            result = *(pointer - 1) / *pointer;
//            std::cout << "pointer: " << *pointer << std::endl;
//            std::cout << "pointer - 1: " << *(pointer - 1) << std::endl;
//            std::cout << "adding " << result <<" to " << pointer - 1 << std::endl;
            *(pointer - 1) = result;

        } else if (isdigit(input.at(i))){
            ++pointer;
            int integer_input = input.at(i) - '0';
            *pointer = integer_input;
//            std::cout << integer_input << " stored at " << pointer << std::endl << std::endl;
            continue;
        } else {
            std::cout << "Error: unknown character" << std::endl;
            return EXIT_FAILURE;
        }
        --pointer;
//        std::cout << std::endl;
    }

    if (pointer > array) {
        std::cout << "Error: too few operators" << std::endl;
        return EXIT_FAILURE;
    }

    if (pointer < array) {
        std::cout << "Error: too few operands" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Correct: " << *array << " is the result" << std::endl;
    return EXIT_SUCCESS;

}
