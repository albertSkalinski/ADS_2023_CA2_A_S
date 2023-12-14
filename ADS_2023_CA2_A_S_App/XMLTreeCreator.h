#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include "DList.h"
#include "Tree.h"

using namespace std;

//Stage 1
//Trimming any whitespaces from a string
string trim(const string& str);

//Loading XML into a tree data structure
Tree<string>* loadXmlData(const string& filename);

//Printing out the tree data structure
void printTree(Tree<string>* node, int depth = 0);