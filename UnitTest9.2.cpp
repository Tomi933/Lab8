#include "pch.h"
#include "CppUnitTest.h"
#include "../Project9.2/Project9.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92
{
	TEST_CLASS(UnitTest92)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{

			Student* p = new Student[5]{
				{"Іваненко", 1, PHISIC, 3, 5, 3},
				{"Мельник", 2, PHISIC, 2, 5, 4},
				{"Солом", 1, PHISIC, 3,  4, 5},
				{"Коваль", 3, PHISIC, 4,  5, 3},
				{"Іваненко", 1, PHISIC, 5,  3, 3}
			};
			Sort(p, 5);

			bool actual = false;
			for (int i = 0; i < 4; i++)
			{
				if (p[i].markPhisic < p[i + 1].markPhisic)
				{
					actual = true;
				}
			}
			Assert::AreEqual(actual, true);

			delete[] p;
		}
		TEST_METHOD(TestMethod2)
		{

			Student* p = new Student[5]{
				{"Іваненко", 1, PHISIC, 3, 5, 3},
				{"Мельник", 2, PHISIC, 2, 5, 4},
				{"Солом", 1, PHISIC, 3,  4, 5},
				{"Коваль", 3, PHISIC, 4,  5, 3},
				{"Іваненко", 1, PHISIC, 5,  3, 3}
			};
			
			bool actual = false;
			for (int i = 0; i < 4; i++)
			{
				if (p[IndexSort(p, 5)[i]].markPhisic < p[IndexSort(p, 5)[i + 1]].markPhisic)
				{
					actual = true;
				}
			}
			Assert::AreEqual(actual, true);

			delete[] p;
		}
		TEST_METHOD(TestMethod3)
		{

			Student* p = new Student[5]{
				{"Іваненко", 1, PHISIC, 3, 5, 3},
				{"Мельник", 2, PHISIC, 2, 5, 4},
				{"Солом", 1, PHISIC, 3,  4, 5},
				{"Коваль", 3, PHISIC, 4,  5, 3},
				{"Іваненко", 1, PHISIC, 5,  3, 3}
			};
			Sort(p, 5);
			int k = 0;
			Specilty specilty = (Specilty)k;
			string prizv = "Мельник";

			int actual = BinSearch(p, 5, prizv, specilty, 2);

			Assert::AreEqual(0, actual);

			delete[] p;
		}
	};
}
