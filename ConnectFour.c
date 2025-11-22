#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "connect4.h"
#define NEG_INF -100000
#define POS_INF 100000
#define max(a, b) ((a)>(b) ? (a) : (b))
#define min(a, b) ((a)<(b) ? (a) : (b))

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
                int playCol = findPlayableCell(row, col, grid, ' ', deltaRow, deltaCol);
                if (playCol != -1)
                    return playCol+1;
            }

            // Check for human blocking move
            if (humanCount == 3 && emptyCount == 1) {
                int blockCol = findPlayableCell(row, col, grid, ' ', deltaRow, deltaCol);
                if (blockCol != -1)
                    return blockCol+1;
            }
        }
    }
  return -1; // no move found
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
    *win = winner;
}

int evaluateBoard(char grid[6][7]){
    int score = 0;
    int directions[4][2] = {
        {0, 1}, // horizontally
        {1, 0}, //vertically
        {1, 1}, // diagonal right 
        {1, -1} //diagonal left
    };

    for(int row=0; row<6; row++){
        if(grid[row][3]=='B') score+=5;
        if(grid[row][3]=='A') score-=5;
    }
    for(int d = 0; d<4; d++){ //loop through all directions
        int deltaRow = directions[d][0];
        int deltaCol = directions[d][1];
        for (int row = 0; row <6; row++) {   
                
            for (int col = 0; col <7; col++) {   

                if(row+3*deltaRow<0 || row+3*deltaRow>=6 || col+3*deltaCol<0 || col+3*deltaCol>=7){
                    continue;
                }
                char c1 = grid[row][col];
                char c2 = grid[row+1*deltaRow][col+deltaCol*1];
                char c3 = grid[row+2*deltaRow][col+deltaCol*2];
                char c4 = grid[row+3*deltaRow][col+deltaCol*3];

                int humanCount = (c1=='A') + (c2=='A') + (c3=='A') + (c4=='A');
                int botCount = (c1=='B') + (c2=='B') + (c3=='B') + (c4=='B');
                int emptyCount = (c1==' ') + (c2==' ') + (c3==' ') + (c4==' ');


                if(botCount > 0 && humanCount > 0) continue;
                
                if(botCount==3 && emptyCount==1) score+=500;
                if(botCount==2 && emptyCount==2) score+=10;
                if(botCount==1 && emptyCount==3) score+=1;

                if(humanCount==3 && emptyCount==1) score-=500;
                if(humanCount==2 && emptyCount==2) score-=10;
                if(humanCount==1 && emptyCount==3) score-=1;
            }
        }
    }
    return score;
}

int minimax(char grid[6][7], int depth, int alpha, int beta, bool isMaximizing){
    //first step: check if this is the final solution
    char winner = fourCheckers(grid); //bot has already won
    if (winner=='A') return -10000; //human has already won
    else if(winner=='B') return 10000;
    else{ //no winner, 2 cases
        if(isGridFull(grid)) return 0; //case 1: draw
        else if(depth==0){ //case 2: can't go deeper
            return evaluateBoard(grid); // 
        }
    }

    //step 2: not terminal
    if(isMaximizing){// Case 1: bot's turn 'B'
        int bestScore = NEG_INF;
        for(int col=0; col<=6; col++){
            char gridcpy[6][7];
            memcpy(gridcpy, grid, sizeof(char)*6*7); //copying the grid
            int placed = placeChecker(gridcpy, col+1, 'B'); //placing 'B' in a different colum in each copy
            if(placed==1){ //placement is successful
                int score = minimax(gridcpy, depth-1, alpha, beta, false); //calling minimax recursively but for human's turn
                bestScore = max(bestScore, score); //update bestScore
                alpha = max(alpha, bestScore); //update alpha
                if(beta<=alpha) break; //prune remaining columns
            }
        }
        return bestScore;
    } 

    else{// Case 2: human's turn 'A'
        int bestScore = POS_INF;
        for(int col=0; col<=6; col++){
            char gridcpy[6][7];
            memcpy(gridcpy, grid, sizeof(char)*6*7);
            int placed = placeChecker(gridcpy, col+1, 'A');
            if(placed==1){
                int score = minimax(gridcpy, depth-1, alpha, beta, true);
                bestScore = min(bestScore, score);
                beta = min(beta, bestScore);
                if(beta<=alpha) break;
            }
        }
        return bestScore;
    }
}

void hardBot(char *win, char grid[6][7]){
    char winner = *win;
    
    while(winner==' ' && !isGridFull(grid)){
        winner = fourCheckers(grid);
        if (winner != ' ') break;

        printf("\nChoose a column (1-7): \n");
        fflush(stdout);
        inputWarning(grid, 'A');
        displayGrid(grid);

        winner = fourCheckers(grid);
        if (winner != ' ') break;

        int bestScore = NEG_INF;
        int bestCol = -1;

        for(int i=0; i<=6; i++){
            char gridcpy[6][7];
            memcpy(gridcpy, grid, sizeof(gridcpy));
            int placed = placeChecker(gridcpy, i+1, 'B');
            if(placed==1){
                int score = minimax(gridcpy, 6, NEG_INF, POS_INF, false);
                if(score>bestScore){
                    bestScore = score;
                    bestCol = i+1; //placeChecker expects columns between 1 and 7
                }
            }
        }

        if(bestCol==-1) return;

        placeChecker(grid, bestCol, 'B');
        printf("\nBot (B) played:\n");
        displayGrid(grid);
        winner = fourCheckers(grid);
    }

    *win = winner;
}



