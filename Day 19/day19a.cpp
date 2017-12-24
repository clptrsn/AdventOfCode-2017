#include <iostream>
#include <fstream>
#include <string>
#include "./Util/graph.cpp"
#include "./Util/queue.cpp"
using namespace std;

string* split(string in, string seperator, int& returnCount)
{
	int count = 1;
	string tmp = in;
	int pos = in.find(seperator);
	//cout << pos << " FOR [" << tmp << "]" << endl;

	while(pos != -1)
	{
		tmp = tmp.substr(pos + seperator.length(), tmp.length());
		pos = tmp.find(seperator);
		//cout << pos << " FOR [" << tmp << "]" << endl;
		count++;
	}

	//cout << "	Allocating " << count << " array of strings" << endl;
	string *returnStrings = new string[count];
	tmp = in;
	for(int i = 0; i < count - 1; i++)
	{
		returnStrings[i] = tmp.substr(0, tmp.find(seperator));
		//cout << returnStrings[i] << endl;
		tmp = tmp.substr(tmp.find(seperator) + seperator.length(), tmp.length());
	}

	returnCount = count;
	returnStrings[count - 1] = tmp;
	return returnStrings;
}

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

void moveInDir(int& row, int& col, int dir)
{
	switch(dir)
	{
		case UP:
			row--;
			break;
		case DOWN:
			row++;
			break;
		case LEFT:
			col--;
			break;
		case RIGHT:
			col++;
			break;
	}
}

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day19_in.txt");

	char graph[200][200];

	for(int row = 0; row < 200; row++)
	{
		for(int col = 0; col < 200; col++)
		{
			graph[row][col] = ' ';
		}
	}
	int rowCount = 0;
	while(getline(myfile, line))
	{
		const char* lineChars = line.c_str();
		for(int col = 0; col < 200; col++)
		{
			graph[rowCount][col] = lineChars[col];
		}
		cout << rowCount << " " << line << endl;
		rowCount++;
	}

	for(int row = 0; row < 200; row++)
	{
		cout << row << " " ;
		for(int col = 0; col < 200; col++)
		{
			cout << graph[row][col];
		}
		
		cout << endl << "end" << endl;
	}

	int row = 0;
	int col = 0;
	int dir = DOWN;

	Queue<char> path;
	path.initQueue();

	// Find starting point
	while(graph[row][col] != '|')
		col++;


	while(1)
	{
		// Find the first + in the current direction
		moveInDir(row, col, dir);
		cout << "Moving to " << row << "," << col << endl;
		if(graph[row][col] == ' ')
			break;

		if(graph[row][col] != '|' && graph[row][col] != '-' && graph[row][col] != '+' )
		{
			path.queueNode(graph[row][col]);
		}

		if(graph[row][col] == '+')
		{
			if(col > 0 && graph[row][col-1] == '-' && dir != RIGHT)
			{
				dir = LEFT;
			}
			else if(col < 199 && graph[row][col+1] == '-' && dir != LEFT)
			{
				dir = RIGHT;
			}
			else if(row > 0 && graph[row-1][col] == '|' && dir != DOWN)
			{
				dir = UP;
			}
			else if(row < 199 && graph[row+1][col] == '|' && dir != UP)
			{
				dir = DOWN;
			}
			else
			{
				cout << "Ended" << endl;
			}
		}
	}

	while(path.len != 0)
	{
		cout << path.dequeueNode();
	}
	cout << endl;

	return 0;

}
