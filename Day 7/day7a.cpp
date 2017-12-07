#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct program {
	string id;
	string children[10];
	int childCount;
	int weight;
	int balancedWeight;
	program* next;
};

int main()
{
	ifstream myfile;
	string line;
	myfile.open("day7_in.txt");

	program* head = NULL;
	program* prev = NULL;
	program* curr = NULL;

	int validPassphrase = 0;
	while(getline(myfile, line))
	{
		char id[15];
		int weight;

		sscanf(line.c_str(), "%s (%d)", id, &weight);
		printf("%s %d\n", id, weight);

		program *newProgram = new program;
		newProgram->id = string(id);
		newProgram->weight = weight;
		newProgram->next = NULL;
		newProgram->childCount = 0;

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

		cout << line << endl;
		if(line.find("-> ") != -1)
		{
			line = line.substr(line.find("-> ") + 3, line.length());
			int tabPos = line.find(", ");
			int count = 0;

			string subString = line.substr(0, tabPos);

			while(tabPos != -1)
			{
				string subString = line.substr(0, tabPos);
				
				line = line.substr(tabPos + 2, line.length());
				tabPos = line.find(", ");
				curr->children[count] = subString;
				count++;
			}

			curr->children[count] = line;
			count++;

			curr->childCount = count;
		}
	}

	program* prevRoot = NULL;
	program* root = head;

	while(prevRoot != root)
	{
		prevRoot = root;
		bool foundRoot = false;
		program* walk = head;
		while(walk != NULL && foundRoot == false)
		{
			for(int i = 0; i < walk->childCount; i++)
			{
				if(root->id == walk->children[i])
				{
					//Found parent
					root = walk;
					foundRoot = true;
					break;
				}
			}
			//cout << " WALKING DOWN " << walk->id << endl;
			walk = walk->next;
		}

		cout << prevRoot->id << "Child of " << root->id << endl;
	}

	cout << root->id << endl;
}