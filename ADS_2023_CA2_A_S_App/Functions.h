#pragma once

#include <string>

#include "Tree.h"

using namespace std;

int countItemsInFolder(Tree<string>* folderNode);

size_t calculateFolderMemoryUsage(Tree<string>* folderNode);

void pruneEmptyFolders(Tree<string>* parentNode);

Tree<string>* findFileOrFolder(Tree<string>* currentNode, const string& filename, string& path);

void displayFolderContents(Tree<string>* folderNode);

size_t calculateFolderMemoryUsageRecursive(Tree<string>* folderNode);

void displayFolderContentsRecursive(Tree<string>* folderNode);