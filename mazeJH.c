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
int msleep(long msec);


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

	// Clears screen to make fresh start
	printf("\e[1;1H\e[2J");

	mazeTraverse(maze,24,24,0);

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
	printf("\e[1;1H\e[2J");
	
	//msleep(999);
	usleep(150*1000);
}


// Not sure why this doesn't work, considering I stole it from stackoverflow and I've used this code before
// https://stackoverflow.com/questions/1157209/is-there-an-alternative-sleep-function-in-c-to-milliseconds
int msleep(long msec) 
{

	struct timespec ts;
	int res;
	
	if (res < 0)
	{
		errno = EINVAL;
		return -1;
	}

	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec % 1000) * 100000;

	do 
	{
		res = nanosleep(&ts,&ts);
	}
	while (res && errno == EINTR);

	return res;
}
