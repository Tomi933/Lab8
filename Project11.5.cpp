#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <Windows.h>
using namespace std;

const int MAX = 100;

const char* FACULTY_NAMES[] = {
    "Фізико-математичний", "Економічний",
    "Філологічний", "Інформатики", "Педагогічний"
};

const char* GROUP_NAMES[] = {
    "Група 101", "Група 102", "Група 201", "Група 202", "Група 301"
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
    cout << "Кількість студентів: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Student s;
        cout << "\nСтудент #" << i + 1 << endl;
        cout << "Прізвище: ";
        cin.ignore();
        cin.getline(s.prizv, 50);
        cout << "Курс: "; cin >> s.kurs;
        cout << "Факультет (0-4): "; cin >> s.facultyId;
        cout << "Група (0-4): "; cin >> s.groupId;
        cout << "Оцінка з математики: "; cin >> s.math;
        cout << "Оцінка з фізики: "; cin >> s.physics;
        cout << "Оцінка з інформатики: "; cin >> s.informatics;

        fout.write((char*)&s, sizeof(Student));
    }
    fout.close();
}

void readFile(const char* filename) {
    ifstream fin(filename, ios::binary);
    if (!fin) return;

    Student s;
    cout << left << setw(15) << "Прізвище" << setw(6) << "Курс" << setw(25)
        << "Факультет" << setw(12) << "Група" << "Математика  Фізика  Інформатика\n";

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
    cout << "Прізвище: ";
    cin.ignore();
    cin.getline(s.prizv, 50);
    cout << "Курс: "; cin >> s.kurs;
    cout << "Факультет (0-4): "; cin >> s.facultyId;
    cout << "Група (0-4): "; cin >> s.groupId;
    cout << "Оцінка з математики: "; cin >> s.math;
    cout << "Оцінка з фізики: "; cin >> s.physics;
    cout << "Оцінка з інформатики: "; cin >> s.informatics;

    fout.write((char*)&s, sizeof(Student));
    fout.close();
}

void editFile(const char* filename) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) return;

    char target[50];
    cout << "Введіть прізвище для редагування: ";
    cin.ignore();
    cin.getline(target, 50);

    Student s;
    while (!file.eof()) {
        streampos pos = file.tellg(); // запам'ятовуємо позицію перед зчитуванням
        file.read((char*)&s, sizeof(Student));

        if (file && strcmp(s.prizv, target) == 0) {
            cout << "Знайдено. Введіть нові дані:\n";
            cout << "Прізвище: ";
            cin.getline(s.prizv, 50);
            cout << "Курс: "; cin >> s.kurs;
            cout << "Факультет (0-4): "; cin >> s.facultyId;
            cout << "Група (0-4): "; cin >> s.groupId;
            cout << "Оцінка з математики: "; cin >> s.math;
            cout << "Оцінка з фізики: "; cin >> s.physics;
            cout << "Оцінка з інформатики: "; cin >> s.informatics;

            file.seekp(pos); // повертаємось у позицію для перезапису
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
    cout << "\nСтуденти з середнім балом 4.5:\n";
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

    // сортуємо індекси за успішністю
    int index[5] = { 0, 1, 2, 3, 4 };
    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 5; j++)
            if (avg[index[i]] > avg[index[j]])
                swap(index[i], index[j]);

    cout << "\nФакультети за зростанням успішності:\n";
    for (int i = 0; i < 5; i++) {
        cout << FACULTY_NAMES[index[i]] << ": " << fixed << setprecision(2) << avg[index[i]] << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char filename[100];
    cout << "Введіть ім'я файлу: ";
    cin.getline(filename, 100);

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Створити файл\n";
        cout << "2. Прочитати файл\n";
        cout << "3. Доповнити файл\n";
        cout << "4. Редагувати студента\n";
        cout << "5. Видалити студентів з трьома двійками (1 курс)\n";
        cout << "6. Студенти з середнім балом 4.5\n";
        cout << "7. Сортування факультетів за успішністю\n";
        cout << "0. Вихід\nВаш вибір: ";
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
