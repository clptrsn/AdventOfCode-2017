#include <iostream>
#include <fstream>
#include <string>
#include <map>
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

const int iterationCount = 10000000;
struct point {
	int x;
	int y;

	bool const operator==(const point& p)
	{
		return x == p.x && y == p.y;
	}
	bool  operator<(const point& p) const {
        return x < p.x || (x <= p.x && y < p.y);
    }
};

map<point, char> grid;

point getPoint(int x, int y)
{
	point result;
	result.x = x;
	result.y = y;
	return result;
}
char getGrid(int x, int y)
{
	point xy = getPoint(x, y);

	map<point, char>::iterator it;
	it = grid.find(xy);
	if(it == grid.end())
	{
		grid[xy] = CLEAN;
	}

	return grid[xy];
}

void setGrid( int x, int y, char val)
{
	grid[getPoint(x, y)] = val;
}

char convertFlags(int state)
{
	switch(state)
	{
		case CLEAN:
			return '.';
		case WEAK:
			return 'W';
		case INFEC:	
			return '#';
		case FLAG:
			return 'F';
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

			cout << convertFlags(getGrid(i, j)) << " ";
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

	int lineCount = 0;
	int lineSize;
	while(getline(myfile, line))
	{
		lineSize = line.length();

		for(int i = 0; i < lineSize; i++)
		{
			if(line[i] == '.')
				setGrid(lineCount, i, CLEAN);
			else
				setGrid(lineCount, i, INFEC);
		}
		cout << "Read Line " << lineCount << " " << line << endl;
		lineCount++;
	}

	curNodeY = lineCount/2;
	curNodeX = lineSize/2;

	int burstCount = 0;
	for(int iter = 0; iter < iterationCount; iter++)
	{
		char state = getGrid(curNodeX, curNodeY);

		setGrid(curNodeX, curNodeY, (state + 1) % 4);

		switch(state)
		{
			case CLEAN:
				dir = (dir + 1) % 4;
				break;
			case WEAK:
				burstCount++;
				dir = dir;
				break;
			case INFEC:
				dir = (dir + 3) % 4;
				break;
			case FLAG:
				dir = (dir + 2) % 4;
				break;
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

		if(iter % 10000 == 0)
			cout << iter << " Done" << endl;
		//cout << "Dir " << dir << endl;
		//printGrid(curNodeX, curNodeY);
	}
	cout << burstCount << endl;
	return 0;
}
