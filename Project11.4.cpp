#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

struct Route {
    string start;
    string end;
    unsigned number;
};

// Запис одного маршруту у файл
void WriteRoute(fstream& f, const Route& r) {
    size_t len;

    len = r.start.size();
    f.write((char*)&len, sizeof(len));
    f.write(r.start.c_str(), len);

    len = r.end.size();
    f.write((char*)&len, sizeof(len));
    f.write(r.end.c_str(), len);

    f.write((char*)&r.number, sizeof(r.number));
}

bool ReadRoute(fstream& f, Route& r) {
    size_t len;
    if (!f.read((char*)&len, sizeof(len))) return false;
    r.start.resize(len);
    f.read(&r.start[0], len);

    if (!f.read((char*)&len, sizeof(len))) return false;
    r.end.resize(len);
    f.read(&r.end[0], len);

    if (!f.read((char*)&r.number, sizeof(r.number))) return false;

    return true;
}

// Переміщення позиції файлу до N-го запису
void SeekToRecord(fstream& f, int index) {
    f.seekg(0, ios::beg);
    for (int i = 0; i < index; i++) {
        Route tmp;
        ReadRoute(f, tmp);
    }
    f.seekp(f.tellg());
}

void AddRoutes(const char* fname, const int N) {
    fstream f(fname, ios::binary | ios::out | ios::app);
    for (int i = 0; i < N; i++) {
        Route r;
        cin.ignore();
        cout << "Новий маршрут №" << i + 1 << ":\n";
        cout << " Початковий пункт: "; getline(cin, r.start);
        cout << " Кінцевий пункт: "; getline(cin, r.end);
        cout << " Номер маршруту: "; cin >> r.number;
        WriteRoute(f, r);
    }
    f.close();
}


void PrintRoutes(const char* fname) {
    fstream f(fname, ios::binary | ios::in);
    if (!f) {
        cout << "Не вдалося відкрити файл для читання!\n";
        return;
    }

    Route r;
    int index = 0;
    while (ReadRoute(f, r)) {
        cout << setw(3) << ++index << ". "
            << setw(15) << left << r.start
            << setw(15) << left << r.end
            << "№" << r.number << endl;
    }

    if (index == 0)
        cout << "Файл порожній або не містить жодного правильного запису.\n";

    f.close();
}


bool FindByPoint(const char* fname, const string& point) {
    fstream f(fname, ios::binary | ios::in);
    Route r;
    bool m = true;
    bool found = false;
    while (ReadRoute(f, r)) {
        if (r.start == point || r.end == point) {
            found = true;
            cout << setw(15) << left << r.start
                << setw(15) << left << r.end
                << setw(10) << r.number << endl;
            m = true;
        }
    }
    if (!found) cout << "Маршрутів із пунктом \"" << point << "\" не знайдено.\n";
    f.close();

    return m;
}

int CountRecords(const char* fname) {
    fstream f(fname, ios::binary | ios::in);
    int count = 0;
    Route r;
    while (ReadRoute(f, r)) count++;
    f.close();
    return count;
}

void SortFile(const char* fname) {
    fstream f(fname, ios::binary | ios::in | ios::out);
    if (!f) {
        cout << "Помилка відкриття файлу!\n";
        return;
    }

    int n = CountRecords(fname);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Зчитати r1
            f.clear();
            f.seekg(0, ios::beg);
            Route r1, r2;

            // Пропускаємо j записів
            for (int k = 0; k < j; k++) {
                ReadRoute(f, r1);
            }
            streampos pos1 = f.tellg();  // позиція r1
            ReadRoute(f, r1);
            streampos pos2 = f.tellg();  // позиція r2
            ReadRoute(f, r2);

            if (r1.number > r2.number) {
                // Поміняти місцями r1 і r2
                f.clear();
                f.seekp(pos1);
                WriteRoute(f, r2);
                f.seekp(pos2);
                WriteRoute(f, r1);
            }
        }
    }

    f.close();
}



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char filename[100];
    cout << "Введіть ім'я файлу: ";
    //routs.txt
    cin >> filename;

    if (!filename) {
        cout << "Файл не відкрився або порожній!\n";

    }
    int menuItem;
    do {
        cout << "\nМеню:\n";
        cout << " [1] - Ввести дані у файл\n";
        cout << " [2] - Вивести всі маршрути\n";
        cout << " [3] - Пошук за пунктом\n";
        cout << " [4] - Відсортувати за номером маршруту\n";
        cout << " [0] - Вихід\n";
        cout << "Ваш вибір: ";
        cin >> menuItem;

        switch (menuItem) {
        case 1: {
            int n;
            cout << "Кількість маршрутів: ";
            cin >> n;
            AddRoutes(filename, n);
            break;
        }
        case 2:
            PrintRoutes(filename);
            break;
        case 3: {
            cin.ignore();
            string point;
            cout << "Введіть назву пункту: ";
            getline(cin, point);
            FindByPoint(filename, point);
            break;
        }
        case 4:
            SortFile(filename);
            cout << "Сортування завершено.\n";
            break;
        case 0:
            break;
        default:
            cout << "Неправильний вибір!\n";
        }

    } while (menuItem != 0);

    return 0;
}
