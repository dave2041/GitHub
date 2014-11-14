#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>

using namespace std;
int main(int argv, char* argc)
{
	int iNumOfPasswords;
	int iLength;
	string strTempPassword;
	vector<string> vecPasswords;

	cout << "How long would you like the passwords?" << endl;
	cin >> iLength;
	cout << "How Many would you like?" << endl;
	cin >> iNumOfPasswords;

	for (int i = 0; i < iNumOfPasswords; i++)
	{
		strTempPassword = "";
		for (int j = 0; j < iLength; j++)
		{
			int iTempAscii = rand() % 57 + 65;
			strTempPassword += static_cast<char>(iTempAscii);
		}
		vecPasswords.push_back(strTempPassword);
	}

	system("pause");
	return 0;
}