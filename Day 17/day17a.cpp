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



int main()
{
	ifstream myfile;
	string line;
	myfile.open("day17_in.txt");

	int input = 329;

	int buffer[2018];
	for(int i = 0; i < input; i++)
	{
		buffer[i] = 0;
	}

	int curPos = 0;
	for(int i = 1; i <= 2017; i++)
	{
		curPos += input;
		curPos = curPos % (i);
		curPos++;
		cout << i <<  " iter CUR = " << curPos << endl;
		for(int j = i; j > curPos; j--)
		{
			buffer[j] = buffer[j-1];
		}
		buffer[curPos] = i;

	for(int in = curPos-5; in <= curPos + 5; in++)
	{
		if(curPos == in)
			cout << "[" << buffer[in] << "] ";
		else
			cout << buffer[in] << " ";
	}
	cout << endl;
	}

}
