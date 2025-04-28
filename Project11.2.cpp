#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

enum Specilty { PHISIC, MATH, INFORMTECH, KOMPSCINCE, TRUDOWE };
string speciltyStr[] = { "Фізика", "Математика", "Інформатика", "Комп’ютерні науки", "Трудове навчання" };

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
    cout << "Скільки студентів додати?: ";
    cin >> N;

    ofstream fout(fname, ios::binary | ios::app);
    if (!fout) {
        cout << "Файл не відкрився для запису!\n";
        return;
    }

    for (int i = 0; i < N; i++) {
        Student s;
        int spec;

        cin.ignore();
        cout << "\nСтудент №" << i + 1 << ":\n";
        cout << " Прізвище: "; getline(cin, s.prizv);
        cout << " Курс: "; cin >> s.kurs;
        cout << " Спеціальність (0-фізика, 1-математика, 2-інформатика, 3-комп. науки, 4-трудове): ";
        cin >> spec;
        s.specilty = (Specilty)spec;
        cout << " Оцінка з фізики: "; cin >> s.markPhisic;
        cout << " Оцінка з математики: "; cin >> s.markMath;

        switch (s.specilty) {
        case KOMPSCINCE:
            cout << " Оцінка з програмування: "; cin >> s.program;
            break;
        case INFORMTECH:
            cout << " Оцінка з чисельних методів: "; cin >> s.varmetod;
            break;
        default:
            cout << " Оцінка з педагогіки: "; cin >> s.pedagogic;
            break;
        }

        WriteStudent(fout, s);
    }

    fout.close();
    cout << "Дані записані у файл.\n";
}


void PrintAllFromFile(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "Файл не відкрився!\n";
        return;
    }

    cout << "=====================================================================================================================\n";
    cout << "| № | Прізвище        | Курс | Спец.                 | Фізика | Математика | Програмування | Числення | Педагогікка |\n";
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

        // Тепер додаємо поля залежно від спеціальності
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
        cout << "Файл не відкрився!\n";
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

    cout << "\nКількість оцінок 'задовільно' (3): " << count << endl;
    fin.close();

    return count;
}


void PrintStudentsWith4s(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "Файл не відкрився!\n";
        return;
    }

    cout << "\nСтуденти, які отримали 4 з фізики і математики:\n";
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
        cout << "\n====== МЕНЮ ======\n";
        cout << "1. Додати студентів у файл\n";
        cout << "2. Вивести усіх студентів\n";
        cout << "3. Порахувати оцінки 'задовільно'\n";
        cout << "4. Студенти з оцінками 4 (фізика і математика)\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
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
            cout << "Вихід з програми.\n";
            break;

        default:
            cout << "Невірний вибір! Спробуйте ще.\n";
        }

    } while (choice != 0);

    return 0;
}
