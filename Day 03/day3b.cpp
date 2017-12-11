#include <iostream>
#include <cmath>
using namespace std;

void getCoord(int n, int& x, int& y)
{
	int dist = ceil((sqrt(n)-1)/2);
	int t = 2*dist;
	int maxNum = (t+1)*(t+1);

	if(n >= maxNum - t)
	{
		x = dist - maxNum + n;
		y = -1*dist;
		return;
	}

	maxNum = maxNum - t;
	if(n >= maxNum - t)
	{
		x = -1*dist;
		y = -1*dist + maxNum - n;
		return;
	}

	maxNum = maxNum - t;
	if(n >= maxNum - t)
	{
		x = -1*dist + maxNum - n;
		y = dist;
		return;
	}

	x = dist;
	y = dist - maxNum + n + t;
	return;	
}

int getIndex(int x, int y)
{
	int max = (abs(x) > abs(y)) ? abs(x) : abs(y);
	int maxNumber = (2*max + 1) * (2*max + 1);
	int n;
//	cout << endl;
//	cout << "MAX = " << max << endl;
//	cout << "MAXNUMB = " << maxNumber << endl;
//	cout << "(X, Y) = (" << x << ", " << y <<  ")" << endl;
	if(y == -1 * max)
	{
		//cout << "maxNumber + x - max = " << maxNumber << " + " << x << " - " << max << endl;
		n = maxNumber + x - max;		
	}
	else if(x == -1 * max)
	{
		//cout << "maxNumber - y - max - 2*max = " << maxNumber << " - " << y << " - " << max << " - " << 2*max << endl;
		n = maxNumber - y - max - 2*max;
	}
	else if(y == max)
	{
		//cout << "maxNumber - x - max - 4*max = " << maxNumber << " - " << x << " - " << max << " - " << 4*max << endl;
		n = maxNumber - x - max - 4*max;
	}
	else if(x == max)
	{
		//cout << "maxNumber - y + max - 6*max = " << maxNumber << " - " << y << " - " << max << " - " << 6*max << endl;
		n = maxNumber - y - max - 6*max;
	}

	return n;
}

void setVal(int *grid, int x, int y, int val)
{
	int n = getIndex(x,y);
	grid[n] = val;
}

int getVal(int *grid, int x, int y)
{
	int n = getIndex(x,y);
	return grid[n];
}

void printGrid(int *grid, int n)
{
	for(int i = 0; i < n; i++)
	{
		int x,y;
		getCoord(i, x, y);
		cout << i << " " << grid[n] << "  @ (" << x << ", " << y << ")" << endl;
	}
}

int main()
{
	int input = 347991;
	int n = ceil(log2(input));
	n = n*n;
	int *grid = new int[n];

	cout << n << endl;
	for(int i = 0; i < n; i++)
	{
		grid[i] = 0;

		int x,y;		
		if(getIndex(x,y) != i)
			cout << "FUCKCKCKCKKC" << endl;
	}

	int i = 0;
	setVal(grid, 0, 0, 1);
	cout << getVal(grid, 0, 0) << endl;
	while(grid[i] < input && i < n)
	{
		i++;

		cout << "Calculation " << i << endl;
		int x,y;
		getCoord(i, x, y);
		cout << "STARTING " << x << ", " << y << " = " << i << endl;
		int result = 0;
		for(int row = -1; row <= 1; row++)
		{
			for(int col = -1; col <= 1; col++)
			{
				cout << x+row << ", " << x+col << " = " << getVal(grid, x+row,y+col) << " " << endl;
				if(row != 0 && col != 0)
					result += getVal(grid, x+row, y+col);
			}
		}
		cout << result << endl;
		setVal(grid, x, y, result);
		printGrid(grid, n);		
	}

	cout << "grid[" << i << "] = " << grid[i] << endl;
}