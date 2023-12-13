#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2023_CA2_A_S_App/Tree.h"
#include "../ADS_2023_CA2_A_S_App/TreeIterator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ADS2023CA2ASTests
{
	TEST_CLASS(ADS2023CA2ASTests)
	{
	public:
		
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

		/*
			Helper function used to set up the tree used for testing.
			The tree should look as follows
			1
			|-2           3
			  |- 4 5 6
		*/
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
		/*
			Test the resetIterator function sets list and
			currentNode to nullptr if no tree is passed in.
		*/
		TEST_METHOD(TestResetIteratorNullPtr)
		{
			TreeIterator<int> iter(nullptr);
			Assert::IsNull(iter.childIter.list);
			Assert::IsNull(iter.childIter.currentNode);

		}
		/*
			Tests the resetIterator sets list and
			currentNode to nullptr if a tree with no
			children is passed in
		*/
		TEST_METHOD(TestResetIteratorValidTreeNoChild)
		{
			Tree<int> t(1);
			TreeIterator<int> iter(&t);
			Assert::IsNotNull(iter.childIter.list);
			Assert::IsNull(iter.childIter.currentNode);

		}
		/*
			Tests the reset iterator function sets the childIter
			to the first child when a valid tree is passed in.
		*/
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
		/*
			Tests the root function moves the iterator to the root of the tree
			if it is set to a leaf node, cc2.
		*/
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
		/*
			Tests the up method moves up one level from a leaf node to the correct parent.
			This test sets the iterator at 5 which has a parent of 2.
			Also ensures resetIterator moves to the childIter to the correct child node.
		*/
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
		/*
			Test ensures the UP function does not allow the iterator to become invalid by moving
			up past the root. It also checks that the reset iterator is called in the event of moving up
			past the root.
		*/
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
		/*
			Tests the down function moves from the root down to the correct child.
			Also tests it will move to any child node currently set by the child iterator

		*/
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
		/*
			Tests the down function does not allow the iterator become invalid if there is no
			children of a node.
		*/
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
		/*
			Tests the child back method will mode the child iter back to teh previous child node.
			Tests moves the iterator to the second child and used childBack to move back to the first node.
		*/
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
		/*
			Tests the childForth method moves to teh next child element.
		*/
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
		/*
		Tests the childStart method moves to the first child element.
		*/
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
		/*
		Tests the childEnd method moves to the last child element.
		*/
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
		/*
		Tests the append child method adds an element to the end of the child list.
		*/
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
		/*
		Tests the prepend child method adds an element to the start of the child list.
		*/
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
		/*
		Tests the insert before child method adds an element before the item selected in the child iterator.
		*/
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
		/*
		Tests the insert after child method adds an element after the item selected in the child iterator.
		*/
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

		/*
			Tests the remove child method removes the item selected by the iterator
		*/
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
	};
}
