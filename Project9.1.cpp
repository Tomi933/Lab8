#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h> 
using namespace std;

enum Specilty { PHISIC, MATH, INFORMTECH, KOMPSCINCE,  TRUDOWE };

string speciltyStr[] = { "Фізик", "Математик", "Інформатик", "Комп’ютерні науки", "Трудове навчання" };

struct Student
{
	string prizv;
	unsigned kurs;
	Specilty specilty;
	unsigned markPhisic;
	unsigned markMath;
	unsigned markInfotmatic;
	union
	{
		int program;
		int varmetod;
		int pedagogic;
	};
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
int Search(Student* p, const int N);
void SearchPrizv(Student* p, const int N);

int main()
{ 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "Введіть N: "; cin >> N;

	Student* p = new Student[N];
	Create(p, N);
	Print(p, N);

	cout << Search(p, N) << endl;
	SearchPrizv(p, N);

	return 0;
}
void Create(Student* p, const int N)
{
	int specilty;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get(); 
		cin.sync();

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс.: "; cin >> p[i].kurs;
		cout << " спеціальність (0 - фізик, 1 - математик, 2 - інформатик, 3 - Комп’ютерні науки, 4 - Трудове навчання): ";
		cin >> specilty;
		cout << " фізика : "; cin >> p[i].markPhisic;
		cout << " математика : "; cin >> p[i].markMath;
		cout << " інформатика : "; cin >> p[i].markInfotmatic;
		p[i].specilty = (Specilty)specilty;
		switch (p[i].specilty)
		{
		case KOMPSCINCE:
			cout << " програмування : "; cin >> p[i].program;
			break;
		case INFORMTECH:
			cout << "  з чисельних методів : "; cin >> p[i].varmetod;
			break;
		default:
			cout << " педагогіка : "; cin >> p[i].pedagogic;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "================================================================================================================================="
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність      | Фізика | Математика | Інформатика | Програмування | Чисельних методів | педагогіки |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[i].prizv
			 << "| " << setw(4) << right << p[i].kurs << " "
			 << "| " << setw(19) << left << speciltyStr[p[i].specilty]
			 << "| " << setw(6) << setprecision(2) << fixed << right << p[i].markPhisic 
			 << " |" << setw(11) << right << p[i].markMath 
			 << " |" << setw(12) << right << p[i].markInfotmatic << " |";

		switch (p[i].specilty)
		{
		case KOMPSCINCE:
			cout << setw(14) << right << p[i].program << " |" << setw(20) << " |" << setw(13) << " |" << endl;
			break;
		case INFORMTECH:
			cout << setw(16) << " |" << setw(18) << right << p[i].varmetod << " |" << setw(13) << " |" << endl;
			break;
		default:
			cout << setw(16) << " |" << setw(20)  << " |" << setw(11) << right << p[i].pedagogic << " |" << endl;
		}
	}
	cout << "================================================================================================================================="
		<< endl;
	cout << endl;
}

int Search(Student* p, const int N)
{
	cout << "Кількість відміних оцінок:";
	int k = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].markPhisic == 3)
		{
			k++;
		}
		if (p[i].markMath == 3)
		{
			k++;
		}
		if (p[i].markInfotmatic == 3)
		{
			k++;
		}
		if (p[i].specilty == INFORMTECH)
		{
			if (p[i].varmetod == 3)
			{
				k++;
			}
		}
		if (p[i].specilty == KOMPSCINCE)
		{
			if (p[i].program == 3)
			{
				k++;
			}
		}
		if (!(p[i].specilty == KOMPSCINCE) && !(p[i].specilty == INFORMTECH))
		{
			if (p[i].pedagogic == 3)
			{
				k++;
			}
		}

	}
	return k;
}

void SearchPrizv(Student* p, const int N)
{
	for (int i = 0; i < N; i++)
	{
		if (p[i].markPhisic == 4 || p[i].markPhisic == 5 && p[i].markMath == 4 || p[i].markMath == 5)
		{
			cout << p[i].prizv << endl;
		}
	}
}
