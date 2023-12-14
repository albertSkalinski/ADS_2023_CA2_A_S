#include "Functions.h"
#include "TreeIterator.h"

#include <string>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

//Stage 2 a.
//I didn't know how to determine the numbers of items in a specified directory so I just counted them all
int countAllItems(Tree<string>* rootNode) 
{
    //Check if there's a root node
    if (rootNode == nullptr) 
    {
        return 0;
    }

    //itemCount = 1, because counting the root node
    int itemCount = 1;

    DListIterator<Tree<string>*> iter = rootNode->children->getIterator();
    while (iter.isValid()) 
    {
        //Using recursion
        itemCount += countAllItems(iter.item());
        //Next child
        iter.advance();
    }

    return itemCount;
}

//Stage 2 b.
int countBFS(Tree<string>* rootNode) 
{
    //Using a queue to store the nodes, based on code from Moodle
    int i = 0;
    queue<Tree<string>*> q;

    q.push(rootNode);
    while (!q.empty()) 
    {
        i += q.front()->data.size();

        DListIterator<Tree<string>*> iter = q.front()->children->getIterator();
        while (iter.isValid()) 
        {
            q.push(iter.item());
            iter.advance();
        }

        q.pop();
    }

    cout << "The amount of memory used: " << i << "B" << endl;

    return i;
}

//Stage 2 c.
void pruneEmptyFolders(Tree<string>* rootNode) 
{
    //I actually don't know if it works or not, there's no empty folders in the tree but it passed its test
    if (rootNode == nullptr) 
    {
        return;
    }

    DListIterator<Tree<string>*> iter = rootNode->children->getIterator();

    while (iter.isValid()) 
    {
        //Recursion again
        pruneEmptyFolders(iter.item());

        //Check if the size is 0 and there's no data assigned to it
        if (iter.item()->children->size() == 0 && iter.item()->data.empty()) 
        {
            //removes the item
            iter = rootNode->children->remove(iter);
        }
        //otherwise, goes to the next child
        else 
        {
            iter.advance();
        }
    }
}

//Stage 2 d.
//Algorithm function
//Uses a vector to store the path
bool findFileOrFolderDFS(Tree<string>* rootNode, const string& target, vector<string>& path) 
{
    if (rootNode == nullptr) 
    {
        return false;
    }
    
    //Saves the root node
    path.push_back(rootNode->getData());

    if (rootNode->getData() == target) 
    {
        return true;
    }

    DListIterator<Tree<string>*> iter = rootNode->children->getIterator();
    while (iter.isValid()) 
    {
        //Recursion again to keep looking for the target
        if (findFileOrFolderDFS(iter.item(), target, path)) 
        {
            return true;
        }
        iter.advance();
    }

    //Goes back if the target is not found
    path.pop_back();

    return false;
}

//Main function of the question
vector<string> findFileOrFolder(Tree<string>* rootNode, const string& target) 
{
    vector<string> path;
    findFileOrFolderDFS(rootNode, target, path);
    return path;
}

//Stage 2 e.
void displayFolderContents(Tree<string>* rootNode, const string& targetFolder) 
{
    if (rootNode == nullptr) 
    {
        return;
    }

    // Check if the current node is the target folder
    if (rootNode->getData() == targetFolder) 
    {
        cout << "Contents of folder '" << targetFolder << "': " << endl;

        DListIterator<Tree<string>*> iter = rootNode->children->getIterator();
        while (iter.isValid()) 
        {
            cout << "  - " << iter.item()->getData();

            // If it's a file, print its size (checks if there's a dot in the name (file extension))
            if (iter.item()->getData().find(".") != string::npos)
            {
                cout << " (Size: " << iter.item()->data.size() << "B)";
            }

            cout << endl;

            iter.advance();
        }

        return;
    }

    //Recursion once again, to keep looking for the target folder
    DListIterator<Tree<string>*> iter = rootNode->children->getIterator();
    while (iter.isValid()) 
    {
        displayFolderContents(iter.item(), targetFolder);
        iter.advance();
    }
}