#ifndef CONNECT4_H
#define CONNECT4_H

#include <stdbool.h>

char fourCheckers(char grid[6][7]);
bool isGridFull(char grid[6][7]);
int placeChecker(char grid[6][7], int col, char player);
void displayGrid(char arr[6][7]);
void inputWarning(char grid[6][7], char player);
int checkForMedium(char grid[6][7], int deltaRow, int deltaCol);
int findPlayableCell(int startRow, int startCol, char grid[6][7], char target, int deltaRow, int deltaCol);
void Multiplayer(char* win, char grid[6][7], bool A);
void easyBot(char* win, char grid[6][7]);
void mediumBot(char *win,char grid[6][7]);

#endif
