import time

def evaluate(board):
    for row in board:
        if all(cell == 'X' for cell in row):
            return 1  
        elif all(cell == 'O' for cell in row):
            return -1  
    
    for col in zip(*board):
        if all(cell == 'X' for cell in col):
            return 1
        elif all(cell == 'O' for cell in col):
            return -1
    
    if all(board[i][i] == 'X' for i in range(3)) or all(board[i][2-i] == 'X' for i in range(3)):
        return 1
    
    if all(board[i][i] == 'O' for i in range(3)) or all(board[i][2-i] == 'O' for i in range(3)):
        return -1
    
    return 0  # Match nul

def minimax(board, depth, is_maximizing):
    score = evaluate(board)

    if score != 0:
        return score

    if ' ' not in [cell for row in board for cell in row]:
        return 0  # Match nul

    if is_maximizing:
        best_score = float('-inf')
        for i in range(3):
            for j in range(3):
                if board[i][j] == ' ':
                    board[i][j] = 'X'
                    score = minimax(board, depth+1, False)
                    board[i][j] = ' '
                    best_score = max(score, best_score)
        return best_score
    else:
        best_score = float('inf')
        for i in range(3):
            for j in range(3):
                if board[i][j] == ' ':
                    board[i][j] = 'O'
                    score = minimax(board, depth+1, True)
                    board[i][j] = ' '
                    best_score = min(score, best_score)
        return best_score

def main():
    start_time = time.time()

    
    with open('dataset.txt', 'r') as file:
        data = file.readlines()

    for line in data:
        board = [list(line[1:4]), list(line[4:7]), list(line[7:10])]
        player = line[0]

        result = minimax(board, 0, player == 'X')

        if result == 1:
            print("Victoire pour", player)
        elif result == -1:
            print("Défaite pour", player)
        else:
            print("Match nul")

    execution_time = time.time() - start_time
    print(f"Temps d'exécution : {execution_time} secondes")

if __name__ == "__main__":
    main()
