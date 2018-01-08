#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include "./Util/graph.cpp"
#include "./Util/queue.cpp"
#include "./Util/util.cpp"
using namespace std;

struct port {
	int a;
	int b;
	bool used = false;
};

port** getPortEdges(Queue<port*> ports, int cur, int& count)
{
	count = 0;
	QueueNode<port*>* walk = ports.head;
	while(walk != NULL)
	{
		if(walk->data->a == cur || walk->data->b == cur)
			count++;
		walk = walk->next;
	}

	port **result = (port**)malloc(sizeof(port*) * count);

	count = 0;
	walk = ports.head;
	while(walk != NULL)
	{
		if(walk->data->a == cur || walk->data->b == cur)
		{
			result[count] = walk->data;
			count++;
		}
		walk = walk->next;
	}

	return result;
}

struct lengthResult {
	int length;
	int cost;
};

lengthResult getMaxCost(Queue<port*> ports, int currentPort)
{
	int edgeCount;
	port** edges = getPortEdges(ports, currentPort, edgeCount);

	int localMax = 0;
	int localLength = 0;

	for(int i = 0; i < edgeCount; i++)
	{
		port* canidateBridge = edges[i];

		if(canidateBridge->used == false)
		{
			canidateBridge->used = true;

			int nextPort;
			if(canidateBridge->a == currentPort)
			{
				nextPort = canidateBridge->b;
			}
			else
			{
				nextPort = canidateBridge->a;
			}

			lengthResult localResult = getMaxCost(ports, nextPort);

			int localCost = canidateBridge->a + canidateBridge->b + localResult.cost;
			int lengthCost = 1 + localResult.length;
			if(lengthCost > localLength || (lengthCost > localLength && localCost > localMax))
			{
				localMax = localCost;
				localLength = lengthCost;
			}

			canidateBridge->used = false;
		}
	}

	lengthResult result;
	result.length = localLength;
	result.cost = localMax;

	return result;
}

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day24_in.txt");

	Queue<port*> q;
	q.initQueue();

	while(getline(myfile, line))
	{
		int a,b;
		sscanf(line.c_str(), "%d/%d", &a, &b);
		cout << line << endl;

		port *newPort = new port;
		newPort->a = a;
		newPort->b = b;

		q.queueNode(newPort);
	}

	lengthResult cost = getMaxCost(q, 0);

	cout << cost.cost << endl;
}
