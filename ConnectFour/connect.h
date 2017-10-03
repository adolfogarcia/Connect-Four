#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

typedef enum
{
	FALSE, TRUE
}Bool;

typedef struct location
{
	int column;
	int row;
}Location;


typedef struct cell
{
	char chip;
	char color;
	Bool isOccupied;
	Location place;
}Cell;



void run_app(Cell gameboard[][7]);
void welcome_screen(void);
void init_board(Cell gameboard[][7]);
void print_board(Cell board[][7], int rows, int cols);
int play(int player, Cell board[][7], char letter);
int check_four_in_a_row(Cell board[][7], char letter);
int check_win_vertical_horizontal(Cell board[][7], int row, int column, int key, char letter);
int check_win_diagonal(Cell board[][7], int row, int column, int key, char letter);
void print_board_update(Cell board[][7], int rows, int cols, char letter, int column, int final_row);