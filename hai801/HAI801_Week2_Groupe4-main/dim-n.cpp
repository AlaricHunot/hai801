#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <random>
#include <ctime>
#include <string>

class TicTacToeBoard {
public:
    TicTacToeBoard(int size) : size(size), board(size, std::vector<char>(size, ' ')) {}

    bool isFinal() const {
        // Vérification des lignes
        for (int row = 0; row < size; row++) {
            char firstCell = board[row][0];
            if (firstCell != ' ') {
                bool win = true;
                for (int col = 1; col < size; col++) {
                    if (board[row][col] != firstCell) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return true;
                }
            }
        }

        // Vérification des colonnes
        for (int col = 0; col < size; col++) {
            char firstCell = board[0][col];
            if (firstCell != ' ') {
                bool win = true;
                for (int row = 1; row < size; row++) {
                    if (board[row][col] != firstCell) {
                        win = false;
                        break;
                    }
                }
                if (win) {
                    return true;
                }
            }
        }

        // Vérification de la diagonale principale
        char firstCell = board[0][0];
        if (firstCell != ' ') {
            bool win = true;
            for (int i = 1; i < size; i++) {
                if (board[i][i] != firstCell) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }

        // Vérification de la diagonale anti-principale
        firstCell = board[0][size - 1];
        if (firstCell != ' ') {
            bool win = true;
            for (int i = 1; i < size; i++) {
                if (board[i][size - 1 - i] != firstCell) {
                    win = false;
                    break;
                }
            }
            if (win) {
                return true;
            }
        }

        // Vérification des cases vides
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                if (board[row][col] == ' ') {
                    return false; // Le jeu n'est pas terminé s'il y a encore une case vide
                }
            }
        }

        return true; // Si aucun joueur n'a gagné et qu'il n'y a plus de cases vides, le jeu est terminé
    }

    std::vector<TicTacToeBoard> getChildren() const {
        std::vector<TicTacToeBoard> children;
        char player = 'X'; // Le joueur X commence toujours
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                if (board[row][col] == ' ') {
                    TicTacToeBoard child(*this); // Copie du plateau actuel
                    child.board[row][col] = player; // Placement du coup du joueur
                    children.push_back(child); // Ajout du plateau enfant à la liste
                }
            }
        }
        return children;
    }

    void printToFile(std::ofstream& file) const {
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                file << board[row][col]; // Écriture du symbole de chaque case dans le fichier
            }
            file << std::endl; // Nouvelle ligne pour séparer les lignes du plateau
        }
        file << std::endl; // Ligne vide pour séparer les plateaux dans le fichier
    }

    size_t hash() const {
        std::hash<std::string> hasher;
        std::string boardString;
        for (const auto& row : board) {
            for (char cell : row) {
                boardString += cell; // Concaténation de tous les symboles de cases pour former une chaîne
            }
        }
        return hasher(boardString); // Utilisation du hachage de la chaîne pour obtenir un hash unique
    }

private:
    int size;
    std::vector<std::vector<char>> board;
};

int main() {
    // Paramètres du jeu
    int size = 4; // Taille du plateau
    int samples = 100000; // Nombre d'échantillons à générer
    std::string output = "dataset.txt"; // Nom du fichier de sortie

    // Initialisation de la graine pour le générateur de nombres aléatoires
    std::mt19937 rng(std::time(nullptr));

    // Génération du dataset
    std::unordered_set<size_t> visitedStates;
    TicTacToeBoard initialBoard(size);
    std::ofstream file(output);
    file << size << std::endl;

    int k = 0;
    std::vector<TicTacToeBoard> stack = {initialBoard};
    while (!stack.empty() && k < samples) {
        TicTacToeBoard currentBoard = stack.back();
        stack.pop_back();
        if (!currentBoard.isFinal()) {
            currentBoard.printToFile(file);
            k++;
            std::vector<TicTacToeBoard> children = currentBoard.getChildren();
            for (const auto& child : children) {
                size_t hashValue = child.hash();
                if (visitedStates.find(hashValue) == visitedStates.end()) {
                    visitedStates.insert(hashValue);
                    stack.push_back(child);
                }
            }
        }
    }

    std::cout << "[" << std::string(50, '=') << "]" << " 100%   " << std::endl;

    return 0;
}