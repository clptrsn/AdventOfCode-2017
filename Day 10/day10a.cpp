#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string* split(string in, string seperator, int& returnCount)
{
	int count = 1;
	string tmp = in;
	int pos = in.find(seperator);
	cout << pos << " FOR [" << tmp << "]" << endl;

	while(pos != -1)
	{
		tmp = tmp.substr(pos + seperator.length(), tmp.length());
		pos = tmp.find(seperator);
		cout << pos << " FOR [" << tmp << "]" << endl;
		count++;
	}

	cout << "	Allocating " << count << " array of strings" << endl;
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
	myfile.open("day10_in.txt");

	const int ropeSize = 256;

	int rope[ropeSize] = {0};
	for(int i =0; i < ropeSize; i++)
	{
		rope[i] = i;
	}

	int curPos = 0;
	int skipSize = 0;

	getline(myfile, line);
	cout << line << endl;
	int lengthLength;
	string *lengths = split(line, ",", lengthLength);

	for(int i = 0; i < lengthLength; i++)
	{
		int len = atoi(lengths[i].c_str());
		cout << endl;
		int first = curPos;
		int last = curPos + len;
		while(first != last && first != last - 1)
		{
			last--;
			cout << "		swapping" << first % ropeSize << " with " << last % ropeSize << endl;
			
			int tmp = rope[first%ropeSize];
			rope[first%ropeSize] = rope[last%ropeSize];
			rope[last%ropeSize] = tmp;

			first++;
		}

		curPos += len + skipSize;
		skipSize++;

		curPos = curPos % ropeSize;

		cout << "Processed " << len << endl;
		for(int i =0; i < ropeSize; i++)
		{
			if(i == curPos)
				cout << "[" << rope[i] << "] ";
			else
			cout << rope[i] << " ";
		}
		cout << "SKIP AT " << skipSize<< endl;
	}


	for(int i =0; i < ropeSize; i++)
	{
		cout << rope[i] << endl;
	}

	cout << rope[0] * rope[1] << endl;
}