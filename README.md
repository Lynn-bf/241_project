# 241_project
Roua Nafeh , Lynn Bou Francis, Nadia Bakri
Connect 4:
- Two players take turns dropping checkers into a 6x7 grid
- Checkers fall into the lowest empty spot in a column ( player must choose a column
between 1 and 7 , if full pick a different one and we check from bottom to up)
- Connect 4 checkers in a row ( horizontal, vertical or diagonal)
- Player A uses red checkers and player B uses yellow checkers
- Game ends when a player wins or the board is full

1) fourCheckers : check if the player has four matching checkers in a row-
horizontally , vertically or diagonally
2) placeChecker: finds the lowest empty row in the chosen column and puts the
player’s checker there
3) displayGrid: shows the current state of the 6x7 board:
Red for player A
Yellow for player B
Empty spots
4) isFull : Checks if the board has no empty spots left, meaning the game ends in a
draw
5) main: initialize the grid with empty characters, loop until a winner is found or grid is
full, check if the column the user entered is correct if not keep on scanning, (do-
while) because we want to be excuted once , display the grid, ask players if they
want to replay

Multiplayer Function:
•	Manages turn-based gameplay between two human players
•	Alternates turns between Player A and Player B
•	Validates player input and updates game board
•	Checks for wins or draws after each move
•	Displays updated grid after every move
Time Complexity: O(1) per move

Easy Bot Function:
•	Basic AI opponent using random move selection
•	Human plays first, then bot responds
•	Randomly picks columns until finding valid placement
•	Checks for game end after each move
•	Displays updated board after bot's move
Time Complexity: O(1) per move

Medium Bot Function:
1- checks for bot’s winning moves in all directions
2- checks for human’s moves to block
3- uses directional scanning ( horizontal, vertical, diagonal) 
4- falls to random moves if no strategic opportunities 
time complexity: O(1) per move

Evaluate Board Function:
•	Scores board position for minimax algorithm
•	Awards points for bot advantages and center control
•	Penalizes human threats and positions
•	Analyzes all 4-cell sequences in 4 directions
•	Uses weighted scoring for different configurations
Time Complexity: O(1)

Minimax Function with Alpha-Beta Pruning:
•	Recursively explores game tree to specified depth (6)
•	Evaluates all possible move sequences for both players
•	Uses alpha-beta pruning to eliminate suboptimal branches
•	Returns optimal score for current board position
•	Alternates between maximizing (bot) and minimizing (human) turns
Time Complexity:
•	Theoretical: O(b^d) where b=7 (branching), d=6 (depth) = O(7^6)
•	With pruning: O(b^(d/2)) ≈ O(7^3) = O(343) average case

Hard Bot Function:
•	First checks for immediate winning moves
•	Then checks for urgent blocking moves against human
•	Falls back to minimax search if no immediate threats
•	early termination when immediate threats/opportunities found
Time Complexity:
•	Best case: O(1) - immediate win/block found
•	Worst case: O(7^d) where d=6 - full minimax search


