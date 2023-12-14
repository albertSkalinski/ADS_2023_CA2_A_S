#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>

#include "DList.h"
#include "Tree.h"
#include "XMLTreeCreator.h"

using namespace std;

//Trimming any whitespaces
string trim(const string& str) 
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

//Loading the XML data
Tree<string>* loadXmlData(const string& filename) 
{
    ifstream file(filename);
    if (!file.is_open()) 
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return nullptr;
    }

    stack<Tree<string>*> treeStack;
    Tree<string>* root = nullptr;
    Tree<string>* currentNode = nullptr;

    string line;
    while (getline(file, line)) 
    {
        line = trim(line);

        //Skipping empty lines
        if (line.empty()) 
        {
            continue;
        }

        //Skipping the XML header
        if (line.find("<?xml") != string::npos || line.find("<!DOCTYPE") != string::npos) 
        {
            continue;
        }

        //Initialising the root
        if (line.find("<filesystem>") != string::npos) 
        {
            root = new Tree<string>("filesystem");
            treeStack.push(root);
        }
        else if (line.find("</filesystem>") != string::npos) 
        {
            treeStack.pop();
        }
        else if (line.find("<directory") != string::npos) 
        {
            //Taking the name of the directory
            string name = line.substr(line.find("name=\"") + 6);
            name = name.substr(0, name.find("\""));

            //Creating its node
            Tree<string>* directory = new Tree<string>("directory");
            directory->data = name;

            currentNode = treeStack.top();
            currentNode->children->append(directory);

            treeStack.push(directory);
        }
        else if (line.find("<file") != string::npos) 
        {
            //Getting file's name
            string name = line.substr(line.find("name=\"") + 6);
            name = name.substr(0, name.find("\""));

            // Creating its ndoe
            Tree<string>* fileNode = new Tree<string>("file");
            fileNode->data = name;

            currentNode = treeStack.top();
            currentNode->children->append(fileNode);
        }
    }

    file.close();
    return root;
}

//Printing the tree
void printTree(Tree<string>* node, int depth) 
{
    if (node == nullptr) 
    {
        return;
    }

    for (int i = 0; i < depth; ++i) 
    {
        cout << "  ";
    }

    cout << node->getData() << endl;

    DListIterator<Tree<string>*> iter = node->children->getIterator();
    while (iter.isValid()) 
    {
        printTree(iter.item(), depth + 1);
        iter.advance();
    }
}