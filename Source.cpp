/*Minesweeper.cpp (Version 8 at this point)
*Alex Dolce
*30 November, 2020
*minesweeper game that player can choose difficulty
*/

#include <iostream>
#include <random>
#include <ctime>
using namespace std;
#include "FileIO.h"


#define max_bomb 100
#define max_side 30
constexpr auto max_move = 800; // 30*30-100;

int SIDE;
int BOMBS;

void clear()
{
	printf("\33[2J\33[1;1H");
}

bool isvalid(int row, int col)
{
	return (row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE);
}

bool isbomb(int row, int col, char board[][max_side])
{
	if (board[row][col] == '*')
		return (true);
	else
		return (false);
}

void make_move(int* x, int* y)
{
	while (true)
	{
		printf("\nEnter your move: [row] [column] -> ");
		scanf_s("%d %d", x, y);
		// Check values to make sure they're not larger than the board size.
		if ((*x < SIDE) && (*y < SIDE))
		{
			return;
		}
	}
}

void printboard(char myboard[][max_side])
{
	clear();
	printf("\n\n\t\t\t    ");

	for (int i = 0; i < SIDE; i++)
	{
		if (i > 9)
			printf("%d ", i / 10);
		else
			printf("  ");
	}

	printf("\n\t\t\t    ");

	for (int i = 0; i < SIDE; i++)
		printf("%d ", i % 10);

	printf("\n\n");

	for (int i = 0; i < SIDE; i++)
	{
		printf("\t\t\t    ");
		for (int j = 0; j < SIDE; j++) {
			printf("%c ", myboard[i][j]);
		}
		printf(" %2d", i);
		printf("\n");
	}
	return;
}

int countadjacent(int row, int col, int bombs[][2], char realboard[][max_side])
{
	int count = 0;

	if (isvalid(row - 1, col) == true)
	{
		if (isbomb(row - 1, col, realboard) == true)
			count++;
	}

	if (isvalid(row + 1, col) == true)
	{
		if (isbomb(row + 1, col, realboard) == true)
			count++;
	}

	if (isvalid(row, col + 1) == true)
	{
		if (isbomb(row, col + 1, realboard) == true)
			count++;
	}

	if (isvalid(row, col - 1) == true)
	{
		if (isbomb(row, col - 1, realboard) == true)
			count++;
	}

	if (isvalid(row - 1, col - 1) == true)
	{
		if (isbomb(row - 1, col - 1, realboard) == true)
			count++;
	}

	if (isvalid(row - 1, col + 1) == true)
	{
		if (isbomb(row - 1, col + 1, realboard) == true)
			count++;
	}

	if (isvalid(row + 1, col - 1) == true)
	{
		if (isbomb(row + 1, col - 1, realboard) == true)
			count++;
	}

	if (isvalid(row + 1, col + 1) == true)
	{
		if (isbomb(row + 1, col + 1, realboard) == true)
			count++;
	}

	return (count);

}

bool playbombsuntil(char myboard[][max_side], char realboard[][max_side], int bombs[][2], int row, int col, int* moves_left)
{
	if (myboard[row][col] != '-')
		return false;

	int i;
	if (realboard[row][col] == '*')
	{
		myboard[row][col] = '*';
		for (i = 0; i < BOMBS; i++)
			myboard[bombs[i][0]][bombs[i][1]] = '*';

		printboard(myboard);
		printf("\nYou lost!\n");
		return (true);
	}

	else
	{
		int count = countadjacent(row, col, bombs, realboard);
		(*moves_left)--;

		myboard[row][col] = count + '0';

		if (!count)
		{

			if (isvalid(row - 1, col) == true)
			{
				if (isbomb(row - 1, col, realboard) == false)
					playbombsuntil(myboard, realboard, bombs, row - 1, col, moves_left);
			}


			if (isvalid(row + 1, col) == true)
			{
				if (isbomb(row + 1, col, realboard) == false)
					playbombsuntil(myboard, realboard, bombs, row + 1, col, moves_left);
			}


			if (isvalid(row, col + 1) == true)
			{
				if (isbomb(row, col + 1, realboard) == false)
					playbombsuntil(myboard, realboard, bombs, row, col + 1, moves_left);
			}


			if (isvalid(row, col - 1) == true)
			{
				if (isbomb(row, col - 1, realboard) == false)
					playbombsuntil(myboard, realboard, bombs, row, col - 1, moves_left);
			}

			if (isvalid(row - 1, col + 1) == true)
			{
				if (isbomb(row - 1, col + 1, realboard) == false)
					playbombsuntil(myboard, realboard, bombs, row - 1, col + 1, moves_left);
			}


			if (isvalid(row - 1, col - 1) == true)
			{
				if (isbomb(row - 1, col - 1, realboard) == false)
					playbombsuntil(myboard, realboard, bombs, row - 1, col - 1, moves_left);
			}

			if (isvalid(row + 1, col + 1) == true)
			{
				if (isbomb(row + 1, col + 1, realboard) == false)
					playbombsuntil(myboard, realboard, bombs, row + 1, col + 1, moves_left);
			}

			if (isvalid(row + 1, col - 1) == true)
			{
				if (isbomb(row + 1, col - 1, realboard) == false)
					playbombsuntil(myboard, realboard, bombs, row + 1, col - 1, moves_left);
			}

		}
		return (false);
	}
}

void placebombs(int bombs[][2], char realboard[][max_side])
{
	bool mark[max_side * max_side];

	memset(mark, false, sizeof(mark));

	for (int i = 0; i > BOMBS;)
	{
		int random = rand() % (SIDE * SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		if (mark[random] == false) //add bomb if not present at position random
		{
			bombs[i][0] = x;
			bombs[i][1] = y;

			realboard[bombs[i][0]][bombs[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}
}


void initialise(char realboard[][max_side], char myboard[][max_side])
{
	srand(time_t(NULL)); //initalising random so that same config doesn't arise

	int i, j;
	for (i = 0; i < SIDE; i++)
		for (j = 0; j < SIDE; j++)
		{
			myboard[i][j] = realboard[i][j] = '-';
		}
	return;
}

void cheatbombs(char realboard[][max_side])
{
	printf("The bombs locations are-\n");
	printboard(realboard);
	return;
}

void replacebomb(int row, int col, char board[][max_side])
{
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] != '*')
			{
				board[i][j] = '*';
				board[row][col] = '-';
				return;
			}
		}

	}

}

void play()
{
	bool gameover = false;

	char realboard[max_side][max_side], myboard[max_side][max_side];

	int moves_left = SIDE * SIDE - BOMBS;
	int x, y;
	int bombs[max_bomb][2]; //stores (x,y) of all bombs

	initialise(realboard, myboard);

	placebombs(bombs, realboard);

	//if you want cheat and win 
	//cheatbombs(realboard);
	int currentmoveindex = 0;

	while (gameover == false)
	{
		printf("Current Status of Board : \n");
		printboard(myboard);
		make_move(&x, &y);

		//if first move is bomb
		if (currentmoveindex == 0)
		{
			if (isbomb(x, y, realboard) == true) //first attempt is a bomb
				replacebomb(x, y, realboard); //replace the bomb at that location
		}

		currentmoveindex++;

		gameover = playbombsuntil(myboard, realboard, bombs, x, y, &moves_left);

		if ((gameover == false) && (moves_left == 0))
		{
			printf("\nYou won !\n");
			gameover = true;
		}
	}


}


void choosedifficulty()
{
	clear();
	cout << "\n\t\t\t\t\t\t\t\tMINESWEEPER";
	cout << "\n\n\t\t\t\t\t\tCHOOSE DIFFICULTY LEVEL : ";
	cout << "\n\n\t\t\t\t\t\t0.BEGINNER\n\t\t\t\t\t\t1.INTERMMEDIATE\n\t\t\t\t\t\t2.ADVANCED";
	cout << "\n\n\t\t\t\t\t\tENTER CHOICE (0-2) : ";
	int choice;
	cin >> choice;
	if (choice == 0)
	{
		SIDE = 10;
		BOMBS = 25;
	}
	else
		if (choice == 1)
		{
			SIDE = 20;
			BOMBS = 50;
		}
		else
			if (choice == 2)
			{
				SIDE = 30;
				BOMBS = 100;
			}
			else
				exit(0);

}


int main()
{
	choosedifficulty();
	play();
	return 0;
}