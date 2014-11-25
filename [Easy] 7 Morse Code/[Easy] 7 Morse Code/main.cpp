#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<char, string> mapMorse;

string StringToMorse(string strInput)
{
	string strOutput = "";
	if (strInput.size() > 0)
	{
		for (unsigned int i = 0; i < strInput.size(); i++)
		{
			if (strInput[i] == ' ') //replace spaces with ' / '
			{
				strOutput += " / ";
			} else {
				map<char, string>::iterator it;
				for (it = mapMorse.begin(); it != mapMorse.end(); it++)
				{
					if (it->first == strInput[i])
					{
						strOutput += it->second;
						if (i != strInput.size()-1) //if not at the end
							strOutput += " ";
					}
				}
			}
		}
	} else
		return "StringToMorse Failed!";
	return strOutput;
}

string MorseToString(string strInput)
{
	string strOutput = "";
	int previousSpacePos = -1;
	bool bAddSpace = false;
	string strTemp = "";

	if (strInput.size() > 0)
	{
		for (unsigned int i = 0; i < strInput.size(); i++)
		{
			if(((strInput[i] == ' ' || strInput[i] == '/') && i > 0) || i == strInput.size()-1)
			{
				if(i + 1 <= strInput.size())
				{
					if (strInput[i] == '/')
					{
						bAddSpace = true;
					} else {
						if (i == strInput.size()-1) // are we at the end of the string?
							strTemp = strInput.substr(previousSpacePos + 1, i - (previousSpacePos));
						else
							strTemp = strInput.substr(previousSpacePos+1, i-(previousSpacePos+1));
						previousSpacePos = i;
						map<char, string>::iterator it;
						for (it = mapMorse.begin(); it != mapMorse.end(); it++)
						{
							if (it->second == strTemp)
								strOutput += it->first;
						}
					}
					if (bAddSpace)
					{
						bAddSpace = false;
						strOutput += ' ';
					}
				} // if not out of bounds
			} // if space or slash
		} //for loop
	} // sanity check
	else
		return "MorseToString Failed!";
	return strOutput;	
}

int main()
{
	mapMorse['a'] = ".-";
	mapMorse['b'] = "-...";
	mapMorse['c'] = "-.-.";
	mapMorse['d'] = "-..";
	mapMorse['e'] = ".";
	mapMorse['f'] = "..-.";
	mapMorse['g'] = "--.";
	mapMorse['h'] = "....";
	mapMorse['i'] = "..";
	mapMorse['j'] = ".---";
	mapMorse['k'] = "-.-";
	mapMorse['l'] = ".-..";
	mapMorse['m'] = "--";
	mapMorse['n'] = "-.";
	mapMorse['o'] = "---";
	mapMorse['p'] = ".--.";
	mapMorse['q'] = "--.-";
	mapMorse['r'] = ".-.";
	mapMorse['s'] = "...";
	mapMorse['t'] = "-";
	mapMorse['u'] = "..-";
	mapMorse['v'] = "...-";
	mapMorse['w'] = ".--";
	mapMorse['x'] = "-..-";
	mapMorse['y'] = "-.--";
	mapMorse['z'] = "--..";

	string strTemp = StringToMorse("this is a test");
	cout << strTemp.c_str() << endl;
	strTemp = MorseToString(strTemp);
	cout << strTemp.c_str() << endl;
	strTemp = MorseToString(".... . .-.. .-.. --- / -.. .- .. .-.. -.-- / .--. .-. --- --. .-. .- -- -- . .-. / --. --- --- -.. / .-.. ..- -.-. -.- / --- -. / - .... . / -.-. .... .- .-.. .-.. . -. --. . ... / - --- -.. .- -.--");
	cout << strTemp.c_str() << endl;

	system("pause");
	return 0;
}