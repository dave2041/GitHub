#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void FixString(string line, char separator)
{
	int day, month, year = 0;
	char output[255];
	vector<string> vecMonths = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

	switch (separator)
	{
	case '#':
		line.erase(remove(line.begin(), line.end(), '#'), line.end());
		month = atoi(line.substr(0, 2).c_str());
		year = atoi(line.substr(2, 2).c_str());
		day = atoi(line.substr(4, 2).c_str());
		break;
	case '/':
		line.erase(remove(line.begin(), line.end(), '/'), line.end());
		month = atoi(line.substr(0, 2).c_str());
		day = atoi(line.substr(2, 2).c_str());
		year = atoi(line.substr(4, 2).c_str());
		break;
	case '-':
		line.erase(remove(line.begin(), line.end(), '-'), line.end());
		year = atoi(line.substr(0, 4).c_str());
		month = atoi(line.substr(4, 2).c_str());
		day = atoi(line.substr(6, 2).c_str());
		break;
	case '*':
		line.erase(remove(line.begin(), line.end(), '*'), line.end());
		day = atoi(line.substr(0, 2).c_str());
		month = atoi(line.substr(2, 2).c_str());
		year = atoi(line.substr(4, 4).c_str());
		break;
	case ',':
		string strMonth = line.substr(0, 3);
		for (unsigned int i = 0; i < vecMonths.size(); i++)
			if (strMonth == vecMonths[i])
				month = i;
		line.erase(remove(line.begin(), line.end(), ','), line.end());
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		day = atoi(line.substr(3, 2).c_str());
		if (line.length() == 7)
			year = atoi(line.substr(5, 2).c_str());
		else
			year = atoi(line.substr(7, 2).c_str());
		break;
	}

	if (year >= 50)
		year += 1900;
	else
		year += 2000;

	sprintf_s(output, "%d-%d-%d", year, month, day);
	cout << output << endl;
}

int main()
{
	ifstream infile("TestDates.txt");
	string line;

	while (getline(infile, line))
	{
		if (line.find('#') != std::string::npos)
			FixString(line, '#');

		if (line.find('-') != std::string::npos)
			FixString(line, '-');

		if (line.find('/') != std::string::npos)
			FixString(line, '/');
		

		if (line.find('*') != std::string::npos)
			FixString(line, '*');

		if (line.find(',') != std::string::npos)
			FixString(line, ',');
	};
	return 0;
}