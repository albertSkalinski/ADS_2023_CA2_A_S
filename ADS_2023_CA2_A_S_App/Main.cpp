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
    string filename = "XML.xml";

    Tree<string>* filesystemTree = loadXmlData(filename);

    printTree(filesystemTree);
    cout << endl;

    //Stage 2 a.
    int totalItems = countAllItems(filesystemTree);
    cout << "Total number of items in the tree: " << totalItems << endl;
    cout << endl;

    //Stage 2 b.
    countBFS(filesystemTree);

    //Stage 2 c.
    pruneEmptyFolders(filesystemTree);

    //Stage 2 d.
    cout << endl;
    cout << "Finding a specific file/folder: " << endl;
    string target = "pic1.jpg";
    vector<string> path = findFileOrFolder(filesystemTree, target);
    
    cout << "Path for '" << target << "': ";
    for (const auto& item : path) {
        std::cout << item << "/";
    }
    cout << endl;
    cout << endl;

    //Stage 2 e.
    string targetFolder = "Downloads";
    displayFolderContents(filesystemTree, targetFolder);

    return 0;
}