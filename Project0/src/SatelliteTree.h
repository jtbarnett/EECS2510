// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 0

#ifndef __SATELLITETREE_H__
#define __SATELLITETREE_H__

#include <memory>
#include <string>
#include <iostream>
#include <fstream>
#include "Satellite.h"
using namespace std;

class SatelliteTree {
public:
	struct Node {
		Satellite satellite;
		shared_ptr<Node> left = nullptr, right = nullptr, parent = nullptr;
	};

	shared_ptr<Node> root;
	void inOrderTraversal(ostream& ostr, shared_ptr<Node> node);
	void inOrderTraversalFileStream(ofstream& ostr, shared_ptr<Node> node);
	void preOrderTraversal(ofstream& ostr, shared_ptr<Node> node);

	SatelliteTree() { root = nullptr;  }

	void deleteRoot();
	void deleteTree(shared_ptr<Node> node);
	void transplant(shared_ptr<Node> nodeToDelete, shared_ptr<Node> nodeChild);
	void deleteNode(shared_ptr<Node> nodeToDelete);
	void insert(Satellite inputSatellite);
	bool isEmpty() { return root == nullptr; }
	void inOrder();
	void preOrder(ofstream& ostr);
	shared_ptr<Node> find(string inputName);
	shared_ptr<Node> treeMinimum(shared_ptr<Node> node);
};

#endif
