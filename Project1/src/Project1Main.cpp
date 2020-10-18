// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 1

#include <memory>
#include <iostream>
#include <string>
#include "operations.h"
#include "BTree.h"
using namespace std;

int main(int argCount, char *argValues[]) {
	// start a new BTree with t = 6
	shared_ptr<BTree> mainBTree(new BTree(6));

	mainBTree->insert("yes");
	mainBTree->insert("no");
	mainBTree->insert("e");
	mainBTree->insert("w");
	mainBTree->insert("t");
	mainBTree->insert("a");
	mainBTree->insert("y");
	mainBTree->insert("f");
	mainBTree->insert("i");
	mainBTree->insert("p");
	mainBTree->insert("m");
	mainBTree->insert("q");

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

    /*
    myBTree->insert("yes");
    myBTree->insert("no");
    myBTree->insert("e");
    myBTree->insert("w");
    myBTree->insert("t");
    myBTree->insert("a");
    myBTree->insert("y");
    myBTree->insert("f");
    myBTree->insert("i");
    myBTree->insert("p");
    myBTree->insert("m");
    */

	return EXIT_SUCCESS;
}
