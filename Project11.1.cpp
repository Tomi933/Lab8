#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void CreateBIN(char* fname) 
{
	ofstream fout(fname, ios::binary | ios::app); 
	char ch; 
	string s; 
	do
	{
		cin.get(); 
		cin.sync(); 
		cout << "enter line: "; getline(cin, s); 
		for (unsigned i = 0; i < s.length(); i++) 
			fout.write((char*)&s[i], sizeof(s[i])); 
		cout << "continue? (y/n): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	cout << endl;
}
string PrintBIN(char* fname) 
{
	ifstream fin(fname, ios::binary); 
	char c; 
	string k;
	int i = 0;
	while (fin.read((char*)&c, sizeof(c))) 
	{
		cout << c; 
		k.push_back(c);
	}
	cout << endl;
	return k;
}
void ProcessBIN1(char* fname, char* gname) 
{ 
	ifstream f(fname, ios::binary); 
	ofstream g(gname, ios::binary);
	char c1, c2;
	if (!f.read((char*)&c1, sizeof(c1))) return;

	while (f.read((char*)&c2, sizeof(c2)))
	{
		if (c2 >= '0' && c2 <= '9')
		{
			g.write((char*)&c1, sizeof(c1)); 
		}
		c1 = c2;
	}
}

int main()
{
	
	char fname[100]; 
	cout << "enter file name 1: "; cin >> fname;
	CreateBIN(fname); 
	PrintBIN(fname);
	char gname[100]; 
	cout << "enter file name 2: "; cin >> gname;
	ProcessBIN1(fname, gname);
	PrintBIN(gname);
	return 0;
}