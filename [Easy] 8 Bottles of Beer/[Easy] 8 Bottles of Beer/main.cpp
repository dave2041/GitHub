#include <iostream>

using namespace std;
int main()
{
	for (int i = 99; i > 1; i--)
	{
		cout << i << " bottles of beer on the wall. " << i << " bottles of beer. You take one down and pass it around;" << i-1 << " bottles of beer on the wall." << endl;
	}
	cout << 1 << " bottle of beer on the wall. " << 1 << " bottles of beer. You take one down and pass it around;" << 0 << " bottles of beer on the wall." << endl;

	system("pause");
	return 0;
}