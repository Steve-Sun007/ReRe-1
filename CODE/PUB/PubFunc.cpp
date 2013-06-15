#include "StdAfx.h"
#include "PubFunc.h"
#include <io.h>


// �ļ��Ƿ����
BOOL FileExists(const char *pchFile)
{
    return ((_access(pchFile, 0)) != -1);
}

// ��ȡ͸�����ڵ�ϵͳ����
PFNTransparentWindow GetSysLibraryTransparentWindow()
{
    PFNTransparentWindow    pfn;
    HMODULE hModule;
    
    hModule = GetModuleHandle("user32.dll");
    if ( hModule == NULL )
    {
        hModule = LoadLibrary("user32.dll");
    }
    if ( hModule == NULL )
    {
        return NULL;
    }
    
    pfn = (PFNTransparentWindow)GetProcAddress(hModule, "SetLayeredWindowAttributes");
    if(pfn == NULL)
    {
        return NULL;
    }
    
    FreeLibrary(hModule);
    return pfn;
}
