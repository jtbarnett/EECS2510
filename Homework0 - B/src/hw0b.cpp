// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Homework 0 - Part B

#include <iostream>
using namespace std;

int main(int argCount, char *argValues[]) {
	int primeInput;
	bool inputIsPrime = true;

	cout << "Please enter an integer: ";
	cin >> primeInput;
	int maxTarget = primeInput / 2;

	if (primeInput <= 1) {
		inputIsPrime = false;
	} else {
		for (int i = 2; i <= maxTarget; i++) {
			if (primeInput % i == 0) {
				inputIsPrime = false;
			}
		}
	}

	if (inputIsPrime) {
		cout << primeInput << " is a prime number";
	} else {
		cout << primeInput << " is not a prime number";
	}

	return EXIT_SUCCESS;
}
