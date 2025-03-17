
#include "pch.h"
#include "CppUnitTest.h"
#include "../Project8.1-it/Project8.1-it.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest81it
{
	TEST_CLASS(UnitTest81it)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char str[101] = "one three AGA OGO";
			Assert::AreEqual(Count(str), 2);
			
		}
	};
}
