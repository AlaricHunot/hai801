import chess
import random


def evaluate_board_v1(board):
    score = 0
    for piece_type in chess.PIECE_TYPES:
        score += len(board.pieces(piece_type, chess.WHITE)) - len(board.pieces(piece_type, chess.BLACK))
    return score

def evaluate_board_v2(board):
    score = 0
    for square in chess.SQUARES:
        piece = board.piece_at(square)
        if piece is not None:
            if piece.color == chess.WHITE:
                score += 1
            else:
                score -= 1
    return score


def hill_climbing(board, evaluate_func, depth):
    best_move = None
    best_score = -float('inf')

    for _ in range(depth):
        legal_moves = list(board.legal_moves)
        random.shuffle(legal_moves)  
        for move in legal_moves:
            board.push(move)
            score = evaluate_func(board)
            if score > best_score:
                best_score = score
                best_move = move
            board.pop()

    return best_move


def play_games(iterations):

    evaluate_func_1 = evaluate_board_v1
    evaluate_func_2 = evaluate_board_v2
    

    for i in range(iterations):
        print("Iteration", i+1)
        

        board = chess.Board()
        

        while not board.is_game_over():
            print(board) 
            print()  
            
            if board.turn == chess.WHITE:
                # IA 1 (Blancs)
                move = hill_climbing(board, evaluate_func_1, depth=3)
            else:
                # IA 2 (Noirs)
                move = hill_climbing(board, evaluate_func_2, depth=3)
                
            board.push(move)
        
    
        print(board)
        print("Game Over")
        print("Result:", board.result())


        if board.result() == '1-0':
            evaluate_func_1 = update_evaluation_function(evaluate_func_1, True)
            evaluate_func_2 = update_evaluation_function(evaluate_func_2, False)
        elif board.result() == '0-1':
            evaluate_func_1 = update_evaluation_function(evaluate_func_1, False)
            evaluate_func_2 = update_evaluation_function(evaluate_func_2, True)

        

def update_evaluation_function(evaluate_func, won):

    if won:
        weight = 1
    else:
        weight = -1

    updated_func = lambda board: evaluate_func(board) + 0.1 * weight
    
    return updated_func

def main():
    iterations = 10

    play_games(iterations)

if __name__ == "__main__":
    main()