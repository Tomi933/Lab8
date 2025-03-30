#include "pch.h"
#include "CppUnitTest.h"
#include "../Project9.1/Project9.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest91
{
	TEST_CLASS(UnitTest91)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student* p = new Student[5]{
				{"��������", 1, PHISIC, 3, 4, 5},
				{"�������", 2, PHISIC, 2, 4, 5},
				{"�����", 1, PHISIC, 3, 5, 4},
				{"������", 3, PHISIC, 4, 4, 5},
				{"��������", 1, PHISIC, 5, 4, 3}
			};
			Assert::AreEqual(Search(p, 5) , 3);

			delete[] p;
		}
		
	};
}
