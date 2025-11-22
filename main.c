#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "connect4.h"


int main(){
    srand(time(NULL));
    
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
        else if(x==3){
            mediumBot(win,grid);
        }
        else if(x==4){
            hardBot(win, grid);
        }
        
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
