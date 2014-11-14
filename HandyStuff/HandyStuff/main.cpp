// remove spaces from a string
std::string::iterator end_pos = std::remove(strSelectedTheme.begin(), strSelectedTheme.end(), ' ');
strSelectedTheme.erase(end_pos, strSelectedTheme.end());



// Get files out of a directory

char szDirectory[MAX_PATH];
		m_pDataStore->m_AppSettings->GetStringProfile("DIRECTORY", "ThemeLocationPath", szDirectory, MAX_PATH);
		sprintf_s(szThemeFolder,"%s%s%s%s", szDirectory, "slot0\\", strSelectedTheme.c_str(), "\\*");

		// Get the contents of specific theme folder
		HANDLE hFind;
		WIN32_FIND_DATA wfd;
		hFind = FindFirstFile(szThemeFolder, &wfd);
		if(hFind != INVALID_HANDLE_VALUE)
		{
			// Loop through all the files
			int i = 0;
			do
			{
				// Is it a directory
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {}
				else
				{
					// It is a file, add to the list
					sprintf_s(rgcFullFilename,"%s%s%s%s%s", szDirectory, "slot0\\", strSelectedTheme.c_str(), "\\", wfd.cFileName);
					if(strstr(rgcFullFilename, ".png"))
						m_listFiles.push_back(string(rgcFullFilename)); // Add to list
				}
			} while(FindNextFile(hFind, &wfd));
			FindClose(hFind);
		}