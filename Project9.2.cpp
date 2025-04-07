#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h> 
using namespace std;

enum Specilty { PHISIC, MATH, INFORMTECH, KOMPSCINCE, TRUDOWE };

string speciltyStr[] = { "Фізик", "Математик", "Інформатик", "Комп’ютерні науки", "Трудове навчання" };

struct Student
{
    string prizv;
    unsigned kurs;
    Specilty specilty;
    unsigned markPhisic;
    unsigned markMath;
    unsigned markInformatics;
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const Specilty specilty, const unsigned markPhisic);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть N: "; cin >> N;

    Student* p = new Student[N];
    
    int ispecilty;
    Specilty specilty;
    string prizv;
    int found;
    int markPhisics;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - фізичне впорядкування даних" << endl;
        cout << " [4] - індексне впорядкування та вивід даних" << endl;
        cout << " [5] - бінарний пошук працівника за посадою та прізвищем" << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> menuItem;
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
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;
        case 5:
            cout << "Введіть ключі пошуку:" << endl;
            cout << " спеціальність (0 - Фізик, 1 - Математик, 2 - Інформатик, 3 - Комп’ютерні науки, 4 - Трудове навчання): ";
            cin >> ispecilty;
            specilty = (Specilty)ispecilty;
            cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
            cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

            cout << " прізвище: "; getline(cin, prizv);

            cout << "Оцінка з фізики:" ; cin >> markPhisics;
            if ((found = BinSearch(p, N, prizv, specilty, markPhisics)) != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (menuItem != 0);

    return 0;
}

void Create(Student* p, const int N)
{
    int specilty;
    for (int i = 0; i < N; i++)
    {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.ignore();
        cout << " Прізвище: "; getline(cin, p[i].prizv);
        cout << " Курс: "; cin >> p[i].kurs;
        cout << " Спеціальність (0 - фізик, 1 - математик, 2 - інформатик, 3 - Комп’ютерні науки, 4 - Трудове навчання): ";
        cin >> specilty;
        p[i].specilty = (Specilty)specilty;
        cout << " Фізика: "; cin >> p[i].markPhisic;
        cout << " Математика: "; cin >> p[i].markMath;
        cout << " Інформатика: "; cin >> p[i].markInformatics;
        cout << endl;
    }
}

void Print(Student* p, const int N)
{
    cout << "=====================================================================================" << endl;
    cout << "| №  | Прізвище   | Курс | Спеціальність        | Фізика | Математика | Інформатика |" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << i + 1 << " | "
            << setw(10) << left << p[i].prizv << " | "
            << setw(4) << right << p[i].kurs << " | "
            << setw(20) << left << speciltyStr[p[i].specilty] << " | "
            << setw(6) << right << p[i].markPhisic << " | "
            << setw(10) << right << p[i].markMath << " | "
            << setw(11) << right << p[i].markInformatics << " |" << endl;
    }
    cout << "=====================================================================================" << endl;
}


void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
            if ((p[i1].markPhisic > p[i1 + 1].markPhisic)
                ||
                (p[i1].markPhisic == p[i1 + 1].markPhisic &&
                    p[i1].specilty > p[i1 + 1].specilty) 
                || 
                (p[i1].markPhisic == p[i1 + 1].markPhisic &&
                    p[i1].specilty == p[i1 + 1].specilty &&
                    p[i1].prizv > p[i1 + 1].prizv))

            {
                tmp = p[i1];
                p[i1] = p[i1 + 1];
                p[i1 + 1] = tmp;
            }
}

int* IndexSort(Student* p, const int N)
{ 
    int* I = new int[N]; 
    for (int i = 0; i < N; i++)
        I[i] = i; 
    
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((p[I[j]].markPhisic > p[value].markPhisic) 
                ||
                (p[I[j]].markPhisic == p[value].markPhisic &&
                    p[I[j]].specilty > p[value].specilty) 
                ||
                (p[I[j]].markPhisic == p[value].markPhisic &&
                    p[I[j]].specilty == p[value].specilty &&
                    p[I[j]].prizv > p[value].prizv));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{ 
    cout << "=====================================================================================" << endl;
    cout << "| №  | Прізвище   | Курс | Спеціальність        | Фізика | Математика | Інформатика |" << endl;
    cout << "-------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(2) << i + 1 << " | "
            << setw(10) << left << p[I[i]].prizv << " | "
            << setw(4) << right << p[I[i]].kurs << " | "
            << setw(20) << left << speciltyStr[p[I[i]].specilty] << " | "
            << setw(6) << right << p[I[i]].markPhisic << " | "
            << setw(10) << right << p[I[i]].markMath << " | "
            << setw(11) << right << p[I[i]].markInformatics << " |" << endl;
    }
    cout << "=====================================================================================" << endl;
}


int BinSearch(Student* p, const int N, const string prizv, const Specilty specilty, const unsigned markPhisic)
{
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].prizv == prizv && p[m].specilty == specilty && p[m].markPhisic == markPhisic)
            return m;
        if ((p[m].markPhisic < markPhisic)
            
            ||
            (p[m].markPhisic == markPhisic &&
                p[m].specilty < specilty) 
            ||
            (p[m].markPhisic == markPhisic &&
                p[m].specilty == specilty &&
                p[m].prizv < prizv))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}
