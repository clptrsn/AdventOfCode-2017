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



int main()
{
	ifstream myfile;
	string line;
	myfile.open("day18_in.txt");


	long long reg[26];
	for(int i = 0; i < 26; i++)
	{
		reg[i] = 0L;
	}
	string instr[1000];
	int instrCount = 0;
	while(getline(myfile, line))
	{
		instr[instrCount] = line;
		cout << instr[instrCount] << endl;
		instrCount++;
	}

	long lastFrequency = 0;
	int curIns = 0;
	while(curIns >= 0 && curIns < instrCount)
	{
		int paramCount;
		string *parts = split(instr[curIns], " ", paramCount);

		string instruction = parts[0];
		curIns++;

		long long regVal;
		long long *regPointer;
		if(parts[1][0] >= 'a' && parts[1][0] <= 'z')
		{
			regPointer = &reg[parts[1][0] - 'a'];
			regVal = *regPointer;
		}
		else
		{
			regVal = atol(parts[1].c_str());
		}

		if(instruction == "snd")
		{
			lastFrequency = *regPointer;
			cout << "Setting lastFrequency to " << lastFrequency << endl;
			continue;
		}

		if(instruction == "rcv")
		{
			cout << "Try Receiving Frequency " << endl;
			if(*regPointer != 0)
			{
				*regPointer = lastFrequency;
				break;
			}
			continue;
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
			cout << "Setting " << parts[1][0] << " to " << value;
			*regPointer = value;
		}

		if(instruction == "add")
		{
			cout << "Adding " << parts[1][0] << " to " << value;
			*regPointer	 += value;
		}

		if(instruction == "mul")
		{
			cout << "Multiplying " << parts[1][0] << " to " << value;
			*regPointer = *regPointer * value;
		}

		if(instruction == "mod")
		{
			cout << "Modding " << parts[1][0] << " to " << value;
			*regPointer %= value;
		}

		if(instruction == "jgz")
		{
			if(*regPointer > 0)
			{
				cout << "Jumping To " << curIns - 1 + value;
				curIns--;
				curIns += value;
			}
		}

		cout << endl;
		cout << "-- Register " << parts[1][0] << " is now " << *regPointer << endl;
	}

	cout << lastFrequency << endl;

}
