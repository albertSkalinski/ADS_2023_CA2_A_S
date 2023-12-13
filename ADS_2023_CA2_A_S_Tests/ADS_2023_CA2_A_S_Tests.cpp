#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2023_CA2_A_S_App/Tree.h"

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
	};
}
