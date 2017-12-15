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

long generateA(long prevValue)
{
	return (prevValue * 16807LL) % (long)2147483647LL;

}

long generateB(long prevValue)
{
	return (prevValue * 48271LL) % (long)2147483647LL;
}


int main()
{
	ifstream myfile;
	string line;
	myfile.open("day15_in.txt");


	long A = 277;
	long B = 349;
	int judgeCount = 0;
	for(int i = 0; i < 5000000; i++)
	{
		long nextA = generateA(A);
		while(nextA % 4 != 0)
			nextA = generateA(nextA);
		
		long nextB = generateB(B);
		while(nextB % 8 != 0)
			nextB = generateB(nextB);
		A = nextA;
		B = nextB;

		bool isSame = true;
		for(int bit = 0; bit < 16; bit++)
		{
			if(nextA % 2 != nextB % 2)
				isSame = false;

			nextA /=2;
			nextB /=2;
		}

		//cout <<resultA << endl;
		//cout << resultB << endl;
		//cout << endl;

		if(isSame)
			judgeCount++;

	}



	cout << judgeCount << endl;
}
