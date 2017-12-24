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

	while(pos != -1)
	{
		tmp = tmp.substr(pos + seperator.length(), tmp.length());
		pos = tmp.find(seperator);
		count++;
	}

	string *returnStrings = new string[count];
	tmp = in;
	for(int i = 0; i < count - 1; i++)
	{
		returnStrings[i] = tmp.substr(0, tmp.find(seperator));
		tmp = tmp.substr(tmp.find(seperator) + seperator.length(), tmp.length());
	}

	returnCount = count;
	returnStrings[count - 1] = tmp;
	return returnStrings;
}

struct program {
	int curIns;
	Queue<long long> frequency;
	int pid;
	long long reg[26];
	bool isWaiting = false;
};


int main()
{
	ifstream myfile;
	string line;
	myfile.open("day18_in.txt");

	program program0;
	program0.curIns = 0;
	program0.frequency.initQueue();
	program0.pid = 0;
	for(int i = 0; i < 26; i++)
	{
		program0.reg[i] = 0L;
	}
	program0.reg['p'-'a'] = 0;

	program program1;
	program1.curIns = 0;
	program1.frequency.initQueue();
	program1.pid = 1;
	for(int i = 0; i < 26; i++)
	{
		program1.reg[i] = 0L;
	}
	program0.reg['p'-'a'] = 1;

	string instr[1000];
	int instrCount = 0;
	while(getline(myfile, line))
	{
		instr[instrCount] = line;
		cout << instr[instrCount] << endl;
		instrCount++;
	}

	int curProg = 0;
	int programOneSendCount = 0;
	while(((program0.isWaiting == false || program0.frequency.len != 0) ||
		  (program1.isWaiting == false || program1.frequency.len != 0)) &&
		program0.curIns >= 0 && program0.curIns < instrCount &&
		program1.curIns >= 0 && program1.curIns < instrCount)
	{
		program *curProgram = curProg == 0 ? &program0 : &program1;
		if(curProg == 0)
			cout << "___PROGRAM ZERO____" << endl;
		else
			cout << "___PROGRAM  ONE____" << endl;

		int paramCount;
		string *parts = split(instr[curProgram->curIns], " ", paramCount);

		string instruction = parts[0];
		curProgram->curIns++;

		long long regVal;
		long long *regPointer;
		if(parts[1][0] >= 'a' && parts[1][0] <= 'z')
		{
			regPointer = &curProgram->reg[parts[1][0] - 'a'];
			regVal = *regPointer;
		}
		else
		{
			regVal = atol(parts[1].c_str());
		}

		if(instruction == "snd")
		{
			if(curProg == 0)
			{
				//hide		
				cout << "Sending " << regVal << " to 1" << endl;
				// Send to 1
				program1.frequency.queueNode(regVal);
				program1.isWaiting = false;
				programOneSendCount++;
			}
			else
			{
				//hide		
				cout << "Sending " << regVal << " to 0" << endl;
				program0.frequency.queueNode(regVal);
				program0.isWaiting = false;
			}
			continue;
		}

		if(instruction == "rcv")
		{
			//hide	
			cout << "Try Receiving Frequency " << endl;
			if(curProgram->frequency.len != 0)
			{
				*regPointer = curProgram->frequency.dequeueNode();
			}
			else
			{
				curProgram->isWaiting = true;
				curProgram->curIns--;

				curProg = (curProg + 1) % 2;
			}
			continue;
		}

		long long value;	
		if(parts[2][0] >= 'a' && parts[2][0] <= 'z')
		{
			value = curProgram->reg[parts[2][0] - 'a'];
		}
		else
		{
			value = atol(parts[2].c_str());
		}

		if(instruction == "set")
		{
			//hide	
			cout << "Setting " << parts[1][0] << " to " << value;
			*regPointer = value;
		}

		if(instruction == "add")
		{
			//hide	
			cout << "Adding " << parts[1][0] << " to " << value;
			*regPointer	 += value;
		}

		if(instruction == "mul")
		{
			//hide	
			cout << "Multiplying " << parts[1][0] << " to " << value;
			*regPointer = *regPointer * value;
		}

		if(instruction == "mod")
		{
			//hide	
			cout << "Modding " << parts[1][0] << " to " << value;
			*regPointer %= value;
		}

		if(instruction == "jgz")
		{
			if(*regPointer > 0)
			{
				//hide		
				cout << "Jumping To " << curProgram->curIns - 1 + value;
				curProgram->curIns--;
				curProgram->curIns += value;
			}
		}

		//hide
		cout << endl;
		//hide
		cout << "-- Register " << parts[1][0] << " is now " << *regPointer << endl;
	}

	cout << programOneSendCount << endl;

}
