#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int memSize = 16;

struct prevMemNode {
	prevMemNode* next;
	int mem[memSize];
};

int main()
{
	ifstream myfile;
	myfile.open("day6_in.txt");
	int mem[memSize];
	for(int i = 0; i < memSize; i++)
	{
		myfile >> mem[i];
	}
	
	prevMemNode* oldMem = NULL;
	int iterations = 0;
	bool changed = true;
	int prevIteration;
	while(changed == true)
	{
		int max = 0;

		prevMemNode* newPrevMem = (prevMemNode*)malloc(sizeof(prevMemNode));
		newPrevMem->next = oldMem;
		for(int i = 0; i < memSize; i++)
		{
			cout << mem[i] << "  ";

			newPrevMem->mem[i] = mem[i];
			if(mem[i] > mem[max])
			{
				max = i;
			}
		}
		cout << endl;	

		int prevMax = mem[max];
		mem[max] = 0;
		for(int i = 1; i <= prevMax; i++)
		{
			mem[(max + i) % memSize]++;
		}

		prevMemNode* check = oldMem;
		if(oldMem == NULL)
			changed = true;

		int currentCount = iterations;
		while(check != NULL)
		{
			currentCount--;
			bool isSame = true;
			for(int i = 0; i < memSize; i++)
			{
				if(mem[i] != check->mem[i])
				{
					isSame = false;
				}
			}

			if(isSame)
			{
				prevIteration = currentCount;
				changed = false;
			}

			check = check->next;
		}

		oldMem = newPrevMem;

		cout << endl;
		iterations++;
	}

	cout << iterations << "   " << iterations - prevIteration << endl;
}