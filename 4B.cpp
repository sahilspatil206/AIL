#include <iostream>
#include <cstdlib>
using namespace std;

double Q[6][2] = {0};

int main() {
    double alpha = 0.1;   // Learning rate
    double gamma = 0.9;   // Discount factor
    double epsilon = 0.2; // Random action probability

    // Training episodes
    for (int episode = 0; episode < 1000; episode++) {

        int state = 0;

        while (state != 5) {

            int action;

            // Exploration or exploitation
            if ((double)rand() / RAND_MAX < epsilon)
                action = rand() % 2;
            else
                action = (Q[state][0] > Q[state][1]) ? 0 : 1;

            // Perform action
            int next;

            if (action == 0)
                next = (state > 0) ? state - 1 : state;
            else
                next = state + 1;

            // Give reward
            int reward = (next == 5) ? 10 : -1;

            // Find maximum future Q value
            double future = 0;

            if (next != 5)
                future = max(Q[next][0], Q[next][1]);

            // Q-Learning formula
            Q[state][action] = Q[state][action] +
                alpha * (reward + gamma * future
                - Q[state][action]);

            state = next;
        }
    }

    // Display learned Q table
    cout << "Learned Q-Table:\n";

    for (int i = 0; i < 6; i++)
        cout << i << " : "
             << Q[i][0] << "  "
             << Q[i][1] << endl;

    // Test trained agent
    cout << "\nAI Learned Path:\n";

    int state = 0;
    cout << state;

    while (state != 5) {
        int action = (Q[state][0] > Q[state][1]) ? 0 : 1;

        if (action == 0)
            state--;
        else
            state++;

        cout << " -> " << state;
    }

    cout << "\nGoal Reached!";
}