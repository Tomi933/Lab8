#include "pch.h"
#include "CppUnitTest.h"
#include "../Project10.1/Project10.(1-2).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1012
{
	TEST_CLASS(UnitTest1012)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char* fname = "file.txt";
			ofstream fout(fname);
			string s = "qwwe AGA";
			fout << s << endl;
			fout.close();
			Assert::AreEqual(true, ProcessTXT1(fname));
		}
	};
}
