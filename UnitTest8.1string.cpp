#include "pch.h"
#include "CppUnitTest.h"
#include "../Project8.1-string/Project8.1-string.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest81string
{
	TEST_CLASS(UnitTest81string)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string str = "AGA1OGO";
			Assert::AreEqual(Count(str), 2);
		}
	};
}
