#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day2b_in.txt");

	int checksum = 0;
	while(getline(myfile, line))
	{
		int vals[100];
		int numCount = 0;
		int tabPos = line.find("\t");

		cout << line << endl;
		string subString = line.substr(0, tabPos);

		while(tabPos != -1)
		{
			string subString = line.substr(0, tabPos);
			
			line = line.substr(tabPos + 1, line.length());
			tabPos = line.find("\t");
			vals[numCount] = atoi(subString.c_str());
			numCount++;
		}
		vals[numCount] = atoi(line.c_str());
		numCount++;

		for(int i = 0; i < numCount; i++)
		{
			for(int j = 0; j < numCount; j++)
			{
				if(i != j && vals[i] % vals[j] == 0)
				{
					checksum += vals[i]/vals[j];
					cout << "[" << checksum << "] " << i << " " << j << " " << vals[i]/vals[j] << endl;
				}
			}
		}
	}

	cout << checksum << endl;	
}