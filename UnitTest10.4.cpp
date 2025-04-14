#include "pch.h"
#include "CppUnitTest.h"
#include "../Project10.4/Project10.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest104
{
	TEST_CLASS(UnitTest104)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const char* sourceFile = "source.txt";
			const char* destFile = "result.txt";
			ofstream fout(sourceFile);
			fout << "Hello, world!" << endl;
			fout << "This is a test." << endl;
			fout.close();
			
			int totalWords = ProcessLines(sourceFile, destFile);

			Assert::AreEqual(6, totalWords);
		}
	};
}
