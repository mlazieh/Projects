/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Michael Lazieh
 * Date        : 9/27/23
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge on my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    
    for (char letter : s) { //Stores the first value of the string as char c, iterates through all of string s.
        
        if (!(islower(letter))) {   //Uses islower() from C standard library to check if value is not lowercase.
            return false;
            }
        }
    
    return true;    //If all return false for being uppercase, then all are lowercase and we return true.
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only. Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.
    unsigned int comparison = 0;        //A bunch of 0s we will update one by one for each letter we find.
    unsigned int letter;            
    
    for (size_t i = 0; i < s.length(); i++) { //We use size_t instead of int because it works better for an array index.
        letter = 1 << (s.at(i) - 'a'); //32 bit version of the character we're on in our string.

        if ((letter & comparison) == 0) {       //If the AND function of letter and comparison gives 0 for this character (which means it's not 1 & 1), there is a letter in the string we have not counted for.
            comparison = comparison | letter;
        }
        
        else {
            return false;
        }
    }

    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    string word;

    //Checks if there's no argument
    if (argc < 2) {
        cout << "Usage: ./unique <string>" << endl;
        return 1;
    } 
    //Checks if there's too many arguments
    else if (argc > 2) {
        cout << "Usage: ./unique <string>" << endl;
        return 1;
    }
    
    //Tests to see if the input can be converted to a string. Won't work if input is numbers.
    if (!(is_all_lowercase(argv[1]))) {
        cout << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if (!(all_unique_letters(argv[1]))) {
        cout << "Duplicate letters found." << endl;
        return 1;
    }

    else {
        cout << "All letters are unique." << endl;
        return 0;
    }

    }