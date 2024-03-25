/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Michael Lazieh 
 * Date        : 10/4/23
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> num_ways = vector<vector<int>>();
    
    if (num_stairs == 0) {
        return vector<vector<int>>(1, vector<int>());
        //vector<vector<int>>(4, vector<int>(5,0));
    }
    
    else {
        for (int i = 1; i <= 3; i++) {
            if ((num_stairs - i) < 0) {
                break;
            }
            vector<vector<int>> prev = get_ways(num_stairs - i);

            for(auto& vector : prev) {  //auto is just a more efficent way of going through the vectors in prev instead of vector<vector<<int>>
                //We want to concatanate the i value of the outer loop to each value in prev
                vector.insert(vector.begin(), i);   //This inserts i at the start of each vector in prev
                num_ways.push_back(vector);     //Now we just push this vector in prev with i prepended onto the total num_ways
            }

        }

        return num_ways;
    }
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    size_t NUM_WAYS = ways.size();
    size_t NUM_STAIRS = ways.at(0).size();
    
    if (NUM_WAYS == 1) {
        cout << NUM_WAYS << " way to climb ";
    }

    else {
        cout << NUM_WAYS << " ways to climb ";
        }

    if (NUM_STAIRS == 1) {
        cout << NUM_STAIRS << " stair." << endl;
    }
    else {
        cout << NUM_STAIRS << " stairs." << endl;
        }

    int LEN = 1;
    while (NUM_WAYS > 10) {
        NUM_WAYS /= 10;
        LEN += 1;

    }
    for (size_t i = 0; i < ways.size(); i++) {
        cout << setw(LEN) << i + 1 << ". ";
        for (size_t j = 0; j < ways.at(i).size(); j++) {
            if (j == 0 && j == ways.at(i).size() - 1) {
                cout << "[" << ways.at(i).at(j) << "]";
            }
            else if (j == 0) {
                cout << "[" << ways.at(i).at(j) << ", "; //Use vector.at(i) cause vector[i] does not check if it goes over
            }
            else if (j == ways.at(i).size() - 1) {
                cout << ways.at(i).at(j) << "]";
            }
            else {cout << ways.at(i).at(j) << ", ";}
        }
        if (i != ways.size() - 1) {
            cout << endl;
        }
    }   
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }

    int n;
    istringstream iss(argv[1]);

    if (!(iss >> n) || n <= 0) {
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    display_ways(get_ways(n));

    return 0;

    }
