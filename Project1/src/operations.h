// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 1

#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

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

	void add(shared_ptr<BTree> mainBTree) {
		string input;
		cout << "enter the key you would like to add: ";
		getline(cin, input);
		mainBTree->insert(input);
		cout << "you have successfully added the key \"" << input << "\"." << endl;
	}

	void lookup(shared_ptr<BTree> mainBTree) {
		string input;
		cout << "enter the key you would like to lookup: ";
		getline(cin, input);
		Node *lookupNode = mainBTree->lookup(input);
		if (lookupNode == NULL) {
			cout << "the key \"" << input << "\" could not be found." << endl;
		} else {
			cout << "the key \"" << input << "\" was found." << endl;
		}
	}

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

	void dump(shared_ptr<BTree> mainBTree) {
		if (mainBTree->getRoot() != NULL) {
			cout << "the dump of the tree is below:" << endl;
			mainBTree->dumpTree();
		} else {
			cout << "the tree is empty, there was nothing to dump." << endl;
		}
	}
}

#endif

