#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <Windows.h>
using namespace std;

const int MAX = 100;

const char* FACULTY_NAMES[] = {
    "Գ����-������������", "����������",
    "Գ���������", "�����������", "�����������"
};

const char* GROUP_NAMES[] = {
    "����� 101", "����� 102", "����� 201", "����� 202", "����� 301"
};

struct Student {
    char prizv[50];
    int kurs;
    int facultyId;
    int groupId;
    int math;
    int physics;
    int informatics;
};

void createFile(const char* filename) {
    ofstream fout(filename, ios::binary);
    if (!fout) return;

    int n;
    cout << "ʳ������ ��������: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Student s;
        cout << "\n������� #" << i + 1 << endl;
        cout << "�������: ";
        cin.ignore();
        cin.getline(s.prizv, 50);
        cout << "����: "; cin >> s.kurs;
        cout << "��������� (0-4): "; cin >> s.facultyId;
        cout << "����� (0-4): "; cin >> s.groupId;
        cout << "������ � ����������: "; cin >> s.math;
        cout << "������ � ������: "; cin >> s.physics;
        cout << "������ � �����������: "; cin >> s.informatics;

        fout.write((char*)&s, sizeof(Student));
    }
    fout.close();
}

void readFile(const char* filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) return;

    Student s;
    cout << left << setw(15) << "�������" << setw(6) << "����" << setw(25)
        << "���������" << setw(12) << "�����" << "����������  Գ����  �����������\n";

    while (fin.read((char*)&s, sizeof(Student))) {
        cout << setw(15) << s.prizv << setw(6) << s.kurs
            << setw(25) << FACULTY_NAMES[s.facultyId]
            << setw(12) << GROUP_NAMES[s.groupId]
            << setw(8) << s.math << setw(9) << s.physics << setw(10) << s.informatics << endl;
    }

    fin.close();
}

void appendFile(const char* filename) {
    ofstream fout(filename, ios::binary | ios::app);
    if (!fout) return;

    Student s;
    cout << "�������: ";
    cin.ignore();
    cin.getline(s.prizv, 50);
    cout << "����: "; cin >> s.kurs;
    cout << "��������� (0-4): "; cin >> s.facultyId;
    cout << "����� (0-4): "; cin >> s.groupId;
    cout << "������ � ����������: "; cin >> s.math;
    cout << "������ � ������: "; cin >> s.physics;
    cout << "������ � �����������: "; cin >> s.informatics;

    fout.write((char*)&s, sizeof(Student));
    fout.close();
}

void editFile(const char* filename) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) return;

    char target[50];
    cout << "������ ������� ��� �����������: ";
    cin.ignore();
    cin.getline(target, 50);

    Student s;
    while (!file.eof()) {
        streampos pos = file.tellg(); // �����'������� ������� ����� �����������
        file.read((char*)&s, sizeof(Student));

        if (file && strcmp(s.prizv, target) == 0) {
            cout << "��������. ������ ��� ���:\n";
            cout << "�������: ";
            cin.getline(s.prizv, 50);
            cout << "����: "; cin >> s.kurs;
            cout << "��������� (0-4): "; cin >> s.facultyId;
            cout << "����� (0-4): "; cin >> s.groupId;
            cout << "������ � ����������: "; cin >> s.math;
            cout << "������ � ������: "; cin >> s.physics;
            cout << "������ � �����������: "; cin >> s.informatics;

            file.seekp(pos); // ����������� � ������� ��� ����������
            file.write((char*)&s, sizeof(Student));
            break;
        }
    }

    file.close();
}


void deleteStudentsWithThreeTwos(const char* filename) {
    ifstream fin(filename, ios::binary);
    ofstream fout("temp.bin", ios::binary);
    Student s;

    while (fin.read((char*)&s, sizeof(Student))) {
        int count = 0;
        if (s.math == 2) count++;
        if (s.physics == 2) count++;
        if (s.informatics == 2) count++;
        if (!(s.kurs == 1 && count == 3)) {
            fout.write((char*)&s, sizeof(Student));
        }
    }

    fin.close();
    fout.close();
    remove(filename);
    rename("temp.bin", filename);
}

void WriteRoute(fstream& fout, const Student& s) {
    fout.write((char*)&s, sizeof(Student));
}

int queryAverage45(const char* filename) {
    ifstream fin(filename, ios::binary);
    Student s;
    int count = 0;
    cout << "\n�������� � ������� ����� 4.5:\n";
    while (fin.read((char*)&s, sizeof(Student))) {
        double avg = (s.math + s.physics + s.informatics) / 3.0;
        if (avg >= 4.5) {
            count++;
            cout << setw(10)<< s.prizv << " | " << GROUP_NAMES[s.groupId]
                << " | " << FACULTY_NAMES[s.facultyId] << endl;
        }
    }

    fin.close();
    return count;
}

void sortFacultiesBySuccess(const char* filename) {
    ifstream fin(filename, ios::binary);
    int facultySum[5] = {}, facultyCount[5] = {};
    Student s;

    while (fin.read((char*)&s, sizeof(Student))) {
        facultySum[s.facultyId] += s.math + s.physics + s.informatics;
        facultyCount[s.facultyId] += 3;
    }
    fin.close();

    double avg[5];
    for (int i = 0; i < 5; i++) {
        avg[i] = (facultyCount[i] ? (double)facultySum[i] / facultyCount[i] : 0);
    }

    // ������� ������� �� ��������
    int index[5] = { 0, 1, 2, 3, 4 };
    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 5; j++)
            if (avg[index[i]] > avg[index[j]])
                swap(index[i], index[j]);

    cout << "\n���������� �� ���������� ��������:\n";
    for (int i = 0; i < 5; i++) {
        cout << FACULTY_NAMES[index[i]] << ": " << fixed << setprecision(2) << avg[index[i]] << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char filename[100];
    cout << "������ ��'� �����: ";
    cin.getline(filename, 100);

    int choice;
    do {
        cout << "\n����:\n";
        cout << "1. �������� ����\n";
        cout << "2. ��������� ����\n";
        cout << "3. ��������� ����\n";
        cout << "4. ���������� ��������\n";
        cout << "5. �������� �������� � ������ ������� (1 ����)\n";
        cout << "6. �������� � ������� ����� 4.5\n";
        cout << "7. ���������� ���������� �� ��������\n";
        cout << "0. �����\n��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1: createFile(filename); break;
        case 2: readFile(filename); break;
        case 3: appendFile(filename); break;
        case 4: editFile(filename); break;
        case 5: deleteStudentsWithThreeTwos(filename); break;
        case 6: queryAverage45(filename); break;
        case 7: sortFacultiesBySuccess(filename); break;
        }

    } while (choice != 0);

    return 0;
}
