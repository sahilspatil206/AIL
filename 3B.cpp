#include <iostream>
using namespace std;

int n = 8, m = 4;

// States
string states[] = {
    "Maharashtra", "Gujarat", "Goa", "Karnataka",
    "Telangana", "Madhya Pradesh", "Rajasthan", "Chhattisgarh"
};

// Adjacency matrix
int graph[8][8] = {
    {0,1,1,1,1,1,0,0},
    {1,0,0,0,0,0,1,0},
    {1,0,0,1,0,0,0,0},
    {1,0,1,0,1,0,0,0},
    {1,0,0,1,0,1,0,1},
    {1,0,0,0,1,0,1,1},
    {0,1,0,0,0,1,0,0},
    {0,0,0,0,1,1,0,0}
};

string colors[] = {"Red", "Green", "Blue", "Yellow"};

int color[8] = {0};

// Check whether color is safe
bool isSafe(int node, int c) {
    for (int i = 0; i < n; i++) {
        if (graph[node][i] == 1 && color[i] == c)
            return false;
    }
    return true;
}

// Backtracking function
bool solve(int node) {
    if (node == n)
        return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(node, c)) {
            color[node] = c;

            if (solve(node + 1))
                return true;

            color[node] = 0;
        }
    }

    return false;
}

int main() {
    if (solve(0)) {
        cout << "Map Coloring Solution:\n";

        for (int i = 0; i < n; i++) {
            cout << states[i] << " : "
                 << colors[color[i] - 1] << endl;
        }
    }
    else {
        cout << "No solution exists!";
    }

    return 0;
}
