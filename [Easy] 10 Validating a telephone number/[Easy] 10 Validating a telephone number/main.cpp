#include <iostream>
#include <regex>
#include <vector>

using namespace std;
int main()
{
	string strNumber;
	vector<regex> vecRegex;
	vecRegex.push_back(std::regex("[[:digit:]]{10}"));
	vecRegex.push_back(std::regex("[[:digit:]]{3} - [[:digit:]]{3} - [[:digit:]]{4}"));
	vecRegex.push_back(std::regex("[[:digit:]]{3}.[[:digit:]]{3}.[[:digit:]]{4}"));
	vecRegex.push_back(std::regex("\\([[:digit:]]{3}\\)[[:digit:]]{3} - [[:digit:]]{4}"));
	vecRegex.push_back(std::regex("\\([[:digit:]]{3}\\) [[:digit:]]{3} - [[:digit:]]{4}"));
	vecRegex.push_back(std::regex("[[:digit:]]{3} - [[:digit:]]{4}"));

	string str1 = "1234567890";
	string str2 = "123 - 456 - 7890";
	string str3 = "123.456.7890";
	string str4 = "(123)456 - 7890";
	string str5 = "(123) 456 - 7890"; //(note the white space following the area code)
	string str6 = "456 - 7890";

	while (true)
	{
		cout << "Please enter a number to validate" << endl;
		char input[100];
		cin.getline(input, 100);
		strNumber = input;
		bool bValid = false;
		if (strNumber == "exit")
			break;

		vector<regex>::iterator it;
		for (it = vecRegex.begin(); it < vecRegex.end(); it++)
		{
			if (regex_match(strNumber, (*it)))
			{
				bValid = true;
				break;
			}
		}
		if (bValid)
		{
			cout << "Telephone number valid" << endl;
		}
		else {
			cout << "Telephone number invalid, sorry." << endl;
		}
	}
	return 0;
}