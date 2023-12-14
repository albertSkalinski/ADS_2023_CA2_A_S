#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2023_CA2_A_S_App/Tree.h"
#include "../ADS_2023_CA2_A_S_App/TreeIterator.h"
#include "../ADS_2023_CA2_A_S_App/XMLTreeCreator.h"
#include "../ADS_2023_CA2_A_S_App/Functions.h"

#include <string>
#include <vector>

using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ADS2023CA2ASTests
{
	TEST_CLASS(ADS2023CA2ASTests)
	{
	public:

		//TREE TESTS
		TEST_METHOD(TestConstructor)
		{
			Tree<int> tree(1);
			Assert::AreEqual(1, tree.data);
			Assert::IsNull(tree.parent);
			Assert::IsNotNull(tree.children);
			Assert::AreEqual(0, tree.children->size());
		}
		TEST_METHOD(TestCountOneItem)
		{
			Tree<int> tree(1);
			Assert::AreEqual(1, tree.count());
		}
		TEST_METHOD(TestCountOneItemWithChildrenAndSubChildren)
		{
			Tree<int> tree(1);
			Tree<int> childOne(2);
			Tree<int> childTwo(3);
			Tree<int> subChild(4);
			childTwo.children->append(&subChild);
			tree.children->append(&childOne);
			tree.children->append(&childTwo);
			Assert::AreEqual(2, childTwo.count());
			Assert::AreEqual(4, tree.count());
		}

		void populateTree(Tree<int>*& root, Tree<int>*& cc2)
		{
			root = new Tree<int>(1);
			Tree<int>* c1 = new Tree<int>(2);
			Tree<int>* c2 = new Tree<int>(3);
			c1->parent = root;
			c2->parent = root;


			Tree<int>* cc1 = new Tree<int>(4);
			Tree<int>* cc3 = new Tree<int>(6);
			cc2 = new Tree<int>(5);
			cc1->parent = c1;
			cc2->parent = c1;
			cc3->parent = c1;
			root->children->append(c1);
			root->children->append(c2);
			c1->children->append(cc1);
			c1->children->append(cc2);
			c1->children->append(cc3);
		}
		
		TEST_METHOD(TestResetIteratorNullPtr)
		{
			TreeIterator<int> iter(nullptr);
			Assert::IsNull(iter.childIter.list);
			Assert::IsNull(iter.childIter.currentNode);

		}

		TEST_METHOD(TestResetIteratorValidTreeNoChild)
		{
			Tree<int> t(1);
			TreeIterator<int> iter(&t);
			Assert::IsNotNull(iter.childIter.list);
			Assert::IsNull(iter.childIter.currentNode);

		}

		TEST_METHOD(TestResetIteratorValidTreeWithChild)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			TreeIterator<int> iter(root);
			Assert::IsNotNull(iter.childIter.list);
			Assert::IsNotNull(iter.childIter.currentNode);
			Assert::AreEqual(2, iter.childIter.currentNode->data->data);

		}

		TEST_METHOD(TestRoot)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(cc2);
			Assert::AreEqual(5, iter.node->data);
			iter.root();
			Assert::IsNotNull(iter.node);
			Assert::AreEqual(1, iter.node->data);
		}

		TEST_METHOD(TestUp)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(cc2);
			Assert::AreEqual(5, iter.node->data);
			Assert::IsFalse(iter.childIter.isValid());

			iter.up();
			Assert::IsNotNull(iter.node);
			Assert::AreEqual(2, iter.node->data);
			Assert::AreEqual(4, iter.childIter.item()->getData());

			iter.up();
			Assert::IsNotNull(iter.node);
			Assert::AreEqual(1, iter.node->data);
			Assert::AreEqual(2, iter.childIter.item()->getData());


		}

		TEST_METHOD(TestUpFromRoot)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			iter.childIter.advance();
			Assert::AreEqual(3, iter.childIter.item()->getData());
			Assert::IsNotNull(iter.node);
			Assert::AreEqual(1, iter.node->data);
			iter.up();
			Assert::IsNotNull(iter.node);
			Assert::AreEqual(1, iter.node->data);
			Assert::AreEqual(2, iter.childIter.item()->getData());
		}

		TEST_METHOD(TestDownFromRoot)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			Assert::AreEqual(1, iter.node->data);
			Assert::IsTrue(iter.childIter.isValid());
			Assert::AreEqual(2, iter.childIter.item()->getData());

			iter.down();
			Assert::IsNotNull(iter.node);
			Assert::AreEqual(2, iter.node->data);
			Assert::AreEqual(4, iter.childIter.item()->getData());
			iter.childForth();
			iter.down();
			Assert::IsNotNull(iter.node);
			Assert::AreEqual(5, iter.node->data);
			Assert::IsFalse(iter.childIter.isValid());

		}

		TEST_METHOD(TestDownFromLeaf)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(cc2);
			Assert::AreEqual(5, iter.node->data);
			Assert::IsFalse(iter.childIter.isValid());

			iter.down();
			Assert::AreEqual(5, iter.node->data);
			Assert::IsFalse(iter.childIter.isValid());

		}

		TEST_METHOD(TestChildBack)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			Assert::AreEqual(2, iter.childIter.item()->getData());
			iter.childIter.advance();
			Assert::AreEqual(3, iter.childIter.item()->getData());
			iter.childBack();
			Assert::AreEqual(2, iter.childIter.item()->getData());

		}

		TEST_METHOD(TestChildForth)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			Assert::AreEqual(2, iter.childIter.item()->getData());
			iter.childForth();
			Assert::AreEqual(3, iter.childIter.item()->getData());

		}

		TEST_METHOD(TestChildStart)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			iter.down();
			Assert::AreEqual(4, iter.childIter.item()->getData());
			iter.childIter.advance();
			iter.childIter.advance();
			Assert::AreEqual(6, iter.childIter.item()->getData());
			iter.childStart();
			Assert::AreEqual(4, iter.childIter.item()->getData());

		}

		TEST_METHOD(TestChildEnd)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			iter.down();
			Assert::AreEqual(4, iter.childIter.item()->getData());
			iter.childEnd();
			Assert::AreEqual(6, iter.childIter.item()->getData());

		}

		TEST_METHOD(TestAppendChild)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			iter.down();
			Assert::AreEqual(4, iter.childIter.item()->getData());
			iter.appendChild(7);
			iter.childEnd();
			Assert::AreEqual(7, iter.childIter.item()->getData());

		}

		TEST_METHOD(TestPrependChild)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			iter.down();
			Assert::AreEqual(4, iter.childIter.item()->getData());
			iter.prependChild(7);
			Assert::AreEqual(7, iter.childIter.item()->getData());

		}

		TEST_METHOD(TestInsertChildBefore)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			iter.down();
			int startChildren[] = { 4,5,6 };
			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(startChildren[i], iter.childIter.item()->getData());
				if (i != 2)
				{
					iter.childForth();
				}

			}
			iter.childStart();
			Assert::IsTrue(iter.childIter.isValid());
			iter.childForth();
			Assert::AreEqual(5, iter.childIter.item()->getData());
			iter.insertChildBefore(7);
			iter.childStart();
			int endChildren[] = { 4,7,5,6 };
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(endChildren[i], iter.childIter.item()->getData());
				iter.childForth();

			}
			iter.childStart();
		}

		TEST_METHOD(TestInsertChildAfter)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			iter.down();
			int startChildren[] = { 4,5,6 };
			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(startChildren[i], iter.childIter.item()->getData());
				if (i != 2)
				{
					iter.childForth();
				}

			}
			iter.childStart();
			Assert::AreEqual(4, iter.childIter.item()->getData());
			iter.insertChildAfter(7);
			Assert::AreEqual(4, iter.childIter.item()->getData());
			iter.childStart();
			int endChildren[] = { 4,7,5,6 };
			for (int i = 0; i < 4; i++)
			{
				Assert::AreEqual(endChildren[i], iter.childIter.item()->getData());
				iter.childForth();

			}
			iter.childStart();
		}

		TEST_METHOD(TestRmoveChild)
		{
			Tree<int>* root = nullptr;
			Tree<int>* cc2 = nullptr;
			populateTree(root, cc2);
			Assert::IsNotNull(root);
			TreeIterator<int> iter(root);
			iter.down();
			int startChildren[] = { 4,5,6 };
			for (int i = 0; i < 3; i++)
			{
				Assert::AreEqual(startChildren[i], iter.childIter.item()->getData());
				if (i != 2)
				{
					iter.childForth();
				}

			}
			iter.childStart();
			iter.childForth();
			iter.removeChild();
			iter.childStart();
			int endChildren[] = { 4,6 };
			for (int i = 0; i < 2; i++)
			{
				Assert::AreEqual(endChildren[i], iter.childIter.item()->getData());
				iter.childForth();

			}
			iter.childStart();
		}

		//XMLVALIDATION TESTS
		TEST_METHOD(TestTrimString)
		{
			string input = "   Hello, World!   ";
			string expected = "Hello, World!";

			string result = trim(input);

			Assert::AreEqual(expected, result);
		}

		//TEST_METHOD(TestLoadXMLData)
		//I have no idea how to test this function

		//FUNCTIONS TESTS

		TEST_METHOD(CountAllItemsInXmlTree) 
		{
			// Arrange
			string filename = "C:\\Users\\sKALa\\Repos\\ADS_2023_CA2_A_S\\ADS_2023_CA2_A_S_Tests\\XML.xml";
			// Load XML data into a tree
			Tree<string>* filesystemTree = loadXmlData(filename);

			// Act
			int itemCount = countAllItems(filesystemTree);

			// Assert
			Assert::AreEqual(18, itemCount); // Adjust the count based on the actual XML structure
		}

		TEST_METHOD(CountBFSInXmlTree)
		{
			// Arrange
			string filename = "C:\\Users\\sKALa\\Repos\\ADS_2023_CA2_A_S\\ADS_2023_CA2_A_S_Tests\\XML.xml";
			// Load XML data into a tree
			Tree<string>* filesystemTree = loadXmlData(filename);

			// Act
			int itemCount = countBFS(filesystemTree);

			// Assert
			Assert::AreEqual(158, itemCount); // Adjust the count based on the actual XML structure
		}

		TEST_METHOD(PruneEmptyFoldersInXmlTree)
		{
			// Arrange
			string filename = "C:\\Users\\sKALa\\Repos\\ADS_2023_CA2_A_S\\ADS_2023_CA2_A_S_Tests\\XML.xml";
			// Load XML data into a tree
			Tree<string>* filesystemTree = loadXmlData(filename);

			// Act
			pruneEmptyFolders(filesystemTree);

			// Assert
			Assert::AreEqual(18, filesystemTree->count()); // Adjust the count based on the actual XML structure
		}

		//I did not know how to test this function either (DFS)
	};
}
