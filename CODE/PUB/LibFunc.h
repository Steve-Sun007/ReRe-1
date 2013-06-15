#ifndef _LIB_FUNC_H
#define _LIB_FUNC_H


// ֻ��������һ��ʵ��
BOOL CALLBACK   EnumWndProc(HWND hwnd,LPARAM lParam);

// ������ת��Ϊʱ�����ʾ��ʽ(12:34:56)
typedef enum {
    TWINKLING_COLON = 0,
    FIXED_COLON,
} TimeFormat;

BOOL            Seconds2Time(UINT nSeconds, char *pchTime, TimeFormat eFormat);

// �ж�һ���ַ����Ƿ�ȫ������
BOOL            IsNumber(CString str);

// ��������֮��ľ���(��������)
UINT            MakeDistance(POINTS a, POINTS b);

// ����������
void            LockKeyboard(BOOL bValue);
void            LockMouse(BOOL bValue);
void            LockKeyBoardAndMouse(BOOL bValue);

// ��ѯ���򿪻�����
BOOL GetAppAutoStartWithSystem(void);
// ���ó��򿪻�����
BOOL SetAppAutoStartWithSystem(BOOL bSetStart, const char *pchAppPath);

// ȫ��ģʽ���
BOOL FullscreenModeDectect(void);

#endif