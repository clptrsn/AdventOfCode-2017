#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
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

	for(int i = 0; i < sequenceLength; i++)
	{
		//cout << "Processed " << (int)lengths[i] << " [" << i << " of " << sequenceLength << "]" << endl;
	}

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

void getRegions(int grid[128][128], int curX, int curY, int regionNumber)
{
	if(curX < 0 || curX >= 128 || curY < 0 || curY >= 128)
	{
		return;
	}

	if(grid[curX][curY] == -1)
	{
		grid[curX][curY] = regionNumber;

		// Explore neighbors
		getRegions(grid, curX + 1, curY, regionNumber);
		getRegions(grid, curX - 1, curY, regionNumber);
		getRegions(grid, curX, curY + 1, regionNumber);
		getRegions(grid, curX, curY - 1, regionNumber);
	}
}

int main()
{
	//char sequence[] = {'j', 'x', 'q', 'l', 'a', 's', 'b', 'h', 17, 31, 73, 47, 23, '-', 0, 0, 0};
	int grid[128][128] = {{0}};
	string input = "jxqlasbh-";
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
					grid[i][(k+1)*8 - b - 1] = -1;
				}
				else
				{
					result = "." + result;
					grid[i][(k+1)*8 - b - 1] = 0;
				}
				curVal = curVal / 2;

				actual++;
			}
			cout << result;
		}
		cout << endl;
	}

	cout << usedCount << endl;
	cout << "Out of " << actual << endl;

	int currentRegionCount = 0;
	for(int x = 0; x < 128; x++)
	{
		for(int y = 0; y < 128; y++)
		{
			if(grid[x][y] == -1)
			{
				currentRegionCount++;
				getRegions(grid, x, y, currentRegionCount);
			}
		}
	}

	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			if(grid[x][y] == 0)
				cout << " . ";
			else
				cout << setw(3) << grid[x][y];
		}
		cout << endl;
	}

	cout << usedCount << endl;
	cout << "Out of " << actual << endl;

	cout << "Has " << currentRegionCount << " regions " << endl;
}
