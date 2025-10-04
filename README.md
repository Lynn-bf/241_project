# 241_project
Roua Nafeh , lynn Bou Francais, Nadia Bakri
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
