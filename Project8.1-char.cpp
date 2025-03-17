#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
int Count(const char* s)
{
	int k = 0;
	const char* substr1 = "AGA";
	const char* substr2 = "OGO";
	const char* pos = s;

	while ((pos = strstr(pos, substr1)) != NULL) {
		k++;
		pos++;
	}

	pos = s;
	while ((pos = strstr(pos, substr2)) != NULL) {
		k++;
		pos++; 
	}

	return k;
}
char* Change(char* s) {
	size_t len = strlen(s);
	char* t = new char[len * 2];
	t[0] = '\0'; 

	char* p;
	int pos1 = 0, pos2 = 0;

	while ((p = strstr(s + pos1, "AGA")) || (p = strstr(s + pos1, "OGO"))) {
		pos2 = p - s;
		strncat_s(t, len * 2, s + pos1, pos2 - pos1);
		strcat_s(t, len * 2, "**"); 
		pos1 = pos2 + 3;
	}

	strcat_s(t, len * 2, s + pos1); 
	strcpy_s(s, len + 1, t); 
	delete[] t; 

	return s;
}

int main()
{
	char str[101];
	
	cout << "Enter string:" << endl;
	cin.getline(str, 100);
	cout << "String contained " << Count(str) << " groups of 'AGA' 'OGO'" << endl;

	char* dest = new char[151];
	dest = Change(str);
	cout << "Modified string (param) : " << str << endl;
	cout << "Modified string (result): " << dest << endl;
	return 0;
}

