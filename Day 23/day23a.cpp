#include <iostream>
#include <fstream>
#include <string>
#include "./Util/graph.cpp"
#include "./Util/queue.cpp"
#include "./Util/util.cpp"
using namespace std;

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day23_in.txt");


	long long reg[8];
	for(int i = 0; i < 8; i++)
	{
		reg[i] = 0L;
	}
	string instr[1000];
	int instrCount = 0;
	while(getline(myfile, line))
	{
		instr[instrCount] = line;
		//cout << instr[instrCount] << endl;
		instrCount++;
	}

	long lastFrequency = 0;
	int curIns = 0;
	int mulCount = 0;

	int count = 0;
	while(curIns >= 0 && curIns < instrCount)
	{
		int paramCount;
		string *parts = split(instr[curIns], " ", paramCount);

		string instruction = parts[0];
		curIns++;

		long long regVal;
		long long *regPointer;
		if(parts[1][0] >= 'a' && parts[1][0] <= 'h')
		{
			regPointer = &reg[parts[1][0] - 'a'];
			regVal = *regPointer;
		}
		else
		{
			regVal = atol(parts[1].c_str());
		}

		long long value;	
		if(parts[2][0] >= 'a' && parts[2][0] <= 'z')
		{
			value = reg[parts[2][0] - 'a'];
		}
		else
		{
			value = atol(parts[2].c_str());
		}

		if(instruction == "set")
		{
			//cout << "Setting " << parts[1][0] << " to " << value;
			*regPointer = value;
		}

		if(instruction == "sub")
		{
			//cout << "Adding " << parts[1][0] << " to " << value;
			*regPointer	 -= value;
		}

		if(instruction == "mul")
		{
			mulCount++;
			//cout << "Multiplying " << parts[1][0] << " to " << value;
			*regPointer *= value;
		}

		if(instruction == "mod")
		{
			//cout << "Multiplying " << parts[1][0] << " to " << value;
			*regPointer %= value;
		}

		if(instruction == "jnz")
		{
			if(regVal != 0)
			{
				//cout << "Jumping To " << curIns - 1 + value;
				curIns--;
				curIns += value;
			}
		}

		//cout << endl;
		//cout << "-- Register " << parts[1][0] << " is now " << *regPointer << endl;
	}

	cout << mulCount << endl;

}
