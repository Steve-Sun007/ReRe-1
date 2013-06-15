#ifndef _RELAX_TIMER_H
#define _RELAX_TIMER_H


// RelaxTimer���е�״̬�б�
typedef enum _TimerStatus{
    STATUS_INIT = 0,
    STATUS_WORK,
    STATUS_SHORT_RELAX,
    STATUS_LONG_RELAX,
    STATUS_PAUSE,
    STATUS_RESET,
    STATUS_AUTO_PAUSE,
    STATUS_AUTO_RESET
} TimerStatus;

// AutoPause�ļ���״̬
typedef enum {
    AUTO_PAUSE_NO = 0,
    AUTO_PAUSE_IDLE,
    AUTO_PAUSE_FULLSCREEN,
} EAutoPauseType;

// ʱ��ͳ�ƽṹ��
typedef struct _TimeStatistics
{
    UINT    nTotalSeconds;      // �����ܵ�����ʱ��
    UINT    nWorkSeconds;       // ����״̬�µ�ʱ��
    UINT    nSRelaxSeconds;     // ����Ϣ״̬�µ�ʱ��
    UINT    nLRelaxSeconds;     // ����Ϣ״̬�µ�ʱ��
    UINT    nPauseSeconds;      // ��ͣ״̬�µ�ʱ��
    UINT    nResetSeconds;      // ��λ״̬�µ�ʱ��
} TimeStatistics;

// ��Ϣͳ�ƽṹ��
typedef struct _RelaxStatistics
{
    UINT    nSRelaxTimes;       // ����Ϣ����
    UINT    nLRelaxTimes;       // ����Ϣ����
    UINT    nDelayedTimes;      // ʹ���ӳٵĴ���
    UINT    nSkippedTimes;      // ʹ�������Ĵ���
} RelaxStatistics;


// RelaxTimer�ඨ��
class RelaxTimer
{
public:
    //////////////////////////////////////////////////////////////////////////
    // ���캯������������
    //////////////////////////////////////////////////////////////////////////
    RelaxTimer();
    ~RelaxTimer();

    //////////////////////////////////////////////////////////////////////////
    //  ��/д��Ա�����ĺ��� (����ӿ�)
    //      ���ɹ�������ȷֵ��ʧ�ܷ���ACCESS_ERROR(0x12345678)
    //      д�ɹ�����TRUE��ʧ�ܷ���FALSE
    //////////////////////////////////////////////////////////////////////////

    // ��ǰ״̬
    TimerStatus     GetStatus();                            // ��m_nStatus
    char*           GetStatusString();                      // ��ȡm_nStatus��Ӧ��״̬�ַ���
    char*           StatusToString(TimerStatus nStatus);    // ��ȡnStatus��Ӧ��״̬�ַ���
    BOOL            SetStatus(TimerStatus nStatus);         // дm_nStatus
    UINT            GetLS();                                // ��m_nLapsedSeconds
    BOOL            IncLS();                                // m_nLapsedSeconds��1
    BOOL            SetLS(UINT nValue);                     // дm_nLapsedSeconds
    UINT            GetSRT();                               // ��m_nShortRelaxedTimes
    BOOL            IncSRT();                               // m_nShortRelaxedTimes��1
    BOOL            DecSRT();                               // m_nShortRelaxedTimes��1
    BOOL            SetSRT(UINT nValue);                    // дm_nShortRelaxedTimes
    // ʱ������
    UINT            GetWD();                                // ��m_nWorkDuration
    BOOL            SetWD(UINT nValue);                     // дm_nWorkDuration
    UINT            GetSRD();                               // ��m_nShortRelaxDuration
    BOOL            SetSRD(UINT nValue);                    // дm_nShortRelaxDuration
    UINT            GetEnableLongRelax();                   // ��m_bEnableLongRelax
    BOOL            SetEnableLongRelax(BOOL bValue);        // дm_bEnableLongRelax
    UINT            GetLRF();                               // ��m_nLongRelaxFrequency
    BOOL            SetLRF(UINT nValue);                    // дm_nLongRelaxFrequency
    UINT            GetLRD();                               // ��m_nLongRelaxDuration
    BOOL            SetLRD(UINT nValue);                    // дm_nLongRelaxDuration
    // �Զ�״̬ת��
    UINT            GetEnableAutoPause();                   // ��m_bEnableAutoPause
    BOOL            SetEnableAutoPause(UINT bValue);        // дm_bEnableAutoPause
    UINT            GetAPT();                               // ��m_nAutoPauseThreshold
    BOOL            SetAPT(UINT nValue);                    // дm_nAutoPauseThreshold
    UINT            GetEnableFullScreenPause();             // ��m_bEnableFullScreenPause
    BOOL            SetEnableFullScreenPause(UINT bValue);  // дm_bEnableFullScreenPause
    UINT            GetAutoPauseType();                     // ��m_eAutoPauseType
    UINT            GetEnableAutoReset();                   // ��m_bEnableAutoReset
    BOOL            SetEnableAutoReset(UINT bValue);        // дm_bEnableAutoReset
    UINT            GetART();                               // ��m_nAutoResetThreshold
    BOOL            SetART(UINT nValue);                    // дm_nAutoResetThreshold

private:
    //////////////////////////////////////////////////////////////////////////
    // ״̬������ (�ڲ�����)
    //////////////////////////////////////////////////////////////////////////
    void            ProcessStatistics();
    TimerStatus     ProcessTimerStatus();

    // ״̬��������
    void            ProcessInitStatus();
    void            ProcessWorkStatus();
    void            ProcessShortRelaxStatus();
    void            ProcessLongRelaxStatus();
    void            ProcessPauseStatus();
    void            ProcessResetStatus();
    void            ProcessAutoPauseStatus();
    void            ProcessAutoResetStatus();

    // ״̬ת��������
    void            Init2Work();
    void            Work2ShortRelax();
    void            Work2LongRelax();
    void            Work2Pause();
    void            Work2Reset();
    void            Work2AutoPause(EAutoPauseType eAutoPauseType);
    void            Work2AutoReset();
    void            ShortRelax2Work();
    void            ShortRelax2Reset();
    void            LongRelax2Work();
    void            LongRelax2Reset();
    void            Pause2Work();
    void            Pause2Reset();
    void            Reset2Work();
    void            Reset2ShortRelax();
    void            Reset2LongRelax();
    void            AutoPause2Work();
    void            AutoPause2AutoReset();
    void            AutoReset2Work();

    // ״̬ת��������
    void            StatusTransferNotSupport(TimerStatus statusFrom, TimerStatus statusTo);

public:
    //////////////////////////////////////////////////////////////////////////
    // ״̬���ƺ��� (����ӿ�)
    //////////////////////////////////////////////////////////////////////////
    TimerStatus     HeartBeat1Second();
    void            StartWork();
    void            StartShortRelax();
    void            StartLongRelax();
    void            RelaxDelay();
    void            RelaxSkip();
    void            TimerPause();
    void            TimerResume();
    void            TimerReset();

    //////////////////////////////////////////////////////////////////////////
    // ͳ�ƺ��� (����ӿ�)
    //////////////////////////////////////////////////////////////////////////
    UINT            StatGet_TotalSeconds();     // �����ܵ�����ʱ��
    UINT            StatGet_WorkSeconds();      // ����״̬�µ�ʱ��
    UINT            StatGet_SRelaxSeconds();    // ����Ϣ״̬�µ�ʱ��
    UINT            StatGet_LRelaxSeconds();    // ����Ϣ״̬�µ�ʱ��
    UINT            StatGet_PauseSeconds();     // ��ͣ״̬�µ�ʱ��
    UINT            StatGet_ResetSeconds();     // ��λ״̬�µ�ʱ��
    UINT            StatGet_SRelaxTimes();      // ����Ϣ����
    UINT            StatGet_LRelaxTimes();      // ����Ϣ����
    UINT            StatGet_DelayedTimes();     // ʹ���ӳٵĴ���
    UINT            StatGet_SkippedTimes();     // ʹ�������Ĵ���

    BOOL            StatSet_TotalSeconds(UINT nValue);  // �����ܵ�����ʱ��
    BOOL            StatSet_WorkSeconds(UINT nValue);   // ����״̬�µ�ʱ��
    BOOL            StatSet_SRelaxSeconds(UINT nValue); // ����Ϣ״̬�µ�ʱ��
    BOOL            StatSet_LRelaxSeconds(UINT nValue); // ����Ϣ״̬�µ�ʱ��
    BOOL            StatSet_PauseSeconds(UINT nValue);  // ��ͣ״̬�µ�ʱ��
    BOOL            StatSet_ResetSeconds(UINT nValue);  // ��λ״̬�µ�ʱ��
    BOOL            StatSet_SRelaxTimes(UINT nValue);   // ����Ϣ����
    BOOL            StatSet_LRelaxTimes(UINT nValue);   // ����Ϣ����
    BOOL            StatSet_DelayedTimes(UINT nValue);  // ʹ���ӳٵĴ���
    BOOL            StatSet_SkippedTimes(UINT nValue);  // ʹ�������Ĵ���

private:
    // ��ǰ״̬
    TimerStatus     m_nStatus;                  // RelaxTimer��ǰ��״̬
    UINT            m_nLapsedSeconds;           // RelaxTimer�ڵ�ǰ״̬�µļ���
    UINT            m_nShortRelaxedTimes;       // RelaxTimer���Ѿ�����Ϣ�Ĵ���
    // ʱ������ (��λ:��)
    UINT            m_nWorkDuration;            // RelaxTimer����ʱ��
    UINT            m_nShortRelaxDuration;      // RelaxTimer����Ϣʱ��
    BOOL            m_bEnableLongRelax;         // RelaxTimer�Ƿ����ó���Ϣ
    UINT            m_nLongRelaxFrequency;      // RelaxTimer���ζ���Ϣ��ʼ����Ϣ
    UINT            m_nLongRelaxDuration;       // RelaxTimer����Ϣʱ��
    // �Զ�״̬ת�� (��λ:��)
    BOOL            m_bEnableAutoPause;         // RelaxTimer�Ƿ������Զ���ͣ
    UINT            m_nAutoPauseThreshold;      // RelaxTimer�����Ӻ�����Զ���ͣ״̬
    BOOL            m_bEnableFullScreenPause;   // RelaxTimer�Ƿ�����ȫ�����Զ���ͣ
    EAutoPauseType  m_eAutoPauseType;           // RelaxTimer���Զ���ͣ״̬
    BOOL            m_bEnableAutoReset;         // RelaxTimer�Ƿ������Զ���λ
    UINT            m_nAutoResetThreshold;      // RelaxTimer�����Ӻ�����Զ���λ״̬
    // ͳ�ƽṹ�����
    TimeStatistics  m_statTime;                 // ʱ��ͳ����
    RelaxStatistics m_statRelax;                // ��Ϣͳ����
};

#endif
