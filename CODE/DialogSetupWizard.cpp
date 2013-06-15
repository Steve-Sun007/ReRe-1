// DialogSetupWizard.cpp : implementation file
//

#include "stdafx.h"
#include "relaxreminder.h"
#include "PubFunc.h"
#include "BtnST.h"
#include "StringTable.h"
#include "RelaxTimer.h"
#include "DialogTrayWindow.h"
#include "DialogDarkerScreen.h"
#include "RelaxReminderDlg.h"
#include "DialogOptionTime.h"
#include "DialogOptionNotify.h"
#include "DialogOptionAutoAway.h"
#include "DialogOptionLanguage.h"
#include "DialogOptionMisc.h"
#include "DialogOption.h"
#include "DialogSetupWizardWelcome.h"
#include "DialogSetupWizard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogSetupWizard dialog


CDialogSetupWizard::CDialogSetupWizard(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSetupWizard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSetupWizard)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogSetupWizard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSetupWizard)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSetupWizard, CDialog)
	//{{AFX_MSG_MAP(CDialogSetupWizard)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSetupWizard message handlers

BOOL CDialogSetupWizard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
    CenterWindow(GetDesktopWindow());
    
    // ���ô���ָ��
    ASSERT(m_pdlgMain != NULL);
    m_dlgWelcome.m_pdlgMain     = m_pdlgMain;
    m_dlgTime.m_pdlgMain        = m_pdlgMain;
    m_dlgTime.m_pdlgOption      = NULL;
    
    // �����ӶԻ���
    m_dlgWelcome.Create(IDD_DIALOG_SETUP_WIZARD_WELCOME, this);
    m_dlgTime.Create(IDD_DIALOG_OPTION_TIME, this);
    
    // �����ӶԻ����ڸ������е�λ��
    CRect rs;
    GetDlgItem(IDC_STATIC_WIZARD_PLAT)->GetClientRect(rs);
    GetDlgItem(IDC_STATIC_WIZARD_PLAT)->ClientToScreen(rs);
    ScreenToClient(rs);
    
    
    // �����ӶԻ���ߴ粢�ƶ���ָ��λ��
    m_dlgWelcome.MoveWindow(rs);
    m_dlgTime.MoveWindow(rs);

    // �ֱ��������غ���ʾ
    PageSelect(PAGE_OPTION_WIZARD_FIRST);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogSetupWizard::PageSelect(EOptionPageIndex eIndex)
{
    m_dlgWelcome.ShowWindow(PAGE_OPTION_WIZARD_WELCOME == eIndex);
    m_dlgTime.ShowWindow(PAGE_OPTION_TIME == eIndex);

    m_ePage = eIndex;
    Invalidate(TRUE);
}

BOOL CDialogSetupWizard::FinishProcess(void)
{
    BOOL    bSettingCheckOK = TRUE;
    
    bSettingCheckOK &= m_dlgTime.CheckSetting();
    
    if (FALSE == bSettingCheckOK)
    {
        return FALSE;
    }
    
    m_dlgTime.ApplySetting();
    OnOK();
    return TRUE;
}
