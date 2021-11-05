// Jack Hansen
// Maze Traversal
// Nov 2, 2021

#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>

#define SIZE 12

// Translations right, down, up, and left, respectively
const int directions[4] = {1, SIZE, -SIZE, -1};


int mazeTraverse(char maze[SIZE][SIZE], int current, int start, int prev);
void display(char maze[SIZE][SIZE], int current);
void clearScreenAndDelay();


int main()
{
	char maze[SIZE][SIZE] = {
		{'#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#','.','.','.','#','.','.','.','.','.','.','#'},
		{'.','.','#','.','#','.','#','#','#','#','.','#'},
		{'#','#','#','.','#','.','.','.','.','#','.','#'},
		{'#','.','.','.','.','#','#','#','.','#','.','.'},
		{'#','#','#','#','.','#','.','#','.','#','.','#'},
		{'#','.','.','#','.','#','.','#','.','#','.','#'},
		{'#','#','.','#','.','#','.','#','.','#','.','#'},
		{'#','.','.','.','.','.','.','.','.','#','.','#'},
		{'#','#','#','#','#','#','.','#','#','#','.','#'},
		{'#','.','.','.','.','.','.','#','.','.','.','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#'}
	};
	// starting grid position
	const int startX = 2;
	const int startY = 0;
	const int startPos = startX * 12 + startY;

	// Clears screen to make fresh start
	printf("\e[1;1H\e[2J");

	
	mazeTraverse(maze,startPos,startPos,0);

	return 0;
}

int mazeTraverse(char maze[SIZE][SIZE], int current, int start, int prev)
{
	// displays the current position
	display(maze, current);

	clearScreenAndDelay();


	// Checks if on right edge
	if (current % SIZE == SIZE-1) return 1;
	// Checks if on bottom edge
	if (current / SIZE == SIZE-1) return 1;
	// Checks if on top edge
	if (current / SIZE == 0) return 1;
	// Checks if on left edge (and not where started)
	if (current % SIZE == 0 && !(current == start)) return 1;


	// iterates through options
	for (int i = 0; i < 4; i++)
	{
		int translation = directions[i];
		int new = current + translation;
		// Checks if the square is empty
		if (maze[new/SIZE][new%SIZE] != '#' && new != prev)
		{
			int val = mazeTraverse(maze, new, start, current);
			if (val) return 1;
		}
	}
	// Unable to find anything
	return 0;
}


// Displays the current maze position
void display(char maze[SIZE][SIZE], int current) 
{
	maze[current/SIZE][current%SIZE] = 'X';
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++) 
		{
			if (maze[i][j] == '#')
			{
				// The solid block unicode string
				printf("\u2588");
			} else if (maze[i][j] == '.')
			{
				printf(" ");
			} else
			{
				printf("%c", maze[i][j]);
			}
		}
		printf("\n");
	}
}

void clearScreenAndDelay()
{
	// ANSI escape code to clear screen
	printf("\e[1;1H\e[2J");
	
	// This is technically deprecated but it works so I'm keeping it in
	usleep(150*1000);
}
