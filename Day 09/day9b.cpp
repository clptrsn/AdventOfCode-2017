#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day9_in.txt");

	getline(myfile, line);

	bool insideGarbage = false;
	bool ignoreNext = false;

	int currentScore = 0;
	int totalScore = 0;
	int charsInsideGarbage = 0;
	for(int pos = 0; pos < line.length(); pos++)
	{
		char token = line[pos];
		cout << token << endl;
		if(ignoreNext)
		{
			ignoreNext = false;
			continue;
		}

		bool opening = false;
		bool closing = false;
		switch(token)
		{
			case '!':
				ignoreNext = true;

				// Ignore this ! in the garbage count
				if(insideGarbage == true)
				{
					charsInsideGarbage--;
				}
				break;
			case '<':
				// If this wasn't inside garbage we can't count it
				if(insideGarbage == false)
				{
					charsInsideGarbage--;
				}
				insideGarbage = true;
				break;
			case '>':
				insideGarbage = false;
				break;
			case '{':
				opening = true;
				break;
			case '}':
				closing = true;
				break;
		}

		if(insideGarbage == false)
		{
			if(opening)
			{
				currentScore++;
			}

			if(closing)
			{
				totalScore += currentScore;
				currentScore--;
			}
		}

		if(insideGarbage)
		{
			charsInsideGarbage++;
		}
	}

	cout << charsInsideGarbage << endl;
}