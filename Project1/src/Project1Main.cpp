// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 1

#include <memory>
#include <fstream>
#include <iostream>
#include <string>
#include "operations.h"
#include "BTree.h"
using namespace std;

int main(int argCount, char *argValues[]) {
	// start a new BTree with t = 6
	shared_ptr<BTree> mainBTree(new BTree(2));

	// Load in the initial data for the BTree
	/*ifstream inFile;
	inFile.open("InputData.txt");
	if (!inFile.is_open()){
		cerr << "Error while opening the file InputData.txt." << endl;
		exit(EXIT_FAILURE);
	} else {
		operations::inputBTree(inFile, mainBTree);
		inFile.close();
	}*/

	cout << "The commands to enter are: A or a (Add a key), L or l (Lookup a key), R or r (Remove a key), \n"
			"D or d (Dump the tree), Q or q (quit the program)" << endl;

	string input;
	while (true) {
		cout << "\nEnter a command (A-add, L-lookup, R-remove, D-dump, Q-quit): ";
		getline(cin, input);

		if (input == "A" || input == "a") {
			operations::add(mainBTree);
		} else if (input == "L" || input == "l") {
			operations::lookup(mainBTree);
		} else if (input == "R" || input == "r") {
			operations::remove(mainBTree);
		} else if (input == "D" || input == "d") {
			operations::dump(mainBTree);
		} else if (input == "Q" || input == "q") {
			cout << "You have exited the program." << endl;
			break;
		} else {
			cout << "You have entered an invalid command. Please try again." << endl;
		}
	}
	return EXIT_SUCCESS;
}
