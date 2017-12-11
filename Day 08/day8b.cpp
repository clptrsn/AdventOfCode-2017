#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct reg {
	string id;
	int val;
	reg* next;
};

reg* initReg(string id)
{
	reg* newReg = new reg;
	newReg->id = id;
	newReg->val = 0;
	newReg->next = NULL;
	return newReg;
}

reg* getCreateReg(reg*& head, string id)
{
	reg* walk = head;
	reg* prev = NULL;
	while(walk != NULL && walk->id != id)
	{
		prev = walk;
		walk = walk->next;
	}

	if(walk == NULL)
	{
		reg* newReg = initReg(id);
		if(prev == NULL)
			head = newReg;
		else
			prev->next = newReg;

		return newReg;
	}
	else
		return walk;
}

string* split(string in, string seperator, int& returnCount)
{
	int count = 1;
	string tmp = in;
	int pos = in.find(seperator);
	cout << pos << " FOR [" << tmp << "]" << endl;

	while(pos != -1)
	{
		tmp = tmp.substr(pos + seperator.length(), tmp.length());
		pos = tmp.find(seperator);
		cout << pos << " FOR [" << tmp << "]" << endl;
		count++;
	}

	cout << "	Allocating " << count << " array of strings" << endl;
	string *returnStrings = new string[count];
	tmp = in;
	for(int i = 0; i < count - 1; i++)
	{
		returnStrings[i] = tmp.substr(0, tmp.find(seperator));
		cout << returnStrings[i] << endl;
		tmp = tmp.substr(tmp.find(seperator) + seperator.length(), tmp.length());
	}

	returnCount = count;
	returnStrings[count - 1] = tmp;
	return returnStrings;
}



int main()
{
	ifstream myfile;
	string line;
	myfile.open("day8_in.txt");

	reg* head = NULL;
	int max = 0;
	while(getline(myfile, line))
	{
		char id[4];
		char instr[4];
		int instrVal;
		char condId[4];
		char op[3];
		int condVal;

		sscanf(line.c_str(), "%s %s %d if %s %s %d", id, instr, &instrVal, condId, op, &condVal);
		
		reg* regId = getCreateReg(head, id);
		reg* condReg = getCreateReg(head, condId);

		cout << line << endl;
		if(!strcmp(instr,"dec"))
		{
			instrVal = -1 * instrVal;
		}

		cout << instrVal << endl;

		cout << "CondReg " << condReg->val << "   " << condVal << endl;
		if(condReg->val < condVal)
		{
			cout << " is less " << endl;
		}
		bool conditionMet = false;
		if(!strcmp(op,"=="))
		{
			if(condReg->val == condVal)
			{
				cout << "==" << endl;
				conditionMet = true;
			}

		}
		else if(!strcmp(op,">="))
		{
			if(condReg->val >= condVal)
			{
				cout << ">=" << endl;
				conditionMet = true;
			}
		}
		else if(!strcmp(op,"<="))
		{
			if(condReg->val <= condVal)
			{
				cout << "<=" << endl;
				conditionMet = true;
			}

		}
		else if(!strcmp(op,">"))
		{
			if(condReg->val > condVal)
			{
				cout << ">" << endl;
				conditionMet = true;
			}

		}
		else if(!strcmp(op,"<"))
		{
			if(condReg->val < condVal)
			{
				cout << "<" << endl;
				conditionMet = true;
			}

		}
		else if(!strcmp(op,"!="))
		{
			if(condReg->val != condVal)
			{
				cout << "!=" << endl;
				conditionMet = true;
			}

		}

		cout << condReg->val << " " << op << " " << condVal << (conditionMet ? " TRUE" : " FALSE") << endl;;

		if(conditionMet)
		{
			regId->val += instrVal;
		}

		if(regId->val > max)
			max = regId->val;

		printf("%s is now %d\n", regId->id.c_str(), regId->val);
	}

	cout << "MAX: " << max << endl;
}