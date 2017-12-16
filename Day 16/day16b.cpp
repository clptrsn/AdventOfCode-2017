#include <iostream>
#include <fstream>
#include <string>
#include "./Util/graph.cpp"
#include "./Util/queue.cpp"
using namespace std;

const int programSize = 16;
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

void spin(char programs[], int x)
{
	for(int i = 0; i < x; i++)
	{
		char tmp = programs[programSize - 1];
		for(int k = programSize - 1; k > 0; k--)
		{
			programs[k] = programs[k-1];
		}
		programs[0] = tmp;
	}
}

void exchange(char programs[], int a, int b)
{
	char tmp = programs[a];
	programs[a] = programs[b];
	programs[b] = tmp;
}

void partner(char programs[], char a, char b)
{
	int aIndex = 0;
	while(programs[aIndex] != a)
		aIndex++;


	int bIndex = 0;
	while(programs[bIndex] != b)
		bIndex++;

	char tmp = programs[aIndex];
	programs[aIndex] = programs[bIndex];
	programs[bIndex] = tmp;
}

bool isBackToStart(char programs[])
{
	for(int i = 0; i < programSize; i++)
	{
		if(programs[i] != 'a' + i)
			return false;
	}

	return true;
}


struct moveCon {
	int type;
	int a;
	int b;
};

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day16_in.txt");

	char programs[programSize];
	for(int i = 0; i < programSize; i++)
	{
		programs[i] = 'a' + i;
	}

	int moveCount;
	getline(myfile, line);
	string *moves = split(line, ",", moveCount);

	moveCon *savedMoves = new moveCon[moveCount];

	for(int i = 0; i < moveCount; i++)
	{
		string move = moves[i];
		moveCon newMoveCon;
		if(move[0] == 's')
		{
			int x;
			sscanf(move.c_str(), "s%d", &x);
			newMoveCon.type = 0;
			newMoveCon.a = x;
			//spin(programs, x);
		}
		else if(move[0] == 'x')
		{
			int a, b;
			sscanf(move.c_str(), "x%d/%d", &a, &b);
			//exchange(programs, a, b);
			newMoveCon.type = 1;
			newMoveCon.a = a;
			newMoveCon.b = b;
		}
		else if(move[0] == 'p')
		{
			char a, b;
			sscanf(move.c_str(), "p%c/%c", &a, &b);
			//partner(programs, a, b);
			newMoveCon.type = 2;
			newMoveCon.a = a;
			newMoveCon.b = b;
		}
		savedMoves[i] = newMoveCon;
	}
	
	for(int i = 0; i < moveCount; i++)
	{
		moveCon newMoveCon = savedMoves[i];
		switch(newMoveCon.type)
		{
			case 0:
				spin(programs, newMoveCon.a);
				break;
			case 1:
				exchange(programs, newMoveCon.a, newMoveCon.b);
				break;
			case 2:
				partner(programs, newMoveCon.a, newMoveCon.b);
		}
	}

	int iter = 1;
	while(isBackToStart(programs) == false)
	{
		for(int i = 0; i < moveCount; i++)
		{
			moveCon newMoveCon = savedMoves[i];
			switch(newMoveCon.type)
			{
				case 0:
					spin(programs, newMoveCon.a);
					break;
				case 1:
					exchange(programs, newMoveCon.a, newMoveCon.b);
					break;
				case 2:
					partner(programs, newMoveCon.a, newMoveCon.b);
			}
		}
		iter++;
	}

	int totalIterations = 1000000000 % iter;
	for(iter = 0; iter < totalIterations; iter++)
	{
		for(int i = 0; i < moveCount; i++)
		{
			moveCon newMoveCon = savedMoves[i];
			switch(newMoveCon.type)
			{
				case 0:
					spin(programs, newMoveCon.a);
					break;
				case 1:
					exchange(programs, newMoveCon.a, newMoveCon.b);
					break;
				case 2:
					partner(programs, newMoveCon.a, newMoveCon.b);
			}
		}
	}


	for(int i = 0; i < programSize; i++)
	{
		cout << programs[i];
	}
}
