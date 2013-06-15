#include "stdafx.h"
#include "LibFunc.h"
#include "Log.h"
#include "RelaxTimer.h"


// �ӳ���Ϣ������(����С�ڹ��������ʱ��)
#define RELAX_DELAY_SECOND                  5 * 60


//////////////////////////////////////////////////////////////////////////
// ���캯������������
//////////////////////////////////////////////////////////////////////////
RelaxTimer::RelaxTimer()
{
    // ��ǰ״̬
    m_nStatus               = STATUS_INIT;
    m_nLapsedSeconds        = 0;
    m_nShortRelaxedTimes    = 0;
    // ʱ������
    m_nWorkDuration         = 0;
    m_nShortRelaxDuration   = 0;
    m_bEnableLongRelax      = FALSE;
    m_nLongRelaxFrequency   = 0;
    m_nLongRelaxDuration    = 0;
    // �Զ�״̬ת��
    m_bEnableAutoPause      = FALSE;
    m_nAutoPauseThreshold   = 0;
    m_eAutoPauseType        = AUTO_PAUSE_NO;
    m_bEnableAutoReset      = FALSE;
    m_nAutoResetThreshold   = 0;
    memset(&m_statTime, 0, sizeof(m_statTime));
    memset(&m_statRelax, 0, sizeof(m_statRelax));
}

RelaxTimer::~RelaxTimer()
{
    // ��ʱû��Ҫ�ͷŵ���Դ����������
}

//////////////////////////////////////////////////////////////////////////
//     ��/д��Ա�����ĺ��� (����ӿ�)
//         ���ɹ�������ȷֵ��ʧ�ܷ���ACCESS_ERROR(0x12345678)
//         д�ɹ�����TRUE��ʧ�ܷ���FALSE
//////////////////////////////////////////////////////////////////////////

// ��ǰ״̬
TimerStatus RelaxTimer::GetStatus()     // ��m_nStatus
{
    return m_nStatus;
}

char* RelaxTimer::GetStatusString()     // ��ȡnStatus��Ӧ��״̬�ַ���
{
    return StatusToString(m_nStatus);
}

char* RelaxTimer::StatusToString(TimerStatus nStatus)   // ��ȡnStatus��Ӧ��״̬�ַ���
{
    switch (nStatus)
    {
    case STATUS_INIT:
        return "init";
    case STATUS_WORK:
        return "work";
    case STATUS_SHORT_RELAX:
        return "short relax";
    case STATUS_LONG_RELAX:
        return "long relax";
    case STATUS_PAUSE:
        return "pause";
    case STATUS_RESET:
        return "reset";
    case STATUS_AUTO_PAUSE:
        return "auto pause";
    case STATUS_AUTO_RESET:
        return "auto reset";
    default:
        return "ERROR";
    }
}

BOOL RelaxTimer::SetStatus(TimerStatus nStatus)     // дm_nStatus
{
    CString strOldStatus, strNewStatus;

    // ��ȡԾǨǰ��״̬
    strOldStatus = GetStatusString();

    // ״̬ԾǨ
    m_nStatus = nStatus;

    // ��ȡԾǨ���״̬
    strNewStatus = GetStatusString();

    AppLog(L_MSG, "timer status[%s] change to status[%s].",
           strOldStatus, strNewStatus);
    return TRUE;
}

UINT RelaxTimer::GetLS()                        // ��m_nLapsedSeconds
{
    return m_nLapsedSeconds;
}

BOOL RelaxTimer::IncLS()                        // m_nLapsedSeconds��1
{
    m_nLapsedSeconds++;
    return TRUE;
}

BOOL RelaxTimer::SetLS(UINT nValue)             // дm_nLapsedSeconds
{
    m_nLapsedSeconds = nValue;
    return TRUE;
}

UINT RelaxTimer::GetSRT()                       // ��m_nShortRelaxedTimes
{
    return m_nShortRelaxedTimes;
}

BOOL RelaxTimer::IncSRT()                       // m_nShortRelaxedTimes��1
{
    m_nShortRelaxedTimes++;
    return TRUE;
}

BOOL RelaxTimer::DecSRT()                       // m_nShortRelaxedTimes��1
{
    m_nShortRelaxedTimes--;
    return TRUE;
}

BOOL RelaxTimer::SetSRT(UINT nValue)            // дm_nShortRelaxedTimes
{
    m_nShortRelaxedTimes = nValue;
    return TRUE;
}

// ʱ������
UINT RelaxTimer::GetWD()                        // ��m_nWorkDuration
{
    return m_nWorkDuration;
}

BOOL RelaxTimer::SetWD(UINT nValue)             // дm_nWorkDuration
{
    m_nWorkDuration = nValue;
    return TRUE;
}

UINT RelaxTimer::GetSRD()                       // ��m_nShortRelaxDuration
{
    return m_nShortRelaxDuration;
}

BOOL RelaxTimer::SetSRD(UINT nValue)            // дm_nShortRelaxDuration
{
    m_nShortRelaxDuration = nValue;
    return TRUE;
}

UINT RelaxTimer::GetEnableLongRelax()           // ��m_bEnableLongRelax
{
    return m_bEnableLongRelax;
}

BOOL RelaxTimer::SetEnableLongRelax(BOOL bValue)    // дm_bEnableLongRelax
{
    m_bEnableLongRelax = bValue;
    return TRUE;
}

UINT RelaxTimer::GetLRF()                       // ��m_nLongRelaxFrequency
{
    return m_nLongRelaxFrequency;
}

BOOL RelaxTimer::SetLRF(UINT nValue)            // дm_nLongRelaxFrequency
{
    m_nLongRelaxFrequency = nValue;
    return TRUE;
}

UINT RelaxTimer::GetLRD()                       // ��m_nLongRelaxDuration
{
    return m_nLongRelaxDuration;
}

BOOL RelaxTimer::SetLRD(UINT nValue)            // дm_nLongRelaxDuration
{
    m_nLongRelaxDuration = nValue;
    return TRUE;
}

// �Զ�״̬ת��
UINT RelaxTimer::GetEnableAutoPause()           // ��m_bEnableAutoPause
{
    return m_bEnableAutoPause;
}

BOOL RelaxTimer::SetEnableAutoPause(UINT bValue)    // дm_bEnableAutoPause
{
    m_bEnableAutoPause = bValue;
    return TRUE;
}

UINT RelaxTimer::GetAPT()                       // ��m_nAutoPauseThreshold
{
    return m_nAutoPauseThreshold;
}

BOOL RelaxTimer::SetAPT(UINT nValue)            // дm_nAutoPauseThreshold
{
    m_nAutoPauseThreshold = nValue;
    return TRUE;
}

UINT RelaxTimer::GetEnableFullScreenPause()     // ��m_bEnableFullScreenPause
{
    return m_bEnableFullScreenPause;
}

BOOL RelaxTimer::SetEnableFullScreenPause(UINT bValue)  // дm_bEnableFullScreenPause
{
    m_bEnableFullScreenPause = bValue;
    return TRUE;
}

UINT RelaxTimer::GetAutoPauseType()             // ��m_eAutoPauseType
{
    return m_eAutoPauseType;
}

UINT RelaxTimer::GetEnableAutoReset()           // ��m_bEnableAutoReset
{
    return m_bEnableAutoReset;
}

BOOL RelaxTimer::SetEnableAutoReset(UINT bValue)    // дm_bEnableAutoReset
{
    m_bEnableAutoReset = bValue;
    return TRUE;
}

UINT RelaxTimer::GetART()                       // ��m_nAutoResetThreshold
{
    return m_nAutoResetThreshold;
}

BOOL RelaxTimer::SetART(UINT nValue)            // дm_nAutoResetThreshold
{
    m_nAutoResetThreshold = nValue;
    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// ״̬������ (�ڲ�����)
//////////////////////////////////////////////////////////////////////////
void RelaxTimer::ProcessStatistics()
{
    // ʱ��ͳ��
    m_statTime.nTotalSeconds++;
    switch (m_nStatus)
    {
    case STATUS_INIT:
        break;
    case STATUS_WORK:
        m_statTime.nWorkSeconds++; break;
    case STATUS_SHORT_RELAX:
        m_statTime.nSRelaxSeconds++; break;
    case STATUS_LONG_RELAX:
        m_statTime.nLRelaxSeconds++; break;
    case STATUS_PAUSE:
        m_statTime.nPauseSeconds++; break;
    case STATUS_RESET:
        m_statTime.nResetSeconds++; break;
    case STATUS_AUTO_PAUSE:
        m_statTime.nPauseSeconds++; break;
    case STATUS_AUTO_RESET:
        m_statTime.nResetSeconds++; break;
    default:
        break;
    }
}

TimerStatus RelaxTimer::ProcessTimerStatus()
{
    switch (m_nStatus)
    {
    case STATUS_INIT:
        ProcessInitStatus(); break;
    case STATUS_WORK:
        ProcessWorkStatus(); break;
    case STATUS_SHORT_RELAX:
        ProcessShortRelaxStatus(); break;
    case STATUS_LONG_RELAX:
        ProcessLongRelaxStatus(); break;
    case STATUS_PAUSE:
        ProcessPauseStatus(); break;
    case STATUS_RESET:
        ProcessResetStatus(); break;
    case STATUS_AUTO_PAUSE:
        ProcessAutoPauseStatus(); break;
    case STATUS_AUTO_RESET:
        ProcessAutoResetStatus(); break;
    default:
        break;
    }
    return m_nStatus;
}

void RelaxTimer::ProcessInitStatus()
{
    // INIT ״̬���仯���ݲ�����
}

void RelaxTimer::ProcessWorkStatus()
{
    LASTINPUTINFO lpi;
    lpi.cbSize = sizeof(lpi);
    GetLastInputInfo(&lpi);

    // ���ʹ����ȫ���Զ���ͣ��ÿ10���Ӽ���Ƿ���ȫ��ģʽ
    if (m_bEnableFullScreenPause == TRUE)
    {
        CTime timeAutoSave = CTime::GetCurrentTime();
        if (timeAutoSave.GetSecond() % 10 == 0)
        {
            if (FullscreenModeDectect())
            {
                Work2AutoPause(AUTO_PAUSE_FULLSCREEN);
                return;
            }
        }
    }

    // ���ʹ�����Զ���ͣ״̬ת��������������δ������Զ�״̬ת��
    if (m_bEnableAutoPause == TRUE)
    {
        if (::GetTickCount()-lpi.dwTime >= m_nAutoPauseThreshold * 1000)
        {
            Work2AutoPause(AUTO_PAUSE_IDLE);
            return;
        }
    }
    // ���ʹ�����Զ���λ״̬ת��������������δ������Զ�״̬ת��
    if (m_bEnableAutoReset == TRUE)
    {
        // �����ʱ��û�����룬��ת���Զ���λ̬
        if (::GetTickCount() - lpi.dwTime >= m_nAutoResetThreshold * 1000)
        {
            Work2AutoReset();
            return;
        }
    }

    IncLS();
    if (m_nLapsedSeconds >= m_nWorkDuration)    
    {// ����״̬������׼��������Ϣ״̬
        if (m_bEnableLongRelax && m_nShortRelaxedTimes >= m_nLongRelaxFrequency)
        {// ��������˳���Ϣ���Ҷ���Ϣ���������趨ֵ����ʼ����Ϣ
            Work2LongRelax();
        }
        else
        {// ����ֱ�ӿ�ʼ����Ϣ
            Work2ShortRelax();
        }
    }
}

void RelaxTimer::ProcessShortRelaxStatus()
{
    IncLS();
    if (m_nLapsedSeconds >= m_nShortRelaxDuration)
    {// ����Ϣ״̬������׼�����빤��״̬
        ShortRelax2Work();
    }
}

void RelaxTimer::ProcessLongRelaxStatus()
{
    IncLS();
    if (m_bEnableLongRelax && m_nLapsedSeconds >= m_nLongRelaxDuration)
    {// ����Ϣ״̬������׼�����빤��״̬
        LongRelax2Work();
    }
}

void RelaxTimer::ProcessPauseStatus()
{
    // PAUSE ״̬���仯���ݲ�����
}

void RelaxTimer::ProcessResetStatus()
{
    // RESET ״̬���仯���ݲ�����
}

void RelaxTimer::ProcessAutoPauseStatus()
{
    LASTINPUTINFO lpi;
    lpi.cbSize = sizeof(lpi);
    GetLastInputInfo(&lpi);

    if (m_eAutoPauseType == AUTO_PAUSE_FULLSCREEN)
    {
        if (FullscreenModeDectect() == FALSE)
        {// �������ȫ��ģʽ����������빤��״̬���Ҽ�������idle״̬���
            AutoPause2Work();
        }
        else
        {// �����Ȼ������ȫ��״̬����������к�����idle״̬���
            return;
        }
    }
    
    if (m_bEnableAutoPause == TRUE)
    {
        // ������������룬��ת�빤��̬
        if (::GetTickCount() - lpi.dwTime < m_nAutoPauseThreshold * 1000)
        {
            AutoPause2Work();
            return;
        }
    }
    if (m_bEnableAutoReset == TRUE)
    {
        // �����ʱ��û�����룬��ת���Զ���λ̬
        if (::GetTickCount() - lpi.dwTime >= m_nAutoResetThreshold * 1000)
        {
            AutoPause2AutoReset();
            return;
        }
    }
}

void RelaxTimer::ProcessAutoResetStatus()
{
    LASTINPUTINFO lpi;
    lpi.cbSize = sizeof(lpi);
    GetLastInputInfo(&lpi);

    if (m_bEnableAutoReset == TRUE)
    {
        // ������������룬��ת�빤��̬
        if (::GetTickCount() - lpi.dwTime < m_nAutoResetThreshold * 1000)
        {
            AutoReset2Work();
            return;
        }
    }
}

// ״̬ת��������
void RelaxTimer::Init2Work()
{
    SetStatus(STATUS_WORK);             // ״̬��Ϊ����̬
    SetLS(0);                           // �����0
}

void RelaxTimer::Work2ShortRelax()
{
    SetStatus(STATUS_SHORT_RELAX);      // ״̬��Ϊ����Ϣ̬
    SetLS(0);                           // �����0
    IncSRT();                           // ����Ϣ������1
    m_statRelax.nSRelaxTimes++;         // ����ͳ����
}

void RelaxTimer::Work2LongRelax()
{
    SetStatus(STATUS_LONG_RELAX);       // ״̬��Ϊ����Ϣ̬
    SetLS(0);                           // �����0
    SetSRT(0);                          // ����Ϣ������0
    m_statRelax.nLRelaxTimes++;         // ����ͳ����
}

void RelaxTimer::Work2Pause()
{
    SetStatus(STATUS_PAUSE);            // ״̬��Ϊ��̬ͣ
}

void RelaxTimer::Work2Reset()
{
    SetStatus(STATUS_RESET);            // ״̬��Ϊ��λ̬
    SetLS(0);                           // �����0
    SetSRT(0);                          // ����Ϣ������0
}

void RelaxTimer::Work2AutoPause(EAutoPauseType eAutoPauseType)
{
    SetStatus(STATUS_AUTO_PAUSE);       // ״̬��Ϊ�Զ���̬ͣ
    m_eAutoPauseType = eAutoPauseType;  // ��¼״̬�ı��ԭ��
}

void RelaxTimer::Work2AutoReset()
{
    SetStatus(STATUS_AUTO_RESET);       // ״̬��Ϊ�Զ���λ̬
    SetLS(0);                           // �����0
    SetSRT(0);                          // ����Ϣ������0
}

void RelaxTimer::ShortRelax2Work()
{
    SetStatus(STATUS_WORK);             // ״̬��Ϊ����̬
    SetLS(0);                           // �����0
}

void RelaxTimer::ShortRelax2Reset()
{
    SetStatus(STATUS_RESET);            // ״̬��Ϊ��λ̬
    SetLS(0);                           // �����0
    SetSRT(0);                          // ����Ϣ������0
}

void RelaxTimer::LongRelax2Work()
{
    SetStatus(STATUS_WORK);             // ״̬��Ϊ����̬
    SetLS(0);                           // �����0
}

void RelaxTimer::LongRelax2Reset()
{
    SetStatus(STATUS_RESET);            // ״̬��Ϊ��λ̬
    SetLS(0);                           // �����0
    SetSRT(0);                          // ����Ϣ������0
}

void RelaxTimer::Pause2Work()
{
    SetStatus(STATUS_WORK);             // ״̬��Ϊ����̬
}

void RelaxTimer::Pause2Reset()
{
    SetStatus(STATUS_RESET);            // ״̬��Ϊ��λ̬
    SetLS(0);                           // �����0
    SetSRT(0);                          // ����Ϣ������0
}

void RelaxTimer::Reset2Work()
{
    SetStatus(STATUS_WORK);             // ״̬��Ϊ����̬
    SetLS(0);                           // �����0
}

void RelaxTimer::Reset2ShortRelax()
{
    SetStatus(STATUS_SHORT_RELAX);      // ״̬��Ϊ����Ϣ̬
    SetLS(0);                           // �����0
    IncSRT();                           // ����Ϣ������1
    m_statRelax.nSRelaxTimes++;         // ����ͳ����
}

void RelaxTimer::Reset2LongRelax()
{
    SetStatus(STATUS_LONG_RELAX);       // ״̬��Ϊ����Ϣ̬
    SetLS(0);                           // �����0
    SetSRT(0);                          // ����Ϣ������0
    m_statRelax.nLRelaxTimes++;         // ����ͳ����
}

void RelaxTimer::AutoPause2Work()
{
    SetStatus(STATUS_WORK);             // ״̬��Ϊ����̬
    m_eAutoPauseType = AUTO_PAUSE_NO;
}

void RelaxTimer::AutoPause2AutoReset()
{
    SetStatus(STATUS_AUTO_RESET);       // ״̬��Ϊ�Զ���λ̬
    SetLS(0);                           // �����0
    SetSRT(0);                          // ����Ϣ������0
    m_eAutoPauseType = AUTO_PAUSE_NO;
}

void RelaxTimer::AutoReset2Work()
{
    SetStatus(STATUS_WORK);             // ״̬��Ϊ����̬
    SetLS(0);                           // �����0
}

// ״̬ת��������
void RelaxTimer::StatusTransferNotSupport(TimerStatus statusFrom,
                                          TimerStatus statusTo)
{
    AppLog(L_WARN, "timer status transfer not support, from[%s] to[%s].",
        StatusToString(statusFrom), StatusToString(statusFrom));
}

//////////////////////////////////////////////////////////////////////////
// ״̬���ƺ��� (����ӿ�)
//////////////////////////////////////////////////////////////////////////
TimerStatus RelaxTimer::HeartBeat1Second()
{
    ProcessStatistics();
    return ProcessTimerStatus();
}

void RelaxTimer::StartWork()
{
    switch (m_nStatus)
    {
    case STATUS_INIT:
        Init2Work(); break;
    case STATUS_SHORT_RELAX:
        ShortRelax2Work(); break;
    case STATUS_LONG_RELAX:
        LongRelax2Work(); break;
    case STATUS_PAUSE:
        Pause2Work(); break;
    case STATUS_RESET:
        Reset2Work(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_WORK); break;
    }
}

void RelaxTimer::StartShortRelax()
{
    switch (m_nStatus)
    {
    case STATUS_WORK:
        Work2ShortRelax(); break;
    case STATUS_RESET:
        Reset2ShortRelax(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_SHORT_RELAX); break;
    }
}

void RelaxTimer::StartLongRelax()
{
    switch (m_nStatus)
    {
    case STATUS_WORK:
        Work2LongRelax(); break;
    case STATUS_RESET:
        Reset2LongRelax(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_LONG_RELAX); break;
    }
}

void RelaxTimer::RelaxDelay()
{
    switch (m_nStatus)
    {
    case STATUS_SHORT_RELAX:
        ShortRelax2Work();
        DecSRT();
        break;
    case STATUS_LONG_RELAX:
        LongRelax2Work();
        DecSRT();
        break;
    default:
        break;
    }
    SetLS((GetWD() >= RELAX_DELAY_SECOND) ?
        GetWD() - RELAX_DELAY_SECOND : 0);

    // ����ͳ�Ʊ���
    m_statRelax.nDelayedTimes++;
}

void RelaxTimer::RelaxSkip()
{
    switch (m_nStatus)
    {
    case STATUS_SHORT_RELAX:
        ShortRelax2Work();
        break;
    case STATUS_LONG_RELAX:
        LongRelax2Work();
        break;
    case STATUS_WORK:
        Work2AutoReset();
        AutoReset2Work();
        break;
    default:
        return;
    }

    // ����ͳ�Ʊ���
    m_statRelax.nSkippedTimes++;

}

void RelaxTimer::TimerPause()
{
    switch (m_nStatus)
    {
    case STATUS_WORK:
        Work2Pause(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_PAUSE); break;
    }
}

void RelaxTimer::TimerResume()
{
    switch (m_nStatus)
    {
    case STATUS_PAUSE:
        Pause2Work(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_WORK); break;
    }
}

void RelaxTimer::TimerReset()
{
    switch (m_nStatus)
    {
    case STATUS_WORK:
        Work2Reset(); break;
    case STATUS_SHORT_RELAX:
        ShortRelax2Reset(); break;
    case STATUS_LONG_RELAX:
        LongRelax2Reset(); break;
    case STATUS_PAUSE:
        Pause2Reset(); break;
    default:
        StatusTransferNotSupport(m_nStatus, STATUS_RESET); break;
    }
}

UINT RelaxTimer::StatGet_TotalSeconds()
{
    return m_statTime.nTotalSeconds;
}

UINT RelaxTimer::StatGet_WorkSeconds()
{
    return m_statTime.nWorkSeconds;
}

UINT RelaxTimer::StatGet_SRelaxSeconds()
{
    return m_statTime.nSRelaxSeconds;
}

UINT RelaxTimer::StatGet_LRelaxSeconds()
{
    return m_statTime.nLRelaxSeconds;
}

UINT RelaxTimer::StatGet_PauseSeconds()
{
    return m_statTime.nPauseSeconds;
}

UINT RelaxTimer::StatGet_ResetSeconds()
{
    return m_statTime.nResetSeconds;
}

UINT RelaxTimer::StatGet_SRelaxTimes()
{
    return m_statRelax.nSRelaxTimes;
}

UINT RelaxTimer::StatGet_LRelaxTimes()
{
    return m_statRelax.nLRelaxTimes;
}

UINT RelaxTimer::StatGet_DelayedTimes()
{
    return m_statRelax.nDelayedTimes;
}

UINT RelaxTimer::StatGet_SkippedTimes()
{
    return m_statRelax.nSkippedTimes;
}

BOOL RelaxTimer::StatSet_TotalSeconds(UINT nValue)
{
    m_statTime.nTotalSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_WorkSeconds(UINT nValue)
{
    m_statTime.nWorkSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_SRelaxSeconds(UINT nValue)
{
    m_statTime.nSRelaxSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_LRelaxSeconds(UINT nValue)
{
    m_statTime.nLRelaxSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_PauseSeconds(UINT nValue)
{
    m_statTime.nPauseSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_ResetSeconds(UINT nValue)
{
    m_statTime.nResetSeconds = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_SRelaxTimes(UINT nValue)
{
    m_statRelax.nSRelaxTimes = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_LRelaxTimes(UINT nValue)
{
    m_statRelax.nLRelaxTimes = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_DelayedTimes(UINT nValue)
{
    m_statRelax.nDelayedTimes = nValue;
    return TRUE;
}

BOOL RelaxTimer::StatSet_SkippedTimes(UINT nValue)
{
    m_statRelax.nSkippedTimes = nValue;
    return TRUE;
}
