#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
int main()
{
	char name, username;
	int age;

	struct tm newtime;
	char am_pm [] = "AM";
	__time64_t long_time;
	char timebuf[26];
	errno_t err;

	// Get time as 64-bit integer.
	_time64(&long_time);
	// Convert to local time.
	err = _localtime64_s(&newtime, &long_time);
	if (err)
	{
		printf("Invalid argument to _localtime64_s.");
		exit(1);
	}
	if (newtime.tm_hour > 12)        // Set up extension. 
		strcpy_s(am_pm, sizeof(am_pm), "PM");
	if (newtime.tm_hour > 12)        // Convert from 24-hour 
		newtime.tm_hour -= 12;    // to 12-hour clock. 
	if (newtime.tm_hour == 0)        // Set hour to 12 if midnight.
		newtime.tm_hour = 12;

	// Convert to an ASCII representation. 
	err = asctime_s(timebuf, 26, &newtime);
	if (err)
	{
		printf("Invalid argument to asctime_s.");
		exit(1);
	}

	ofstream file;
	file.open("file.txt");

	cout << "What is your name?" << endl;
	cin >> name;
	cout << "What is your age?" << endl;
	cin >> age;
	cout << "What is your username?" << endl;
	cin >> username;

	file << timebuf << am_pm << " :: Your name is: " << name << " Your age is: " << age << " years. Your username is: " << username << endl;
	cout << "Your name is: " << name << " Your age is: " << age << " years. Your username is: " << username << endl;

	system("pause");
	return 0;
}