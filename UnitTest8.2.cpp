#include "pch.h"
#include "CppUnitTest.h"
#include "../Project8.2/Project8.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest82
{
	TEST_CLASS(UnitTest82)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string str = "abc";
			Assert::AreEqual(Ischar(str), true);
		}
	};
}
