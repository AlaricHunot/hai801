#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <ctime>
#include <algorithm>
using namespace std;

// Fonction d'évaluation basique pour le morpion
int evaluate(vector<vector<char>>& board) {
    for (const auto& row : board) {
        if (all_of(row.begin(), row.end(), [&](char cell) { return cell == 'X'; })) {
            return 1;  // Victoire du joueur X
        } else if (all_of(row.begin(), row.end(), [&](char cell) { return cell == 'O'; })) {
            return -1;  // Victoire du joueur O
        }
    }

    for (int col = 0; col < 3; ++col) {
        if (all_of(board.begin(), board.end(), [col](const auto& row) { return row[col] == 'X'; })) {
            return 1;
        } else if (all_of(board.begin(), board.end(), [col](const auto& row) { return row[col] == 'O'; })) {
            return -1;
        }
    }

    if (all_of(board.begin(), board.end(), [&](const auto& row) { return row[&row - &board[0]] == 'X'; })) {
        return 1;
    }

    if (all_of(board.begin(), board.end(), [&](const auto& row) { return row[2 - (&row - &board[0])] == 'X'; })) {
        return 1;
    }

    if (all_of(board.begin(), board.end(), [&](const auto& row) { return row[&row - &board[0]] == 'O'; })) {
        return -1;
    }

    if (all_of(board.begin(), board.end(), [&](const auto& row) { return row[2 - (&row - &board[0])] == 'O'; })) {
        return -1;
    }

    return 0;  // Match nul
}


// Fonction Minimax
int minimax(vector<vector<char>>& board, int depth, bool is_maximizing) {
    int score = evaluate(board);

    if (score != 0) {
        return score;
    }

    if (all_of(board.begin(), board.end(), [](const auto& row) { return none_of(row.begin(), row.end(), [](char cell) { return cell == ' '; }); })) {
        return 0;  // Match nul
    }

    if (is_maximizing) {
        int best_score = INT_MIN;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    score = minimax(board, depth + 1, false);
                    board[i][j] = ' ';
                    best_score = max(score, best_score);
                }
            }
        }
        return best_score;
    } else {
        int best_score = INT_MAX;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    score = minimax(board, depth + 1, true);
                    board[i][j] = ' ';
                    best_score = min(score, best_score);
                }
            }
        }
        return best_score;
    }
}

int main() {
    clock_t start_time = clock();

    // Charger le fichier dataset.txt
    ifstream file("dataset.txt");
    if (!file.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier." << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        vector<vector<char>> board{{line[1], line[2], line[3]},
                                   {line[4], line[5], line[6]},
                                   {line[7], line[8], line[9]}};

        char player = line[0];

        int result = minimax(board, 0, player == 'X');

        if (result == 1) {
            cout << "Victoire pour " << player << endl;
        } else if (result == -1) {
            cout << "Défaite pour " << player << endl;
        } else {
            cout << "Match nul pour " << player << endl;
        }
    }

    double execution_time = static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC;
    cout << "Temps d'exécution : " << execution_time << " secondes" << endl;

    return 0;
}
