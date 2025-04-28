#include "pch.h"
#include "CppUnitTest.h"
#include "../Project11.1/Project11.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest111
{
	TEST_CLASS(UnitTest111)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char* sourceFile = "file1.txt";
			char* destFile = "file2.txt";
			ofstream fout(sourceFile, ios::binary);
			fout << "1H2e3l4l1o2, world!" << endl;
			fout.close();
			ProcessBIN1(sourceFile, destFile);

			string totalWords = PrintBIN(destFile);
			string res = "Hello";

			Assert::AreEqual(res, totalWords);
		}
	};
}
