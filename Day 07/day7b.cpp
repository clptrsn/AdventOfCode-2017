#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct program {
	string id;
	string children[10];
	program *childNodes[10];
	int childCount;
	int weight;
	int balancedWeight;
	program* next;
};

program* findNode(program* root, string id)
{
	program* walk = root;
	while(walk != NULL && walk->id != id)
	{
		walk = walk->next;
	}
	return walk;
}

int createBalancedWeight(program* root, program* head, program* node)
{
	if(node == NULL)
		return 0;

	if(node->childCount == 0)
	{
		node->balancedWeight = node->weight;
		return node->weight;
	}
	else
	{
		int weight = node->weight;
		for(int i = 0; i < node->childCount; i++)
		{
			program* child = findNode(head, node->children[i]);

			node->childNodes[i] = child;
			weight += createBalancedWeight(root, head, child);
		}
		node->balancedWeight = weight;
		return weight;
	}
}

program* findWrongNode(program* root, program* node)
{
	if(node == NULL)
		return NULL;

	if(node->childCount == 0)
	{
		return NULL;
	}
	else
	{
		int balancedWeight = node->childNodes[0]->balancedWeight;
		bool isWrong = false;
		program* wrongNode;

		for(int i = 0; i < node->childCount; i++)
		{
			if(balancedWeight != node->childNodes[i]->balancedWeight)
			{
				// See if there is imbalance further down the tree
				wrongNode = findWrongNode(root, node->childNodes[i]);
				// If there isn't, the imbalance might be on the the first node
				if(wrongNode == NULL)
					wrongNode = findWrongNode(root, node->childNodes[0]);

				isWrong = true;
			}
		}

		if(isWrong)
		{
			if(wrongNode == NULL)
				return node;
			else
				return wrongNode;
		}
		else
		{
			for(int i = 0; i < node->childCount; i++)
			{
				program* possibleWrong = findWrongNode(root, node->childNodes[i]);
				if(possibleWrong != NULL)
					return possibleWrong;
			}
			return NULL;
		}
	}	
}

void printTree(program* root, program* node, string indent="")
{
	if(node == NULL)
	{
		return;
	}

	cout << indent << left << setw(10) << node->id <<  " " << setw(5) << node->weight << " [" << node->balancedWeight << "]" << endl;
	for(int i = 0; i < node->childCount; i++)
	{
		printTree(root, node->childNodes[i], indent + "   ");
	}

}

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
		}
		else
		{
			//cout << prev << " next " << curr << endl;
			prev->next = curr;
		}

		prev = curr;

		//cout << line << endl;
		if(line.find("-> ") != -1)
		{
			line = line.substr(line.find("-> ") + 3, line.length());
			int tabPos = line.find(", ");
			int count = 0;

			string subString = line.substr(0, tabPos);

			while(tabPos != -1)
			{
				//cout << line.substr(0, tabPos) << " " << count<< endl;
				string subString = line.substr(0, tabPos);
				
				line = line.substr(tabPos + 2, line.length());
				tabPos = line.find(", ");
				curr->children[count] = subString;
				count++;
			}

			curr->children[count] = line;
			count++;

			curr->childCount = count;
			//cout << line << endl;
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
			walk = walk->next;
		}

		cout << prevRoot->id << " is Child of " << root->id << endl;
	}

	cout << root->id << endl;
	createBalancedWeight(root, head, root);
	printTree(root, root);
	program* wrong = findWrongNode(root, root);
	cout << wrong->id << endl;

	int valCounts[2] = {0};
	int vals[2] = {-1};
	program* lastVal[2] = {NULL};

	for(int i = 0; i < wrong->childCount; i++)
	{
		int weight = wrong->childNodes[i]->balancedWeight;
		int index;
		if(vals[0] == -1 || vals[0] == weight)
		{
			index = 0;
		}
		else
		{
			index = 1;
		}

		valCounts[index]++;
		vals[index] = weight;
		lastVal[index] = wrong->childNodes[i];
		cout << wrong->childNodes[i]->id << " " << wrong->childNodes[i]->balancedWeight << endl;
		
	}

	if(valCounts[0] == 1)
	{
		cout << vals[1] - lastVal[0]->balancedWeight + lastVal[0]->weight << endl;
	}
	else
	{
		cout << vals[0] - lastVal[1]->balancedWeight + lastVal[1]->weight << endl;
	}
}