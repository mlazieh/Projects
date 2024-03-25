/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Michael Lazieh
 * Date        : 9/14/23
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() { //This is a destructor. You have to delete all your objects after they're printed cause it's not automatically deleted like with the Java VM.
        delete [] is_prime_;
    }

    void display_primes() const; 

private:
    // Instance variables
    bool * const is_prime_; //Array of truth values
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}




void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    int primes_printed = 1;
    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width + 1);

    for (int i = 2; i <= limit_; i++) { //Make a variable primes_printed and increase by 1 each output. When it equals primes_per_row, make a new line.
        if (limit_ == 2) {
            cout << i << endl;
        }
        else {
                if (is_prime_[i]) {
                    if (num_primes_ <= 28) {
                        if (i == max_prime_) {
                            cout << " " << i << endl;
                        } 
                        
                        else {
                            if (primes_printed > 1) {
                                cout << " ";
                            }
                            cout << i;
                            primes_printed++;
                        }
                    }
 

                    else {
                        if (i == max_prime_) {
                            cout << setw(max_prime_width) << i << endl;
                        }
                    
                        else if (primes_printed == primes_per_row) {    //If its the last in a line
                            cout << setw(max_prime_width) << i << endl;
                            primes_printed = 1;
                        }
                    
                        else if (primes_printed == 1) { //If its the first in a line
                            cout << setw(max_prime_width) << i << " ";
                            primes_printed++;
                        }
                    
                        else {  //If its in the middle of a line
                            cout << setw(max_prime_width) << i << " " << setw(max_prime_width);
                            primes_printed++;
                        } 
                    }
                }
            }
        }
    }
    
void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.
    num_primes_ = 0;    //THIS CANT BE AN INT OR ELSE THE WHOLE THING FAILS. I DO NOT KNOW WHY.
    for (int i = 0; i <= limit_; i++) {
        is_prime_[i] = true;
    }

    for (int i = 2; i <= sqrt(limit_); i++) {
        if (is_prime_[i]) {
                for (int j = i * i; j <= limit_; j+=i) {
                    is_prime_[j] = false;
                }
            }
        }
    
    for (int i = 2; i <= limit_; i++) {
        if (is_prime_[i]) {
            num_primes_++;
            max_prime_ = i;
        }
    }

    if (limit_ == 2) {
        num_primes_ = 1;
    }

    cout << "\nNumber of primes found: " << num_primes_ <<  "\nPrimes up to " << limit_ << ":" << endl;
}

int PrimesSieve::num_digits(int num) { 
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count = 0;
    while (num > 0) {
        num = num/10;
        count++;
    }

    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve test (limit);
    test.display_primes();

    // TODO: write code that uses your class to produce the desired output.
    return 0;
}
