#include "Functions.h"
#include "TreeIterator.h"

#include <string>

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