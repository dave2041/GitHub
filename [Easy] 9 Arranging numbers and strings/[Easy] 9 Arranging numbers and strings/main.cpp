#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
	vector<int> vecNumbers;
	vector<string> vecText;
	bool bDone = false;
	bool bText = false;
	char cAnswer;
	cout << "Would you like to enter text? y/n" << endl;
	cin >> cAnswer;

	if (cAnswer == 'y')
		bText = true;

	if (bText)
	{
		cout << "Enter a string and press enter to add it to the list, type \"exit\" to exit" << endl;
		while (!bDone)
		{
			char strTmp[255];
			cin >> strTmp;
			if (strcmp(strTmp, "exit") == 0)
			{
				bDone = true;
			} else
				vecText.push_back(strTmp);
		}
	}
	else {
		cout << "Enter a number and press enter to add it to the list, type -1 to exit" << endl;
		while (!bDone)
		{
			int iTempInt;
			cin >> iTempInt;
			if (iTempInt == -1)
			{
				bDone = true;
			}
			else
				vecNumbers.push_back(iTempInt);

		}
	}
	cout << "Thanks for your input! Here is the sorted list: ";
	if (bText)
	{
		sort(vecText.begin(), vecText.end());
		vector<string>::iterator it;
		for (it = vecText.begin(); it < vecText.end(); it++)
		{
			cout << (*it).c_str() << endl;
		}
	}
	else {
		sort(vecNumbers.begin(), vecNumbers.end());
		vector<int>::iterator it;
		for (it = vecNumbers.begin(); it < vecNumbers.end(); it++)
		{
			cout << (*it) << endl;
		}
	}

	system("pause");
	return 0;
}