#include <iostream>
#include <cctype>
#include <string>

using namespace std;

bool check_english(string s) {
    bool b = true;
    for (long unsigned int i = 0; i < s.length(); ++i) {
        char c = s.at(i);
        if(c < 97 || c > 122) {
            b = false;
        }
    }
    return b;
}

bool check_all_letters(string s) {

    bool b = true;

    //calculate sum of 97-122
    int sum = 0;
    for(int i = 97; i <= 122; ++i) {
        sum += i;
    }

    //calculate sum of all characters in the string
    int key_sum = 0;
    for (long unsigned int i = 0; i < s.length(); ++i) {
        char c = s.at(i);
        key_sum += c;
    }

    //cout << "sum and key sum: " << sum << " " << key_sum << endl;

    //the sums should be the same if the string contains all characters a-z
    if (sum != key_sum) {
        b = false;
    }

    return b;

}

string encrypt(string k, string t) {

    string blacklist= "";

    //go through all characters in the key
    for (long unsigned int i = 0; i < k.length(); ++i) {

        //select which character we're replacing, starting with 'a' (97)
        char char_to_replace = 97 + i;

        //select the character we're going to replace it with by getting it from the key
        char replacement = k.at(i);


        //go through all characters in the text
        for (long unsigned int j = 0; j < t.length(); ++j) {

            //if we find the character we're replacing, replace it
            if(t.at(j) == char_to_replace) {

                if(blacklist.find("a" + to_string(j) + "b") == string::npos) {
                    //blacklist the letter index
                    blacklist.append("a" + to_string(j) + "b");

                    string poop = string(1, replacement);
                    //cout << "character to replace found: " << string(1,t.at(j)) << ", replacing with " << poop << endl;
                    t.replace(j,1,poop);
                } else {
                    //cout << "not replacing " << j << " again" << endl;
                }


            }
        }

        //cout << blacklist << endl;




        //cout << t << endl;
        //cout << endl;

    }

    return t;


}

int main()
{

    string key = "";
    string text = "";
    key = "qwertyuiopasdfghjklzxcvbnm";
    cout << "Enter the encryption key: ";
    getline(cin, key);

    //check 1: key must be 26 characters long
    if (key.length() != 26) {
        cout << "Error! The encryption key must contain 26 characters.";
        return EXIT_FAILURE;
    }

    //check 2: key must contain only lowercase english letters
    if (!check_english(key)) {
        cout << "Error! The encryption key must contain only lower case characters.";
        return EXIT_FAILURE;
    }

    //check 3: key must contain all letters in the english alphabet
    if (!check_all_letters(key)) {
        cout << "Error! The encryption key must contain all alphabets a-z.";
        return EXIT_FAILURE;
    }

    cout << "Enter the text to be encrypted: ";
    getline(cin, text);

    //check 4: text must contain only lowercase english letters
    if (!check_english(text)) {
        cout << "Error! The text to be encrypted must contain only lower case characters.";
        return EXIT_FAILURE;
    }

    cout << "Encrypted text: " << encrypt(key,text);


}
