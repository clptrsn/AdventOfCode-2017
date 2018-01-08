#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <map>
#include "./Util/graph.cpp"
#include "./Util/queue.cpp"
#include "./Util/util.cpp"
using namespace std;

struct instruct {
	int writeVal;
	int offset;
	int nextState;
};

struct state {
	instruct instructFor0;
	instruct instructFor1;
};

state createState(int writeVal0, int offset0, char nextState0, 
	int writeVal1, int offset1, char nextState1) {
	state result;

	result.instructFor0.writeVal = writeVal0;
	result.instructFor0.offset = offset0;
	result.instructFor0.nextState = nextState0 - 'A';

	result.instructFor1.writeVal = writeVal1;
	result.instructFor1.offset = offset1;
	result.instructFor1.nextState = nextState1 - 'A';

	return result;
}

#define LEFT -1
#define RIGHT 1

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day25_in.txt");

	int currentState = 0;
	int currentPosition = 0;

	map<int, char> tape;

	state states[6];
	// A
	states[0] = createState(1, RIGHT, 'B', 1, LEFT, 'E');
	// B
	states[1] = createState(1, RIGHT, 'C', 1, RIGHT, 'F');
	// C
	states[2] = createState(1, LEFT,  'D', 0, RIGHT, 'B');
	// D	
	states[3] = createState(1, RIGHT, 'E', 0, LEFT,  'C');
	// E
	states[4] = createState(1, LEFT,  'A', 0, RIGHT, 'D');
	// F
	states[5] = createState(1, RIGHT, 'A', 1, RIGHT, 'C');
	
	for(int i = 0; i < 12459852; i++)
	{
		state curState = states[currentState];
		instruct curInstruct;
		if(tape[currentPosition] == 0)
		{
			curInstruct = curState.instructFor0;
		}
		else
		{
			curInstruct = curState.instructFor1;
		}

		tape[currentPosition] = curInstruct.writeVal;
		currentPosition += curInstruct.offset;
		currentState = curInstruct.nextState;

		if(i % 10000 == 0)
			cout << i << endl;
	}

	int sumCount = 0;
	for(map<int, char>::iterator it = tape.begin(); it != tape.end(); it++)
	{
		if(it->second == 1)
			sumCount++;
	}

	cout<< "Done with " << sumCount << endl;


	return 0;
}
