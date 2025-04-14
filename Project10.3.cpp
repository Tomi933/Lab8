#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iostream>
#include <iomanip>

using namespace std;

struct Route {
    string start;
    string end;
    string number;
};


void AddRoute(const char* fname) {
    ofstream fout(fname); 
    Route r;
    char ch;
    do {
        cin.ignore();
        cout << "���������� �����: ";
        getline(cin, r.start);
        cout << "ʳ������ �����: ";
        getline(cin, r.end);
        cout << "����� ��������: ";
        getline(cin, r.number);

        fout << r.start << ";" << r.end << ";" << r.number << endl;

        cout << "������ ��? (y/n): ";
        cin >> ch;
        cin.ignore();
    } while (ch == 'y' || ch == 'Y');

    fout.close();
    cout << "�������� ������.\n";
}


void ViewRoutes(const char* fname) {
    ifstream fin(fname);
    string line;
    string point;
    int count = 0;
    
    cout << "-----------------------------------------------------" << endl;
    cout << "|" << setw(17) <<  "���������� �����" << "|" << setw(17) << "ʳ������ �����" << "|" << setw(15) << "�����" << "|" << endl;
    cout << "-----------------------------------------------------" << endl;
    while (getline(fin, line)) {
        size_t firstDelim = line.find(';');
        size_t secondDelim = line.rfind(';');

        if (firstDelim == string::npos || secondDelim == string::npos || firstDelim == secondDelim)
            continue;

        string start = line.substr(0, firstDelim);
        string end = line.substr(firstDelim + 1, secondDelim - firstDelim - 1);
        string number = line.substr(secondDelim + 1);

        cout << "|" << setw(16) << start << " | " << setw(16) << end << "|  " << setw(13) << number << "|" << endl;
        cout << "-----------------------------------------------------" << endl;
        
    }
    if (count == 0)
        cout << "���� ������� ��� �� ��������.\n";

    fin.close();
}


bool SearchRoutes(const char* fname, string point) {

    ifstream fin(fname);
    string line;
    
    bool found = false;

    cout << "-----------------------------------------------------" << endl;
    cout << "|" << setw(17) << "���������� �����" << "|" << setw(17) << "ʳ������ �����" << "|" << setw(15) << "�����" << "|" << endl;
    cout << "-----------------------------------------------------" << endl;
    while (getline(fin, line)) {
        size_t firstDelim = line.find(';');
        size_t secondDelim = line.rfind(';');

        if (firstDelim == string::npos || secondDelim == string::npos || firstDelim == secondDelim)
            continue;

        string start = line.substr(0, firstDelim);
        string end = line.substr(firstDelim + 1, secondDelim - firstDelim - 1);
        string number = line.substr(secondDelim + 1);

        if (start == point || end == point) {
            cout << "|" << setw(16) << start << " | " << setw(16) << end << "|  " << setw(13) << number << "|" << endl;
            cout << "-----------------------------------------------------" << endl;
            found = true;
        }
    }

    if (!found)
        cout << "�������� � ������� \"" << point << "\" �� ��������.\n";
    fin.close();

    return found;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string point;
    char fname[100];
    cout << "������ ����� �����: ";
    cin >> fname;

    int choice;
    while (true) {
        cout << "\n����:\n";
        cout << "1. ����������� �� ��������\n";
        cout << "2. ������ �������\n";
        cout << "3. ����� �������� �� �������\n";
        cout << "4. �����\n";
        cout << "��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            ViewRoutes(fname);
            break;
        case 2:
            AddRoute(fname);
            break;
        case 3:
            cin.ignore();
            cout << "������ ����� ������ ��� ������: ";
            getline(cin, point);
            SearchRoutes(fname, point);
            break;
        case 4:
            return 0;
        default:
            cout << "������� ����.\n";
        }
    }

    return 0;
}



