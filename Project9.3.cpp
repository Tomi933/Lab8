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
{ // ������������ ����������� ��������:
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

	int N;
	cout << "������ N: "; cin >> N;

	char filename[100];

	Route* p = new Route[N];

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� �����" << endl;
		cout << " [4] - ����� ��������" << endl;
		cout << " [5] - ����� ����� � ����" << endl;
		cout << " [6] - ���������� ����� �� �����" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
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
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

			cout << "������ ��'� �����: "; cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 6:
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

			cout << "������ ��'� �����: "; cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
			break;

		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	
	

	return 0;
}
void Create(Route* p, const int N)
{
	int posada;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

		cout << " ����������� ������ ��������: "; getline(cin, p[i].start);
		cout << " �������� ������ ��������: "; getline(cin, p[i].end);
		cout << " ����� ��������: "; cin >> p[i].number;
		
		cout << endl;
	}
}

void Print(Route* p, const int N)
{
	cout << "================================================================================"
		<< endl;
	cout << "| � | ����������� ������ �������� | ʳ������� ������ �������� | ����� �������� |"
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
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
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

	cout << "�� ����������� - 1, �� ����������� - 2, � �����: " << endl;
	cout << "Choise:"; cin >> ch;
	
	cout << "������ ����� ��������:";
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
			cout << "| � | ����������� ������ �������� | ʳ������� ������ �������� | ����� �������� |"
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
	ofstream fout(filename, ios::binary); // ������� ������� ���� ������
	fout.write((char*)&N, sizeof(N)); // �������� ������� ��������
	for (int i = 0; i < N; i++)
	fout.write((char*)&p[i], sizeof(Route)); // �������� �������� ������
	fout.close(); // ������� ����
}
void LoadFromFile(Route*& p, int& N, const char* filename)
{
	delete[] p; // ������� �������� ���
	ifstream fin(filename, ios::binary); // ������� ������� ���� ����������
	fin.read((char*)&N, sizeof(N)); // ��������� ������� ��������
	p = new Route[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		fin.read((char*)&p[i], sizeof(Route)); // ��������� �������� ������
	fin.close(); // ������� ����
}