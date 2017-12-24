#include <iostream>
#include <fstream>
#include <string>
#include "./Util/graph.cpp"
#include "./Util/queue.cpp"
#include "./Util/util.cpp"

using namespace std;

string flip(string in, int size)
{
	if(size == 2)
	{
		string result = "xx/xx";
		result[0] = in[1];
		result[1] = in[0];
		result[3] = in[4];
		result[4] = in[3];

		return result;
	}
	else
	{
		string result = "xxx/xxx/xxx";
		result[0] = in[2];
		result[1] = in[1];
		result[2] = in[0];
		result[4] = in[6];
		result[5] = in[5];
		result[6] = in[4];
		result[8] = in[10];
		result[9] = in[9];
		result[10] = in[8];

		return result;
	}	
}

string rotate(string in, int size)
{
	if(size == 2)
	{
		string result = "xx/xx";
		result[0] = in[3];
		result[1] = in[0];
		result[3] = in[4];
		result[4] = in[1];

		return result;
	}
	else
	{
		string result = "xxx/xxx/xxx";
		result[0] = in[8];
		result[1] = in[4];
		result[2] = in[0];
		result[4] = in[9];
		result[5] = in[5];
		result[6] = in[1];
		result[8] = in[10];
		result[9] = in[6];
		result[10] = in[2];

		return result;
	}
}

string getSubsquare(string in, int size, int subSquare, int row, int col)
{
	string result;
	if(subSquare ==2)
		result = "../..";
	else
		result = ".../.../...";

	row = row*subSquare;
	col = col*subSquare;
	for(int x = row; x < row + subSquare; x++)
	{
		for(int y = col; y < col + subSquare; y++)
		{
			result[(x-row)*(subSquare+1) + (y-col)] = in[x*size + y + x];
		}
	}

	return result;
}

string writeSubsquare(string current, int size, int subSquare, int row, int col, string sub)
{
	row = row*subSquare;
	col = col*subSquare;

	for(int x = row; x < row + subSquare; x++)
	{
		for(int y = col; y < col + subSquare; y++)
		{
			current[x*size + y + x] = sub[(x-row)*(subSquare+1) + (y-col)];
		}
	}

	return current;
}

string getNextString(int size)
{
	string result = "";
	if(size % 2 == 0)
	{
		size = size / 2 * 3;
	}
	else
	{
		size = size / 3 * 4;
	}

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			result += ".";	
		}

		if(i < size - 1)
			result += "/";
	}

	return result;
}

struct rule
{
	string input;
	string output;
};

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day21_in.txt");

	Queue<rule> Rules;
	Rules.initQueue();

	while(getline(myfile, line))
	{
		string *parts = split(line, " => ");

		rule newRule;
		newRule.input = parts[0];
		newRule.output = parts[1];

		cout << line << endl;

		Rules.queueNode(newRule);
	}

	string input = ".#./..#/###";
	int size = 3;
	for(int iter = 0; iter < 5; iter++)
	{
		string next = getNextString(size);
		int subSquareCount;
		int subSquareSize;
		int newSize;

		if(size % 2 == 0)
		{
			subSquareCount = size / 2;
			subSquareSize = 2;
			newSize = size / 2 * 3;
		}
		else if(size % 3 == 0)
		{
			subSquareCount = size / 3;
			subSquareSize = 3;
			newSize = size / 3 * 4;
		}

		for(int i = 0; i < subSquareCount; i++)
		{
			for(int j = 0; j < subSquareCount; j++)
			{
				string subString = getSubsquare(input, size, subSquareSize, i, j);
				
				string output;
				bool isDone = false;
				QueueNode<rule>* walk = Rules.head;
				while(walk != NULL && isDone == false)
				{
					for(int fl = 0; fl < 2; fl++)
					{
						for(int rot = 0; rot < 4; rot++)
						{
							if(subString == walk->data.input)
							{
								output = walk->data.output;
								isDone = true;
								break;
							}
							subString = rotate(subString, subSquareSize);
							//cout << "Rotate " << rot << " " << subString << endl;
						}
						if(subString == walk->data.input)
						{
							output = walk->data.output;
							isDone = true;
							break;
						}
						if(isDone)
							break;

						subString = flip(subString, subSquareSize);
						//cout << "Flip " << fl << " " << subString << endl;
					}

					if(isDone == false)
						walk = walk->next;
				}


				//cout << "MATCHED " << walk->data.input << endl;
				next = writeSubsquare(next, newSize, subSquareSize+1, i, j, output);
			}
		}
		//cout << next << endl;
		input = next;
		size = newSize;

	}

	int onCount = 0;
	for(int i = 0; i < input.length(); i++)
	{
		if(input[i] == '#')
			onCount++;
	}

	cout << onCount << endl;
	return 0;
}
