#include <iostream>
#include <fstream>
#include <string>
#include <map>
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

	map<string, string> rules;
	while(getline(myfile, line))
	{
		string *parts = split(line, " => ");

		rule newRule;
		newRule.input = parts[0];
		newRule.output = parts[1];

		int ruleSize;
		if(newRule.input.length() == 5)
			ruleSize = 2;
		else
			ruleSize = 3;

		for(int fl = 0; fl < 2; fl++)
		{
			for(int rot = 0; rot < 4; rot++)
			{				
				rules[newRule.input] = newRule.output;
				//cout << newRule.input.length() << " " << newRule.input << " => " << newRule.output << endl;
				newRule.input = rotate(newRule.input, ruleSize);
			}
			newRule.input = flip(newRule.input, ruleSize);
		}
	}

	string input = ".#./..#/###";
	int size = 3;
	for(int iter = 0; iter < 18; iter++)
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
				string result = "";

				int row = i*subSquareSize;
				int col = j*subSquareSize;
				for(int x = row; x < row + subSquareSize; x++)
				{
					for(int y = col; y < col + subSquareSize; y++)
					{
						result += input[x*size + y + x];
					}
					result += "/";
				}
				result.pop_back();

				// Get the output from rules
				string output = rules[result];

				// Write the output to the next string
				subSquareSize++;
				row = i*subSquareSize;
				col = j*subSquareSize;

				for(int x = row; x < row + subSquareSize; x++)
				{
					for(int y = col; y < col + subSquareSize; y++)
					{
						next[x*newSize + y + x] = output[(x-row)*(subSquareSize+1) + (y-col)];
					}
				}
				subSquareSize--;
			}
		}
		cout << iter << "at" << size << endl;
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
