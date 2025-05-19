#include "pch.h"
#include "CppUnitTest.h"
#include "../Project12.10/Project12.10.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1210
{
	TEST_CLASS(UnitTest1210)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Node* root = nullptr;
			root = CreateTree(0);
			InsertNode(root, 3);

			bool actual = false;
			if (FindNode(root, 3))
				actual = true;
			DeleteNode(root, 3);
			Assert::AreEqual(true, actual);

		}
	};
}
