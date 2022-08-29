// TransferDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SIPSample.h"
#include "TransferDlg.h"


// CTransferDlg dialog

IMPLEMENT_DYNAMIC(CTransferDlg, CDialog)

CTransferDlg::CTransferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransferDlg::IDD, pParent)
	, m_TransferNumber(_T(""))
	, m_ReplaceLine(0)
{

}

CTransferDlg::~CTransferDlg()
{
}

void CTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_TransferNumber);
	DDX_Text(pDX, IDC_EDIT2, m_ReplaceLine);
}


BEGIN_MESSAGE_MAP(CTransferDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CTransferDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTransferDlg message handlers

BOOL CTransferDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	if (pMsg->message == WM_KEYDOWN)
	{
		if ((pMsg->wParam == VK_RETURN) || (pMsg->wParam == VK_ESCAPE))
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);

}



CString CTransferDlg::getTransferNumber()
{
	return m_TransferNumber;
}


BOOL CTransferDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	m_TransferNumber = "";
	m_ReplaceLine = 0;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTransferDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	OnOK();
}
