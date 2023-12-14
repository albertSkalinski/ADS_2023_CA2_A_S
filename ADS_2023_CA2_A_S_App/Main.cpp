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

//Old main()
//int main() 
//{
//    string filename = "XML.xml";
//
//    Tree<string>* filesystemTree = loadXmlData(filename);
//
//    printTree(filesystemTree);
//    cout << endl;
//
//    //Stage 2 a.
//    int totalItems = countAllItems(filesystemTree);
//    cout << "Total number of items in the tree: " << totalItems << endl;
//    cout << endl;
//
//    //Stage 2 b.
//    countBFS(filesystemTree);
//
//    //Stage 2 c.
//    pruneEmptyFolders(filesystemTree);
//
//    //Stage 2 d.
//    cout << endl;
//    cout << "Finding a specific file/folder: " << endl;
//    string target = "pic1.jpg";
//    vector<string> path = findFileOrFolder(filesystemTree, target);
//    
//    cout << "Path for '" << target << "': ";
//    for (const auto& item : path) {
//        std::cout << item << "/";
//    }
//    cout << endl;
//    cout << endl;
//
//    //Stage 2 e.
//    string targetFolder = "Downloads";
//    displayFolderContents(filesystemTree, targetFolder);
//
//    return 0;
//}

int main() {
    string filename = "XML.xml";
    Tree<string>* filesystemTree = loadXmlData(filename);

    while (true) {
        // Display menu options
        cout << "Choose an option:" << endl;
        cout << "1. Print Tree" << endl;
        cout << "2. Count All Items" << endl;
        cout << "3. Count BFS" << endl;
        cout << "4. Prune Empty Folders" << endl;
        cout << "5. Find File/Folder" << endl;
        cout << "6. Display Folder Contents" << endl;
        cout << "0. Exit" << endl;

        // Get user input
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        string target;
        vector<string> path;
        string targetFolder;

        switch (choice) 
        {
        case 1:
            printTree(filesystemTree);
            cout << endl;
            break;

        case 2:
            cout << "Total number of items in the tree: " << countAllItems(filesystemTree) << endl;
            cout << endl;
            break;

        case 3:
            countBFS(filesystemTree);
            break;

        case 4:
            pruneEmptyFolders(filesystemTree);
            break;

        case 5:
            if (filesystemTree != nullptr) 
            {
                cout << "Enter the target file/folder name: ";
                cin >> target;

                if (findFileOrFolder(filesystemTree, target).empty()) 
                {
                    cout << "File/Folder not found." << endl;
                }
                else 
                {
                    path = findFileOrFolder(filesystemTree, target);
                    cout << "Path for '" << target << "': ";
                    for (const auto& item : path) 
                    {
                        cout << item << "/";
                    }
                    cout << endl;
                    cout << endl;
                }
            }
            else 
            {
                cout << "Please load XML data first." << endl;
            }
            break;

        case 6:
            if (filesystemTree != nullptr) 
            {
                cout << "Enter the target folder name: ";
                cin >> targetFolder;

                if (findFileOrFolder(filesystemTree, targetFolder).empty()) 
                {
                    cout << "Folder not found." << endl;
                }
                else 
                {
                    displayFolderContents(filesystemTree, targetFolder);
                }
            }
            else 
            {
                cout << "Please load XML data first." << endl;
            }
            break;

        case 0:
            cout << "Exiting the program." << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}