#include <iostream>
#include <algorithm>
using namespace std;

char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

// Check winner
int winner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            if (board[i][0] == 'O') return 10;
            if (board[i][0] == 'X') return -10;
        }

        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) {
            if (board[0][i] == 'O') return 10;
            if (board[0][i] == 'X') return -10;
        }
    }

    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == 'O') return 10;
        if (board[0][0] == 'X') return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == 'O') return 10;
        if (board[0][2] == 'X') return -10;
    }

    return 0;
}

// Check empty spaces
bool empty() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' &&
                board[i][j] != 'O')
                return true;

    return false;
}

// Minimax with Alpha-Beta Pruning
int minimax(bool computer, int alpha, int beta, int depth) {
    int score = winner();

    if (score != 0) return score;
    if (!empty()) return 0;

    if (computer) {
        int best = -1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' &&
                    board[i][j] != 'O') {

                    char temp = board[i][j];
                    board[i][j] = 'O';

                    best = max(best,
                        minimax(false, alpha, beta, depth + 1));

                    board[i][j] = temp;

                    alpha = max(alpha, best);

                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' &&
                    board[i][j] != 'O') {

                    char temp = board[i][j];
                    board[i][j] = 'X';

                    best = min(best,
                        minimax(true, alpha, beta, depth + 1));

                    board[i][j] = temp;

                    beta = min(beta, best);

                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    }
}

// Computer's best move
void computerMove() {
    int best = -1000, r = -1, c = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' &&
                board[i][j] != 'O') {

                char temp = board[i][j];
                board[i][j] = 'O';

                int score = minimax(false, -1000, 1000, 0);

                board[i][j] = temp;

                if (score > best) {
                    best = score;
                    r = i;
                    c = j;
                }
            }
        }
    }

    board[r][c] = 'O';
}

void display() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

int main() {
    int move;

    while (true) {
        display();

        if (winner() != 0 || !empty()) break;

        cout << "\nEnter your position (X): ";
        cin >> move;

        int r = (move - 1) / 3;
        int c = (move - 1) % 3;

        if (move < 1 || move > 9 ||
            board[r][c] == 'X' || board[r][c] == 'O') {
            cout << "Invalid move!\n";
            continue;
        }

        board[r][c] = 'X';

        if (winner() != 0 || !empty()) break;

        computerMove();
    }

    display();

    if (winner() == 10)
        cout << "Computer Wins!";
    else if (winner() == -10)
        cout << "You Win!";
    else
        cout << "Draw!";
}