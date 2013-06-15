// KeyboardMouseHook.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "KeyboardMouseHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CKeyboardMouseHookApp

BEGIN_MESSAGE_MAP(CKeyboardMouseHookApp, CWinApp)
	//{{AFX_MSG_MAP(CKeyboardMouseHookApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyboardMouseHookApp construction

CKeyboardMouseHookApp::CKeyboardMouseHookApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKeyboardMouseHookApp object

CKeyboardMouseHookApp theApp;

//////////////////////////////////////////////////////////////////////////
// ���������
//////////////////////////////////////////////////////////////////////////

// ȫ�ֹ��Ӷ���
HHOOK g_hKeyboardHook = NULL;
HHOOK g_hMouseHook = NULL;

// �ײ㹳�Ӻ���
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

//////////////////////////////////////////////////////////////////////////
// �ײ㹳�Ӻ���ʵ��
//////////////////////////////////////////////////////////////////////////

// �ײ���̹��Ӻ���
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= HC_ACTION)
	{// nCode���ڵ���0ʱ�����ܵ����Լ��Ļص��������� (MSDN��Ҫ��)
		return TRUE;	// ����������Ϣ����
	}
	else
	{// nCodeС��0ʱ���������CallNextHookEx (MSDN��Ҫ��)
		return CallNextHookEx(g_hKeyboardHook, nCode, wParam, lParam);
	}
}

// �ײ���깳�Ӻ���
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= HC_ACTION)
	{// nCode���ڵ���0ʱ�����ܵ����Լ��Ļص��������� (MSDN��Ҫ��)
		return TRUE;	// ����������Ϣ����
	}
	else
	{// nCodeС��0ʱ���������CallNextHookEx (MSDN��Ҫ��)
		return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
	}
}

//////////////////////////////////////////////////////////////////////////
// dll�������� (�ⲿ�ӿ�)
//////////////////////////////////////////////////////////////////////////

DllExport BOOL WINAPI DllExport_InstallKeyboardHook()
{
	// ����Ѿ���װ�˼��̹��ӣ��򷵻�TRUE
	if (g_hKeyboardHook != NULL)
	{
		return TRUE;
	}

	// ��ʼ��װ���̹���
	g_hKeyboardHook = (HHOOK)SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, theApp.m_hInstance, 0);
	if (g_hKeyboardHook == NULL)
	{// ��װ���̹���ʧ�ܣ��򷵻�FALSE
		return FALSE;
	}	
	return TRUE;
}

DllExport BOOL WINAPI DllExport_UninstallKeyboardHook()
{
	if (UnhookWindowsHookEx(g_hKeyboardHook) == FALSE)
	{
		return FALSE;
	}	
	g_hKeyboardHook = NULL;
	return TRUE;
}

DllExport BOOL WINAPI DllExport_InstallMouseHook()
{
	// ����Ѿ���װ����깳�ӣ��򷵻�TRUE
	if (g_hMouseHook != NULL)
	{
		return TRUE;
	}

	// ��ʼ��װ��깳��
	g_hMouseHook = (HHOOK)SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, theApp.m_hInstance, 0);
	if (g_hMouseHook == NULL)
	{// ��װ��깳��ʧ�ܣ��򷵻�FALSE
		return FALSE;
	}	
	return TRUE;
}

DllExport BOOL WINAPI DllExport_UninstallMouseHook()
{
	if (UnhookWindowsHookEx(g_hMouseHook) == FALSE)
	{
		return FALSE;
	}	
	g_hMouseHook = NULL;
	return TRUE;
}
