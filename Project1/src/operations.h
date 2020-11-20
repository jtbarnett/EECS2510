// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 1

#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <fstream>
#include <iostream>
#include <string>
#include "BTree.h"
using namespace std;

/*
 * This file is used for operations such as adding, looking up,
 * removing, and dumping the BTree data
 */
namespace operations {
	void add(shared_ptr<BTree> mainBTree);
	void lookup(shared_ptr<BTree> mainBTree);
	void remove(shared_ptr<BTree> mainBTree);
	void dump(shared_ptr<BTree> mainBTree);
	void inputBTree(ifstream& inFile, shared_ptr<BTree> mainBTree);

	// Add a key
	void add(shared_ptr<BTree> mainBTree) {
		string input;
		cout << "enter the key you would like to add: ";
		getline(cin, input);
		mainBTree->insert(input);
		cout << "you have successfully added the key \"" << input << "\"." << endl;
	}

	// Lookup a key
	void lookup(shared_ptr<BTree> mainBTree) {
		string input;
		cout << "enter the key you would like to lookup: ";
		getline(cin, input);
		// string returnString = mainBTree->lookup(input);
		mainBTree->lookup(input);
		/*if (returnString == input) {
			cout << "the key \"" << input << "\" was found." << endl;
		} else {
			cout << "the key \"" << input << "\" could not be found." << endl;
		}*/
	}

	// Remove a key
	void remove(shared_ptr<BTree> mainBTree) {
		string input;
		cout << "enter the key you would like to remove: ";
		getline(cin, input);
		mainBTree->remove(input);
		if (mainBTree->getWasRemoved()) {
			cout << "you have successfully removed the key \"" << input << "\"." << endl;
		} else {
			cout << "the key \"" << input << "\" was not removed beacause it could not be found." << endl;
		}
	}

	// Dump the tree
	void dump(shared_ptr<BTree> mainBTree) {
		if (mainBTree->getRoot() != NULL) {
			cout << "the dump of the tree is below:" << endl;
			mainBTree->dumpTree();
		} else {
			cout << "the tree is empty, there was nothing to dump." << endl;
		}
	}

	// Input the data from InputData.txt file
	void inputBTree(ifstream& inFile, shared_ptr<BTree> mainBTree) {
		string input;
		while (inFile.good() && !inFile.eof()) {
			if (inFile.bad() || inFile.eof()) {
				break;
			}
			getline(inFile, input);
			mainBTree->insert(input);
		}
	}
}

#endif

