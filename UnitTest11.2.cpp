#include "pch.h"
#include "CppUnitTest.h"
#include "../Project11.2/Project11.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest112
{
	TEST_CLASS(UnitTest112)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            const char* testFile = "test_students.dat";

            // Створюємо тестовий файл
            ofstream fout(testFile, ios::binary);
            if (!fout) {
                cout << "Помилка відкриття файлу для тесту\n";
                return;
            }

            // Створюємо студентів
            Student s1 = { "Іваненко", 1, PHISIC, 3, 4 };
            s1.pedagogic = 3;

            Student s2 = { "Петренко", 2, KOMPSCINCE, 5, 5 };
            s2.program = 5;

            Student s3 = { "Сидоренко", 3, MATH, 2, 2 };
            s3.pedagogic = 2;


            // Запис у файл
            WriteStudent(fout, s1);
            WriteStudent(fout, s2);
            WriteStudent(fout, s3);
            fout.close();

            // Очікуємо 2 задовільні записи (оцінки ≥ 3)
            int expected = 2;
            int actual = CountSatisfactory(testFile);

            Assert::AreEqual(expected, actual);
		}
	};
}
