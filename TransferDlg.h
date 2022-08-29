#pragma once


// CTransferDlg dialog

class CTransferDlg : public CDialog
{
	DECLARE_DYNAMIC(CTransferDlg)

public:
	CTransferDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTransferDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };


public:
	int GetReplaceLine() { return m_ReplaceLine; }


public:
	afx_msg void OnBnClickedOk();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()


public:
	CString getTransferNumber();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();

public:

	CString m_TransferNumber;
	int m_ReplaceLine;
};
