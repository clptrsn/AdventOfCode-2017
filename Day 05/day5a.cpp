#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day5a_in.txt");
	int maze[10000] = {0};
	int mazeCount = 0;
	while(getline(myfile, line))
	{
		cout << line << endl;
		maze[mazeCount] = atoi(line.c_str());
		mazeCount++;
	}

	int i = 0;
	int iterations = 0;
	while(i >= 0 && i < mazeCount)
	{
		maze[i]++;
		i += maze[i] - 1;
		iterations++;
	}

	cout << iterations << endl;
}