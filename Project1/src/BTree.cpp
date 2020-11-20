// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 1

#include "BTree.h"

Node::Node(int t, bool leafValue, int a) {
	tValue = t;
    leaf = leafValue;
    keys = new string[2*tValue-1];
    childPointers = new Node *[2*tValue];
    numberOfKeys = 0;
    address = a;

    int i;
    for (i = 0; i < 2*tValue; i++) {
    	childPointers[i] = NULL;
    }
}

void Node::insertNonFull(string inputKey, BTree* tree) {
    int i = numberOfKeys - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > inputKey) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = inputKey;
        numberOfKeys = numberOfKeys + 1;
    } else {
        while (i >= 0 && keys[i] > inputKey) {
            i--;
        }
        tree->treeDisk.readBlock(childPointers[i + 1]->address);
        if (childPointers[i + 1]->numberOfKeys == 2 * tValue - 1) {
            splitChild(i + 1, childPointers[i + 1], tree);
            if (keys[i + 1] < inputKey) {
                i++;
            }
        }
        childPointers[i+1]->insertNonFull(inputKey, tree);
    }
}

void Node::splitChild(int i, Node *inputNode, BTree* tree) {
	Node *newNode = new Node(inputNode->tValue, inputNode->leaf, tree->addressNumber);
    tree->treeDisk.createBlock(newNode->tValue, newNode->leaf, newNode->address);
    tree->treeDisk.writeBlock(newNode->address, *newNode);
	tree->addressNumber++;
	newNode->numberOfKeys = tValue - 1;

    for (int j = 0; j < tValue - 1; j++) {
    	newNode->keys[j] = inputNode->keys[j + tValue];
    }

    if (inputNode->leaf == false) {
        for (int j = 0; j < tValue; j++) {
        	newNode->childPointers[j] = inputNode->childPointers[j + tValue];
        }
    }

    inputNode->numberOfKeys = tValue - 1;

    for (int j = numberOfKeys; j >= i + 1; j--) {
    	childPointers[j + 1] = childPointers[j];
    }

    childPointers[i + 1] = newNode;

    tree->treeDisk.createBlock(childPointers[i + 1]->tValue, childPointers[i + 1]->leaf, childPointers[i + 1]->address);
    tree->treeDisk.writeBlock(childPointers[i + 1]->address, *childPointers[i + 1]);

    tree->treeDisk.createBlock(inputNode->tValue, inputNode->leaf, inputNode->address);
    tree->treeDisk.writeBlock(inputNode->address, *inputNode);

    for (int j = numberOfKeys - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }

    keys[i] = inputNode->keys[tValue - 1];

    numberOfKeys = numberOfKeys + 1;
}

void Node::lookup(string inputKey, BTree* tree) {
    int i = 0;
    while (i < numberOfKeys && inputKey > keys[i]) {
        i++;
    }

    if (keys[i] == inputKey) {
		cout << "the key \"" << keys[i] << "\" was found." << endl;
		return;
    }

    if (leaf == true) {
		cout << "the key \"" << inputKey << "\" could not be found." << endl;
		return;
    }

    tree->treeDisk.readBlock(childPointers[i]->address);
    return childPointers[i]->lookup(inputKey, tree);
}

void Node::dumpTree(Node *inputNode, BTree* tree) {
	string leaftext;
	if (inputNode->leaf) {
		leaftext = "true";
	} else {
		leaftext = "false";
	}

    if (inputNode != NULL) {
        cout << "\nNODE CONTENTS:" <<endl;
        cout << "Is node a leaf: " << leaftext << endl;
        cout << "List of all links:" << endl;
        int index = 0;
        if (childPointers[index] == NULL) {
        	cout << "**this node does not have any links" << endl;
        }
        while (childPointers[index] != NULL) {
        	cout << childPointers[index] << endl;
        	index++;
        }
        cout << "List of all keys:" << endl;
    }

    int i;
    for (i = 0; i < numberOfKeys; i++) {
        cout << keys[i] << endl;
    }

    int j;
    for (j = 0; j < 2*tValue; j++) {
    	if (childPointers[j] != NULL) {
    	    tree->treeDisk.readBlock(childPointers[j]->address);
    		childPointers[j]->dumpTree(childPointers[j], tree);
    	}
    }
}

void Node::remove(string inputKey, BTree* tree) {
    int index = findKeyRemoval(inputKey);

    if (index < numberOfKeys && keys[index] == inputKey) {
        if (leaf) {
            removeFromLeaf(index);
        } else {
            removeFromNonLeaf(index, tree);
        }
    } else {
        if (leaf) {
        	tree->setWasRemoved(false);
            return;
        }
        bool flag = ((index == numberOfKeys) ? true : false );

        tree->treeDisk.readBlock(childPointers[index]->address);
        if (childPointers[index]->numberOfKeys < tValue) {
            fill(index, tree);
        }

        if (flag && index > numberOfKeys) {
            tree->treeDisk.readBlock(childPointers[index - 1]->address);
        	childPointers[index - 1]->remove(inputKey, tree);
        } else {
            tree->treeDisk.readBlock(childPointers[index]->address);
        	childPointers[index]->remove(inputKey, tree);
        }
    }
    return;
}

void Node::removeFromLeaf(int index) {
	if (index == 10) {
		keys[index] = "";
	} else {
	    for (int i = index + 1; i < numberOfKeys; ++i) {
	        keys[i-1] = keys[i];
	    }
	}
    numberOfKeys--;
    return;
}

void Node::removeFromNonLeaf(int index, BTree* tree) {
    string currentKey = keys[index];

    tree->treeDisk.readBlock(childPointers[index]->address);
    if (childPointers[index]->numberOfKeys >= tValue) {
        string predecessor = predecessorKey(index);
        keys[index] = predecessor;
        childPointers[index]->remove(predecessor, tree);
    }
    else if  (childPointers[index + 1]->numberOfKeys >= tValue) {
        tree->treeDisk.readBlock(childPointers[index + 1]->address);
        string successor = successorKey(index);
        keys[index] = successor;
        childPointers[index + 1]->remove(successor, tree);
    } else {
        merge(index, tree);
        childPointers[index]->remove(currentKey, tree);
    }
    return;
}

void Node::borrowFromPrev(int index) {
	Node *childNode = childPointers[index];
	Node *siblingNode = childPointers[index-1];

    for (int i = childNode->numberOfKeys - 1; i >= 0; --i) {
    	childNode->keys[i+1] = childNode->keys[i];
    }
    if (!childNode->leaf) {
        for(int i = childNode->numberOfKeys; i >= 0; --i)
        	childNode->childPointers[i + 1] = childNode->childPointers[i];
    }

    childNode->keys[0] = keys[index - 1];

    if(!childNode->leaf) {
    	childNode->childPointers[0] = siblingNode->childPointers[siblingNode->numberOfKeys];
    }

    keys[index-1] = siblingNode->keys[siblingNode->numberOfKeys - 1];

    childNode->numberOfKeys += 1;
    siblingNode->numberOfKeys -= 1;
    return;
}

void Node::borrowFromNext(int index) {
	Node *childNode = childPointers[index];
	Node *siblingNode = childPointers[index + 1];

	childNode->keys[(childNode->numberOfKeys)] = keys[index];

    if (!(childNode->leaf)) {
    	childNode->childPointers[(childNode->numberOfKeys) + 1] = siblingNode->childPointers[0];
    }
    keys[index] = siblingNode->keys[0];

    for (int i = 1; i < siblingNode->numberOfKeys; ++i) {
    	siblingNode->keys[i-1] = siblingNode->keys[i];
    }

    if (!siblingNode->leaf) {
        for(int i = 1; i <= siblingNode->numberOfKeys; ++i) {
        	siblingNode->childPointers[i-1] = siblingNode->childPointers[i];
        }
    }

    childNode->numberOfKeys += 1;
    siblingNode->numberOfKeys -= 1;
    return;
}

string Node::predecessorKey(int index) {
	Node *currentNode = childPointers[index];
    while (!currentNode->leaf) {
    	currentNode = currentNode->childPointers[currentNode->numberOfKeys];
    }
    return currentNode->keys[currentNode->numberOfKeys - 1];
}

string Node::successorKey(int index) {
	Node *currentNode = childPointers[index + 1];
    while (!currentNode->leaf) {
    	currentNode = currentNode->childPointers[0];
    }
    return currentNode->keys[0];
}

int Node::findKeyRemoval(string inputKey) {
    int index = 0;
    while (index < numberOfKeys && keys[index] < inputKey) {
        ++index;
    }
    return index;
}

void Node::fill(int index, BTree* tree) {
    if (index != 0 && childPointers[index - 1]->numberOfKeys >= tValue) {
        borrowFromPrev(index);
    } else if (index != numberOfKeys && childPointers[index + 1]->numberOfKeys >= tValue) {
        borrowFromNext(index);
    } else {
        if (index != numberOfKeys) {
            merge(index, tree);
        } else {
            merge(index-1, tree);
        }
    }
    return;
}

void Node::merge(int index, BTree* tree) {
	Node *childNode = childPointers[index];
	Node *siblingNode = childPointers[index + 1];

    childNode->keys[tValue - 1] = keys[index];

    for (int i = 0; i < siblingNode->numberOfKeys; ++i) {
    	childNode->keys[i + tValue] = siblingNode->keys[i];
    }

    if (!childNode->leaf) {
        for(int i = 0; i <= siblingNode->numberOfKeys; ++i) {
        	childNode->childPointers[i + tValue] = siblingNode->childPointers[i];
        }
    }

    for (int i = index + 1; i < numberOfKeys; ++i) {
        keys[i - 1] = keys[i];
    }

    for (int i = index + 2; i <= numberOfKeys; ++i) {
    	childPointers[i - 1] = childPointers[i];
    }

    childNode->numberOfKeys += siblingNode->numberOfKeys + 1;
    numberOfKeys--;

    childPointers[index + 1] = NULL;
    tree->addressNumber--;
    return;
}

void BTree::insert(string inputKey) {
	// Root is empty
    if (root == NULL) {
        root = new Node(tValue, true, addressNumber);
        root->keys[0] = inputKey;
        root->numberOfKeys = 1;
        treeDisk.createBlock(root->tValue, root->leaf, root->address);
        treeDisk.writeBlock(root->address, *root);
        addressNumber++;
    } else {
    	// If root is full
        if (root->numberOfKeys == 2*tValue-1) {
            Node *newRoot = new Node(tValue, false, addressNumber);
            treeDisk.createBlock(newRoot->tValue, newRoot->leaf, newRoot->address);
            treeDisk.writeBlock(newRoot->address, *newRoot);
            addressNumber++;

            newRoot->childPointers[0] = root;
            newRoot->splitChild(0, root, this);

            int i = 0;
            if (newRoot->keys[0] < inputKey) {
                i++;
            }
            newRoot->childPointers[i]->insertNonFull(inputKey, this);
            root = newRoot;
        } else {
            root->insertNonFull(inputKey, this);
        }
    }
}

void BTree::lookup(string inputKey) {
	if (root == NULL) {
		cout << "the key \"" << inputKey << "\" could not be found." << endl;
		return;
	} else {
		root->lookup(inputKey, this);
	}
}

void BTree::dumpTree() {
    if (root != NULL) {
    	treeDisk.readBlock(root->address);
    	root->dumpTree(root, this);
    }
}

void BTree::remove(string inputKey) {
    if (root == NULL) {
        wasRemoved = false;
        return;
    }

    wasRemoved = true;
    root->remove(inputKey, this);

    if (root->numberOfKeys == 0) {
    	Node *tempNode = root;
        if (root->leaf) {
            root = NULL;
        } else {
            root = root->childPointers[0];
        }

        delete tempNode;
        addressNumber--;
    }
    return;
}

Node *BTree::getRoot() {
	return root;
}

bool BTree::getWasRemoved() {
	return wasRemoved;
}

