import copy
import math
import tkinter as tk


# Define the BoardGame class to encapsulate the game logic
class BoardGame:
    def __init__(self):
        # Initialize the game board with an 8x8 grid filled with '.'
        self.game_board = [['.' for _ in range(8)] for _ in range(8)]
        # Set up the initial four pieces in the center
        self.game_board[3][3] = 'W'
        self.game_board[3][4] = 'B'
        self.game_board[4][3] = 'B'
        self.game_board[4][4] = 'W'
        # Set the active player to 'B' (Black)
        self.active_player = 'B'
        # Initialize previous_move to None; it will store the last move made
        self.previous_move = None

    def legal_move(self, row, col):
        if not (0 <= row < 8 and 0 <= col < 8) or self.game_board[row][col] != '.':
            return False

        # Define all eight possible directions from a cell
        directions = [(x, y) for x in [-1, 0, 1] for y in [-1, 0, 1] if not (x == 0 and y == 0)]

        # Check each direction for a legal move
        for x, y in directions:
            r, c = row + x, col + y
            if not (0 <= r < 8 and 0 <= c < 8) or self.game_board[r][c] == self.active_player:
                continue

            # Move in the direction until a rival piece is found
            while 0 <= r < 8 and 0 <= c < 8 and self.game_board[r][c] == self.rival():
                r += x
                c += y

            if not (0 <= r < 8 and 0 <= c < 8) or self.game_board[r][c] == '.':
                continue

            # If the active player's piece is found, the move is legal
            if self.game_board[r][c] == self.active_player:
                return True

        # If no legal moves are found, return False
        return False

    def rival(self):
        return 'W' if self.active_player == 'B' else 'B'

    def place_piece(self, row, col):
        # If the move is legal, place the piece
        if self.legal_move(row, col):
            self.game_board[row][col] = self.active_player
            # Update the previous_move with the current move
            self.previous_move = (row, col)

            # Flip the rival's pieces in all directions
            for x in [-1, 0, 1]:
                for y in [-1, 0, 1]:
                    if x == 0 and y == 0:
                        continue
                    r, c = row + x, col + y
                    # Flip the pieces until the active player's piece is found
                    while 0 <= r < 8 and 0 <= c < 8 and self.game_board[r][c] == self.rival():
                        r += x
                        c += y
                        # When the active player's piece is found, flip the rival's pieces
                        if 0 <= r < 8 and 0 <= c < 8 and self.game_board[r][c] == self.active_player:
                            r, c = row + x, col + y
                            while self.game_board[r][c] == self.rival():
                                self.game_board[r][c] = self.active_player
                                r += x
                                c += y
                            break
            # Switch the active player to the rival
            self.active_player = self.rival()
        else:
            # If the move is not legal, print an error message
            print("Move not allowed")

    # Define a method to count the score for each player
    def score_count(self):
        black_score = sum(row.count('B') for row in self.game_board)
        white_score = sum(row.count('W') for row in self.game_board)
        return black_score, white_score

    # check if the game is over
    def end_of_game(self):
        # Return True if no legal moves are available for either player
        return not any(self.legal_move(row, col) for row in range(8) for col in range(8))

    # the winner of the game
    def game_winner(self):
        black_score, white_score = self.score_count()
        if black_score > white_score:
            return 'Black wins'
        elif black_score < white_score:
            return 'White wins'
        else:
            return 'Draw'


# the BoardGameUI
class BoardGameUI:
    def __init__(self, master, game_manager):
        # Set up the main window and game manager
        self.master = master
        self.game_manager = game_manager
        # Create a canvas for displaying the game board
        self.display_canvas = tk.Canvas(self.master, width=400, height=400)
        self.display_canvas.pack(side=tk.LEFT)
        self.display_canvas.bind('<Button-1>', self.handle_click)

        self.stats_frame = tk.Frame(self.master)
        self.stats_frame.pack(side=tk.RIGHT, padx=10)

        self.score_label = tk.Label(self.stats_frame, text="Black: 2\nWhite: 2")
        self.score_label.pack()

        self.result_label = tk.Label(self.stats_frame, text="")
        self.result_label.pack()

        # render the game board
        self.render_board()

    # render the game board on the canvas
    def render_board(self):
        # Clear the canvas
        self.display_canvas.delete('all')
        # Get the game board from the GameManager
        game_board = self.game_manager.game.game_board
        # Draw the game board grid and pieces
        for i in range(8):
            for j in range(8):
                # Calculate the coordinates for each cell
                x0, y0 = j * 50, i * 50
                x1, y1 = x0 + 50, y0 + 50
                # Draw the cell and fill it based on the move is legal
                self.display_canvas.create_rectangle(x0, y0, x1, y1, fill='green' if game_board[i][
                                                                                         j] == '.' and self.game_manager.game.legal_move(
                    i, j) else 'white', outline='black')
                # Draw the pieces on the board
                if game_board[i][j] == 'B':
                    self.display_canvas.create_oval(x0 + 5, y0 + 5, x1 - 5, y1 - 5, fill='black')
                elif game_board[i][j] == 'W':
                    self.display_canvas.create_oval(x0 + 5, y0 + 5, x1 - 5, y1 - 5, fill='white')

        # Highlight the previous move
        if self.game_manager.game.previous_move:
            row, col = self.game_manager.game.previous_move
            # Calculate the coordinates for the highlight
            x0, y0 = col * 50 + 20, row * 50 + 20
            x1, y1 = x0 + 10, y0 + 10
            # Draw the highlight
            self.display_canvas.create_oval(x0, y0, x1, y1, fill='red')

    def handle_click(self, event):
        # Handle user clicks on the board
        col = event.x // 50
        row = event.y // 50
        self.game_manager.play_human_vs_ai_move(row, col)  # Use game_manager instead of controller
        self.render_board()
        self.update_info()

    def update_info(self):
        # Update the game info displayed on the UI
        black_count, white_count = self.game_manager.game.score_count()
        self.score_label.config(text=f"Black: {black_count}\nWhite: {white_count}")

        if self.game_manager.game.end_of_game():  # Corrected method name
            winner = self.game_manager.game.game_winner()
            if winner == 'Draw':
                self.result_label.config(text="It's a Draw!")
            else:
                self.result_label.config(text=f"The winner is {winner}!")

        self.master.update_idletasks()


class DifficultySelectorUI:
    def __init__(self):
        # Initialize the difficulty selector UI
        self.root = tk.Tk()
        self.root.title("Select Difficulty")
        self.difficulty = None

        label = tk.Label(self.root, text="Select Difficulty:")
        label.pack()

        self.var = tk.StringVar(self.root)

        easy_button = tk.Radiobutton(self.root, text="Easy", variable=self.var, value="easy")
        easy_button.pack()

        medium_button = tk.Radiobutton(self.root, text="Medium", variable=self.var, value="medium")
        medium_button.pack()

        hard_button = tk.Radiobutton(self.root, text="Hard", variable=self.var, value="hard")
        hard_button.pack()

        confirm_button = tk.Button(self.root, text="Confirm", command=self.confirm)
        confirm_button.pack()

    def confirm(self):
        # Confirm the selected difficulty
        self.difficulty = self.var.get()
        self.root.destroy()


class GameManager:
    def __init__(self):
        # Initialize the game manager
        self.difficulty_selector_ui = DifficultySelectorUI()
        self.difficulty_selector_ui.root.mainloop()
        self.difficulty = self.difficulty_selector_ui.difficulty
        self.game = BoardGame()
        self.previous_move = self.game.previous_move  # Initialize previous_move
        self.ui = BoardGameUI(tk.Tk(), self)

    def play_human_vs_ai_move(self, row, col):
        # Play a move in human vs AI mode
        if self.game.active_player == 'B':
            self.game.place_piece(row, col)
            if not any(self.game.legal_move(row, col) for row in range(8) for col in range(8)):
                self.switch_turn()
                return
            new_state = self.alpha_beta_search(
                1 if self.difficulty == 'easy' else 3 if self.difficulty == 'medium' else 5, 'W')
            if new_state:
                self.game = new_state
        else:
            self.game.place_piece(row, col)
            if not any(self.game.legal_move(row, col) for row in range(8) for col in range(8)):
                self.switch_turn()
                return
        self.previous_move = self.game.previous_move  # Update previous_move
        self.ui.render_board()

    def switch_turn(self):
        # Switch the turn between players
        self.game.active_player = self.game.rival()

    def alpha_beta_search(self, depth, player):
        # Perform Alpha-Beta pruning search to find the best move for the AI
        def max_value(state, alpha, beta, depth):
            if depth == 0 or state.end_of_game():
                return state, self.evaluate_board(player)
            max_state = None
            v = -math.inf
            for row in range(8):
                for col in range(8):
                    if state.legal_move(row, col):
                        new_state = copy.deepcopy(state)
                        new_state.place_piece(row, col)
                        _, min_val = min_value(new_state, alpha, beta, depth - 1)
                        if min_val > v:
                            max_state = new_state
                            v = min_val
                        alpha = max(alpha, v)
                        if alpha >= beta:
                            break
            return max_state, v

        def min_value(state, alpha, beta, depth):
            if depth == 0 or state.end_of_game():
                return state, self.evaluate_board(player)
            min_state = None
            v = math.inf
            for row in range(8):
                for col in range(8):
                    if state.legal_move(row, col):
                        new_state = copy.deepcopy(state)
                        new_state.place_piece(row, col)
                        _, max_val = max_value(new_state, alpha, beta, depth - 1)
                        if max_val < v:
                            min_state = new_state
                            v = max_val
                        beta = min(beta, v)
                        if alpha >= beta:
                            break
            return min_state, v

        return max_value(self.game, -math.inf, math.inf, depth)[0]

    def evaluate_board(self, player):
        # Evaluate the board state for the AI player
        black_count, white_count = self.game.score_count()
        if player == 'B':
            return black_count - white_count
        else:
            return white_count - black_count


# Example usage:
game_manager = GameManager()
tk.mainloop()
