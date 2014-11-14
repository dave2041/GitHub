#include <string>
#include <iostream>
using namespace std;

string EncryptMessage(string message, bool encrypt = false)
{
	for (unsigned int i = 0; i < message.size(); i++)
	{
		if (encrypt)
			message[i] = message[i] + 14;
		else
			message[i] = message[i] - 14;
	}
	return message;
}

int main(int argc, char *argv [])
{
	string strMessage = "Don't Shoot!";
	cout << "Message is: " << strMessage << endl;
	string strEncrypted = EncryptMessage(strMessage, true);
	cout << "Message is: " << strEncrypted << endl;
	string strDecrypted = EncryptMessage(strEncrypted, false);
	cout << "Message is: " << strDecrypted << endl;

	system("pause");
	return 0;
}