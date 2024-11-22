import chess
import random

def evaluate_board(board):

    score = 0
    for piece_type in chess.PIECE_TYPES:
        score += len(board.pieces(piece_type, chess.WHITE)) - len(board.pieces(piece_type, chess.BLACK))
    return score

def hill_climbing(board, depth):

    best_move = None
    best_score = -float('inf')

    for _ in range(depth):
        legal_moves = list(board.legal_moves)
        random.shuffle(legal_moves)  # Mélange les mouvements pour éviter les biais
        for move in legal_moves:
            board.push(move)
            score = evaluate_board(board)
            if score > best_score:
                best_score = score
                best_move = move
            board.pop()

    return best_move

def play_game():
    board = chess.Board()
    while not board.is_game_over():
        print(board)
        if board.turn == chess.WHITE:
            move = hill_climbing(board, depth=3)
        else:
            move = input("Your move: ")
            move = chess.Move.from_uci(move)
        board.push(move)

    print("Game Over")
    print("Result:", board.result())

if __name__ == "__main__":
    play_game()