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

/*
struct layer {
	int depth;
	int range;
	int curRange;
};
struct stackNode {
	layer* node;
	stackNode* next;
};

struct stack {
	stackNode* first;
};

void reverse(Queue<layer*>& q)
{
	stack newStack;
	newStack.first = NULL;

	while(q.len != 0)
	{
		stackNode* newNode = new stackNode;
		newNode->node = q.dequeueNode();
		newNode->next = newStack.first;
		newStack.first = newNode;
	}

	while(newStack.first != NULL)
	{
		q.queueNode(newStack.first->node);

		newStack.first = newStack.first->next;
	}
}
*/
int main()
{
	ifstream myfile;
	string line;
	myfile.open("day13_in.txt");

	int error = 0;
	while(getline(myfile, line))
	{
		int depth;
		int range;
		sscanf(line.c_str(), "%d: %d", &depth, &range);


		bool countingUp = true;
		int curRange = 0;
		for(int i = 0; i < depth; i++)
		{
			if(countingUp)
			{
				curRange++;
				if(curRange == range - 1)
					countingUp = false;
			}
			else
			{
				curRange--;
				if(curRange == 0)
					countingUp = true;

			}
		}

		if(curRange == 0)
		{
			cout << "CAUGHT AT " << depth  << endl;
			error += depth * range;
		}
		else
		{
			cout << "ESCAPED " << depth << endl;
		}
	}




	cout << error << endl;
}
