#include <iostream>
using namespace std;

int main()
{
	int b,c,d,e,f,h;
	h = 0;
	b = 81 * 100 + 100000;
	c = b + 17000;
	while(b <= c) {
		f = 1;
		for(d = 2; d < b; d++)
		{
			if(b % d == 0)
				f = 0;
			/*
			for(e = 2; e < b; e++)
			{
				if(d*e == b)
					f = 0;


			}*/
		}

		if(f == 0)
			h++;

		b += 17;
		cout << "b " << b << endl; 
	}

	cout << "h " << h << endl;
}