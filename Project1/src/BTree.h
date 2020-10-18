// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 1

#ifndef __BTREE_H__
#define __BTREE_H__

#include <iostream>
#include <string>
using namespace std;

class Node {
    string *keys;
    int tValue;
    Node **childPointers;
    int numberOfKeys;
    bool leaf;
public:
    Node(int t, bool leaf);
    friend class BTree;

    void insertNonFull(string inputKey);
    void splitChild(int index, Node *inputNode);
    Node *lookup(string inputKey);
    void dumpTree(Node *inputNode);
    void remove(string inputKey);

    // A function to remove the key present in idx-th position in
    // this node which is a leaf
    void removeFromLeaf(int index);

    // A function to remove the key present in idx-th position in
    // this node which is a non-leaf node
    void removeFromNonLeaf(int index);

    // A function to borrow a key from the C[idx-1]-th node and place
    // it in C[idx]th node
    void borrowFromPrev(int index);

    // A function to borrow a key from the C[idx+1]-th node and place it
    // in C[idx]th node
    void borrowFromNext(int index);

    // A function to get the predecessor of the key- where the key
    // is present in the idx-th position in the node
    string predecessorKey(int index);

    // A function to get the successor of the key- where the key
    // is present in the idx-th position in the node
    string successorKey(int index);

    // A function that returns the index of the first key that is greater
    // or equal to k
    int findKeyRemoval(string inputKey);

    // A function to fill up the child node present in the idx-th
    // position in the C[] array if that child has less than t-1 keys
    void fill(int index);

    // A function to merge idx-th child of the node with (idx+1)th child of
    // the node
    void merge(int index);
};

class BTree {
private:
	Node *root;
    int tValue;
    bool wasRemoved;
public:
    BTree(int t) {
        root = NULL;
        tValue = t;
        wasRemoved = false;
    }
    void insert(string inputKey);
    Node *lookup(string inputKey);
    void dumpTree();
    void remove(string inputKey);
    Node *getRoot();
    bool getWasRemoved();
};

#endif
