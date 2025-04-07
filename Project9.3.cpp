#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

struct Route
{
	string start;
	string end;
	unsigned number;
	
};
void Create(Route* p, const int N);
void Print(Route* p, const int N);
void Sort(Route* p, const int N);
void LineSearch(Route* p, const int N);
void SaveToFile(Route* p, const int N, const char* filename);
void LoadFromFile(Route*& p, int& N, const char* filename);

int main()
{ // забезпечення відображення кирилиці:
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть N: "; cin >> N;

	char filename[100];

	Route* p = new Route[N];

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - пошук маршруту" << endl;
		cout << " [5] - запис даних у файл" << endl;
		cout << " [6] - зчитування даних із файлу" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			break;
		case 4:
			LineSearch(p, N);
			break;
		case 5:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 6:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
			break;

		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	
	

	return 0;
}
void Create(Route* p, const int N)
{
	int posada;
	for (int i = 0; i < N; i++)
	{
		cout << "Маршрут № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " початкового пункту маршруту: "; getline(cin, p[i].start);
		cout << " кінцевого пункту маршруту: "; getline(cin, p[i].end);
		cout << " номер маршруту: "; cin >> p[i].number;
		
		cout << endl;
	}
}

void Print(Route* p, const int N)
{
	cout << "================================================================================"
		<< endl;
	cout << "| № | Початкового пункту маршруту | Кінцевого пункту маршруту | номер маршруту |"
		<< endl;
	cout << "--------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(28) << left << p[i].start
			<< "| " << setw(25) << right << p[i].end << " "
			<< "| " << setw(15) << left << p[i].number << "| " <<endl;
		
	}
	cout << "================================================================================"
		<< endl;
	cout << endl;
}

void Sort(Route* p, const int N)
{
	Route tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].number > p[i1 + 1].number)
				||
				(p[i1].number == p[i1 + 1].number &&
					p[i1].start > p[i1 + 1].start))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}

void LineSearch(Route* p, const int N)
{
	int ch;
	string start1;
	string end1;

	cout << "які починаються - 1, які закінчуються - 2, в пункті: " << endl;
	cout << "Choise:"; cin >> ch;
	
	cout << "Введіть назву маршруту:";
	if (ch == 1)
	{
		cin >> start1;
	}
	if (ch == 2)
	{
		cin >> end1;
	}
	

	int k = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].start == start1 && ch == 1 || p[i].end == end1 && ch == 2)
		{
			
			cout << "================================================================================"
				<< endl;
			cout << "| № | Початкового пункту маршруту | Кінцевого пункту маршруту | номер маршруту |"
				<< endl;
			cout << "--------------------------------------------------------------------------------"
				<< endl;
			cout << "| " << setw(1) << right << 1 << " ";
			cout << "| " << setw(28) << left << p[i].start
					<< "| " << setw(25) << right << p[i].end << " "
					<< "| " << setw(15) << left << p[i].number << "| " << endl;

			cout << "================================================================================"
				<< endl;
			cout << endl;
		}
	}
	
}

void SaveToFile(Route* p, const int N, const char* filename)

{
	ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
	fout.write((char*)&N, sizeof(N)); // записали кількість елементів
	for (int i = 0; i < N; i++)
	fout.write((char*)&p[i], sizeof(Route)); // записали елементи масиву
	fout.close(); // закрили файл
}
void LoadFromFile(Route*& p, int& N, const char* filename)
{
	delete[] p; // знищили попередні дані
	ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
	fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
	p = new Route[N]; // створили динамічний масив
	for (int i = 0; i < N; i++)
		fin.read((char*)&p[i], sizeof(Route)); // прочитали елементи масиву
	fin.close(); // закрили файл
}