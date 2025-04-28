#include "pch.h"
#include "CppUnitTest.h"
#include "../Project11.3/Project11.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest113
{
	TEST_CLASS(UnitTest113)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const char* testFile = "test_students.bin";
            ofstream fout(testFile, ios::binary);

            Student s1 = { "Іваненко", 1, PHYSICS, 3, 4 };
            s1.markPed = 3;

            Student s2 = { "Петренко", 2, COMPSCINCE, 5, 5 };
            s2.markProg = 5;

            Student s3 = { "Сидоренко", 3, INFOTECH, 2, 2 };
            s3.markMetods = 2;

            WriteStudent(fout, s1);
            WriteStudent(fout, s2);
            WriteStudent(fout, s3);
            fout.close();
            bool k = false;
            if (BinSearch(testFile, "Іваненко", PHYSICS, 3) != -1) {
                k = true;
            }
            
            Assert::AreEqual(true, k);

           
            remove(testFile);
		}
	};
}
