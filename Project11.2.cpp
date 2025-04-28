#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

enum Specilty { PHISIC, MATH, INFORMTECH, KOMPSCINCE, TRUDOWE };
string speciltyStr[] = { "Գ����", "����������", "�����������", "��������� �����", "������� ��������" };

struct Student {
    string prizv;
    unsigned kurs;
    Specilty specilty;
    unsigned markPhisic;
    unsigned markMath;

    union {
        int program;
        int varmetod;
        int pedagogic;
    };
};

void WriteStudent(ofstream& fout, const Student& s) {
    size_t len = s.prizv.size();
    fout.write((char*)&len, sizeof(len));
    fout.write(s.prizv.c_str(), len);
    fout.write((char*)&s.kurs, sizeof(s.kurs));
    fout.write((char*)&s.specilty, sizeof(s.specilty));
    fout.write((char*)&s.markPhisic, sizeof(s.markPhisic));
    fout.write((char*)&s.markMath, sizeof(s.markMath));

    switch (s.specilty) {
    case KOMPSCINCE: fout.write((char*)&s.program, sizeof(s.program)); break;
    case INFORMTECH: fout.write((char*)&s.varmetod, sizeof(s.varmetod)); break;
    default: fout.write((char*)&s.pedagogic, sizeof(s.pedagogic)); break;
    }
}

Student ReadStudent(ifstream& fin) {
    Student s;
    size_t len;
    fin.read((char*)&len, sizeof(len));
    s.prizv.resize(len);
    fin.read(&s.prizv[0], len);
    fin.read((char*)&s.kurs, sizeof(s.kurs));
    fin.read((char*)&s.specilty, sizeof(s.specilty));
    fin.read((char*)&s.markPhisic, sizeof(s.markPhisic));
    fin.read((char*)&s.markMath, sizeof(s.markMath));

    switch (s.specilty) {
    case KOMPSCINCE: fin.read((char*)&s.program, sizeof(s.program)); break;
    case INFORMTECH: fin.read((char*)&s.varmetod, sizeof(s.varmetod)); break;
    default: fin.read((char*)&s.pedagogic, sizeof(s.pedagogic)); break;
    }

    return s;
}

void AddStudentsToFile(const char* fname) {
    int N;
    cout << "������ �������� ������?: ";
    cin >> N;

    ofstream fout(fname, ios::binary | ios::app);
    if (!fout) {
        cout << "���� �� �������� ��� ������!\n";
        return;
    }

    for (int i = 0; i < N; i++) {
        Student s;
        int spec;

        cin.ignore();
        cout << "\n������� �" << i + 1 << ":\n";
        cout << " �������: "; getline(cin, s.prizv);
        cout << " ����: "; cin >> s.kurs;
        cout << " ������������ (0-������, 1-����������, 2-�����������, 3-����. �����, 4-�������): ";
        cin >> spec;
        s.specilty = (Specilty)spec;
        cout << " ������ � ������: "; cin >> s.markPhisic;
        cout << " ������ � ����������: "; cin >> s.markMath;

        switch (s.specilty) {
        case KOMPSCINCE:
            cout << " ������ � �������������: "; cin >> s.program;
            break;
        case INFORMTECH:
            cout << " ������ � ��������� ������: "; cin >> s.varmetod;
            break;
        default:
            cout << " ������ � ���������: "; cin >> s.pedagogic;
            break;
        }

        WriteStudent(fout, s);
    }

    fout.close();
    cout << "��� ������� � ����.\n";
}


void PrintAllFromFile(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "���� �� ��������!\n";
        return;
    }

    cout << "=====================================================================================================================\n";
    cout << "| � | �������        | ���� | ����.                 | Գ���� | ���������� | ������������� | �������� | ���������� |\n";
    cout << "---------------------------------------------------------------------------------------------------------------------\n";

    int i = 0;
    while (fin.peek() != EOF) {
        Student s = ReadStudent(fin);

        cout << "| " << ++i << " | "
            << setw(16) << left << s.prizv
            << "|" << setw(5) << s.kurs << " | "
            << setw(22) << left << speciltyStr[s.specilty]
            << "| " << setw(7) << s.markPhisic
            << "| " << setw(11) << s.markMath;

        // ����� ������ ���� ������� �� ������������
        switch (s.specilty) {
        case KOMPSCINCE:
            cout << "| " << setw(14) << s.program
                << "| " << setw(9) << " "
                << "| " << setw(12) << " " << "|" << endl;
            break;
        case INFORMTECH:
            cout << "| " << setw(14) << " "
                << "| " << setw(9) << s.varmetod
                << "| " << setw(12) << " " << "|" << endl;
            break;
        default:
            cout << "| " << setw(14) << " "
                << "| " << setw(9) << " "
                << "| " << setw(12) << s.pedagogic << "|" << endl;
            break;
        }
    }

    cout << "=====================================================================================================================\n";
    fin.close();
}


int CountSatisfactory(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "���� �� ��������!\n";
        return 0;
    }

    int count = 0;
    while (fin && fin.peek() != EOF) {
        Student s = ReadStudent(fin);

        if (s.markPhisic == 3) count++;
        if (s.markMath == 3) count++;

        int mark;
        switch (s.specilty) {
        case KOMPSCINCE:   mark = s.program; break;
        case INFORMTECH:   mark = s.varmetod; break;
        default:           mark = s.pedagogic; break;
        }

        if (mark == 3) count++;
    }

    cout << "\nʳ������ ������ '���������' (3): " << count << endl;
    fin.close();

    return count;
}


void PrintStudentsWith4s(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "���� �� ��������!\n";
        return;
    }

    cout << "\n��������, �� �������� 4 � ������ � ����������:\n";
    while (fin.peek() != EOF) {
        Student s = ReadStudent(fin);
        if (s.markPhisic >= 4 && s.markMath >= 4)
            cout << " - " << s.prizv << endl;
    }

    fin.close();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* fname = "student.txt";
    int choice;

    do {
        cout << "\n====== ���� ======\n";
        cout << "1. ������ �������� � ����\n";
        cout << "2. ������� ��� ��������\n";
        cout << "3. ���������� ������ '���������'\n";
        cout << "4. �������� � �������� 4 (������ � ����������)\n";
        cout << "0. �����\n";
        cout << "��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            AddStudentsToFile(fname);
            break;

        case 2:
            PrintAllFromFile(fname);
            break;

        case 3:
            CountSatisfactory(fname);
            break;

        case 4:
            PrintStudentsWith4s(fname);
            break;

        case 0:
            cout << "����� � ��������.\n";
            break;

        default:
            cout << "������� ����! ��������� ��.\n";
        }

    } while (choice != 0);

    return 0;
}
