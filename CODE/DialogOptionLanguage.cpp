// DialogOptionLanguage.cpp : implementation file
//

#include "stdafx.h"
#include "relaxreminder.h"
#include "Ini.h"
#include "PubFunc.h"
#include "BtnST.h"
#include "CreditsCtrl.h"
#include "StringTable.h"
#include "RelaxTimer.h"
#include "DialogTrayWindow.h"
#include "DialogDarkerScreen.h"
#include "RelaxReminderDlg.h"
#include "DialogAboutAbout.h"
#include "DialogAboutThanks.h"
#include "DialogAboutChangelog.h"
#include "DialogAboutStatistics.h"
#include "DialogAboutDonate.h"
#include "DialogAbout.h"
#include "DialogOptionTime.h"
#include "DialogOptionNotify.h"
#include "DialogOptionAutoAway.h"
#include "DialogOptionLanguage.h"
#include "DialogOptionMisc.h"
#include "DialogOption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionLanguage dialog


CDialogOptionLanguage::CDialogOptionLanguage(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogOptionLanguage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogOptionLanguage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogOptionLanguage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogOptionLanguage)
	DDX_Control(pDX, IDC_LIST_LANGUAGES, m_listLanguages);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogOptionLanguage, CDialog)
	//{{AFX_MSG_MAP(CDialogOptionLanguage)
	ON_NOTIFY(NM_CLICK, IDC_LIST_LANGUAGES, OnClickListLanguages)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogOptionLanguage message handlers

BOOL CDialogOptionLanguage::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    LoadLanguageStrings();

    // ��ȡ�����б�
    if (FALSE == LoadLanguageListFromIniFile())
    {
        return TRUE;
    }
    
    // ��ȡ��ǰ������
    LoadFromCurrentSetting();
    
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDialogOptionLanguage::LoadLanguageListFromIniFile()
{
    // �ж�LanguageList�Ƿ����
    CIni Ini(m_pdlgMain->m_strLanguageFile);
    BOOL bLanguageListExist = Ini.CheckExist("Index", "LanguageList");
    
    // ���������б��Ƿ�������ý�����ʾ
    GetDlgItem(IDC_STATIC_LANGUAGE_SELECT)->ShowWindow(bLanguageListExist);
    GetDlgItem(IDC_LIST_LANGUAGES)->ShowWindow(bLanguageListExist);
    GetDlgItem(IDC_STATIC_NO_LANGUAGE_FILE)->ShowWindow(!bLanguageListExist);

    if (!bLanguageListExist)
    {
        return FALSE;
    }

    LoadListCtrl();

    return TRUE;
}

void CDialogOptionLanguage::LoadListCtrl()
{
    // ������ʾ����
    ListView_SetExtendedListViewStyle(m_listLanguages,
        LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
    m_listLanguages.SetBkColor(GetSysColor(COLOR_3DFACE));
    m_listLanguages.SetTextBkColor(GetSysColor(COLOR_WINDOW));
    m_listLanguages.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
    
    // ����������
    m_listLanguages.InsertColumn(0, "LANGUAGE");
    m_listLanguages.SetColumnWidth(0, 130);
    m_listLanguages.InsertColumn(1, "LANGUAGE NAME");
    m_listLanguages.SetColumnWidth(1, 130);
    m_listLanguages.InsertColumn(2, "AVAILABLE");
    m_listLanguages.SetColumnWidth(2, 71);

    // ����INI�ļ��е������б�
    CIni Ini(m_pdlgMain->m_strLanguageFile);

    CString strLanguageList = Ini.ReadText("Index", "LanguageList");
    strLanguageList += ",";
    
    int iStart = 0;
    int iEnd = 0;
    while (iStart <= strLanguageList.GetLength() - 1)
    {
        CString strLanguageId;
        iEnd = strLanguageList.Find(',', iStart);
        strLanguageId = strLanguageList.Mid(iStart, iEnd - iStart);
        strLanguageId.TrimLeft();
        strLanguageId.TrimRight();
        
        BOOL bLanguageNameExist;
        BOOL bLanguageAvailableExist;
        bLanguageNameExist = Ini.CheckExist(strLanguageId, "LanguageName");
        bLanguageAvailableExist = Ini.CheckExist(strLanguageId, "Available");
        if (bLanguageNameExist && bLanguageAvailableExist)
        {
            CString strLanguageName;
            strLanguageName = Ini.ReadText(strLanguageId, "LanguageName");
            
            BOOL bLanguageAvailable;
            bLanguageAvailable = Ini.ReadInt(strLanguageId, "Available");
            
            InsertItem(strLanguageId.GetBuffer(0), strLanguageName.GetBuffer(0), bLanguageAvailable);
        }
        iStart = iEnd + 1;
    }
}

BOOL CDialogOptionLanguage::InsertItem(char *pchLanguageId,
                                       char *pchLanguageName,
                                       BOOL bAvailable)
{
    // ָ�벻��Ϊ��
    if (pchLanguageId == NULL || pchLanguageName == NULL) 
    {
        return FALSE;
    }
    
    // CListCtrl��������
    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = m_listLanguages.GetItemCount();
    // ����LanguageId
    lvItem.iSubItem = 0;
    lvItem.pszText = pchLanguageId;
    m_listLanguages.InsertItem(&lvItem);
    // ����LanguageName
    lvItem.iSubItem = 1;
    lvItem.pszText = pchLanguageName;
    m_listLanguages.SetItem(&lvItem);
    // ����Available
    lvItem.iSubItem = 2;
    lvItem.pszText = bAvailable ? "*" : "";
    m_listLanguages.SetItem(&lvItem);
    
    return TRUE;
}

BOOL CDialogOptionLanguage::LoadFromCurrentSetting()
{
    m_strLanguageId = m_pdlgMain->m_strLanguageId;

    int iItemNum = m_listLanguages.GetItemCount();
    for (int iItemLoop = 0; iItemLoop < iItemNum; iItemLoop++)
    {
        if (m_strLanguageId == m_listLanguages.GetItemText(iItemLoop, 0))
        {
            m_listLanguages.SetCheck(iItemLoop, TRUE);
            return TRUE;
        }
    }

    return FALSE;
}

void CDialogOptionLanguage::LoadSettingFromDefault()
{
    m_strLanguageId.Empty();

    int iItemNum = m_listLanguages.GetItemCount();
    for (int iItemLoop = 0; iItemLoop < iItemNum; iItemLoop++)
    {
        m_listLanguages.SetCheck(iItemLoop, FALSE);
    }
}

BOOL CDialogOptionLanguage::CheckSetting()
{
    // ȡ����ǰѡ�е����ԣ��жϸ������Ƿ����
    int iItemNum = m_listLanguages.GetItemCount();
    for (int iItemLoop = 0; iItemLoop < iItemNum; iItemLoop++)
    {
        if (TRUE == m_listLanguages.GetCheck(iItemLoop))
        {
            if ("*" == m_listLanguages.GetItemText(iItemLoop, 2))
            {
                m_strLanguageId = m_listLanguages.GetItemText(iItemLoop, 0);
            }
            else
            {
                CStringTable *pst = &(m_pdlgMain->m_str);
                MessageBox(pst->GetStr(OPTION_LANGUAGE_CHECK_FAIL_UNAVAILABLE),
                           pst->GetStr(OPTION_CHECK_FAIL_CAPTION),
                           MB_ICONSTOP);
                return FALSE;
            }
            break;
        }
    }

    return TRUE;
}

BOOL CDialogOptionLanguage::ApplySetting()
{
    // ���������Ա�����ֵ
    m_pdlgMain->m_strLanguageId = m_strLanguageId;

    // �ı��������
    m_pdlgMain->m_str.LoadStringTable(m_pdlgMain->m_strLanguageFile,
                                      m_strLanguageId);

    CDialogOption *pdlgOption = m_pdlgMain->m_pdlgOption;
    if (pdlgOption)
    {
        pdlgOption->LoadLanguageStrings();
        pdlgOption->m_dlgTime.LoadLanguageStrings();
        pdlgOption->m_dlgNotify.LoadLanguageStrings();
        pdlgOption->m_dlgAutoAway.LoadLanguageStrings();
        pdlgOption->m_dlgLanguage.LoadLanguageStrings();
        pdlgOption->m_dlgMisc.LoadLanguageStrings();
    }

    CDialogAbout *pdlgAbout = m_pdlgMain->m_pdlgAbout;
    if (pdlgAbout)
    {
        pdlgAbout->LoadLanguageStrings();
        pdlgAbout->m_dlgAbout.LoadLanguageStrings();
        pdlgAbout->m_dlgThanks.LoadLanguageStrings();
        pdlgAbout->m_dlgChangelog.LoadLanguageStrings();
        pdlgAbout->m_dlgStatistics.LoadLanguageStrings();
        pdlgAbout->m_dlgDonate.LoadLanguageStrings();
   }

    m_pdlgMain->m_dlgRelaxNotify.LoadLanguageStrings();
    
    return TRUE;
}

void CDialogOptionLanguage::UpdateButtonStatusBySettingChange()
{
    if (NULL == m_pdlgOption)
    {
        return;
    }
    
    m_pdlgOption->ChangeButtonStatus(OPTION_SETTING_CHANGED);
}

void CDialogOptionLanguage::LoadLanguageStrings()
{
    CStringTable *pst;
    
    pst = &(m_pdlgMain->m_str);
    SetDlgItemText(IDC_STATIC_LANGUAGE_SELECT, pst->GetStr(OPTION_LANGUAGE_SELECT));
    SetDlgItemText(IDC_STATIC_TIPS, pst->GetStr(OPTION_LANGUAGE_TIPS));
    Invalidate(TRUE);
}

void CDialogOptionLanguage::OnClickListLanguages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    int iItemClick = ((NM_LISTVIEW*)pNMHDR)->iItem;

    if (FALSE == m_listLanguages.GetCheck(iItemClick))
    {
        int iItemNum = m_listLanguages.GetItemCount();
        for (int iItemLoop = 0; iItemLoop < iItemNum; iItemLoop++)
        {
            if (iItemLoop != iItemClick)
            {
                m_listLanguages.SetCheck(iItemLoop, FALSE);
            }
        }
    }

    UpdateButtonStatusBySettingChange();

    *pResult = 0;
}
