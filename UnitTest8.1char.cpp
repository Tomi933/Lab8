
#include "pch.h"
#include "CppUnitTest.h"
#include "../Project8.1-char/Project8.1-char.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest81char
{
	TEST_CLASS(UnitTest81char)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char str[12] = "AGA OGO";
			Assert::AreEqual(Count(str), 2);
		}
	};
}
