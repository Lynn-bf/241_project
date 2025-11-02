#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "connect4.h"

char fourCheckers(char grid[6][7]){
    
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            char c = grid[i][j];

            if(c==' ') continue;

            //check horizontally
            if(j<=3 && c==grid[i][j+1] && c==grid[i][j+2] && c==grid[i][j+3]){
                return c; //return winner
            }

            //check vertically
            if(i<=2 && c==grid[i+1][j] && c==grid[i+2][j] && c==grid[i+3][j]){
                return c;
            }

            //check diagonally (to the right)
            if(i<=2 && j<=3 && c==grid[i+1][j+1] && c==grid[i+2][j+2] && c==grid[i+3][j+3]){
                return c;
            }

            //check diagonally (to the left)
            if(i<=2 && j>=3 && c==grid[i+1][j-1] && c==grid[i+2][j-2] && c==grid[i+3][j-3]){
                return c;
            }
        }
    }

    return ' '; //case where no fourCheckers is found
}

bool isGridFull(char grid[6][7]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (grid[i][j] == ' ') {
                return false; 
            }
        }
    }
    return true; 
}

int placeChecker(char grid[6][7],int col, char player){
    if(col <= 0 || col >7){
        return -1; //invalid index
    }
    for(int i=6-1; i >=0; i--){
        if(grid [i][col-1]==' '){
           grid[i][col-1]= player;
           return 1; //success
        }
    }
    return 0; //full
}

void displayGrid(char arr[6][7]){
    for(int i=0;i<6;i++){
        for(int j=0;j<7;j++){
            char a=arr[i][j];
            //prints . if empty
            if(a==' ')
                printf(". ");
            //prints A in yellow
            else if(a=='A')
                    printf("\033[1;93m%c \033[0m",a);
            //prints B in red
            else
                printf("\033[1;31m%c \033[0m",a);
        }
        //goes to next line
        printf("\n");
    }
        //print the numbers of the columns
        for (int i=1;i<8;i++)
                printf("%d ",i);
        printf("\n");
}

void inputWarning(char grid[6][7] , char player){
        int placement;
        int col;
        //we keep scanning until the user enters a valid column
        //do-while -> because we want it to be executed at leat once
        do{
            if (scanf("%d", &col) != 1) {
                printf("Invalid input! Please enter a number.\n");
 
            
            // Clear the invalid input from the buffer
            while (getchar() != '\n'); // discard characters until newline
                continue; // skip the rest of the loop iteration 
            }
            
            placement = placeChecker(grid, col, player);
            if(placement==-1){
                printf("Invalid column! Enter again\n");
            }
            else if(placement==0){
                printf("Full column! Enter again\n");
            }
        }while(placement!=1);
     
}

int checkForMedium(char grid[6][7], int deltaRow, int deltaCol) {
    //horizontal: dr=1, dc=0
    //vertical: dr=0, dc=1
    //diagonal right: dr=1, dc=1
    //diagonal left: dr=1, dc=-1
    // Loop over all starting points for right diagonals of length 4
    for (int row = 0; row <=6; row++) {       
        for (int col = 0; col <7; col++) {   
            
            if(row+3*deltaRow<0 || row+3*deltaRow>=6 || col+3*deltaCol<0 || col+3*deltaCol>=7){
                continue;
            }
            char c1 = grid[row][col];
            char c2 = grid[row+1*deltaRow][col+deltaCol*1];
            char c3 = grid[row+2*deltaRow][col+deltaCol*2];
            char c4 = grid[row+3*deltaRow][col+deltaCol*3];

            int botCount = (c1=='A') + (c2=='A') + (c3=='A') + (c4=='A');
            int humanCount = (c1=='B') + (c2=='B') + (c3=='B') + (c4=='B');
            int emptyCount = (c1==' ') + (c2==' ') + (c3==' ') + (c4==' ');

            // Check for bot winning move
            if (botCount == 3 && emptyCount == 1) {
                int playCol = findPlayableDiagonalCell(row, col, grid, ' ', -1);
                if (playCol != -1)
                    return playCol;
            }

            // Check for human blocking move
            if (humanCount == 3 && emptyCount == 1) {
                int blockCol = findPlayableDiagonalCell(row, col, grid, ' ', -1);
                if (blockCol != -1)
                    return blockCol;
            }
        }
    }
  return -1; // no move found
}

// Helper function to find which cell is empty and playable
int findPlayableCell(int startRow, int startCol, char grid[6][7], char target, int deltaRow, int deltaCol) {
    //
    for (int i = 0; i < 4; i++) {
        int row = startRow + deltaRow*i;
        int col = startCol + deltaCol*i;
        if (grid[row][col] == target) {
            // Check if it's the lowest empty cell in its column
            if (row == 5 || grid[row+1][col] != ' ')
                return col;
        }
    }
    return -1;  
}

void Multiplayer(char* win, char grid[6][7], bool A){
    char winner= *win;
    //looping until a winner is found or grid is full

    while(winner==' ' && !isGridFull(grid)){
        char player = A ? 'A' : 'B'; 
        printf("\nPlayer %c, choose a column (1-7):\n", player);
        fflush(stdout);
        inputWarning(grid,player);
        displayGrid(grid);
        winner = fourCheckers(grid);
        A = !A;// switch between the players
    }
    *win=winner;
}

void easyBot(char* win, char grid[6][7]) {
    char winner = *win;

    while (winner == ' ' && !isGridFull(grid)) {
        printf("\nChoose a column (1–7): \n");
        fflush(stdout);
        inputWarning(grid, 'A');
        displayGrid(grid); // show grid right after player's move

        winner = fourCheckers(grid);
        if (winner != ' ' || isGridFull(grid)) break;

        //  Bot's chooses a random column
        srand(time(NULL));
        while (true) {
            int col = rand() % 7 + 1;
            int check = placeChecker(grid, col, 'B');
            if (check == 1) break;
        }

        printf("\nBot (B) played:\n");
        displayGrid(grid);

        winner = fourCheckers(grid);
    }

    *win = winner;
}

void mediumBot(char *win,char grid[6][7]){
    char winner = *win;

    while (winner == ' ' && !isGridFull(grid)) {
        printf("\nChoose a column (1–7): \n");
        fflush(stdout);
        inputWarning(grid, 'A');
        displayGrid(grid); // show grid right after player's move


        if (winner != ' ' || isGridFull(grid)) break;

        int directions[4][2] = {
            {1, 0},   // horizontal
            {0, 1},   // vertical
            {1, 1},   // diagonal right
            {1, -1}   // diagonal left
        };
        
        int move = -1;
        for (int i = 0; i < 4; i++) {
            int dr = directions[i][0];
            int dc = directions[i][1];
            move = checkForMedium(grid, dr, dc);
            if (move != -1) {
                placeChecker(grid, move, 'B');
                break;
            }
        }
        
        if (move == -1) {
            // place randomly
            while (true) {
                int col = rand() % 7 + 1;
                int check = placeChecker(grid, col, 'B');
                if (check == 1) break;
            }
        }

        printf("\nBot (B) played:\n");
        displayGrid(grid);
        winner = fourCheckers(grid);
    }
}









