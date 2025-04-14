#include "pch.h"
#include "CppUnitTest.h"
#include "../Project10.3/Project10.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest103
{
	TEST_CLASS(UnitTest103)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			
			ofstream fout("routes.txt");
			fout << "Lviv;fcagr;101\n";
			fout << "fcagr;Kyiv;102\n";
			fout.close();

			char fname[100] = "routes.txt";
			string point = "fcagr";
			Assert::AreEqual(true, SearchRoutes(fname, point));
		}
	};
}
