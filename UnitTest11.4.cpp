#include "pch.h"
#include "CppUnitTest.h"
#include "../Project11.4/Project11.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest114
{
	TEST_CLASS(UnitTest114)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const char* testFile = "test_students.bin";
            fstream fout(testFile, ios::binary);

            Route s1 = { "Іваненко", "wcfcrw", 4 };
            Route s2 = { "Петренко", "wcfcw", 5};
            Route s3 = { "Сидоренко", "kbjt", 2};

            WriteRoute(fout, s1);
            WriteRoute(fout, s2);
            WriteRoute(fout, s3);
            fout.close();
            string point = "wcfcw";
            Assert::AreEqual(true, FindByPoint(testFile, point));

		}
	};
}
