#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

int Count(const char* str, int i)
{
    size_t len = strlen(str);
    if (i > len - 3)
        return 0;

    if ((str[i] == 'O' && str[i + 1] == 'G' && str[i + 2] == 'O') ||
        (str[i] == 'A' && str[i + 1] == 'G' && str[i + 2] == 'A'))
        return 1 + Count(str, i + 1);
    else
        return Count(str, i + 1);
}

char* Change(char* dest, const char* str, char* t, int i)
{
    size_t len = strlen(str);
    if (i >= len)
    {
        *t = '\0';
        return dest;
    }

    if ((i + 2 < len) &&
        ((str[i] == 'O' && str[i + 1] == 'G' && str[i + 2] == 'O') ||
            (str[i] == 'A' && str[i + 1] == 'G' && str[i + 2] == 'A')))
    {
        strcat_s(t,len + 1, "**");
        return Change(dest, str, t + 2, i + 3);
    }
    else
    {
        *t = str[i];
        *(t + 1) = '\0';
        return Change(dest, str, t + 1, i + 1);
    }
}

char* ChangeWrapper(char* str)
{
    size_t len = strlen(str);
    if (len < 3)
        return str;

    char* tmp = new char[len * 2 + 1];
    tmp[0] = '\0';
    Change(tmp, str, tmp, 0);
    strcpy_s(str,len + 1, tmp);
    delete[] tmp;
    return str;
}

int main()
{
    char str[101];
    std::cout << "Enter string:" << std::endl;
    std::cin.getline(str, 100);

    std::cout << "String contained " << Count(str, 0) << " groups of 'AGA' or 'OGO'" << std::endl;

    std::cout << "Modified string: " << ChangeWrapper(str) << std::endl;

    return 0;
}
