#include <iostream>
#include <string>
using namespace std;
int Count(const string s)
{
	int k = 0;
	size_t pos = 0;
	while ((pos = s.find('AGA', pos)) != -1 || (pos = s.find('OGO', pos)) != -1)
	{
		pos++;
		k++;
	}
	return k;
}
string Change(string& s)
{
	size_t pos = 0;
	while (true) {
		size_t posAGA = s.find("AGA", pos);
		size_t posOGO = s.find("OGO", pos);

		if (posAGA == -1 && posOGO == -1) break; 

		
		if (posAGA != -1 && (posOGO == -1 || posAGA < posOGO)) {
			pos = posAGA;
		}
		else {
			pos = posOGO;
		}

		s.replace(pos, 3, "**"); 
		pos += 2; 
	}
	return s;
}
int main()
{
	string str;
	cout << "Enter string:" << endl;
	getline(cin, str);
	cout << "String contained " << Count(str) << " groups of 'AGA' 'OGO'" << endl;
	string dest = Change(str);
	cout << "Modified string (param) : " << str << endl;
	cout << "Modified string (result): " << dest << endl;
	return 0;
}