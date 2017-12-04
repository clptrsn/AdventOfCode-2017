#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day4a_in.txt");

	int validPassphrase = 0;
	while(getline(myfile, line))
	{
		int tabPos = line.find(" ");
		string phrases[40];
		int count = 0;

		string subString = line.substr(0, tabPos);

		while(tabPos != -1)
		{
			cout << line << endl;
			cout << tabPos <<  " " << line.substr(0, tabPos) << endl;
			string subString = line.substr(0, tabPos);
			
			line = line.substr(tabPos + 1, line.length());
			tabPos = line.find(" ");
			phrases[count] = subString;
			count++;
		}

		phrases[count] = line;
		count++;

		cout << line << endl;

		bool invalid = false;
		for(int i = 0; i < count; i++)
		{
			for(int j = i+1; j < count; j++)
			{
				if(phrases[i].compare(phrases[j]) == 0)
				{
					invalid = true;
				}
			}
		}

		if(invalid == false)
		{
			validPassphrase++;
		}
	}

	cout << validPassphrase << endl;	
}