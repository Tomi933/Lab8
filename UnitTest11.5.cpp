#include "pch.h"
#include "CppUnitTest.h"
#include "../Project11.5/Project11.5.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest115
{
	TEST_CLASS(UnitTest115)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const char* testFile = "test_students.bin";
			ofstream fout(testFile, ios::binary);

			// Тестові дані
			Student s1 = { "Іваненко", 1, 4, 2, 4, 5, 4 }; // середнє = 4.33 → не проходить
			Student s2 = { "Петренко", 1, 5, 1, 4, 5, 5 }; // середнє = 4.67 → проходить
			Student s3 = { "Сидоренко", 2, 2, 2, 3, 4, 4 }; // середнє = 3.67 → не проходить
			Student s4 = { "Ковальчук", 3, 3, 0, 5, 4, 4 }; // середнє = 4.33 → не проходить
			Student s5 = { "Мельник", 4, 1, 3, 5, 5, 4 };   // середнє = 4.67 → проходить

			// Запис у файл
			fout.write((char*)&s1, sizeof(Student));
			fout.write((char*)&s2, sizeof(Student));
			fout.write((char*)&s3, sizeof(Student));
			fout.write((char*)&s4, sizeof(Student));
			fout.write((char*)&s5, sizeof(Student));
			fout.close();

			// Очікуємо 2 студенти з середнім >= 4.5 (Петренко і Мельник)
			Assert::AreEqual(2, queryAverage45(testFile));
		}
	};
}
