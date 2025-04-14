#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>


using namespace std;

// ������� ��� ��������� ��������� �����
void CreateTXT(const char* fname) {
    ofstream fout(fname);
    char ch;
    string s;
    do {
        cin.get();
        cin.sync();
        cout << "������ �����: ";
        getline(cin, s);
        fout << s << endl;
        cout << "����������? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << endl;
}

// ������� ��� ��������� �����
void PrintTXT(const char* fname) {
    ifstream fin(fname);
    string s;
    cout << "\n���� �����:\n";
    while (getline(fin, s)) {
        cout << s << endl;
    }
    cout << endl;
}


int ProcessLines(const char* sourceFile, const char* destFile) {
    ifstream fin(sourceFile);
    ofstream fout(destFile);
    string line;
    int totalWordCount = 0;

    while (getline(fin, line)) {
        int wordCount = 0;
        int punctuationCount = 0;
        bool inWord = false;

        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];

            if (c != ' ' && c != '\t') {
                if (!inWord) {
                    wordCount++;
                    inWord = true;
                }
            }
            else {
                inWord = false;
            }

            if (c == '.' || c == ',' || c == '!' || c == '?' || c == ':' || c == ';' ||
                c == '-' || c == '(' || c == ')' || c == '"' || c == '\'') {
                punctuationCount++;
            }
        }

        totalWordCount += wordCount;
        fout << wordCount << " " << line << " " << punctuationCount << endl;
    }

    cout << "������� ���������. ��������� ��������� � " << destFile << endl;
    return totalWordCount;
}



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int res = 0;
    char sourceFile[100]; // "source.txt"
    char resultFile[100]; // "result.txt"
    cout << "enter file sourceFile: "; cin >> sourceFile;
    cout << "enter file resultFile: "; cin >> resultFile;

    int choice;
    while (true) {
        cout << "\n����:\n";
        cout << "1. ����������� ����\n";
        cout << "2. �������� ����\n";
        cout << "3. �������� ���� (���������� ����� �� ������� �����)\n";
        cout << "4. �����\n";
        cout << "��� ����: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "choice: "; cin >> res;
            if (res == 0)
            {
                PrintTXT(sourceFile);
                break;
            }
            else {
                PrintTXT(resultFile);
                break;
            }
            
        case 2:
            CreateTXT(sourceFile);
            break;
        case 3:
            ProcessLines(sourceFile, resultFile);
            break;
        case 4:
            return 0;
        default:
            cout << "������� ����.\n";
        }
    }

    return 0;
}
