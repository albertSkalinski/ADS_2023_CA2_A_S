#pragma once

#include "Tree.h"
#include <string>
#include <vector>


using namespace std;

int countAllItems(Tree<string>* rootNode);
int countBFS(Tree<string>* tree);
void pruneEmptyFolders(Tree<string>* root);
bool findFileOrFolderDFS(Tree<string>* node, const string& target, std::vector<string>& path);
vector<string> findFileOrFolder(Tree<string>* root, const string& target);
void displayFolderContents(Tree<string>* node, const string& targetFolder);