#include "Functions.h"
#include "TreeIterator.h"

#include <string>
#include <queue>
#include <iostream>

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