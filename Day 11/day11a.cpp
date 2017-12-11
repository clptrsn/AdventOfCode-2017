#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int max(int a, int b)
{
	return a > b ? a : b;
}

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

int getDistance(int x, int y, int z)
{
	return max(max(abs(x), abs(y)), abs(z));
}

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day11_in.txt");

	int x = 0;
	int y = 0;
	int z = 0;

	getline(myfile, line);
	int dirLen;
	string *dirs = split(line, ",", dirLen);

	for(int i = 0; i < dirLen; i++)
	{
		string dir = dirs[i];

		if(dir == "n")
		{
			y++;
			z--;
		}
		if(dir == "s")
		{
			y--;
			z++;
		}
		if(dir == "nw")
		{
			y++;
			x--;
		}
		if(dir == "se")
		{
			y--;
			x++;
		}
		if(dir == "ne")
		{
			x++;
			z--;
		}
		if(dir == "sw")
		{
			x--;
			z++;
		}
	}


	cout << "DIST " << getDistance(x, y, z) << endl;
}