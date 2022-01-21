#include "stdafx.h"
#include <CkGlobalW.h>
#include "resource.h"

// Globals
CEdit * pOUTPUT;
CButton * pSTART;
CkGlobalW glob;

class MAIN_FORM : public CDialog
{
public:
	MAIN_FORM(CWnd* pParent = NULL) : CDialog(MAIN_FORM::IDD, pParent) {};
	//Dialog data, name of dialog here
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX) { CDialog::DoDataExchange(pDX); };
	//Called right after constructor. Initialize things here
	virtual BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();
		pOUTPUT = (CEdit *)GetDlgItem(CE_OUTPUT);
		pSTART = (CButton *)GetDlgItem(CB_UNLOCK);
		pOUTPUT->SetWindowText(L"Click \"START\" to begin!\r\nThe Chilkat API can be unlocked for a fully-functional 30-day trial by passing any string\r\nto the UnlockBundle method.");

		return true;
	}

public:
	//---------------------------------------------
	afx_msg void start() { UNLOCKBUTTON(); }
	//---------------------------------------------
	void UNLOCKBUTTON()
	{

		bool success = glob.UnlockBundle(L"Anything for 30-day trial");
		if (success != true) {
			CStringW err = (L"ERROR: \r\n");
			MessageBox(err + glob.lastErrorText());
		}
		CStringW suc = (L"SUCCESS: \r\n");
		SetDlgItemText(CE_OUTPUT, suc + glob.lastErrorText());
		pSTART->EnableWindow(false);
	}
	DECLARE_MESSAGE_MAP()
};

//Actual App
class UnlockChilkatGlo : public CWinApp
{
public:
	UnlockChilkatGlo() {};
	virtual BOOL InitInstance()
	{
		CWinApp::InitInstance();
		MAIN_FORM dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		return false;
	}
};

//---------------------------------------------
//Need a Message Map Macro for both CDialog and CWinApp
BEGIN_MESSAGE_MAP(MAIN_FORM, CDialog)
	ON_COMMAND(CB_UNLOCK, start)
END_MESSAGE_MAP()
//---------------------------------------------

//Start application
UnlockChilkatGlo theApp;