#include <iostream>
#include <fstream>
#include <string>
#include "./Util/graph.cpp"
#include "./Util/queue.cpp"
#include "./Util/util.cpp"

using namespace std;

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define CLEAN 0
#define WEAK 1
#define INFEC 2
#define FLAG 3

const int maxGridSize = 10000;
char grid[maxGridSize][maxGridSize];
char getGrid( int x, int y)
{
	return grid[maxGridSize/2 + x][maxGridSize/2 + y];
}

void setGrid( int x, int y, char val)
{
	grid[maxGridSize/2 + x][maxGridSize/2 + y] = val;
}

void initGrid()
{
	for(int i = 0; i < maxGridSize; i++)
	{
		for(int j = 0; j < maxGridSize; j++)
		{
			grid[i][j] = true;
		}
	}
}

void printGrid(int curX, int curY)
{
	for(int i = -5; i < 5; i++)
	{
		for(int j = -5; j < 5; j++)
		{
			if(i == curX && j == curY)
				cout << "*";
			else
				cout << " ";

			cout << (getGrid(i, j) ? "." : "#") << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day22_in.txt");

	int curNodeX = 0;
	int curNodeY = 0;
	int dir = UP;

	initGrid();

	cout << "Test" << endl;

	int lineCount = 0;
	int lineSize;
	while(getline(myfile, line))
	{
		lineSize = line.length();

		for(int i = 0; i < lineSize; i++)
		{
			if(line[i] == '.')
				setGrid(lineCount, i, true);
			else
				setGrid(lineCount, i, false);
		}
		cout << "Read Line " << lineCount << " " << line << endl;
		lineCount++;
	}

	curNodeY = lineCount/2;
	curNodeX = lineSize/2;

	int burstCount = 0;
	for(int iter = 0; iter < 10000; iter++)
	{
		char state = getGrid(curNodeX, curNodeY);

		setGrid(curNodeX, curNodeY, (state + 1) % 4);

		switch(state)
		{
			case CLEAN:
				dir = (dir + 1) % 4;
				break;
			case WEAK:
				dir = dir;
				break;
			case INFEC:
				dir = (dir + 3) % 4;
				break;
			case FLAG:
				dir = (dir + 2) % 4;
				break;
		}
		if(isClean)
		{
			dir = (dir + 1) % 4;
			setGrid(curNodeX, curNodeY, false);
			burstCount++;
		}
		else
		{
			dir = (dir + 3) % 4;
			setGrid(curNodeX, curNodeY, true);
		}


		if(dir == LEFT)
		{
			curNodeY--;		
		}
		if(dir == RIGHT)
		{
			curNodeY++;	
		}
		if(dir == UP)
		{
			curNodeX--;		
		}
		if(dir == DOWN)
		{
			curNodeX++;
		}
		//cout << "Dir " << dir << endl;
		//printGrid(curNodeX, curNodeY);
	}
	cout << burstCount << endl;
	return 0;
}
