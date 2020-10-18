// TreeDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*#include <iostream>
#include "Tree.h"
#include "Tree2.h"
#include <string>

using namespace std;

int main() {
    Tree testTree;
    Tree2<string> testTree2;

    testTree.insert("String 1");
    testTree.insert("Thursday");
    testTree.insert("Monday");
    testTree.insert("Friday");
    testTree.insert("Saturday");
    testTree.insert("Anyday");
    testTree.inOrder();
    cout << "Preorder Traversal" << endl;
    testTree.preOrder();

    if (testTree.find("Friday") != nullptr) {
        cout << "Found Friday\n";
    }
    else {
        cout << "Couldn't find Friday\n";
    }
    if (testTree.find("Wednesday") != nullptr) {
        cout << "Found Wednesday\n";
    }
    else {
        cout << "Couldn't find Wednesday\n";
    }

    testTree2.insert("Anyday");
    testTree2.insert("Saturday");
    testTree2.insert("String 1");
    testTree2.insert("Monday");
    testTree2.insert("Friday");
    testTree2.insert("Thursday");
    testTree2.inOrder();
    auto result = testTree2.find("Friday");
    if ( result != nullptr) {
        cout << "Found " << "Friday" << endl;
    }
    else {
        cout << "Couldn't find " << "Friday" << endl;
    }
    if (testTree2.find("Wednesday") != nullptr) {
        cout << "Found Wednesday\n";
    }
    else {
        cout << "Couldn't find Wednesday\n";
    }
    std::cout << "Hello World!\n";

    Tree2<int> intTree;

    intTree.insert(657);
    intTree.insert(23556);
    intTree.insert(-100);
    intTree.insert(256);
    intTree.insert(65536);
    intTree.insert(262144);
    intTree.insert(2);
    intTree.insert(-32768);
    intTree.inOrder();
    return EXIT_SUCCESS;
}*/
