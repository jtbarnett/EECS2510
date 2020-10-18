#ifndef __TREE2_H__   // change the value here since the
#define __TREE2_H__   // filename changed.

/*
 * Templates are completely in the header file.
 * You do NOT want them in a .cpp file!
 */

#include <memory>
#include <string>
#include <iostream>

using namespace std;

template <class T>   // Added a template statement with class info...
class Tree2 {        // Class name changed so I can have both
	struct Node {
		T datum;	 // Data item is now of type T
		shared_ptr<Node> left = nullptr, right = nullptr;
		weak_ptr<Node> parent;
	};

protected:
	shared_ptr<Node> root;
	void inOrderTraversal(ostream& ostr, shared_ptr<Node> node);

public:
	Tree2() { root = nullptr; }  // name change for class

	void insert(T value);        // string replaced with T
	bool isEmpty() { return root == nullptr; }
	void inOrder();
	shared_ptr<Tree2::Node> find(T key);  // string replaced with T
};


template <class T>  // added line
void Tree2<T>::inOrderTraversal(ostream& ostr, shared_ptr<Node> node) {
	if (node != nullptr) {
		inOrderTraversal(ostr, node->left);
		ostr << node->datum << endl;
		inOrderTraversal(ostr, node->right);
	}
}


template <class T>  // added line
void Tree2<T>::insert(T value) {
	shared_ptr<Node> nptr(new Node);
	nptr->datum = value;
	if (isEmpty()) {
		root = nptr;
	}
	else {
		shared_ptr<Node> previous;
		shared_ptr<Node> current = root;
		while (current != nullptr) {
			previous = current;
			if (current->datum > value) { //  go left
				current = current->left;
			}
			else {
				current = current->right;
			}

		}
		// current == nullptr, previous points at the last item.
		if (previous->datum > value) {
			previous->left = nptr;
		}
		else {
			previous->right = nptr;
		}
		nptr->parent = previous;
		previous = nullptr;
	}
	nptr = nullptr;
}


template <class T>   // added line
void Tree2<T>::inOrder() {
	inOrderTraversal(cout, root);
}


template <class T>
shared_ptr<typename Tree2<T>::Node> Tree2<T>::find(T key) {
	shared_ptr<Tree2::Node> current = root;
	while (current != nullptr && current->datum != key) {
		if (key < current->datum) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return shared_ptr<Tree2::Node> (current);
}

#endif
