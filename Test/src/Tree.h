#ifndef __TREE_H__
#define __TREE_H__

#include <memory>   // for shared_ptr and weak_ptr
#include <string>
#include <iostream>

using namespace std;

class Tree {
	struct Node {
		string datum;
		shared_ptr<Node> left = nullptr, right = nullptr;
		weak_ptr<Node> parent;
	};

protected:
	shared_ptr<Node> root;
	void inOrderTraversal(ostream& ostr, shared_ptr<Node> node);
	void preOrderTraversal(ostream& ostr, shared_ptr<Node> node);
public:
	Tree() { root = nullptr;  }

	void insert(string value);
	bool isEmpty() { return root == nullptr; }
	void inOrder();
	void preOrder();
	shared_ptr<Node> find(string value);
};

#endif
