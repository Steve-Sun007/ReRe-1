#ifndef _PUB_FUNC_H
#define _PUB_FUNC_H


// �ļ��Ƿ����
BOOL FileExists(const char *pchFile);


// ���ô���͸����
typedef BOOL (__stdcall *PFNTransparentWindow)(HWND, COLORREF, BYTE, DWORD); 
PFNTransparentWindow    GetSysLibraryTransparentWindow();

#endif