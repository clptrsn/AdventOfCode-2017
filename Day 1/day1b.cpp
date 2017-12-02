#include <iostream>
#include <string>

using namespace std;

int main() {
	string input;
	cin >> input;

	int n = input.length();
	int sum = 0;

	for(int i = 0; i < n; i++) {
		if(input[i] == input[(i+n/2)%n]) {
			sum += input[i] - '0';
		}
	}

	cout << sum << endl;
}