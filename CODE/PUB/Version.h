#ifndef _VERSION_H
#define _VERSION_H


// ��ȡ�ļ��汾��
CString GetFileVersion(const char *pchFile);
// �汾�ַ���ת��ΪUINT�Ͱ汾��
UINT VersionString2Num(const char *pchVersion);
// UINT�Ͱ汾��ת��Ϊ�汾�ַ���
CString VersionNum2String(UINT dwVersion);
// ��ȡ�ļ��޸�ʱ��
CString GetFileData(const char *pchFile);
// ��ȡ�ļ�PrivateBuild
CString GetFileVerInfoItem(const char *pchFileName, const char *pchItem);


#endif