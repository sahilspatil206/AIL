#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

string goal = "123456780";

// Calculate Manhattan distance
int heuristic(string s) {
    int h = 0;

    for (int i = 0; i < 9; i++) {
        if (s[i] == '0') continue;

        int num = s[i] - '1';
        h += abs(i / 3 - num / 3);
        h += abs(i % 3 - num % 3);
    }
    return h;
}

// Display board
void display(string s) {
    for (int i = 0; i < 9; i++) {
        cout << s[i] << " ";
        if (i % 3 == 2) cout << endl;
    }
    cout << endl;
}

int main() {
    string start;
    cout << "Enter 9 digits (0 for blank): ";
    cin >> start;

    // Priority queue: lowest cost first
    priority_queue<pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>> pq;

    map<string, int> dist;
    map<string, string> parent;

    pq.push({heuristic(start), start});
    dist[start] = 0;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (!pq.empty()) {
        string s = pq.top().second;
        pq.pop();

        if (dist[s] + heuristic(s) < 0) continue;

        if (s == goal) break;

        int pos = s.find('0');
        int x = pos / 3, y = pos % 3;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3)
                continue;

            string t = s;
            swap(t[pos], t[nx * 3 + ny]);

            if (!dist.count(t) || dist[s] + 1 < dist[t]) {
                dist[t] = dist[s] + 1;
                parent[t] = s;

                pq.push({dist[t] + heuristic(t), t});
            }
        }
    }

    if (!dist.count(goal)) {
        cout << "No solution found!";
        return 0;
    }

    // Print solution path
    vector<string> path;
    string s = goal;

    while (s != start) {
        path.push_back(s);
        s = parent[s];
    }

    path.push_back(start);

    cout << "\nSolution:\n";

    for (int i = path.size() - 1; i >= 0; i--)
        display(path[i]);

    cout << "Total moves: " << dist[goal];
}






Important concepts
1. What is A algorithm?*

A* is an informed search algorithm that finds the shortest path using:
\[
f(n)=g(n)+h(n)
\]

- g(n) = Cost from starting state to current state.
- h(n) = Estimated cost from current state to goal.
- f(n) = Total estimated cost.
2. What is a heuristic?

A heuristic estimates how far the current state is from the goal.

Your program uses Manhattan Distance.

3. What is Manhattan Distance?

It calculates the sum of horizontal and vertical distances of every tile from its correct position.
\[
h(n)=\sum (|x_1-x_2|+|y_1-y_2|)
\]

4. Why use a priority queue?

To select the state with the lowest f(n) value first.

5. Why use a map?
- dist: Stores the minimum known cost to reach a state.
- parent: Stores the previous state to reconstruct the solution path.
Important code explanation
Code	Purpose
heuristic(start)	Calculates Manhattan distance
priority_queue	Selects lowest-cost state
s.find('0')	Finds blank position
swap()	Moves blank tile
parent[t] = s	Stores previous state
dist[t] = dist[s] + 1	Updates path cost

Viva questions
Q1. Which algorithm is used?

A. A* Search Algorithm.

Q2. Is A informed or uninformed search?*

A. Informed search because it uses a heuristic.

Q3. What is the time complexity?

A. It depends on the search space and heuristic; in the worst case it can be exponential.

Q4. Is Manhattan distance admissible?

A. Yes. It never overestimates the minimum number of moves needed to reach the goal.

Q5. What does 0 represent?

A. The blank space.

Q6. What is the difference between BFS and A?*

A. BFS explores level by level, whereas A* uses path cost and heuristic to select promising states.