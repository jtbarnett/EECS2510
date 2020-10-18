#include <string>
using namespace std;

class BST {
public:
    struct Node {
        string key;
        Node *left, *right, *parent;
    };
    Node *root;
    BST () { root = nullptr; }
    bool isEmpty () { return root == nullptr; }

    bool contains (string value) {
    	if(isEmpty()) {
    		return false;
    	}
    	Node *current = root;
    	while (current != nullptr) {
    		if (current->key == value) {
    			return true;
    		}
    		else if (current->key < value) {
    			current = current->right;
    		}
    		else {
    			current = current->left;
    		}
    	}
    	return false;
    }

    int height (Node *inputNode) {
    	if (isEmpty() || (root->left == nullptr && root->right == nullptr)) {
    		return 0;
    	} else {
    		return max(height(inputNode->left), height(inputNode->right)) + 1;
    	}
    }

};
