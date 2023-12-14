#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>

#include "DList.h"
#include "Tree.h"
#include "XMLTreeCreator.h"

using namespace std;

// Function to trim leading and trailing whitespaces from a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Function to load XML data into a tree
Tree<string>* loadXmlData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        
        cerr << "Error: Unable to open file " << filename << endl;
        return nullptr;
    }

    stack<Tree<string>*> treeStack;
    Tree<string>* root = nullptr;
    Tree<string>* currentNode = nullptr;

    string line;
    while (getline(file, line)) {
        line = trim(line);

        if (line.empty()) {
            continue; // Skip empty lines
        }

        if (line.find("<?xml") != string::npos || line.find("<!DOCTYPE") != string::npos) {
            continue; // Skip XML declaration and DOCTYPE
        }

        if (line.find("<filesystem>") != string::npos) {
            // Initialize the root of the tree
            root = new Tree<string>("filesystem");
            treeStack.push(root);
        }
        else if (line.find("</filesystem>") != string::npos) {
            // Pop the root from the stack
            treeStack.pop();
        }
        else if (line.find("<directory") != string::npos) {
            // Extract directory name
            string name = line.substr(line.find("name=\"") + 6);
            name = name.substr(0, name.find("\""));

            // Create a new directory node
            Tree<string>* directory = new Tree<string>("directory");
            directory->data = name;

            // Add the directory node to the current node
            currentNode = treeStack.top();
            currentNode->children->append(directory);

            // Push the directory node onto the stack
            treeStack.push(directory);
        }
        else if (line.find("<file") != string::npos) {
            // Extract file name
            string name = line.substr(line.find("name=\"") + 6);
            name = name.substr(0, name.find("\""));

            // Create a new file node
            Tree<string>* fileNode = new Tree<string>("file");
            fileNode->data = name;

            // Add the file node to the current node
            currentNode = treeStack.top();
            currentNode->children->append(fileNode);
        }
    }

    file.close();
    return root;
}



// Function to print the tree structure
void printTree(Tree<string>* node, int depth) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < depth; ++i) {
        cout << "  ";
    }

    cout << node->getData() << endl;

    DListIterator<Tree<string>*> iter = node->children->getIterator();
    while (iter.isValid()) {
        printTree(iter.item(), depth + 1);
        iter.advance();
    }
}