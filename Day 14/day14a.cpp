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

int* getKnotHash(const char* lengths, int sequenceLength)
{
	const int ropeSize = 256;
	int rope[ropeSize] = {0};
	for(int i =0; i < ropeSize; i++)
	{
		rope[i] = i;
	}

	int curPos = 0;
	int skipSize = 0;

	for(int rond = 0; rond < 64; rond++)
	{
		for(int i = 0; i < sequenceLength; i++)
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

	int *denseHash = new int[ropeSize/16];

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

		//cout << hex << hash;
	}

	return denseHash;
}
int main()
{
	string input = "flqrgnkx-";
	char exChar[] = {17, 31, 73, 47, 23, 0};
	string extra = string(exChar);

	int usedCount = 0;
	int actual = 0;
	for(int i = 0; i < 128; i++)
	{
		string s = input + to_string(i) + extra;
		int* vals = getKnotHash(s.c_str(), s.length());


		for(int k = 0; k < 16; k++)
		{
			int curVal = vals[k];
			string result = "";
			for(int b = 0; b < 8; b++)
			{
				if(curVal % 2 == 1)
				{
					result = "#" + result;
					usedCount++;
				}
				else
					result = "." + result;

				curVal = curVal / 2;

				actual++;
			}
			cout << result;
		}
		cout << endl;
	}

	cout << usedCount << endl;
	cout << "Out of " << actual << endl;
}
