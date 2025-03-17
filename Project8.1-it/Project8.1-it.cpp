#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int Count(const char* str) {
    size_t len = strlen(str);
	if (len < 3)
		return 0;

	int k = 0;
	for (int i = 0; i <= len - 3; i++) {
		if ((str[i] == 'O' && str[i + 1] == 'G' && str[i + 2] == 'O') ||
			(str[i] == 'A' && str[i + 1] == 'G' && str[i + 2] == 'A')) {
			k++;
		}
	}
	return k;
}

char* Change(char* str)
{
    size_t len = strlen(str);
    if (len < 3)
        return str;

    char* tmp = new char[len + 1];
    tmp[0] = '\0';

    size_t i = 0;
    while (i < len)
    {
        if ((i + 2 < len) &&
            ((str[i] == 'O' && str[i + 1] == 'G' && str[i + 2] == 'O') ||
                (str[i] == 'A' && str[i + 1] == 'G' && str[i + 2] == 'A')))
        {
            strcat_s(tmp,len + 1, "**");
            i += 3;
        }
        else
        {
            size_t l = strlen(tmp);
            tmp[l] = str[i];
            tmp[l + 1] = '\0';
            i++;
        }
    }

    strcpy_s(str, len + 1, tmp);
    delete[] tmp;

    return str;
}

int main()
{
	char str[101];
	cout << "Enter string:" << endl;
	cin.getline(str, 100);
	cout << "String contained " << Count(str) << " groups of 'AGA OGO'" << endl;

	char* dest = new char[151];
    
	dest = Change(str);
    cout << "Modified string (param) : " << str << endl;
	cout << "Modified string (result): " << dest << endl;
	return 0;
}