#include<stdio.h>
#include<string>
#include<vector>
#include<iostream>
#include<windows.h>

using namespace std;

	enum eArrayName { ExcludedFiles, ExecSystemFiles, IncludedFileTypes, SystemDirectories, ExecutiveDLLFolder, MiscStrings
            , Mk6, Mk6v1_3, Mk65, Mk7, Mk7v1_11, Mk8XP, Mk8W7 };
    enum eDataType { eString, eStringAndHash, eStringAndCabType };

	struct FileHeader
    {
        unsigned long FileHeaderSize;
        unsigned long FileSize;
        unsigned long ulVersionNumber;
        unsigned long ulNumOfArrays;
    };

    struct ArrayHeader
    {
        eArrayName enumArrayName;
        eDataType enumDataType;
        unsigned long ulArrayItemCount;
        unsigned long ulArraySize;
        unsigned long ulArrayStartBlock;
    };

    struct VerificationDataItem
    {
		unsigned long strLength;
        string strValue;
    };
	
    struct VerificationDataAndHashItem
    {
        string strValue;
        string strHash;
    };

    struct VerificationDataAndCabTypeItem
    {
        string strValue;
        string strCabType;
    };

	string ReadData(FILE *pMyFile, int iSize)
	{
		string strData;
		char * pNewData = new char[iSize+1];
		pNewData[iSize] = 0;
		fread(pNewData, iSize, 1, pMyFile);
		return pNewData;
	}
	unsigned char ReadLength(FILE *pMyFile, int iSize)
	{
		unsigned char ucSize = 0;		
		fread(&ucSize,iSize,1,pMyFile);
		return ucSize;
	}

	int main()
	{
			std::string result;

			
                int i = 0;
                i = sizeof(unsigned long);
                i = sizeof(signed long);

		//HRSRC hhRes = FindResource(0, MAKEINTRESOURCE(IDR_TEXT_FILE2), "TEXT_FILE");
		//if(NULL != hhRes)
		//{
		//	HGLOBAL hData = LoadResource(0, hhRes);
		//	if(NULL != hData)
		//	{
		//		DWORD dataSize = SizeofResource(0, hhRes);
		//		//dataSize = 1091747;
		//		char* data = (char*)LockResource(hData);
		//		result.assign(data, dataSize);
		//	}
		//}



		FILE *pMyFile;
		struct FileHeader fileHeader;
		struct ArrayHeader arrayHeader;

		fopen_s(&pMyFile,"EncodedVerification.txt","rb");

		//fopen_s(&pMyFile,"test.bin","rb");
		if (!pMyFile)
		{
			printf("Unable to open file!");
			return 1;
		}
		
		fread(&fileHeader,sizeof(struct FileHeader),1,pMyFile);// read the file header

		vector<ArrayHeader> vecArrayHeaders;
		for(unsigned int i = 0; i < fileHeader.ulNumOfArrays; i++)
		{
			ArrayHeader ah;
			fread(&arrayHeader,sizeof(struct ArrayHeader),1,pMyFile);
			ah.enumArrayName = arrayHeader.enumArrayName;
			ah.enumDataType = arrayHeader.enumDataType;
			ah.ulArrayItemCount = arrayHeader.ulArrayItemCount;
			ah.ulArraySize = arrayHeader.ulArraySize;
			ah.ulArrayStartBlock = arrayHeader.ulArrayStartBlock;

			vecArrayHeaders.push_back(ah);
		}

		vector<VerificationDataItem> vecDataItems;
		vector<VerificationDataAndHashItem> vecDataAndHashItems;
		vector<VerificationDataAndCabTypeItem> vecDataAndCabTypeItems;
		vector<ArrayHeader>::iterator it;
		for(it = vecArrayHeaders.begin(); it < vecArrayHeaders.end(); it++)
		{
			if(true)//(it)->enumArrayName == SystemDirectories)
			{
				fseek(pMyFile,(it)->ulArrayStartBlock,SEEK_SET);
				for(unsigned int i = 0; i < (it)->ulArrayItemCount; i++)
				{
					string strData;
					unsigned char ucSize = 0;
					switch((it)->enumDataType)
					{
					case eString:
						{
							struct VerificationDataItem vdi;
							vdi.strLength = ReadLength(pMyFile, sizeof(unsigned char));
							vdi.strValue = ReadData(pMyFile, vdi.strLength);
							vecDataItems.push_back(vdi);
							break;
						}
					case eStringAndCabType:
						{
							// the string and the cab type
							struct VerificationDataAndCabTypeItem vdcti;
							int iLength = ReadLength(pMyFile, sizeof(unsigned char));
							vdcti.strValue = ReadData(pMyFile, iLength);
							
							iLength = ReadLength(pMyFile, sizeof(unsigned char));
							vdcti.strCabType = ReadData(pMyFile, iLength);

							vecDataAndCabTypeItems.push_back(vdcti);
							break;
						}
					case eStringAndHash:
						{
							// the string and the hash
							struct VerificationDataAndHashItem vdhi;
							int iLength = ReadLength(pMyFile, sizeof(unsigned char));
							vdhi.strValue = ReadData(pMyFile, iLength);
							
							iLength = ReadLength(pMyFile, sizeof(unsigned char));
							vdhi.strHash = ReadData(pMyFile, iLength);
							vecDataAndHashItems.push_back(vdhi);
							break;
						}
					} // end switch
				} //for array data
			} // if specific array
		} // for array headers

		//string strValue = vecDataItems[vecDataItems.size()-1].strValue;
		
		fclose(pMyFile);
		return 0;
	}