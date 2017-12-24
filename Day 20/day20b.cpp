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

struct Vector3
{
	int x;
	int y;
	int z;
};

struct particle
{
	Vector3 p;
	Vector3 v;
	Vector3 a;

	bool isActive = true;
};

Vector3 createVec(int x, int y, int z)
{
	Vector3 newVec;
	newVec.x = x;
	newVec.y = y;
	newVec.z = z;

	return newVec;
}

Vector3 add(Vector3 a, Vector3 b)
{
	Vector3 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return result;
}

void printVec(Vector3 a)
{
	cout << "x:" << a.x << " y:" << a.y << " z:" << a.z << endl;
}

int dist(Vector3 a, Vector3 b)
{
	return abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z);
}

int dist(Vector3 a)
{
	return abs(a.x) + abs(a.y) + abs(a.z);
}

void tick(particle* par)
{
	if(par->isActive)
	{
		Vector3 prevP = par->p;
		par->v = add(par->v, par->a);
		par->p = add(par->p, par->v);
	}
}


int main()
{
	ifstream myfile;
	string line;
	myfile.open("day20_in.txt");

	particle inputs[1000];
	int currentPar = 0;
	while(getline(myfile, line))
	{
		int x,y,z;

		particle newParticle;
		int componentCount;
		string *components = split(line, ", ", componentCount);

		// Position
		sscanf(components[0].c_str(), "p=<%d,%d,%d>", &x, &y, &z);
		newParticle.p = createVec(x,y,z);

		// Velocity
		sscanf(components[1].c_str(), "v=<%d,%d,%d>", &x, &y, &z);
		newParticle.v = createVec(x,y,z);

		// Acceleration
		sscanf(components[2].c_str(), "a=<%d,%d,%d>", &x, &y, &z);
		newParticle.a = createVec(x,y,z);

		newParticle.isActive = true;
		inputs[currentPar] = newParticle;
		currentPar++;
	}

	bool stable = false;
	int closestParticle = 0;

	int totalParticleCount = currentPar;

	int iterationsSinceCollision = 0;
	bool activeStatus[1000];

	while(stable == false && iterationsSinceCollision < 1000)
	{
		for(int i = 0; i < totalParticleCount; i++)
		{
			activeStatus[i] = inputs[i].isActive;
		}
		bool collisionsOccurred = false;
		for(int i = 0; i < totalParticleCount; i++)
		{
			for(int j = i+1; j < totalParticleCount; j++)
			{
				if(activeStatus[i] && activeStatus[j])
				{
					if(inputs[i].p.x == inputs[j].p.x && 
						inputs[i].p.y == inputs[j].p.y && 
						inputs[i].p.z == inputs[j].p.z)
					{
						collisionsOccurred = true;

						if(inputs[i].isActive == true)
						{
							inputs[i].isActive = false;
							currentPar--;
						}

						if(inputs[j].isActive == true)
						{
							inputs[j].isActive = false;
							currentPar--;
						}
					}
				}
			}
		}

		for(int i = 0; i < totalParticleCount; i++)
		{
			inputs[i].isActive = activeStatus[i];
			tick(&inputs[i]);
		}


		cout << currentPar << endl;
		if(collisionsOccurred == false)
		{	
			iterationsSinceCollision++;	
		}
		else
		{
			iterationsSinceCollision = 0;
		}
	}

	cout << currentPar << endl;
	return 0;
}
