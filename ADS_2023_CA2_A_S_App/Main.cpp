#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

#include "DList.h"
#include "Tree.h"
#include "XMLValidation.h"

using namespace std;

int main() {
    // Provide the path to your XML file
    string filename = "XML.xml";
    // Load XML data into a tree
    Tree<string>* filesystemTree = loadXmlData(filename);
    // Print the tree structure
    printTree(filesystemTree);

    return 0;
}