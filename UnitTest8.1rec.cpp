#include "pch.h"
#include "CppUnitTest.h"
#include "../Project8.1-1rec/Project8.1-1rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest81rec
{
	TEST_CLASS(UnitTest81rec)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char str[101] = "aaaass sss AGA OGO";
			Assert::AreEqual(Count(str, 0), 2);
		}
	};
}
