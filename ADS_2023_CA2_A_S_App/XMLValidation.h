#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include "DList.h"
#include "Tree.h"

using namespace std;

// Function to trim leading and trailing whitespaces from a string
string trim(const string& str);

// Function to load XML data into a tree
Tree<string>* loadXmlData(const string& filename);

// Function to print the tree structure
void printTree(Tree<string>* node, int depth = 0);