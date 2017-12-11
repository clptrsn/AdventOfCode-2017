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


	getline(myfile, line);
	cout << line << endl;

	int sequenceLength = line.length();

	char *lengths = new char[sequenceLength + 5];
	for(int i = 0; i < sequenceLength; i++)
	{
		lengths[i] = line[i];
	}

	int extra[] = {17,31,73,47,23};
	for(int i = sequenceLength; i < sequenceLength + 5; i++)
	{
		lengths[i] = extra[i - sequenceLength];
	}

	int curPos = 0;
	int skipSize = 0;

	for(int rond = 0; rond < 64; rond++)
	{
		for(int i = 0; i < sequenceLength + 5; i++)
		{
			int len = (int)lengths[i];
			int first = curPos;
			int last = curPos + len;
			while(first != last && first != last - 1)
			{
				last--;
				//cout << "		swapping" << first % ropeSize << " with " << last % ropeSize << endl;
				
				int tmp = rope[first%ropeSize];
				rope[first%ropeSize] = rope[last%ropeSize];
				rope[last%ropeSize] = tmp;

				first++;
			}

			curPos += len + skipSize;
			skipSize++;

			curPos = curPos % ropeSize;

			//cout << "Processed " << len << endl;
			//cout << "SKIP AT " << skipSize<< endl;
		}
	}

	int denseHash[ropeSize/16] = {0};

	for(int i = 0; i < ropeSize/16; i++)
	{
		int start = ropeSize / 16 * i;
		int end = ropeSize / 16 * (i + 1);

		int hash = 0;
		for(int idx = start; idx < end; idx++)
		{
			hash ^= rope[idx];
		}
		denseHash[i] = hash;

		cout << hex << hash;
	}
}