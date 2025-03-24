#include <iostream>
#include <string>
using namespace std;
bool Ischar(const string s)
{
	int k = 0;
	size_t start = 0;

	if (s[0] == 'a')
	{
		return true;
	}


	while ((start = s.find_first_of(" ", start)) != -1)
	{
		if (s[start + 1] == 'a') {
			return true;
		}

		start++;
	}
	return false;
}
int main()
{
	string str;
	cout << "Enter string:" << endl;
	getline(cin, str);
	bool a = Ischar(str);
	cout << "Length of min groups of digits: " << a << endl;
	return 0;
}