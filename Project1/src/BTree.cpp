// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 1

#include "BTree.h"

Node::Node(int t, bool leafValue) {
	tValue = t;
    leaf = leafValue;
    keys = new string[2*tValue-1];
    childPointers = new Node *[2*tValue];
    numberOfKeys = 0;

    int i;
    for (i = 0; i < 2*tValue; i++) {
    	childPointers[i] = NULL;
    }
}

void Node::insertNonFull(string inputKey) {
    // Initialize index as index of rightmost element
    int i = numberOfKeys - 1;

    // If this is a leaf node
    if (leaf == true) {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > inputKey) {
            keys[i + 1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i + 1] = inputKey;
        numberOfKeys = numberOfKeys + 1;
    } else { // If this node is not leaf
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > inputKey) {
            i--;
        }
        // See if the found child is full
        if (childPointers[i + 1]->numberOfKeys == 2 * tValue - 1) {
            // If the child is full, then split it
            splitChild(i + 1, childPointers[i + 1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two.  See which of the two
            // is going to have the new key
            if (keys[i + 1] < inputKey) {
                i++;
            }
        }
        childPointers[i+1]->insertNonFull(inputKey);
    }
}

void Node::splitChild(int i, Node *inputNode) {
    // Create a new node which is going to store (t-1) keys of y
	Node *newNode = new Node(inputNode->tValue, inputNode->leaf);
	newNode->numberOfKeys = tValue - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < tValue - 1; j++) {
    	newNode->keys[j] = inputNode->keys[j + tValue];
    }

    // Copy the last t children of y to z
    if (inputNode->leaf == false) {
        for (int j = 0; j < tValue; j++)
        	newNode->childPointers[j] = inputNode->childPointers[j + tValue];
    }

    // Reduce the number of keys in y
    inputNode->numberOfKeys = tValue - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = numberOfKeys; j >= i + 1; j--) {
    	childPointers[j + 1] = childPointers[j];
    }

    // Link the new child to this node
    childPointers[i + 1] = newNode;

    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = numberOfKeys - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }

    // Copy the middle key of y to this node
    keys[i] = inputNode->keys[tValue - 1];

    // Increment count of keys in this node
    numberOfKeys = numberOfKeys + 1;
}

Node *Node::lookup(string inputKey) {
    // Find the first key greater than or equal to inputKey
    int i = 0;
    while (i < numberOfKeys && inputKey > keys[i]) {
        i++;
    }

    // If the found key is equal to inputKey, return this node
    if (keys[i] == inputKey) {
        return this;
    }

    // If key is not found here and this is a leaf node
    if (leaf == true) {
        return NULL;
    }

    // Go to the appropriate child
    return childPointers[i]->lookup(inputKey);
}

void Node::dumpTree(Node *inputNode) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    /*int i;
    for (i = 0; i < numberOfKeys; i++) {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false) {
        	childPointers[i]->dumpTree();
        }
        cout << "Node contents:" <<endl;
        cout << keys[i] << endl;
    }

    // Print the subtree rooted with last child
    if (leaf == false) {
    	childPointers[i]->dumpTree();
    }*/



    if (inputNode != NULL) {
        cout << "Node contents:" <<endl;
    }

    int i;
    for (i = 0; i < numberOfKeys; i++) {
        cout << keys[i] << endl;
    }

    int j;
    for (j = 0; j < 2*tValue; j++) {
    	if (childPointers[j] != NULL) {
    		childPointers[j]->dumpTree(childPointers[j]);
    	}
    }
}

void Node::remove(string inputKey) {
    int index = findKeyRemoval(inputKey);

    // The key to be removed is present in this node
    if (index < numberOfKeys && keys[index] == inputKey) {

        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (leaf) {
            removeFromLeaf(index);
        } else {
            removeFromNonLeaf(index);
        }
    } else {

        // If this node is a leaf node, then the key is not present in tree
        if (leaf) {
            cout << "The key "<< inputKey <<" is does not exist in the tree\n";
            return;
        }

        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ((index == numberOfKeys) ? true : false );

        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (childPointers[index]->numberOfKeys < tValue)
            fill(index);

        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (index-1)th child. Else, we recurse on the
        // (index)th child which now has atleast t keys
        if (flag && index > numberOfKeys)
        	childPointers[index-1]->remove(inputKey);
        else
        	childPointers[index]->remove(inputKey);
    }
    return;
}

void Node::removeFromLeaf(int index) {
    // Move all the keys after the index-th pos one place backward
    for (int i = index + 1; i < numberOfKeys; ++i) {
        keys[i-1] = keys[i];
    }
    numberOfKeys--;
    return;
}

void Node::removeFromNonLeaf(int index) {
    string currentKey = keys[index];

    // If the child that precedes k (C[index]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[index]. Replace k by pred. Recursively delete pred
    // in C[index]
    if (childPointers[index]->numberOfKeys >= tValue) {
        string predecessor = predecessorKey(index);
        keys[index] = predecessor;
        childPointers[index]->remove(predecessor);
    }

    // If the child C[index] has less that t keys, examine C[index+1].
    // If C[index+1] has atleast t keys, find the successor 'succ' of k in
    // the subtree rooted at C[index+1]
    // Replace k by succ
    // Recursively delete succ in C[index+1]
    else if  (childPointers[index + 1]->numberOfKeys >= tValue) {
        string successor = successorKey(index);
        keys[index] = successor;
        childPointers[index + 1]->remove(successor);
    }

    // If both C[index] and C[index+1] has less that t keys,merge k and all of C[index+1]
    // into C[index]
    // Now C[index] contains 2t-1 keys
    // Free C[index+1] and recursively delete k from C[index]
    else {
        merge(index);
        childPointers[index]->remove(currentKey);
    }
    return;
}

void Node::borrowFromPrev(int index) {
	Node *childNode = childPointers[index];
	Node *siblingNode = childPointers[index-1];

    // The last key from C[index-1] goes up to the parent and key[index-1]
    // from parent is inserted as the first key in C[index]. Thus, the  loses
    // sibling one key and child gains one key

    // Moving all key in C[index] one step ahead
    for (int i = childNode->numberOfKeys - 1; i >= 0; --i) {
    	childNode->keys[i+1] = childNode->keys[i];
    }

    // If C[index] is not a leaf, move all its child pointers one step ahead
    if (!childNode->leaf) {
        for(int i = childNode->numberOfKeys; i >= 0; --i)
        	childNode->childPointers[i + 1] = childNode->childPointers[i];
    }

    // Setting child's first key equal to keys[index-1] from the current node
    childNode->keys[0] = keys[index - 1];

    // Moving sibling's last child as C[index]'s first child
    if(!childNode->leaf) {
    	childNode->childPointers[0] = siblingNode->childPointers[siblingNode->numberOfKeys];
    }

    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    keys[index-1] = siblingNode->keys[siblingNode->numberOfKeys - 1];

    childNode->numberOfKeys += 1;
    siblingNode->numberOfKeys -= 1;

    return;
}

void Node::borrowFromNext(int index) {
	Node *childNode = childPointers[index];
	Node *siblingNode = childPointers[index + 1];

    // keys[index] is inserted as the last key in C[index]
	childNode->keys[(childNode->numberOfKeys)] = keys[index];

    // Sibling's first child is inserted as the last child
    // into C[index]
    if (!(childNode->leaf)) {
    	childNode->childPointers[(childNode->numberOfKeys) + 1] = siblingNode->childPointers[0];
    }

    //The first key from sibling is inserted into keys[index]
    keys[index] = siblingNode->keys[0];

    // Moving all keys in sibling one step behind
    for (int i = 1; i < siblingNode->numberOfKeys; ++i) {
    	siblingNode->keys[i-1] = siblingNode->keys[i];
    }

    // Moving the child pointers one step behind
    if (!siblingNode->leaf) {
        for(int i = 1; i <= siblingNode->numberOfKeys; ++i) {
        	siblingNode->childPointers[i-1] = siblingNode->childPointers[i];
        }
    }
    // Increasing and decreasing the key count of C[index] and C[index+1]
    // respectively
    childNode->numberOfKeys += 1;
    siblingNode->numberOfKeys -= 1;

    return;
}

string Node::predecessorKey(int index) {
    // Keep moving to the right most node until we reach a leaf
	Node *currentNode = childPointers[index];
    while (!currentNode->leaf) {
    	currentNode = currentNode->childPointers[currentNode->numberOfKeys];
    }
    // Return the last key of the leaf
    return currentNode->keys[currentNode->numberOfKeys - 1];
}

string Node::successorKey(int index) {
    // Keep moving the left most node starting from C[index+1] until we reach a leaf
	Node *currentNode = childPointers[index + 1];
    while (!currentNode->leaf) {
    	currentNode = currentNode->childPointers[0];
    }

    // Return the first key of the leaf
    return currentNode->keys[0];
}

int Node::findKeyRemoval(string inputKey) {
    int index = 0;
    while (index < numberOfKeys && keys[index] < inputKey) {
        ++index;
    }
    return index;
}

void Node::fill(int index) {
    // If the previous child(C[index-1]) has more than t-1 keys, borrow a key
    // from that child
    if (index != 0 && childPointers[index - 1]->numberOfKeys >= tValue) {
        borrowFromPrev(index);
    }

    // If the next child(C[index+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (index != numberOfKeys && childPointers[index + 1]->numberOfKeys >= tValue) {
        borrowFromNext(index);
    }

    // Merge C[index] with its sibling
    // If C[index] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else {
        if (index != numberOfKeys) {
            merge(index);
        } else {
            merge(index - 1);
        }
    }
    return;
}

void Node::merge(int index) {
	Node *childNode = childPointers[index];
	Node *siblingNode = childPointers[index + 1];

    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[index]
    childNode->keys[tValue - 1] = keys[index];

    // Copying the keys from C[index+1] to C[index] at the end
    for (int i = 0; i < siblingNode->numberOfKeys; ++i) {
    	childNode->keys[i + tValue] = siblingNode->keys[i];
    }

    // Copying the child pointers from C[index+1] to C[index]
    if (!childNode->leaf) {
        for(int i = 0; i <= siblingNode->numberOfKeys; ++i) {
        	childNode->childPointers[i + tValue] = siblingNode->childPointers[i];
        }
    }

    // Moving all keys after index in the current node one step before -
    // to fill the gap created by moving keys[index] to C[index]
    for (int i = index + 1; i < numberOfKeys; ++i) {
        keys[i - 1] = keys[i];
    }

    // Moving the child pointers after (index+1) in the current node one
    // step before
    for (int i = index + 2; i <= numberOfKeys; ++i) {
    	childPointers[i - 1] = childPointers[i];
    }

    // Updating the key count of child and the current node
    childNode->numberOfKeys += siblingNode->numberOfKeys + 1;
    numberOfKeys--;

    delete(siblingNode);
    return;
}

void BTree::insert(string inputKey) {
    if (root == NULL) {
        root = new Node(tValue, true);
        root->keys[0] = inputKey;
        root->numberOfKeys = 1;
    } else {
        // If root is full, then tree grows in height
        if (root->numberOfKeys == 2*tValue-1) {
            Node *newRoot = new Node(tValue, false);

            // Make old root as child of new root
            newRoot->childPointers[0] = root;

            // Split the old root and move 1 key to the new root
            newRoot->splitChild(0, root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (newRoot->keys[0] < inputKey) {
                i++;
            }
            newRoot->childPointers[i]->insertNonFull(inputKey);
            root = newRoot;
        } else { // If root is not full, call insertNonFull for root
            root->insertNonFull(inputKey);
        }
    }
}

Node *BTree::lookup(string inputKey) {
    return (root == NULL) ? NULL : root->lookup(inputKey);
}

void BTree::dumpTree() {
    if (root != NULL) root->dumpTree(root);
}

void BTree::remove(string inputKey) {
    if (!root) {
        wasRemoved = false;
        return;
    }

    wasRemoved = true;
    root->remove(inputKey);

    // If the root node has 0 keys, make its first child as the new root
    // if it has a child, otherwise set root as NULL
    if (root->numberOfKeys == 0) {
    	Node *tempNode = root;
        if (root->leaf) {
            root = NULL;
        } else {
            root = root->childPointers[0];
        }

        // free old root
        delete(tempNode);
    }
    return;
}

Node *BTree::getRoot() {
	return root;
}

bool BTree::getWasRemoved() {
	return wasRemoved;
}

