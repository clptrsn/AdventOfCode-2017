#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day2a_in.txt");

	int checksum = 0;
	while(getline(myfile, line))
	{
		int tabPos = line.find("\t");

		string subString = line.substr(0, tabPos);
		int max = atoi(subString.c_str());
		int min = atoi(subString.c_str());

		while(tabPos != -1)
		{
			cout << line << endl;
			cout << tabPos <<  " " << line.substr(0, tabPos) << endl;
			string subString = line.substr(0, tabPos);
			if(atoi(subString.c_str()) > max)
				max = atoi(subString.c_str());
			if(atoi(subString.c_str()) < min)
				min = atoi(subString.c_str());
			
			line = line.substr(tabPos + 1, line.length());
			tabPos = line.find("\t");
		}

		cout << line << endl;
		cout << tabPos <<  " " << line.substr(0, tabPos) << endl;
			
		if(atoi(line.c_str()) > max)
			max = atoi(line.c_str());
		if(atoi(line.c_str()) < min)
			min = atoi(line.c_str());

		cout << "MAX " << max << "  MIN " << min << endl;
		checksum += max - min;		
	}

	cout << checksum << endl;	
}