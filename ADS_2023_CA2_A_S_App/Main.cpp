#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

#include "DList.h"
#include "Tree.h"
#include "XMLTreeCreator.h"
#include "Functions.h"

using namespace std;

int main() 
{
    // Provide the path to your XML file
    string filename = "XML.xml";
    // Load XML data into a tree
    Tree<string>* filesystemTree = loadXmlData(filename);
    // Print the tree structure
    printTree(filesystemTree);

    int totalItems = countAllItems(filesystemTree);

    cout << "Total number of items in the tree: " << totalItems << std::endl;

    countBFS(filesystemTree);

    pruneEmptyFolders(filesystemTree);

    string target = "pic1.jpg";
    vector<string> path = findFileOrFolder(filesystemTree, target);

    // Display the path
    cout << "Path for '" << target << "': ";
    for (const auto& item : path) {
        std::cout << item << "/";
    }
    cout << endl;

    string targetFolder = "Documents";
    displayFolderContents(filesystemTree, targetFolder);

    return 0;
}