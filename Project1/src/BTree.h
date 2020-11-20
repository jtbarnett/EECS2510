// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 1

#ifndef __BTREE_H__
#define __BTREE_H__

#include <iostream>
#include <string>
#include "Disk.h"
using namespace std;

class BTree;
class Node;

class Node {
    string *keys;
    int tValue;
    Node **childPointers;
    int numberOfKeys;
    bool leaf;
    int address;
public:
    // Set to to 6 in this case
    Node(int t=2, bool leaf=true, int a=0);
    friend class BTree;

    // All functions of the Node class
    void insertNonFull(string inputKey, BTree* tree);
    void splitChild(int index, Node *inputNode, BTree* tree);
    void lookup(string inputKey, BTree* tree);
    void dumpTree(Node *inputNode, BTree* tree);
    void remove(string inputKey, BTree* tree);
    // Remove the key in index position in leaf node
    void removeFromLeaf(int index);
    // Remove the key present in index position in non-leaf node
    void removeFromNonLeaf(int index, BTree* tree);
    // Borrow a key from the childPointers[index-1] node and place in childPointers[index] node
    void borrowFromPrev(int index);
    // Borrow a key from the childPointers[index+1] node and place in childPointers[index] node
    void borrowFromNext(int index);
    // Get predecessor of the key where key is in the index position in node
    string predecessorKey(int index);
    // Get the successor of the key where key is in the index position in node
    string successorKey(int index);
    // Returns the index of the first key that is greater or equal to inputKey
    int findKeyRemoval(string inputKey);
    // Fill the child node in the index in the childPointers[] array if child has less than t-1 keys
    void fill(int index, BTree* tree);
    // Merge index child of node with (index+1) child of node
    void merge(int index, BTree* tree);
};

class BTree {
private:
	Node *root;
    int tValue;
    // Used to let user know if key was removed by printing statement in operations.h file
    bool wasRemoved;
public:
	Disk<Node> treeDisk;
	int addressNumber;
    BTree(int t) {
        root = NULL;
        tValue = t;
        wasRemoved = false;
        addressNumber = 0;
    }
    void insert(string inputKey);
    void lookup(string inputKey);
    void dumpTree();
    void remove(string inputKey);
    Node *getRoot();
    bool getWasRemoved();
    void setWasRemoved(bool input) {
    	wasRemoved = input;
    }
};

#endif
