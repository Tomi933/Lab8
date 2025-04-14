#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;
void CreateTXT(char* fname) 
{
	ofstream fout(fname); 
	char ch; 
	string s; 
	do
	{
		cin.get(); 
		cin.sync(); 
		cout << "enter line: "; getline(cin, s); 
		fout << s << endl;
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
}
void PrintTXT(char* fname) 
{
	ifstream fin(fname); 
	string s; 
	while (getline(fin, s)) 
	{
		cout << s << endl; 
	}
	cout << endl;
}
bool ProcessTXT1(char* fname) 
{
	ifstream fin(fname); 
	string s; 
	bool isChar = false; 
	while (getline(fin, s)) 
	{ 
		for (unsigned i = 0; i < s.length() - 2; i++)
			if (s[i] == 'O' && s[i + 1] == 'G' && s[i + 2] == 'O' || s[i] == 'A' && s[i + 1] == 'G' && s[i + 2] == 'A') {
				isChar = true;
				return isChar;
			}
	}
	return isChar;
}

void ProcessTXT2(const char* fname)
{
	ifstream fin(fname);
	if (!fin.is_open()) {
		cout << "�� ������� ������� ����." << endl;
		return;
	}

	string s;
	while (fin >> s)
	{
		if (!s.empty() && s[0] == 'a')
		{
			cout << "�������� �����, �� ���������� � 'a': " << s << endl;
			return;
		}
	}

	cout << "� ���� ���� �����, �� ���������� � 'a'." << endl;
}



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char fname[100];
	cout << "enter file name 1: "; cin >> fname;

	int menuItem;
	do {
		cout  << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - ��������� ����� � �������� �����" << endl;
		cout << " [2] - ��������� ����� �� �����" << endl;
		cout << " [3] - �� � � ����� ���� ����� ������ ���� �OGO� ��� �AGA�" << endl;
		cout << " [4] - �� � � ����� ���� ����� �� ����� 'a'" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout  << endl << endl;

		switch (menuItem)
		{
		case 1:
			CreateTXT(fname);
			break;
			
		case 2:
			PrintTXT(fname);
			break;
		case 3:
			cout << "Is 'OGO' or 'AGA': " << ProcessTXT1(fname) << endl;
			break;
		case 4:
			ProcessTXT2(fname);
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
