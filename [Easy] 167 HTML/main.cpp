#include <windows.h>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	char cTitle[1000];
	char cBuffer[1000];
	char cFileName[1000];
	char cParagraph[1000];
	char cCompleteParagraph[1000];

	cout << "Please enter a page title:" << endl;
	cin.getline(cBuffer, 1000);
	sprintf_s(cTitle,sizeof(cTitle),cBuffer);

	cout << "Please enter a Paragraph:" << endl;
	cin.getline(cBuffer, 1000);
	sprintf_s(cParagraph,sizeof(cParagraph),cBuffer);

	sprintf_s(cCompleteParagraph,sizeof(cCompleteParagraph),"<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<style type=\"text/css\">\n\t\t\t.mycss{text-shadow:2px 1px 2px rgba(28,1,1,1);font-weight:normal;color:#FF19BA;background-color:#B0FFE5;border: 2px solid #b5a759;letter-spacing:1pt;word-spacing:5pt;font-size:22px;text-align:justify;font-family:helvetica, sans-serif;line-height:1;}\n\t\t</style>\n\t\t<title>%s</title>\n\t</head>\n\n\t<body>\n\t\t<p class=\"mycss\">%s</p>\n\t</body>\n</html>\0",cTitle, cParagraph);
	strncpy_s(cFileName, "MyWebpage.html", sizeof(cFileName));

	std::ofstream ofile(cFileName);
	ofile << cCompleteParagraph << endl;
	ofile.close();

	HINSTANCE h = ShellExecute(0,0, cFileName, 0, 0, SW_SHOWNORMAL);

	return 0;
}