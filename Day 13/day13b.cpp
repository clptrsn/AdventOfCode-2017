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

struct firewallNode {
	int depth;
	int range;
};

bool hasError(firewallNode nodes[], int count, int offset)
{
	int error = 0;
	for(int i = 0; i < count; i++)
	{
		int depth = nodes[i].depth;
		int range = nodes[i].range;

		int period = 2*(range-1);

		if((depth+offset) % period == 0)
		{
			//cout << "CAUGHT AT " << depth  << endl;
			return true;
		}
		else
		{
			//cout << "ESCAPED " << depth << endl;
		}
	}
	return false;
}

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day13_in.txt");

	Queue<string> q;
	q.initQueue();

	int error = 0;

	while(getline(myfile, line))
	{
		q.queueNode(line);
	}

	int count = q.len;
	firewallNode *nodes = new firewallNode[q.len];
	int i = 0;
	while(q.len != 0)
	{
		line = q.dequeueNode();
		int depth;
		int range;
		sscanf(line.c_str(), "%d: %d", &depth, &range);
		firewallNode newNode;
		newNode.depth = depth;
		newNode.range = range;

		nodes[i] = newNode;

		i++;
	}

	i = 0;
	while(hasError(nodes, count, i) == true)
	{
		i++;
		if(i % 10000 == 0)
			cout << "---------------- " << i << endl;
		//cout << "----------- offset " << i << endl;
	}

	cout << " at " << i << endl;
}
