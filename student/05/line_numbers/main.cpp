#include <iostream>
#include <fstream>

using namespace std;

int main()
{

    cout << "Input file: ";
    string input_file;
    getline(cin, input_file);

    cout << "Output file: ";
    string output_file;
    getline(cin, output_file);

    ifstream reader(input_file);
    ofstream printer(output_file);

    if(reader) {
        string line;
        int i = 0;
        while(getline(reader, line)) {
            i++;
            string new_line = to_string(i) + " " + line;
            printer << new_line;
        }
        reader.close();
        printer.close();
    } else {
        cout << "Error! The file " << input_file << " cannot be opened.";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
