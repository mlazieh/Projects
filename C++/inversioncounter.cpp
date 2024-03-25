/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Michael Lazieh
 * Version     : 1.0
 * Date        : 11/4/23
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;
//w
// Function prototype.
//static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long inversions = 0;
    for (int i = 0; i < length - 1; i++) {
        for (int j= i+1; j < length; j++) {
            if (array[i] > array[j]) {
                //swap(array[i],array[j]);
                inversions++;
            }
        }
    }
    return inversions;
}


long merge(int array[], int scratch[], int low, int mid, int high) {    

    long merge_inversions = 0;

    int i1 = low, i2 = mid + 1, i = low;

    while (i1 <= mid && i2 <= high) {
        if (array[i1] <= array[i2]) {
            scratch[i++] = array[i1++];
        } else { // Inversion here
            scratch[i++] = array[i2++];
            merge_inversions += (mid - i1 + 1);
        }
    }

    while (i1 <= mid) {
        scratch[i++] = array[i1++];
    }

    while (i2 <= high) { 
        scratch[i++] = array[i2++];
    }

    for (int i = low; i <= high; i++) {
        array[i] = scratch[i];
    }

    return merge_inversions;
}


static long mergesort(int array[], int scratch[], int low, int high) {      //What does this do
    // TODO
    long merge_inversions = 0;

    if (low < high) {
        int mid = low + (high-low)/2;   
        merge_inversions += mergesort(array, scratch, low, mid);
        merge_inversions += mergesort(array, scratch, mid+1, high);
        merge_inversions += merge(array, scratch, low, mid, high);
    }
    return merge_inversions;
}
/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    //return merge_inversions;

    int* scratch = new int[length];
    long count = mergesort(array, scratch, 0, length - 1);  //length - 1 because we need to index it properly
    delete[] scratch;       //Need to free memory
    return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    string type = "fast";  // Default to "fast"

    if (argc == 2) {
        if (string(argv[1]) == "slow") {    //Checks if it's slow or if it's anything other than slow
            type = "slow";
        } else {
            cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
            return 1;
        }
    } else if (argc != 1) {
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    }

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;

    cout << "Enter sequence of integers, each followed by a space: " << flush;


    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if (values.empty()) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    // TODO: produce output
    long inversion_count;
    
    if (type == "slow") {
        inversion_count = count_inversions_slow(&values[0], values.size());     
        cout << "Number of inversions (slow): " << inversion_count << endl;
    } 
    else {
        inversion_count = count_inversions_fast(&values[0], values.size());
        cout << "Number of inversions (fast): " << inversion_count << endl;
    }

    return 0;
}
