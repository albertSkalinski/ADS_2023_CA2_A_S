#pragma once

#include "Tree.h"
#include <string>
#include <vector>


using namespace std;

//Stage 2 a.
int countAllItems(Tree<string>* rootNode);

//Stage 2 b.
int countBFS(Tree<string>* tree);

//Stage 2 c.
void pruneEmptyFolders(Tree<string>* root);

//Stage 2 d.
bool findFileOrFolderDFS(Tree<string>* node, const string& target, vector<string>& path);
vector<string> findFileOrFolder(Tree<string>* root, const string& target);

//Stage 2 e.
void displayFolderContents(Tree<string>* node, const string& targetFolder);