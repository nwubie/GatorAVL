#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    string ufID;
    Node* left;
    Node* right;
    int height;
    int balanceFactor;
    Node(string name, string ufID) {
        this->name = name;
        this->ufID = ufID;
        this->left = nullptr;
        this->right = nullptr;
    }
    // Returns the current height of the tree
    int getHeight(Node* root) {
    // referenced slide 17 of module 3 trees powerpoint
        // if the tree is empty
        if(root == nullptr)
        {
            return 0;
        }
        else
        {
            // visits each child node
            root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        }
        return root->height;
    }
    // Returns the balance factor of a specific node
    int getBalanceFactor() {
        int leftHeight = 0;
        int rightHeight = 0;
        if(left == nullptr)
            leftHeight = 0;
        else
            leftHeight = left->height;
        if(right == nullptr)
            rightHeight = 0;
        else
            rightHeight = right->height;

        balanceFactor = leftHeight - rightHeight;
        return balanceFactor;
    }
};

class AVLTree {
private:
    Node* root = nullptr;
    // Helper function for the insert() method
    Node* insertHelper(Node* current, string& name, string& ufID) {
    // referenced slide 34 of module 3 trees powerpoint
        // if the current node is empty
        if(current == nullptr)
        {
            return new Node(name, ufID);
        }
        // if the passed in id is less than that of the current node (branch left)
        else if(ufID < current->ufID)
        {
            current->left = insertHelper(current->left, name, ufID);
        }
        // if the passed in id is greater than that of the current node (branch right)
        else
        {
            current->right = insertHelper(current->right, name, ufID);
        }
        // referenced slide 35 of module 4 balanced trees powerpoint
        // find height
        current->height = current->getHeight(current);

        // if tree is right heavy
        if(current->getBalanceFactor() < -1)
        {
            // if tree's right subtree is left heavy
            if(current->right->getBalanceFactor() > 0)
            {
                // perform right left rotation & update height
                current->right = rotateRight(current->right);
                return rotateLeft(current);
            }
            else
            {
                // perform left rotation & update height
                return rotateLeft(current);
            }
        }
        // if tree is left heavy
        else if(current->getBalanceFactor() > 1)
        {
            // if tree's left subtree is right heavy
            if(current->left->getBalanceFactor() < 0)
            {
                // perform left right rotation & update height
                current->left = rotateLeft(current->left);
                return rotateRight(current);
            }
            else
            {
                // perform right rotation & update height
                return rotateRight(current);
            }
        }
        current->height = current->getHeight(current);
        return current;
    }
    // Helper function to perform a left rotation on the tree
    Node* rotateLeft(Node* node) {
    // referenced slide 12 of module 4 balanced trees powerpoint
        Node* grandchild = node->right->left;
        Node* newParent = node->right;
        newParent->left = node;
        node->right = grandchild;

        return newParent;
    }
    // Helper function to perform a right rotation on the tree
    Node* rotateRight(Node* node) {
        // referenced slide 12 of module 4 balanced trees powerpoint
        Node* grandchild = node->left->right;
        Node* newParent = node->left;
        newParent->right = node;
        node->left = grandchild;

        return newParent;
    }
    // Helper function for the removeID() method
    Node* removeIDHelper(Node* current, string& ufID) {
    // referenced slide 38 of module 3 trees powerpoint
        // if the current node is empty
        if(current == nullptr)
        {
            return nullptr;
        }
        // if the passed in node is less than the current node
        if(ufID < current->ufID)
        {
            current->left = removeIDHelper(current->left, ufID);
        }
        // if the passed in node is greater than the current node
        else if (ufID > current->ufID)
        {
            current->right = removeIDHelper(current->right, ufID);
        }
        else
        {
            // if the local root has no children
            if(current->left == nullptr && current->right == nullptr)
            {
                delete current;
                return nullptr;
            }
            else if(current->left == nullptr)
            {
                Node* tempNode = current->right;
                delete current;
                return tempNode;
            }
            else if(current->right == nullptr)
            {
                Node* tempNode = current->left;
                delete current;
                return tempNode;
            }
            else
            {
                if(current->right->left == nullptr)
                {
                    Node* tempNode = current->right;
                    tempNode->left = current->left;
                    delete current;
                    return tempNode;
                }
                else
                {
                    Node* tempNode = findLeftmostInRightSub(current);
                    current->ufID = tempNode->ufID;
                    current->name = tempNode->name;
                    current->right->left = removeIDHelper(current->right->left, tempNode->ufID);
                }
            }
        }
        return current;
    }
    // Helper function used to aid remove() in performing inorder successor
    Node* findLeftmostInRightSub(Node* current){
        Node* tempNode = current->right;
        while(tempNode->left != nullptr)
        {
            tempNode = tempNode->left;
        }
        return tempNode;
    }
    // Helper function for the searchID() method
    Node* searchIDHelper(Node* current, string &ufID) {
    // referenced slide 32 of module 3 trees powerpoint
        // if the current node is empty
        if(current == nullptr)
        {
            return nullptr;
        }
        // if the passed in node has the same id as the current node
        else if(current->ufID == ufID)
        {
            return current;
        }
        // if the passed in id is less than that of the current node (branch left)
        else if(ufID < current->ufID)
        {
            return searchIDHelper(current->left, ufID);
        }
        // if the passed in id is greater than that of the current node (branch right)
        else
        {
            return searchIDHelper(current->right, ufID);
        }
    }
    // Helper function for the searchName() method
    void searchNameHelper(Node* current, string &name, vector<string> &ids) {
    // referenced slide 32 of module 3 trees powerpoint
        // if the current node is empty
        if(current == nullptr)
        {
            return;
        }
        // if the passed in node has the same name as the current node
        else if(current->name == name)
        {
            ids.push_back(current->ufID);
            cout << current->ufID << endl;
        }
        // left branch
        searchNameHelper(current->left, name, ids);
        // right branch
        searchNameHelper(current->right, name, ids);
    }
    // Helper function for the printInorder() method
    void inorderTraversal(Node* current, vector<string> &names) {
    // referenced slide 50 of module 3 trees powerpoint
        // if the tree is empty
        if(current == nullptr)
        {
            return;
        }
        else
        {
            // left node recursive call
            inorderTraversal(current->left, names);
            // pushes names into vector
            names.push_back(current->name);
            // right node recursive call
            inorderTraversal(current->right, names);
        }
    }
    // Helper function for the removeInorder() method
    void removeInorderTraversal(Node* current, vector<Node*> &nodes) {
        // referenced slide 50 of module 3 trees powerpoint
        // if the tree is empty
        if(current == nullptr)
        {
            return;
        }
        else
        {
            // left node recursive call
            removeInorderTraversal(current->left, nodes);
            // pushes nodes into vector
            nodes.push_back(current);
            // right node recursive call
            removeInorderTraversal(current->right, nodes);
        }
    }
    // Helper function for the printPreorder() method
    void preorderTraversal(Node* current, vector<string> &names) {
    // referenced slide 53 of module 3 trees powerpoint
        // if the tree is empty
        if(current == nullptr)
        {
            return;
        }
        else
        {
            // pushes names into vector
            names.push_back(current->name);
            // left node recursive call
            preorderTraversal(current->left, names);
            // right node recursive call
            preorderTraversal(current->right, names);
        }
    }
    // Helper function for the printPostorder() method
    void postorderTraversal(Node* current, vector<string> &names) {
    // referenced slide 55 of module 3 trees powerpoint
        // if the tree is empty
        if(current == nullptr)
        {
            return;
        }
        else
        {
            // left node recursive call
            postorderTraversal(current->left, names);
            // right node recursive call
            postorderTraversal(current->right, names);
            // pushes names into vector
            names.push_back(current->name);
        }
    }
public:
    AVLTree(): root(nullptr) {}
    // Inserts a valid name and ID into the tree as a Node object
    void insert(string name, string ufID) {
        this->root = insertHelper(this->root, name, ufID);
        cout << "successful" << endl;
    }
    // Finds & removes the ID and its associated name from the tree
    void removeID(string ufID) {
        this->root = removeIDHelper(this->root, ufID);
    }
    // Searches for a Gator ID within the tree and prints its associated name
    void searchID(string ufID) {
        Node* matchingID = searchIDHelper(root, ufID);
        // if id was found, prints name
        if(matchingID != nullptr)
        {
            cout << matchingID->name << endl;
        }
        // if id does not exist, print unsuccessful
        else
        {
            cout << "unsuccessful" << endl;
        }
    }
    // Searches for a name within the tree and prints its associated ID(s)
    void searchName(string name) {
        vector<string> ids;
        searchNameHelper(root, name, ids);
        // if the name is not found
        if (ids.empty())
        {
            cout << "unsuccessful" << endl;
        }
    }
    // Prints out a comma seperated inorder traversal of the names in the tree
    void printInorder() {
    // prints the names in the tree using the inorder traversal method
        vector<string> names;
        inorderTraversal(root, names);
        for(unsigned int i = 0; i < names.size(); i++)
        {
            if(i == (names.size() - 1))
            {
                cout << names[i] << endl;
            }
            else
            {
                cout << names[i] << ", ";
            }
        }
    }
    // Prints out a comma seperated preorder traversal of the names in the tree
    void printPreorder() {
        // prints the names in the tree using the inorder traversal method
        vector<string> names;
        preorderTraversal(root, names);
        for(unsigned int i = 0; i < names.size(); i++)
        {
            if(i == (names.size() -1))
            {
                cout << names[i] << endl;
            }
            else
            {
                cout << names[i] << ", ";
            }
        }
    }
    // Prints out a comma seperated postorder traversal of the names in the tree
    void printPostorder() {
        // prints the names in the tree using the inorder traversal method
        vector<string> names;
        postorderTraversal(root, names);
        for(unsigned int i = 0; i < names.size(); i++)
        {
            if(i == (names.size() -1))
            {
                cout << names[i] << endl;
            }
            else
            {
                cout << names[i] << ", ";
            }
        }
    }
    // Prints the number of levels that exist in the tree
    void printLevelCount() {
        cout << root->getHeight(root) << endl;
    }
    // Removes the Nth GatorID from the inorder traversal of the tree
    void removeInorder(int n) {
        vector <Node*> nodes;
        removeInorderTraversal(root, nodes);
        if(n > nodes.size())
        {
            cout << "unsuccessful" << endl;
        }
        else
        {
            cout << "successful" << endl;
            for(int i = 0; i < nodes.size(); i++)
            {
                if(i==n)
                {
                    removeID(nodes[i]->ufID);
                }
            }
        }
    }
};