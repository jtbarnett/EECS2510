// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 0

#include "SatelliteTree.h"

void SatelliteTree::inOrderTraversal(ostream& ostr, shared_ptr<Node> node) {
	if (node != nullptr) {
		inOrderTraversal(ostr, node->left);
		ostr << node->satellite.name << endl;
		inOrderTraversal(ostr, node->right);
	}
}

void SatelliteTree::inOrderTraversalFileStream(ofstream& ostr, shared_ptr<Node> node) {
	if (node != nullptr) {
		inOrderTraversalFileStream(ostr, node->left);
		ostr << node->satellite.name << endl;
		ostr << node->satellite.country << endl;
		ostr << node->satellite.nameOfOperator << endl;
		ostr << node->satellite.type << endl;
		ostr << node->satellite.purpose << endl;
		ostr << node->satellite.detailedPurpose << endl;
		ostr << node->satellite.orbitType << endl;
		ostr << node->satellite.apogee << endl;
		ostr << node->satellite.perigee << endl;
		ostr << node->satellite.period << endl;
		ostr << node->satellite.date << endl;
		ostr << node->satellite.expectedLifetime << endl;
		ostr << node->satellite.launchSite << endl;
		ostr << node->satellite.launchVehicle << endl;
		ostr << node->satellite.noradNumber << endl;
		inOrderTraversalFileStream(ostr, node->right);
	}
}

void SatelliteTree::preOrderTraversal(ofstream& ostr, shared_ptr<Node> node) {
	if (node != nullptr) {
		ostr << node->satellite.name << endl;
		ostr << node->satellite.country << endl;
		ostr << node->satellite.nameOfOperator << endl;
		ostr << node->satellite.type << endl;
		ostr << node->satellite.purpose << endl;
		ostr << node->satellite.detailedPurpose << endl;
		ostr << node->satellite.orbitType << endl;
		ostr << node->satellite.apogee << endl;
		ostr << node->satellite.perigee << endl;
		ostr << node->satellite.period << endl;
		ostr << node->satellite.date << endl;
		ostr << node->satellite.expectedLifetime << endl;
		ostr << node->satellite.launchSite << endl;
		ostr << node->satellite.launchVehicle << endl;
		ostr << node->satellite.noradNumber << endl;
		inOrderTraversalFileStream(ostr, node->left);
		inOrderTraversalFileStream(ostr, node->right);
	}
}

void SatelliteTree::inOrder() {
	inOrderTraversal(cout, root);
}

void SatelliteTree::preOrder(ofstream& ostr) {
	preOrderTraversal(ostr, root);
}

void SatelliteTree::insert(Satellite inputSatellite) {
	shared_ptr<Node> nodeptr(new Node);
	nodeptr->satellite = inputSatellite;
	if (isEmpty()) {
		root = nodeptr;
	} else {
		shared_ptr<Node> previous = nullptr;
		shared_ptr<Node> current = root;
		while (current != nullptr) {
			previous = current;
			if (current->satellite.name > inputSatellite.name) { //  go left
				current = current->left;
			}
			else {
				current = current->right;
			}

		}
		// current == nullptr, previous points at the last item.
		if (previous->satellite.name > inputSatellite.name) {
			previous->left = nodeptr;
		}
		else {
			previous->right = nodeptr;
		}
		nodeptr->parent = previous;
		previous = nullptr;
	}
	nodeptr = nullptr;
}

shared_ptr<SatelliteTree::Node> SatelliteTree::find(string inputName) {
	shared_ptr<Node> nullNode = nullptr;

	if (isEmpty()) {
		return nullNode;
	}
	shared_ptr<Node> current = root;
	while (current != nullptr) {
		if (current->satellite.name == inputName) {
			return current;
		}
		else if (current->satellite.name < inputName) {
			current = current->right;
		}
		else {
			current = current->left;
		}
	}
	return nullNode;
}

shared_ptr<SatelliteTree::Node> SatelliteTree::treeMinimum(shared_ptr<Node> node) {
	while (node->left != nullptr) {
		node = node->left;
	}
	return node;
}

void SatelliteTree::transplant(shared_ptr<Node> nodeToDelete, shared_ptr<Node> childNode) {
	if (nodeToDelete->parent == nullptr) {
		root = childNode;
	} else if (nodeToDelete == nodeToDelete->parent->left) {
		nodeToDelete->parent->left = childNode;
	} else {
		nodeToDelete->parent->right = childNode;
	}
	if (childNode != nullptr) {
		childNode->parent = nodeToDelete->parent;
	}
}

void SatelliteTree::deleteNode(shared_ptr<Node> nodeToDelete) {
	if (nodeToDelete->left == nullptr) {
		transplant(nodeToDelete, nodeToDelete->right);
	} else if (nodeToDelete->right == nullptr) {
		transplant(nodeToDelete, nodeToDelete->left);
	} else {
		shared_ptr<Node> successor = treeMinimum(nodeToDelete->right);
		if (successor->parent != nodeToDelete) {
			transplant(successor, successor->right);
			successor->right = nodeToDelete->right;
			successor->right->parent = successor;
		}
		transplant(nodeToDelete, successor);
		successor->left = nodeToDelete->left;
		successor->left->parent = successor;
	}
}

void SatelliteTree::deleteTree(shared_ptr<Node> node) {
	if (node != nullptr) {
		deleteTree(node->left);
		deleteTree(node->right);
		if (node->left != nullptr) {
			node->left = nullptr;
		}
		if (node->right != nullptr) {
			node->right = nullptr;
		}
		node = nullptr;
	}
}

void SatelliteTree::deleteRoot() {
	if (root != nullptr) {
		if (root->left != nullptr) {
			root->left = nullptr;
		}
		if (root->right != nullptr) {
			root->right = nullptr;
		}
		root = nullptr;
	}
}
