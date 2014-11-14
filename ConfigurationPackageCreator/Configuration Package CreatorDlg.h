// Configuration Package CreatorDlg.h : header file
//

#pragma once

#include <vector>
using std::vector;
#include <string>
using std::string;

#include <map>
using std::map;


// Constants
static const char* s_kprgcSettingsFile = "Settings.ini";

static const char* s_kprgcUKRegionCode = "44";

static const char* s_kprgcSharePackageDirectory = "\\Packages";

static const char* s_kprgcLogFile = "ConfigPackCreatorLog.txt";

static const char* s_kprgcUIDFile = "UID.txt";

static const char* s_kprgcConfigDataTypeBuddy = "buddy";

// CConfigurationPackageCreatorDlg dialog
class CConfigurationPackageCreatorDlg : public CDialog
{
private:

	// the latest package version
	static const int skdwCurrentPackageVersion = 1;

// Construction
public:
	CConfigurationPackageCreatorDlg(CWnd* pParent = NULL);	// standard constructor

	virtual ~CConfigurationPackageCreatorDlg(); // destructor

// Dialog Data
	enum { IDD = IDD_CONFIGURATIONPACKAGECREATOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void OnBnClickedLoad();

	afx_msg void OnEnUpdateEditPackage();
	afx_msg void OnEnUpdateEditVersion();

	afx_msg void OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnCbnSelchangeValueCombo();
	afx_msg void OnEnUpdateEditValue();
	afx_msg void OnBnClickedApplyButton();

	afx_msg void OnBnClickedRadioEnabled();
	afx_msg void OnBnClickedRadioDisabled();
	afx_msg void OnBnClickedCheckNoChangeCurrentValue();

	afx_msg void OnBnClickedRadioYesHideUser();
	afx_msg void OnBnClickedRadioNoHideUser();
	afx_msg void OnBnClickedCheckNoChangeHideUser();

	afx_msg void OnBnClickedRadioYesHideServer();
	afx_msg void OnBnClickedRadioNoHideServer();
	afx_msg void OnBnClickedCheckNoChangeHideServer();

	afx_msg void OnBnClickedRadioReadOnlyTerminalYes();
	afx_msg void OnBnClickedRadioReadOnlyTerminalNo();
	afx_msg void OnBnClickedCheckReadOnlyTerminalUseDefault();

	afx_msg void OnBnClickedRadioReadOnlyServerYes();
	afx_msg void OnBnClickedRadioReadOnlyServerNo();
	afx_msg void OnBnClickedCheckReadOnlyServerUseDefault();

	afx_msg void OnBnClickedButtonResetAll();

	afx_msg void OnBnClickedButtonSave();

	afx_msg void OnBnClickedExit();

private:

	/* ----------
	required paths
	 ---------- */
	string m_strCurrDir; // used to unpack bpaks when loading
	string m_strTreeIniPath;
	string m_strEnglishTxuPath;

	int m_dwNumChangedNodes; // number of nodes that will be written to the created config pack
	int m_dwCurrentNodeNum;  // when writing to config pack nodes are numbered 1-n (this keeps track of that number)

	// package
	CStatic* m_pPackageStaticControl;
	CEdit*	 m_pPackageEditControl;

	// version
	CStatic* m_pVersionStaticControl;
	CEdit*	 m_pVersionEditControl;

	// current value
	CButton*   m_pCurrentValueUseDefaultControl;
	CEdit*     m_pEditCurrentValueControl;     // for editable values (strings, etc.)
	CButton*   m_pApplyButtonControl;          // applies the current editable value to the node
	CButton*   m_pCurrentValueEnabledControl;  // for boolean values
	CButton*   m_pCurrentValueDisabledControl; //
	CComboBox* m_pCurrentValueComboBoxControl; // for combo box values
	CStatic*   m_pMinCurrentValueControl;
	CStatic*   m_pMaxCurrentValueControl;

	// hide
	CButton* m_pHideFromTerminalUseDefaultControl;

	CButton* m_pHideFromServerUseDefaultControl;

	CButton* m_pHideGMControl;
	CButton* m_pUnHideGMControl;
	CButton* m_pReadWriteGMControl;
	CButton* m_pReadOnlyGMControl;

	CButton* m_pHideMControl;
	CButton* m_pUnHideMControl;
	CButton* m_pReadWriteMControl;
	CButton* m_pReadOnlyMControl;

	// read only
	CButton* m_pReadOnlyAtTerminalUseDefaultControl;

	CButton* m_pReadOnlyAtServerUseDefaultControl;

	// load
	CEdit*   m_pLoadEditControl;
	CStatic* m_pLoadStaticControl;
	CButton* m_pLoadButtonControl;


	// reset
	CButton* m_pResetAllButton;

	// save
	CButton* m_pSaveButtonControl;


	// list of data types in tree.ini that can be edited through the edit box
	vector<string> vstrEditableTypes; // contains: string, period, unsignedlong, cash, unboundint and unboundcash

	// list of data types in tree.ini that can be edited using the boolean controls
	vector<string> vstrBooleanTypes; // contains: boolean

	// list of data types in tree.ini that are stored as integers
	vector<string> vstrIntegerTypes; //contains: unsignedlong, period, cash, unboundint and unboundcash

	// list of data types in tree.ini that may contain min and max values
	vector<string> vstrBoundTypes; // contains: string, period and unsignedlong

	
	/* ---------------------------------------
	stuff related to drop down combo box values
	 --------------------------------------- */
	struct SComboBoxOptions
	{
		string strMacroName;
		vector<string> vstrOptions;
	};

	vector<SComboBoxOptions*> m_vComboOptions; // populated in OnInitDialog()

	bool m_bReqDropDownBox;


	bool ParseEnglishTxu();
	map<string, string> m_LookupStringMap;

	bool m_bDistributionFolderLocated;


	bool m_bExistingPackageLoaded;
	string m_strLoadedBpak;
	string m_strLoadedBpakPath;
	string m_strLoadedPackageName;
	string m_strLoadedVersionNumber;

	bool m_bChangesNeedSaving;

	bool LoadBpak(string strBpakPath);

	bool ApplyConfiguration(string strConfigFilePath);


	int m_iRedIconIndex;
	int m_iGreenIconIndex;
	int m_iPurpleIconIndex;
	int m_iBlueIconIndex;

	enum EEventType
	{
		ePackageCreation
	};

	bool LogEvent(EEventType eEventType);
	bool LogEvent(string strLogText);

	CImageList* m_pTreeImageList;

	string GetCurrentDateTime();

	bool GetPackageUID(int &iUID);

	string m_strErrorText;

	string m_strCurrentDirectory;
	string m_strSharePath;

	bool InvalidCharacter(char &cCharacter);
public:
	afx_msg void OnEnChangeEditValue();
};
