#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

enum Specialty { PHYSICS, MATH, INFOTECH, COMPSCINCE, LABOR };
const string specialtyStr[] = { "Фізика", "Математика", "Інформатика", "Комп’ютерні науки", "Трудове навчання" };

struct Student {
    string surname;
    unsigned course;
    Specialty specialty;
    unsigned markPhysics;
    unsigned markMath;
    union {
        unsigned markProg;
        unsigned markMetods;
        unsigned markPed;
    };
};

void WriteStudent(ofstream& fout, const Student& s) {
    size_t len = s.surname.size();
    fout.write((char*)&len, sizeof(len));
    fout.write(s.surname.c_str(), len);
    fout.write((char*)&s.course, sizeof(s.course));
    fout.write((char*)&s.specialty, sizeof(s.specialty));
    fout.write((char*)&s.markPhysics, sizeof(s.markPhysics));
    fout.write((char*)&s.markMath, sizeof(s.markMath));

    switch (s.specialty) {
    case COMPSCINCE:
        fout.write((char*)&s.markProg, sizeof(s.markProg));
        break;
    case INFOTECH:
        fout.write((char*)&s.markMetods, sizeof(s.markMetods));
        break;
    default:
        fout.write((char*)&s.markPed, sizeof(s.markPed));
        break;
    }
}

void WriteBIN(const char* fname, int N) {
    ofstream fout(fname, ios::binary | ios::app);
    for (int i = 0; i < N; i++) {
        Student s;
        int spec;
        cin.ignore();
        cout << "\nСтудент #" << i + 1 << ":\n";
        cout << "Прізвище: "; getline(cin, s.surname);
        cout << "Курс: "; cin >> s.course;
        cout << "Спеціальність (0 - Фізика, 1 - Математика, 2 - Інформатика, 3 - Комп'ютерні науки, 4 - Трудове): "; cin >> spec;
        s.specialty = (Specialty)spec;
        cout << "Оцінка з фізики: "; cin >> s.markPhysics;
        cout << "Оцінка з математики: "; cin >> s.markMath;
        switch (s.specialty) {
        case COMPSCINCE: cout << "Оцінка з програмування: "; cin >> s.markProg; break;
        case INFOTECH: cout << "Оцінка з чисельних методів: "; cin >> s.markMetods; break;
        default: cout << "Оцінка з педагогіки: "; cin >> s.markPed; break;
        }

        WriteStudent(fout, s);
    }
    fout.close();
}

bool ReadStudent(ifstream& fin, Student& s) {
    size_t len;
    if (!fin.read((char*)&len, sizeof(len)))
        return false;

    s.surname.resize(len);
    fin.read(&s.surname[0], len);
    fin.read((char*)&s.course, sizeof(s.course));
    fin.read((char*)&s.specialty, sizeof(s.specialty));
    fin.read((char*)&s.markPhysics, sizeof(s.markPhysics));
    fin.read((char*)&s.markMath, sizeof(s.markMath));

    switch (s.specialty) {
    case COMPSCINCE: fin.read((char*)&s.markProg, sizeof(s.markProg)); break;
    case INFOTECH:   fin.read((char*)&s.markMetods, sizeof(s.markMetods)); break;
    default:         fin.read((char*)&s.markPed, sizeof(s.markPed)); break;
    }

    return true;
}

void PrintAll(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "Файл не відкрився або порожній!\n";
        return;
    }

    cout << "====================================================================================================================\n";
    cout << "| № | Прізвище        | Курс | Спец                 | Фізика | Математика | Програмування | Числення | Педагогіка |\n";
    cout << "--------------------------------------------------------------------------------------------------------------------\n";

    int i = 1;
    Student s;
    while (ReadStudent(fin, s)) {
        cout << "| " << left << setw(2) << i++ << "| "
            << setw(16) << left << s.surname
            << "| " << setw(5) << s.course << "|"
            << setw(22) << left << specialtyStr[s.specialty]
            << "|" << setw(8) << s.markPhysics
            << "| " << setw(11) << s.markMath;

        switch (s.specialty) {
        case COMPSCINCE:
            cout << "| " << setw(14) << s.markProg
                << "| " << setw(9) << " "
                << "| " << setw(12) << " " << "|" << endl;
            break;
        case INFOTECH:
            cout << "| " << setw(14) << " "
                << "| " << setw(9) << s.markMetods
                << "| " << setw(12) << " " << "|" << endl;
            break;
        default:
            cout << "| " << setw(14) << " "
                << "| " << setw(9) << " "
                << "| " << setw(12) << s.markPed << "|" << endl;
            break;
        }
    }

    cout << "====================================================================================================================\n";
    fin.close();
}

int BinSearch(const char* fname, string surname, Specialty specialty, unsigned markPhysics) {
    ifstream fin(fname, ios::binary);
    if (!fin) return -1;

    int index = 0;
    Student s;
    while (ReadStudent(fin, s)) {
        if (s.surname == surname && s.specialty == specialty && s.markPhysics == markPhysics) {
            return index;
        }
        index++;
    }
    return -1;
}

int CountRecords(const char* fname) {
    ifstream fin(fname, ios::binary);
    if (!fin) return 0;

    int count = 0;
    Student s;
    while (ReadStudent(fin, s)) {
        count++;
    }
    return count;
}

void SortInFile(const char* fname) {
    int N = CountRecords(fname);
    if (N <= 1) return;

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            ifstream f(fname, ios::binary | ios::in | ios::out);
            Student s1, s2;

            streampos pos1 = f.tellg();
            for (int k = 0; k <= j; k++) {
                ReadStudent(f, s1);
                pos1 = f.tellg();
            }

            streampos pos2 = f.tellg();
            ReadStudent(f, s2);

            bool needSwap = false;
            if ((s1.markPhysics > s2.markPhysics) ||
                (s1.markPhysics == s2.markPhysics && s1.specialty > s2.specialty) ||
                (s1.markPhysics == s2.markPhysics && s1.specialty == s2.specialty && s1.surname > s2.surname)) {
                needSwap = true;
            }

            if (needSwap) {
                f.close();

                // Переписуємо обидва записи, помінявши їх місцями
                fstream f2(fname, ios::binary | ios::in | ios::out);

                f2.seekp(pos1 - (streamoff)(sizeof(size_t) + s1.surname.size() + sizeof(unsigned) * 4));
                size_t len1 = s2.surname.size();
                f2.write((char*)&len1, sizeof(len1));
                f2.write(s2.surname.c_str(), len1);
                f2.write((char*)&s2.course, sizeof(s2.course));
                f2.write((char*)&s2.specialty, sizeof(s2.specialty));
                f2.write((char*)&s2.markPhysics, sizeof(s2.markPhysics));
                f2.write((char*)&s2.markMath, sizeof(s2.markMath));
                switch (s2.specialty) {
                case COMPSCINCE: f2.write((char*)&s2.markProg, sizeof(s2.markProg)); break;
                case INFOTECH: f2.write((char*)&s2.markMetods, sizeof(s2.markMetods)); break;
                default: f2.write((char*)&s2.markPed, sizeof(s2.markPed)); break;
                }

                f2.seekp(pos2 - (streamoff)(sizeof(size_t) + s2.surname.size() + sizeof(unsigned) * 4));
                size_t len2 = s1.surname.size();
                f2.write((char*)&len2, sizeof(len2));
                f2.write(s1.surname.c_str(), len2);
                f2.write((char*)&s1.course, sizeof(s1.course));
                f2.write((char*)&s1.specialty, sizeof(s1.specialty));
                f2.write((char*)&s1.markPhysics, sizeof(s1.markPhysics));
                f2.write((char*)&s1.markMath, sizeof(s1.markMath));
                switch (s1.specialty) {
                case COMPSCINCE: f2.write((char*)&s1.markProg, sizeof(s1.markProg)); break;
                case INFOTECH: f2.write((char*)&s1.markMetods, sizeof(s1.markMetods)); break;
                default: f2.write((char*)&s1.markPed, sizeof(s1.markPed)); break;
                }

                f2.close();
            }
        }
    }
    cout << "Файл відсортовано.\n";
}

void IndexSort(const char* fname, int* index) {
    int N = CountRecords(fname);
    for (int i = 0; i < N; i++) index[i] = i;

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            ifstream fin(fname, ios::binary);
            Student s1, s2;

            // Зчитуємо s1
            int skip1 = index[j];
            for (int k = 0; k <= skip1; k++)
                ReadStudent(fin, s1);

            // Зчитуємо s2
            fin.clear();
            fin.seekg(0);
            int skip2 = index[j + 1];
            for (int k = 0; k <= skip2; k++)
                ReadStudent(fin, s2);
            fin.close();

            // Порівняння
            bool needSwap = false;
            if ((s1.markPhysics > s2.markPhysics) ||
                (s1.markPhysics == s2.markPhysics && s1.specialty > s2.specialty) ||
                (s1.markPhysics == s2.markPhysics && s1.specialty == s2.specialty && s1.surname > s2.surname)) {
                needSwap = true;
            }

            if (needSwap) {
                swap(index[j], index[j + 1]);
            }
        }
    }
}
void PrintIndexed(const char* fname, int* index) {
    ifstream fin(fname, ios::binary);
    if (!fin) {
        cout << "Файл не відкрився або порожній!\n";
        return;
    }

    cout << "====================================================================================================================\n";
    cout << "| № | Прізвище        | Курс | Спец                 | Фізика | Математика | Програмування | Числення | Педагогіка |\n";
    cout << "--------------------------------------------------------------------------------------------------------------------\n";

    int i = 1;
    int total = CountRecords(fname);
    for (int k = 0; k < total; k++) {
        fin.clear();
        fin.seekg(0);
        Student s;
        for (int j = 0; j <= index[k]; j++) {
            ReadStudent(fin, s);
        }

        cout << "| " << left << setw(2) << i++ << "| "
            << setw(16) << left << s.surname
            << "| " << setw(5) << s.course << "|"
            << setw(22) << left << specialtyStr[s.specialty]
            << "|" << setw(8) << s.markPhysics
            << "| " << setw(11) << s.markMath;

        switch (s.specialty) {
        case COMPSCINCE:
            cout << "| " << setw(14) << s.markProg
                << "| " << setw(9) << " "
                << "| " << setw(12) << " " << "|" << endl;
            break;
        case INFOTECH:
            cout << "| " << setw(14) << " "
                << "| " << setw(9) << s.markMetods
                << "| " << setw(12) << " " << "|" << endl;
            break;
        default:
            cout << "| " << setw(14) << " "
                << "| " << setw(9) << " "
                << "| " << setw(12) << s.markPed << "|" << endl;
            break;
        }
    }

    cout << "====================================================================================================================\n";
    fin.close();
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* fname = "poject.txt";
    int choice;
    do {
        cout << "\n=== МЕНЮ ===\n";
        cout << "1. Додати студентів\n";
        cout << "2. Вивести файл\n";
        cout << "3. Сортувати файл\n";
        cout << "4. Бінарний пошук\n";
        cout << "5. Індексне сортування (вивід)\n";
        cout << "0. Вихід\nВаш вибір: ";
        cin >> choice;
        switch (choice) {
        case 1: {
            int N;
            cout << "Скільки студентів?: ";
            cin >> N;
            WriteBIN(fname, N);
            break;
        }
        case 2:
            PrintAll(fname);
            break;
        case 3:
            SortInFile(fname);
            break;
        case 4: {
            string s;
            int sp;
            unsigned mark;
            cin.ignore();
            cout << "Прізвище: "; getline(cin, s);
            cout << "Спеціальність (0-4): "; cin >> sp;
            cout << "Оцінка з фізики: "; cin >> mark;

            int result = BinSearch(fname, s, (Specialty)sp, mark);
            if (result != -1)
                cout << "Запис знайдено! Індекс: " << result << endl;
            else
                cout << "Запис не знайдено.\n";
            break;
        }
        case 5: {
            int N = CountRecords(fname);
            if (N == 0) {
                cout << "Файл порожній або не існує.\n";
                break;
            }
            int* index = new int[N];
            IndexSort(fname, index);
            PrintIndexed(fname, index);
            delete[] index;
            break;
        }
        case 0:
            cout << "До побачення!\n";
            break;
        default:
            cout << "Невірний вибір! Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}

