#include "connect.h"

void run_app(Cell gameboard[][7])
{
	int victor;
	welcome_screen();
	init_board(gameboard);
//	print_board(gameboard, 6, 7);

	system("cls");
	
	do {
		system("cls");
		print_board(gameboard, 6, 7);	
		victor = play(1, gameboard, 'X');
		if (victor != 0)
			break;
		system("cls");
		print_board(gameboard, 6, 7);
		victor = play(2, gameboard, 'O');
	} while (victor == 0);
	//putchar('\n');
	system("cls");
	print_board(gameboard, 6, 7);
	printf("Congratulations, Player %d, you are the WINNER!\n", victor);
}

void welcome_screen(void)
{
	int end = 0, option = 0, press = 0;
	
	while (!_kbhit())
	{
		printf("\n");
		printf("                                 Welcome to CONNECT FOUR!\n");
		printf("                               Press any buttom to continue:\n");
		printf("\n\n");
		_sleep(800);
		system("cls");
		_sleep(400);
	}
	do {
		do
		{
			printf("1. LEARN TO PLAY\n");
			printf("2. LET'S START\n");
			printf("3. GET ME OUT OF HERE\n");
			scanf("%d", &option);
			system("cls");
		} while ((option < 1) || (option > 3));

		switch (option)
		{
		case 1: // print_game_rules ()
			//print_rules();
			printf("blah blah rules\n");
			printf("Press any key to return to the main menu. \n");
			while (!_kbhit())
			{
			}
			system("cls");
			break;
		case 2: // play_craps ()
			end = 1;
		//	printf("play game\n");
			break;
		case 3: // exit ()
			printf("See ya!\n");
			end = 1;
			break;
		default: // catch all would execute if the other cases are not matched
			break;
		}
	} while (end != 1);
}

//Initiates the game board by filling arrays with 'o' to simulate empty slots
void init_board(Cell gameboard[][7])
{
	
	int row_index = 0, col_index = 0;
	for (row_index = 0; row_index < 6; ++row_index) // controls which row
	{
		for (col_index = 0; col_index < 7; ++col_index) // controls which column
		{
			gameboard[row_index][col_index].color = '\0';
			gameboard[row_index][col_index].isOccupied = FALSE;
			gameboard[row_index][col_index].place.row = row_index;
			gameboard[row_index][col_index].place.column = col_index;
		}
	}
}

//prints game board
void print_board(Cell board[][7], int rows, int cols)
{
	int i = 0, j = 0;
	int row_index = 0, col_index = 0;

	printf("   1    2    3    4    5    6    7\n");
	for (i = 0; i<6; i++) 
	{
		printf("+");
		for (j = 0; j < 7; j++)
		{
			//_sleep(65);
			printf("----+");
		}

		printf("\n");
		printf("|");
		
		for (j = 0; j < 7; j++)
		{
			printf(" %c", board[i][j].chip);  //prints the chip in that slot
			printf("  |");
		}
		printf("\n");
	}

	printf("+");
	for (j = 0; j<7; j++)
		printf("----+");
	printf("\n");
}

int play(int player, Cell board[][7], char letter)
{
	int col = 0, key = 0;
	int row_index = 0, col_index = 0;
	
	printf("Alright Player %d, it is your turn!\n", player);
	do
	{
	do {
		printf("Choose the column in which you want to drop your disc.\n");
		scanf("%d", &col);
	} while ((col < 0) || (col > 7));
	col -= 1;

	if (board[0][col].isOccupied == TRUE)
	{
		printf("Whoa whoa whoa, back it up a little. This column\n");
		printf("is already full. Why not choose another one?\n");
	}
	else
		key = 1;
	} while (key == 0);
	while ((board[row_index][col].isOccupied == FALSE) && (row_index <6))
	{
		row_index++;
	}

	row_index--;

	board[row_index][col].isOccupied = TRUE;
	board[row_index][col].place.column = col;
	board[row_index][col].place.row = row_index;

	//printf("Your disc will be placed at %d, %d\n", col + 1, row_index + 1);
	if (player == 1)
	{
		//print_board_update(board, 6, 7, 'X', col, row_index);
		board[row_index][col].chip = 'X';
		//print_board(board, 6, 7);
		if (check_four_in_a_row(board, 'X') > 0)
			return player;
		else
			return 0;
	}
	else
	{
		//print_board_update(board, 6, 7, 'O', col, row_index);
		board[row_index][col].chip = 'O';
		//print_board(board, 6, 7);
		if (check_four_in_a_row(board, 'O') > 0)
			return player;
		else
			return 0;
	}
	//print_board(board, 6, 7);
	//if (check_four_in_a_row(board, letter) > 0)
	//	return player;
	//else
	//	return 0;
}

int check_four_in_a_row(Cell board[][7], char letter)
{
	int row_index = 0, col_index = 0, win = 0;
	for (row_index = 0; row_index < 6; ++row_index) // controls which row
	{
		for (col_index = 0; col_index < 7; ++col_index) // controls which column
		{
			if (board[row_index][col_index].chip == letter)
			{
				win += check_win_vertical_horizontal(board, row_index, col_index, 1, letter);
				//win += check_win_vertical_horizontal(board, row_index, col_index, 2, letter);
				//win += check_win_vertical_horizontal(board, row_index, col_index, 3, letter);
				win += check_win_vertical_horizontal(board, row_index, col_index, 4, letter);
				win += check_win_diagonal(board, row_index, col_index, 1, letter);
				win += check_win_diagonal(board, row_index, col_index, 2, letter);
				//win += check_win_diagonal(board, row_index, col_index, 3, letter);
				//win += check_win_diagonal(board, row_index, col_index, 4, letter);
			}
		}
	}
	if (win >= 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_win_vertical_horizontal(Cell board[][7], int row, int column, int key, char letter)
{
	int i = 0, win = 0;

	if (key == 1) // CHECKS UP
	{
		while (board[row][column].chip == letter) // checks vertical up win
		{
			row++;
			win++;
		}
		if (win == 4)
			return 1;
		else
			return 0;
	}
	//else if (key == 2)//CHECKS DOWN
	//{
	//	while (board[row][column].chip == letter) // checks vertical up win
	//	{
	//		row--;
	//		win++;
	//	}
	//	if (win == 4)
	//		return 1;
	//	else
	//		return 0;
	//}
	//else if (key == 3)//CHECKS left
	//{
	//	while (board[row][column].chip == letter) // checks vertical up win

	//	{
	//		column--;
	//		win++;
	//	}
	//	if (win == 4)
	//		return 1;
	//	else
	//		return 0;
	//}
	else if (key == 4)//CHECKS right
	{
		while (board[row][column].chip == letter) // checks vertical up win
		{
			column++;
			win++;
		}
		if (win == 4)
			return 1;
		else
			return 0;
	}
}

int check_win_diagonal(Cell board[][7], int row, int column, int key, char letter)
{
	int i = 0, count = 0, win = 0;

	if (key == 1) // CHECKS SE
	{
		while (board[row][column].chip == letter) // checks vertical up win
		{
			row++;
			column++;
			win++;
		}
		if (win == 4)
			return 1;
		else
			return 0;
	}
	else if (key == 2) // CHECKS SW
	{
		while (board[row][column].chip == letter) // checks vertical up win
		{
			row++;
			column--;
			win++;
		}
		if (win == 4)
			return 1;
		else
			return 0;
	}
	//else if (key == 3) // CHECKS NE
	//{
	//	while (board[row][column].chip == letter) // checks vertical up win
	//	{
	//		row--;
	//		column++;
	//		win++;
	//	}
	//	if (win == 4)
	//		return 1;
	//	else
	//		return 0;
	//}
	//else if (key == 4) // CHECKS NW
	//{
	//	while (board[row][column].chip != '\0') // checks vertical up win
	//	{
	//		row--;
	//		column--;
	//		win++;
	//	}
	//	if (win == 4)
	//		return 1;
	//	else
	//		return 0;
	//}
}

//void print_board_update(Cell board[][7], int rows, int cols, char letter, int column, int final_row)
//{
//	int i = 0, j = 0;
//	int row_index = 0, col_index = 0;
//
//	printf("   1    2    3    4    5    6    7\n");
//	for (i = 0; i<6; i++)
//	{
//		printf("+");
//		for (j = 0; j < 7; j++)
//		{
//			//_sleep(65);
//			printf("----+");
//		}
//
//		printf("\n");
//		printf("|");
//
//		for (j = 0; j < 7; j++)
//		{
//			if ((j == column) && (i <= final_row))
//			{
//				printf("%c", letter);
//				printf("\r");
//				_sleep(120);
//				putchar('\n');
//			}
//			printf(" %c", board[i][j].chip);  //prints the chip in that slot
//			printf(" |");
//		}
//		printf("\n");
//	}
//
//	printf("+");
//	for (j = 0; j<7; j++)
//		printf("----+");
//	printf("\n");
//
//	/*for (i = 0; i < final_row; i++)
//	{
//	for (j = 0; j < column; j++)
//	{
//		printf("     ");
//	}
//	
//		printf("%c", letter);
//		printf("\r");
//		_sleep(120);
//		putchar('\n');
//	}*/
//	
//
//}