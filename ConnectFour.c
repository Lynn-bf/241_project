#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

int main(){
    printf("Welcome to Connect Four!");

    //printing the modes
    printf("\nModes:");
    printf("\n\tMultiplayer:1\n\tEasy:2\n\tMedium:3\n\tHard:4\n");

    //user chooses the mode
    printf("Enter your choice: ");
    fflush(stdout);
    int x;
    do{
        
        if (scanf("%d",&x)!=1){
            printf("Invalid input! Please enter a number.\n");

            // Clear the invalid input from the buffer
            while (getchar() != '\n'); // discard characters until newline
                continue; // skip the rest of the loop iteration 
            
        }
        if (x<1 || x>4){
            printf("Please enter a valid number!\n");
        }
        else{
            break;
        }
    }while(true);

    bool again = false;
    int pointsA = 0, pointsB = 0;

    do{
        //initialize the grid with empty characters
        char grid[6][7];
        for(int i=0; i<6; i++){
            for(int j=0; j<7; j++){
                grid[i][j] = ' ';
            }
        }

        bool A = true; //boolean to determine whose turn is it
        char winner = ' '; 

        char *win=&winner;  

        if(x==1){
            Multiplayer(win,grid,A);
        }

        else if(x==2){
            easyBot(win,grid);
        }
        // other modes to be implemented in later sprints

        if(winner!=' '){
            printf("\n\033[1;32mPlayer %c wins! \033[0m\n", winner); //display winner
            if(winner=='A') pointsA++;
            if(winner=='B') pointsB++;
        }
        else{ //the grid is full
            printf("Game over - Nobody wins.\n");
        }

        //asking the players if they want to replay
        printf("Do you want to play again? [y, n]\n");
        char replay;
        scanf(" %c", &replay);
        again = (replay=='y' || replay=='Y'); //to decide if we reset the game

    } while(again);

    printf("\nScores:\n\033[1;93mA: %d \033[0m- \033[1;31mB: %d \033[0m\n", pointsA, pointsB);
}

