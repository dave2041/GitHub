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
	string strUser, strPass;
	map<string, string> mapUsers;

	while (getline(infile, line))
	{
		strUser = strPass = "";
		sscanf_s(line.c_str(), "%s %s", strUser, strPass);
		mapUsers.insert(strUser, strPass);
	};

	system("pause");
	return 0;
}

