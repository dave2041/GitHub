#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <map>

using namespace std;
int main()
{
	ifstream infile("passwords.txt");
	string line;
	string strUser, strPass, strUserInput, strPassInput = "";
	map<string, string> mapUsers;
	bool bAllowAccess = false;

	while (true)
	{
		bAllowAccess = false;

		cout << "Please enter your username: " << endl;
		cin >> strUserInput;
		cout << "\nPlease enter a password" << endl;
		cin >> strPassInput;

		while (getline(infile, line))
		{
			strUser = strPass = "";
			int commaPos = line.find(',');
			strUser = line.substr(0, commaPos);
			strPass = line.substr(commaPos + 1, line.length());

			if (strUserInput == strUser && strPassInput == strPass)
			{
				bAllowAccess = true;
				break;
			}
		}

		if (bAllowAccess)
		{
			cout << "\n\n----------------------------------------------------" << endl;
			cout << "Welcome to this useless program!" << endl;
			cout << "----------------------------------------------------" << endl << endl;
		}
		else
			cout << "No access for you!!!\n\n";
	}
	system("pause");
	return 0;
}

