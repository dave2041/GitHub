// Configuration Package CreatorDlg.cpp : implementation file

#include "stdafx.h"
#include "Configuration Package Creator.h"
#include "Configuration Package CreatorDlg.h"

#include <windows.h>
#include <winver.h>

#include <algorithm>
#include <sstream>
#include <string.h>
#include <sys/stat.h>

#include <direct.h>

#define MAX_BUFFER_SIZE 256
#define BLOCK_SIZE		1024


// CConfigurationPackageCreatorDlg constructor
CConfigurationPackageCreatorDlg::CConfigurationPackageCreatorDlg(CWnd* pParent /* = NULL */)
: CDialog(CConfigurationPackageCreatorDlg::IDD, pParent)
{
}


// CConfigurationPackageCreatorDlg destructor
CConfigurationPackageCreatorDlg::~CConfigurationPackageCreatorDlg()
{
}


void CConfigurationPackageCreatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfigurationPackageCreatorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_LOAD, &CConfigurationPackageCreatorDlg::OnBnClickedLoad)
	ON_BN_CLICKED(ID_FILE_OPEN, &CConfigurationPackageCreatorDlg::OnBnClickedLoad)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CConfigurationPackageCreatorDlg::OnTvnSelchangedTree)

	ON_EN_UPDATE(IDC_EDIT_VALUE, &CConfigurationPackageCreatorDlg::OnEnUpdateEditValue)

	ON_BN_CLICKED(IDC_CHECK_NO_CHANGE_VALUE, &CConfigurationPackageCreatorDlg::OnBnClickedCheckNoChangeCurrentValue)
	ON_BN_CLICKED(IDC_RADIO_ENABLED, &CConfigurationPackageCreatorDlg::OnBnClickedRadioEnabled)
	ON_BN_CLICKED(IDC_RADIO_DISABLED, &CConfigurationPackageCreatorDlg::OnBnClickedRadioDisabled)
	ON_BN_CLICKED(IDC_RADIO_YES_HIDE_USER, &CConfigurationPackageCreatorDlg::OnBnClickedRadioYesHideUser)
	ON_BN_CLICKED(IDC_RADIO_HIDE_GAMINGMACHINE, &CConfigurationPackageCreatorDlg::OnBnClickedRadioYesHideUser)
	ON_BN_CLICKED(IDC_RADIO_UNHIDE_GAMINGMACHINE, &CConfigurationPackageCreatorDlg::OnBnClickedRadioNoHideUser)
	ON_BN_CLICKED(IDC_RADIO_NO_HIDE_USER, &CConfigurationPackageCreatorDlg::OnBnClickedRadioNoHideUser)
	ON_BN_CLICKED(IDC_CHECK_NO_CHANGE_HIDE_USER, &CConfigurationPackageCreatorDlg::OnBnClickedCheckNoChangeHideUser)
	ON_BN_CLICKED(IDC_RADIO_YES_HIDE_SERVER, &CConfigurationPackageCreatorDlg::OnBnClickedRadioYesHideServer)
	ON_BN_CLICKED(IDC_RADIO_HIDE_MANAGEMENT, &CConfigurationPackageCreatorDlg::OnBnClickedRadioYesHideServer)
	ON_BN_CLICKED(IDC_RADIO_UNHIDE_MANAGEMENT, &CConfigurationPackageCreatorDlg::OnBnClickedRadioNoHideServer)
	ON_BN_CLICKED(IDC_RADIO_NO_HIDE_SERVER, &CConfigurationPackageCreatorDlg::OnBnClickedRadioNoHideServer)
	ON_BN_CLICKED(IDC_CHECK_NO_CHANGE_HIDE_SERVER, &CConfigurationPackageCreatorDlg::OnBnClickedCheckNoChangeHideServer)
	ON_BN_CLICKED(IDC_APPLY_BUTTON, &CConfigurationPackageCreatorDlg::OnBnClickedApplyButton)
	ON_BN_CLICKED(IDC_RADIO_READ_ONLY_TERMINAL_YES, &CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyTerminalYes)
	ON_BN_CLICKED(IDC_RADIO_READONLY_GAMINGMACHINE, &CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyTerminalYes)
	ON_BN_CLICKED(IDC_RADIO_READ_ONLY_TERMINAL_NO, &CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyTerminalNo)
	ON_BN_CLICKED(IDC_RADIO_READWRITE_GAMINGMACHINE, &CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyTerminalNo)
	ON_BN_CLICKED(IDC_CHECK_READ_ONLY_TERMINAL_USE_DEFAULT, &CConfigurationPackageCreatorDlg::OnBnClickedCheckReadOnlyTerminalUseDefault)
	ON_BN_CLICKED(IDC_RADIO_READ_ONLY_SERVER_YES, &CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyServerYes)
	ON_BN_CLICKED(IDC_RADIO_READONLY_MANAGEMENT, &CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyServerYes)
	ON_BN_CLICKED(IDC_RADIO_READ_ONLY_SERVER_NO, &CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyServerNo)
	ON_BN_CLICKED(IDC_RADIO_READWRITE_MANAGEMENT, &CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyServerNo)
	ON_BN_CLICKED(IDC_CHECK_READ_ONLY_SERVER_USE_DEFAULT, &CConfigurationPackageCreatorDlg::OnBnClickedCheckReadOnlyServerUseDefault)
	ON_EN_UPDATE(IDC_EDIT_PACKAGE, &CConfigurationPackageCreatorDlg::OnEnUpdateEditPackage)
	ON_EN_UPDATE(IDC_EDIT_VERSION, &CConfigurationPackageCreatorDlg::OnEnUpdateEditVersion)
	ON_BN_CLICKED(IDC_CANCEL, &CConfigurationPackageCreatorDlg::OnBnClickedExit)
	ON_BN_CLICKED(ID_FILE_EXIT, &CConfigurationPackageCreatorDlg::OnBnClickedExit)
	ON_CBN_SELCHANGE(IDC_VALUE_COMBO, &CConfigurationPackageCreatorDlg::OnCbnSelchangeValueCombo)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_AS, &CConfigurationPackageCreatorDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(ID_FILE_SAVE, &CConfigurationPackageCreatorDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_RESET_ALL, &CConfigurationPackageCreatorDlg::OnBnClickedButtonResetAll)
	ON_BN_CLICKED(ID_FILE_NEW, &CConfigurationPackageCreatorDlg::OnBnClickedButtonResetAll)
	ON_EN_CHANGE(IDC_EDIT_VALUE, &CConfigurationPackageCreatorDlg::OnEnChangeEditValue)
END_MESSAGE_MAP()


// CConfigurationPackageCreatorDlg message handlers
BOOL CConfigurationPackageCreatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Setup pointers to controls

	// Package controls
	m_pPackageStaticControl = (CStatic*)GetDlgItem(IDC_STATIC_PACKAGE);
	ASSERT(m_pPackageStaticControl != NULL);

	m_pPackageEditControl = (CEdit*)GetDlgItem(IDC_EDIT_PACKAGE);
	ASSERT(m_pPackageEditControl != NULL);

	// Version controls
	m_pVersionStaticControl = (CStatic*)GetDlgItem(IDC_STATIC_VERSION);
	ASSERT(m_pVersionStaticControl != NULL);

	m_pVersionEditControl = (CEdit*)GetDlgItem(IDC_EDIT_VERSION);
	ASSERT(m_pVersionEditControl != NULL);

	// Current value controls
	m_pEditCurrentValueControl = (CEdit*)GetDlgItem(IDC_EDIT_VALUE);
	ASSERT(m_pEditCurrentValueControl != NULL);

	m_pCurrentValueUseDefaultControl = (CButton*)GetDlgItem(IDC_CHECK_NO_CHANGE_VALUE);
	ASSERT(m_pCurrentValueUseDefaultControl != NULL);

	m_pCurrentValueEnabledControl = (CButton*)GetDlgItem(IDC_RADIO_ENABLED);
	ASSERT(m_pCurrentValueEnabledControl != NULL);

	m_pCurrentValueDisabledControl = (CButton*)GetDlgItem(IDC_RADIO_DISABLED);
	ASSERT(m_pCurrentValueDisabledControl != NULL);

	m_pCurrentValueComboBoxControl = (CComboBox*)GetDlgItem(IDC_VALUE_COMBO);
	ASSERT(m_pCurrentValueComboBoxControl != NULL);

	// Min and max value labels
	m_pMinCurrentValueControl = (CStatic*)GetDlgItem(IDC_MIN);
	ASSERT(m_pMinCurrentValueControl != NULL);

	m_pMaxCurrentValueControl = (CStatic*)GetDlgItem(IDC_MAX);
	ASSERT(m_pMaxCurrentValueControl != NULL);

	// Hide from user controls
	m_pHideFromTerminalUseDefaultControl = (CButton*)GetDlgItem(IDC_CHECK_NO_CHANGE_HIDE_USER);
	ASSERT(m_pHideFromTerminalUseDefaultControl != NULL);

	// Hide from server controls
	m_pHideFromServerUseDefaultControl = (CButton*)GetDlgItem(IDC_CHECK_NO_CHANGE_HIDE_SERVER);
	ASSERT(m_pHideFromServerUseDefaultControl != NULL);

	// Read only from terminal controls
	m_pReadOnlyAtTerminalUseDefaultControl = (CButton*)GetDlgItem(IDC_CHECK_READ_ONLY_TERMINAL_USE_DEFAULT);
	ASSERT(m_pReadOnlyAtTerminalUseDefaultControl != NULL);
	
	
	m_pReadWriteGMControl = (CButton*)GetDlgItem(IDC_RADIO_READWRITE_GAMINGMACHINE);
	ASSERT(m_pReadWriteGMControl != NULL);

	m_pReadOnlyGMControl = (CButton*)GetDlgItem(IDC_RADIO_READONLY_GAMINGMACHINE);
	ASSERT(m_pReadOnlyGMControl != NULL);

	m_pHideGMControl = (CButton*)GetDlgItem(IDC_RADIO_HIDE_GAMINGMACHINE);
	ASSERT(m_pHideGMControl != NULL);

	m_pUnHideGMControl = (CButton*)GetDlgItem(IDC_RADIO_UNHIDE_GAMINGMACHINE);
	ASSERT(m_pUnHideGMControl != NULL);
	
	m_pReadWriteMControl = (CButton*)GetDlgItem(IDC_RADIO_READWRITE_MANAGEMENT);
	ASSERT(m_pReadWriteMControl != NULL);

	m_pReadOnlyMControl = (CButton*)GetDlgItem(IDC_RADIO_READONLY_MANAGEMENT);
	ASSERT(m_pReadOnlyMControl != NULL);

	m_pHideMControl = (CButton*)GetDlgItem(IDC_RADIO_HIDE_MANAGEMENT);
	ASSERT(m_pHideMControl != NULL);

	m_pUnHideMControl = (CButton*)GetDlgItem(IDC_RADIO_UNHIDE_MANAGEMENT);
	ASSERT(m_pUnHideMControl != NULL);

	// Read only from server controls
	m_pReadOnlyAtServerUseDefaultControl = (CButton*)GetDlgItem(IDC_CHECK_READ_ONLY_SERVER_USE_DEFAULT);
	ASSERT(m_pReadOnlyAtServerUseDefaultControl != NULL);

	// Apply button
	m_pApplyButtonControl = (CButton*)GetDlgItem(IDC_APPLY_BUTTON);
	ASSERT(m_pApplyButtonControl != NULL);

	// Load controls
	m_pLoadStaticControl = (CStatic*)GetDlgItem(IDC_STATIC_LOAD);
	ASSERT(m_pLoadStaticControl != NULL);

	m_pLoadEditControl = (CEdit*)GetDlgItem(IDC_EDIT_LOAD);
	ASSERT(m_pLoadEditControl != NULL);

	m_pLoadButtonControl = (CButton*)GetDlgItem(IDC_LOAD);
	ASSERT(m_pLoadButtonControl != NULL);

	// Save button
	m_pSaveButtonControl = (CButton*)GetDlgItem(IDC_BUTTON_SAVE_AS);
	ASSERT(m_pSaveButtonControl != NULL);

	// Reset all button
	m_pResetAllButton = (CButton*)GetDlgItem(IDC_BUTTON_RESET_ALL);
	ASSERT(m_pResetAllButton != NULL);

	// get the current directory as a wchar* string
	char rgcCurrDir[MAX_BUFFER_SIZE];
	GetCurrentDirectory(MAX_BUFFER_SIZE, rgcCurrDir);
	m_strCurrDir = rgcCurrDir;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConfigurationPackageCreatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConfigurationPackageCreatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConfigurationPackageCreatorDlg::OnBnClickedLoad()
{
	// open file dialog for bpaks
	CFileDialog fileDialog(true, "bpak", NULL, OFN_OVERWRITEPROMPT, "bpak files (*.bpak)|*.bpak", this);
	if (fileDialog.DoModal() == IDOK)
	{
		string strBpakPath = fileDialog.GetPathName();
		LoadBpak(strBpakPath);
		m_bExistingPackageLoaded = true;
		m_strLoadedBpakPath = strBpakPath;

		// enable reset all button
		m_pResetAllButton->EnableWindow(true);
	}
}

void CConfigurationPackageCreatorDlg::OnBnClickedRadioEnabled()
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedRadioDisabled()
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedCheckNoChangeCurrentValue()
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedRadioYesHideUser()
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedRadioNoHideUser()
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedCheckNoChangeHideUser()
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedRadioYesHideServer()
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedRadioNoHideServer()
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedCheckNoChangeHideServer()
{
}

void CConfigurationPackageCreatorDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
}

void CConfigurationPackageCreatorDlg::OnEnUpdateEditValue()
{
	char rgcControlValue[MAX_BUFFER_SIZE]; // always ensure this is big enough to hold the respective char* string
	m_pEditCurrentValueControl->GetWindowText(rgcControlValue, MAX_BUFFER_SIZE);
}

void CConfigurationPackageCreatorDlg::OnEnUpdateEditPackage()
{
}

bool CConfigurationPackageCreatorDlg::InvalidCharacter(char &cCharacter)
{
	int iCharAsciiValue = (int)cCharacter;

	if ((iCharAsciiValue >= (int)'0' && iCharAsciiValue <= (int)'9') || // 0-9 check
		(iCharAsciiValue >= (int)'A' && iCharAsciiValue <= (int)'Z') || // A-Z check
		(iCharAsciiValue >= (int)'a' && iCharAsciiValue <= (int)'z'))   // a-z check
	{
		return false; // valid char
	}

	return true; // invalid char
}

void CConfigurationPackageCreatorDlg::OnEnUpdateEditVersion()
{
	// prevent dots from being entered into the edit box
	char rgcVersionNumber[MAX_BUFFER_SIZE];
	m_pVersionEditControl->GetWindowText(rgcVersionNumber, MAX_BUFFER_SIZE);
	string strVersionNumber(rgcVersionNumber);

	for (string::iterator i = strVersionNumber.begin(); i != strVersionNumber.end(); ++i)
	{
		if (InvalidCharacter(*i))
		{
			std::stringstream stringStream;
			stringStream << (*i);
			string strIllegalChar;
			stringStream >> strIllegalChar;

			MessageBox(string(string("The package version cannot contain ") + strIllegalChar.c_str() + string("'s")).c_str(), "Error", MB_OK);

			strVersionNumber.erase(i);
			m_pVersionEditControl->SetWindowText(strVersionNumber.c_str());

			break;
		}
	}
}

void CConfigurationPackageCreatorDlg::OnBnClickedExit()
{
	// exit the application
	PostQuitMessage(0);
}

void CConfigurationPackageCreatorDlg::OnCbnSelchangeValueCombo()
{
	CString cstrCurrentValue;
	m_pCurrentValueComboBoxControl->GetWindowTextA(cstrCurrentValue);
}

void CConfigurationPackageCreatorDlg::OnBnClickedApplyButton()
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyTerminalYes() // read-only selected
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyTerminalNo() // read-write selected
{
}


void CConfigurationPackageCreatorDlg::OnBnClickedCheckReadOnlyTerminalUseDefault()
{
}


void CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyServerYes() // Read-only selected
{
}


void CConfigurationPackageCreatorDlg::OnBnClickedRadioReadOnlyServerNo() // read-write selected
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedCheckReadOnlyServerUseDefault()
{
}

void CConfigurationPackageCreatorDlg::OnBnClickedButtonSave()
{
}

bool CConfigurationPackageCreatorDlg::LoadBpak(string strBpakPath)
{
	return true;
}

void CConfigurationPackageCreatorDlg::OnBnClickedButtonResetAll()
{
}
void CConfigurationPackageCreatorDlg::OnEnChangeEditValue()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
