#include <iostream>
#include <fstream>
#include <string>

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
struct pipe {
	int to;
	pipe* next;
};

struct program {
	int id;
	program* next;
	pipe* firstPipe;
};


struct node {
	program* data;
	node* next;
};

void printList(node* list)
{
	node* walk = list;
	while(walk != NULL)
	{
		cout << walk->data->id << " To " << endl;
		walk = walk->next;
	}
}

void addNode(node*& head, program* data)
{
	//cout << "Adding " << data->id;
	node* newNode = new node;
	newNode->data = data;
	newNode->next = head;

	head = newNode;
	//cout << "Finished" << endl;

	//printList(head);
}

bool findNode(node* head, int id)
{
	node* walk = head;
	while(walk != NULL && walk->data->id != id)
	{
		//cout  << "			looking at " << walk->data->id <<endl;
		walk = walk->next;
	}

	if(walk == NULL)
		return false;
	else
	{
		//cout << "			found " << walk->data->id << endl;
		return true;
	}
}

program* findInProgram(program* head, int id)
{
	program* walk = head;
	while(walk != NULL && walk->id != id)
	{
		walk = walk->next;
	}

	return walk;
}


void findChildren(program* head, int id, node*& list, int& ref)
{
	//cout << "Searching " << id << endl;
	program* programNode = findInProgram(head, id);
	if(programNode == NULL)
		return;

	//cout << "Found " << id << endl;
	pipe* walk = programNode->firstPipe;
	while(walk != NULL)
	{
		//cout << "	Walking At " << walk->to << endl;
		if(findNode(list, walk->to) == false)
		{
			//cout << "	Not Found " << walk->to << endl;
			ref++;
			addNode(list, findInProgram(head, walk->to));
			findChildren(head, walk->to, list, ref);
		}

		walk = walk->next;
	}

	cout << "Exiting " << id << endl;
}

void printPrograms(program* head)
{
	program* walk = head;
	while(walk != NULL)
	{
		pipe* walkPipe = walk->firstPipe;
		//cout << "ID: " << walk->id << endl;

		while(walkPipe != NULL)
		{
			//cout << "	To:" << walkPipe->to << endl;

			walkPipe = walkPipe->next;
		}

		walk = walk->next;
	}
}

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day12_in.txt");

	program* head = NULL;
	program* prev = NULL;
	program* curr = NULL;

	while(getline(myfile, line))
	{
		int id;

		sscanf(line.c_str(), "%d", &id);

		program *newProgram = new program;
		newProgram->id = id;
		newProgram->next = NULL;
		newProgram->firstPipe = NULL;

		curr = newProgram;
		if(head == NULL)
		{
			head = curr;
			//cout << "HEADEAD" << endl;
		}
		else
		{
			//cout << prev << " next " << curr << endl;
			prev->next = curr;
		}

		prev = curr;


		//cout << line << endl;
		int pos = line.find("<-> ");

		line = line.substr(pos + 4, line.length());

		int childrenLength;
		string *children = split(line, ", ", childrenLength);
		for(int i = 0; i < childrenLength; i++)
		{
			//cout << children[i] << " inside" << endl;
			int toId = atoi(children[i].c_str());

			pipe* newPipe = new pipe;
			newPipe->to = toId;
			newPipe->next = curr->firstPipe;

			curr->firstPipe = newPipe;
		}
		//cout << "END" << endl;
	}

	//printPrograms(head);

	node* list = NULL;
	int programCount = 0;
	findChildren(head, 0, list, programCount);

	cout << programCount << endl;
}
