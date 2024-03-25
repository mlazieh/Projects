/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Michael Lazieh
 * Date        : 10/21/23
 * Description : Water Jug
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} {  }

    void set_string(State* parent) {    //This is how I can create copys of the current state in the pour function and store each valid current state with a string of directions.
                                            //It sets the currents direction as the parents directions and current directions as a string.
        directions = parent->directions + "\n" + directions + " " + to_string();        //parent -> directions is the parents directions, directions is current directions.
    }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

//Queue is going to add a copy of the acceptable states out of the 6 that can be created. When it hits one that it's seen before, (it'll check with another
//2D array we store it in- think memoization but not for efficenecy) it will skip that one and not include it in the next call of queue. When it 
//reaches the end of possibilities cause everything's invalid or a repeat, then it'll find the goal state one that is in there and print out it and all the parents 
//it points to all the way to the initial state.


//The 2D array from before is going to store all the states we make. It will have A + 1 rows and B + 1 columns.
//When we create a valid state (a,b,c), we store it in [a][b] of this array. 

//For (3,8,5), we start by storing state(0,0,8) in [0][0] with a null pointer to parent.
//Next, state(3,0,5) is stored in [3][0] with a parent pointer at element [0][0]
//Next, state(3,5,0) is stored in [3][5] with a parent pointer at [3][0]


bool operator==(const State& State1, const State& State2) {       //This lets me do State == State 
    return (State1.a == State2.a) && (State1.b == State2.b) && (State1.c == State2.c);
}

bool inVisited(State current, vector<vector<bool>> Visited) {
    return Visited[current.a][current.b];
}

//try the 6 ways to pour water, pushing new States to the queue
vector<State> pours(State current, int a_cap, int b_cap, int c_cap) {
    vector<State> Pours;
    State currentcopy = current;
    int POUR;
    int Space_in_A = a_cap - current.a;
    int Space_in_B = b_cap - current.b;
    int Space_in_C = c_cap - current.c;
    
    // 1) From C to A
    if ((Space_in_A != 0) && (current.c != 0)) {    //If A is not full and C is not empty, transfer it.
        POUR = min(current.c,Space_in_A);
        currentcopy = current;
        currentcopy.c -= POUR; 
        currentcopy.a += POUR;
        
        if (POUR == 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallon from C to A.";}
        if (POUR != 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallons from C to A.";}
        currentcopy.set_string(&current); 
        
            Pours.push_back(currentcopy);

    }
        // 2) From B to A
    if ((Space_in_A != 0) && (current.b != 0)) {    //If A is not full and B is not empty, transfer it.
        POUR = min(current.b,Space_in_A);
        currentcopy = current;
        currentcopy.b -= POUR; 
        currentcopy.a += POUR;

        if (POUR == 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallon from B to A.";}
        if (POUR != 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallons from B to A.";}
        currentcopy.set_string(&current); 

        Pours.push_back(currentcopy);
    }
        
        // 3) From C to B
    if ((Space_in_B != 0) && (current.c != 0)) {    //If B is not full and C is not empty, transfer it.
        POUR = min(current.c,Space_in_B);
        currentcopy = current;
        currentcopy.c -= POUR; 
        currentcopy.b += POUR;

        if (POUR == 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallon from C to B.";}
        if (POUR != 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallons from C to B.";}
        currentcopy.set_string(&current); 

        Pours.push_back(currentcopy);
    }
        // 4) From A to B
     if ((Space_in_B != 0) && (current.a != 0)) {    //If B is not full and A is not empty, transfer it.
        POUR = min(current.a,Space_in_B);
        currentcopy = current;
        currentcopy.a -= POUR; 
        currentcopy.b += POUR;

        if (POUR == 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallon from A to B.";}
        if (POUR != 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallons from A to B.";}
        currentcopy.set_string(&current); 

        Pours.push_back(currentcopy);
    }
        // 5) From B to C
    if ((Space_in_C != 0) && (current.b != 0)) {    //If C is not full and B is not empty, transfer it.
        POUR = min(current.b,Space_in_C);
        currentcopy = current;
        currentcopy.b -= POUR; 
        currentcopy.c += POUR;

        if (POUR == 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallon from B to C.";}
        if (POUR != 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallons from B to C.";}
        currentcopy.set_string(&current); 

        Pours.push_back(currentcopy);
    }
        // 6) From A to C
    if ((Space_in_C != 0) && (current.a != 0)) {    //If C is not full and C is not empty, transfer it.
        POUR = min(current.a,Space_in_C);
        currentcopy = current;
        currentcopy.a -= POUR; 
        currentcopy.c += POUR;

        if (POUR == 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallon from A to C.";}
        if (POUR != 1) {
            currentcopy.directions = "Pour " + to_string(POUR) + " gallons from A to C.";}
        currentcopy.set_string(&current); 

        Pours.push_back(currentcopy);
    }
    
    return Pours;
}

void bfs(int a_cap, int b_cap, int c_cap, int a_goal, int b_goal, int c_goal) {
    int num_rows = a_cap + 1;
    int num_cols = b_cap + 1;
    
    State Initial_State(0, 0 , c_cap, "Initial state. (0, 0, "+to_string(c_cap)+")");
    //cout << Initial_State.to_string() << endl;
    vector<vector<bool>> Visited;

    for(int i = 0; i < num_rows; i++) {     //This sets the whole Visited vector to false
        vector<bool> row;
        for (int j = 0; j < num_cols; j++) {
            row.push_back(false);
        }
        Visited.push_back(row);     //Need to push back vector of falses each iteration
    }


    queue<State> Queue;
    
    State goal_state(a_goal, b_goal, c_goal, "Initial state");
    // State* current_address = new State(a_cap,b_cap,c_cap,"Initial state.");     //Current_address points towards the memory that has the state in it.
    //State current = *current_address;       //Current points towards the object of the state we have the address of.

    //add new State(a, b, c) to queue
    Queue.push(Initial_State);
    while(!(Queue.empty())) {
        //current <- front of queue
        State current = Queue.front(); 
        //pop from the queue
        Queue.pop();

        //if current equals goal_state
        if (current == goal_state) {
            //return the backtracked solution
            cout << current.directions;
            Visited.clear();
            Visited.shrink_to_fit();        //FOUND THIS ONLINE. Frees memory of vector.
            return;
        }
        //if current has already been seen continue
        if (inVisited(current, Visited)) {
            continue;
        }
        //mark current as having been visited
        Visited[current.a][current.b] = true;
        
        //for loop to get States
        vector<State> Pours = pours(current, a_cap, b_cap, c_cap);
        
        //try the 6 ways to pour water, pushing new States to the queue
        
        for (long unsigned int i = 0; i < Pours.size(); i++) {
            //cout << Pours[i].to_string() << endl;
            Queue.push(Pours[i]);
        }
    }
    cout << "No solution.";
}







int main(int argc, char * const argv[]) {
    if (argc != 7) {
        cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    } 
    
    istringstream iss;
    int goal;
    int A_cap, B_cap, C_cap, A_goal, B_goal, C_goal;

    // Move theses out of the for loop, have 6 if statements for each goal and capacity, iss.clear()
    //This checks that each value is an int, not negative, and that the last 3 values don't exceed the goal

    iss.str(argv[1]);
    if (!(iss >> A_cap) || A_cap <= 0) {
        cout << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
        return 1;
    }

    iss.clear();
    iss.str(argv[2]);

    if (!(iss >> B_cap) || B_cap <= 0) {
        cout << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
        return 1;
    }

    iss.clear();
    iss.str(argv[3]);


    if (!(iss >> C_cap) || C_cap <= 0) {
        cout << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
        return 1;
    }

    iss.clear();
    iss.str(argv[4]);

    if (!(iss >> A_goal) || A_goal < 0) {
        cout << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
        return 1;
    }

    iss.clear();
    iss.str(argv[5]);

    if (!(iss >> B_goal) || B_goal < 0) {
        cout << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
        return 1;
    }

    iss.clear();
    iss.str(argv[6]);

    if (!(iss >> C_goal) || C_goal < 0) {
        cout << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
        return 1;
    }

    iss.clear();

    //Checks each goal isn't above capacity
    if (A_goal > A_cap) {cout << "Error: Goal cannot exceed capacity of jug A." << endl; return 1;}
    if (B_goal > B_cap) {cout << "Error: Goal cannot exceed capacity of jug B." << endl; return 1;}
    if (C_goal > C_cap) {cout << "Error: Goal cannot exceed capacity of jug C." << endl; return 1;}
    
    //This gets the capacity for Jug C and to check that the goal equals C_cap
    goal = A_goal + B_goal + C_goal;

    if (goal != C_cap) {
        cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }

    bfs(A_cap, B_cap, C_cap, A_goal, B_goal, C_goal);

    return 0;
};