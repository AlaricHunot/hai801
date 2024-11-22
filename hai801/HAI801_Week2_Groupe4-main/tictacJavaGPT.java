import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class tictacJavaGPT {
    public static void main(String[] args) {
        long startTime = System.currentTimeMillis();
        long occurence= 0;
        try (BufferedReader reader = new BufferedReader(new FileReader("dataset.txt"))) {
            String line;
            while ((line = reader.readLine()) != null) {
                char[][] board = {
                        {line.charAt(1), line.charAt(2), line.charAt(3)},
                        {line.charAt(4), line.charAt(5), line.charAt(6)},
                        {line.charAt(7), line.charAt(8), line.charAt(9)}
                };
                char player = line.charAt(0);

                int result = minimax(board, 0, player == 'X');

                if (result == 1) {
                    System.out.println("Victoire " + player);
                    occurence++;
                } else if (result == -1) {
                    System.out.println("Défaite " + player);
                    occurence++;
                } else {
                    System.out.println("Match nul");
                    occurence++;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        long executionTime = System.currentTimeMillis() - startTime;
        System.out.println("Temps d'exécution : " + (executionTime / 1000.0) + " secondes");
        System.out.println(occurence);
    }

    private static int minimax(char[][] board, int depth, boolean isMaximizing) {
        int score = evaluate(board);

        if (score != 0) {
            return score;
        }

        if (!containsEmptyCell(board)) {
            return 0;
        }

        if (isMaximizing) {
            int bestScore = Integer.MIN_VALUE;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'X';
                        int currentScore = minimax(board, depth + 1, false);
                        board[i][j] = ' ';
                        bestScore = Math.max(currentScore, bestScore);
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = Integer.MAX_VALUE;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        board[i][j] = 'O';
                        int currentScore = minimax(board, depth + 1, true);minmaxPy2CPPGPT
                        board[i][j] = ' ';
                        bestScore = Math.min(currentScore, bestScore);
                    }
                }
            }
            return bestScore;
        }
    }

    private static int evaluate(char[][] board) {
        for (char[] row : board) {
            if (row[0] == row[1] && row[1] == row[2] && row[0] != ' ') {
                return (row[0] == 'X') ? 1 : -1;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
                return (board[0][i] == 'X') ? 1 : -1;
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
            return (board[0][0] == 'X') ? 1 : -1;
        }

        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
            return (board[0][2] == 'X') ? 1 : -1;
        }

        return 0;
    }

    private static boolean containsEmptyCell(char[][] board) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return true;
                }
            }
        }
        return false;
    }
}
