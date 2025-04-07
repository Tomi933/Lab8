#include "pch.h"
#include "CppUnitTest.h"
#include "../Project9.3/Project9.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest93
{
	TEST_CLASS(UnitTest93)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Route* p = new Route[5]{
				{"Іваненко","carcrg", 13},
				{"vrhth","vthrh", 13},
				{"tnjunt","ggg", 13},
				{"nyu","uyu", 13},
				{"sccr","ooo", 13}
			};
			Sort(p, 5);

			bool actual = false;
			int k = 0;
			for (int i = 0; i < 4; i++)
			{
				if (p[i].number >= p[i + 1].number)
				{
					k++;
				}
				if (k == 4)
				{
					actual = true;
				}
			}
			Assert::AreEqual(actual, true);

			delete[] p;
		}
	};
}
