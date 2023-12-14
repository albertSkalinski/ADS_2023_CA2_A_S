#include "Functions.h"
#include "TreeIterator.h"

#include <string>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

int countAllItems(Tree<string>* rootNode) {
    if (rootNode == nullptr) {
        return 0;
    }

    int itemCount = 1; // Count the root node itself

    DListIterator<Tree<string>*> iter = rootNode->children->getIterator();
    while (iter.isValid()) {
        itemCount += countAllItems(iter.item()); // Recursively count items in the child subtree
        iter.advance(); // Move to the next child
    }

    return itemCount;
}

int countBFS(Tree<string>* tree) {
    int i = 0;
    queue<Tree<string>*> q;

    q.push(tree);
    while (!q.empty()) {
        // Assuming each file has a length attribute
        i += q.front()->data.size();

        // Enqueue children for further traversal
        DListIterator<Tree<string>*> iter = q.front()->children->getIterator();
        while (iter.isValid()) {
            q.push(iter.item());
            iter.advance();
        }

        q.pop();
    }

    cout << "This is the amount of memory used: " << i << " B" << endl;

    return i;
}

// Function to prune the tree and remove empty folders
void pruneEmptyFolders(Tree<string>* root) {
    if (root == nullptr) {
        return;
    }

    DListIterator<Tree<string>*> iter = root->children->getIterator();
    while (iter.isValid()) {
        pruneEmptyFolders(iter.item()); // Recursively prune children

        if (iter.item()->children->size() == 0 && iter.item()->data.empty()) {
            iter = root->children->remove(iter); // Remove empty folder
        }
        else {
            iter.advance();
        }
    }
}

bool findFileOrFolderDFS(Tree<string>* node, const string& target, std::vector<string>& path) {
    if (node == nullptr) {
        return false;
    }

    path.push_back(node->getData());

    if (node->getData() == target) {
        return true;
    }

    DListIterator<Tree<string>*> iter = node->children->getIterator();
    while (iter.isValid()) {
        if (findFileOrFolderDFS(iter.item(), target, path)) {
            return true;
        }
        iter.advance();
    }

    path.pop_back();  // Backtrack if the target is not found in this subtree
    return false;
}

vector<string> findFileOrFolder(Tree<string>* root, const string& target) {
    vector<string> path;
    findFileOrFolderDFS(root, target, path);
    return path;
}