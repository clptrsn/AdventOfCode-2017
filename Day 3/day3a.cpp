#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int input = 347991;

	int rootInput = ceil(sqrt(input));
	
	if(rootInput % 2 == 0)
	{
		rootInput = rootInput + 1;
	}

	int layerDist = rootInput / 2;
	cout << layerDist << endl;
	int axisNum = rootInput*rootInput - 2*layerDist;

	cout << axisNum << endl;
	while(input < axisNum)
	{
		cout << axisNum << endl;
		axisNum = axisNum - 2*layerDist;
	}

	cout << layerDist + abs(axisNum + layerDist - input) << endl;
}