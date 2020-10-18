#include "Tree.h"

void Tree::inOrderTraversal(ostream& ostr, shared_ptr<Node> node) {
	if (node != nullptr) {
		inOrderTraversal(ostr, node->left);
		ostr << node->datum << endl;
		inOrderTraversal(ostr, node->right);
	}
}
void Tree::preOrderTraversal(ostream& ostr, shared_ptr<Node> node) {
	if (node != nullptr) {
		ostr << node->datum << endl;
		inOrderTraversal(ostr, node->left);
		inOrderTraversal(ostr, node->right);
	}
}

void Tree::insert(string value) {
	shared_ptr<Node> nptr(new Node);
	nptr->datum = value;
	if (isEmpty()) {
		root = nptr;
	} else {
		shared_ptr<Node> previous = nullptr;
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


void Tree::inOrder() {
	inOrderTraversal(cout, root);
}

void Tree::preOrder() {
	preOrderTraversal(cout, root);
}

shared_ptr<Tree::Node> Tree::find(string value) {
	shared_ptr<Node> item = nullptr;

	if (isEmpty()) {
		return item;
	}
	shared_ptr<Node> current = root;
	while (current != nullptr) {
		if (current->datum == value) {
			return current;
		}
		else if (current->datum < value) {
			current = current->right;
		}
		else {
			current = current->left;
		}
	}
	return item;
}

