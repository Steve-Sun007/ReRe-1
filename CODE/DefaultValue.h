#ifndef _DEFAULT_VALUE_H
#define _DEFAULT_VALUE_H
//////////////////////////////////////////////////////////////////////////
// ������
//////////////////////////////////////////////////////////////////////////
#define ACCESS_ERROR    0x12345678


//////////////////////////////////////////////////////////////////////////
// �������õ�Ĭ������ֵ (��λ:��)
//////////////////////////////////////////////////////////////////////////
// Ĭ��ʱ�����
#define DEFAULT_WORK_DURATION           (45 * 60)
#define DEFAULT_SHORT_RELAX_DURATION    (5 * 60)
#define DEFAULT_ENABLE_LONG_RELAX       TRUE
#define DEFAULT_LONG_RELAX_FREQUENCY    (2)
#define DEFAULT_LONG_RELAX_DURATION     (15 * 60)

// Ĭ����ʾ����
#define DEFAULT_ENABLE_PRENOTIFY        TRUE
#define DEFAULT_ENABLE_LOCK_INPUT       FALSE
#define DEFAULT_LOCK_TYPE               RELAX_LOCK_BOTH
#define DEFAULT_GRACE_TIME_BEFORE_LOCK_INPUT    (10)
#define DEFAULT_ENABLE_DARKER_SCREEN    TRUE
#define DEFAULT_DARKER_SCREEN_ALPHA     (180)
#define DEFAULT_DARKER_SCREEN_ANIMATE   ((EAnimateType)(2))
#define DEFAULT_DARKER_SCREEN_COLOR     (RGB(0,0,0))

// Ĭ�϶���ʾ������
#define DEFAULT_NOTIFY_WINDOW_TYPE      MASTER_MONITOR
#define DEFAULT_DARKER_SCREEN_TYPE      MASTER_MONITOR

// Ĭ���Զ�״̬ת������
#define DEFAULT_ENABLE_AUTO_PAUSE       TRUE
#define DEFAULT_AUTO_PAUSE_THRESHOLD    (1 * 60)
#define DEFAULT_ENABLE_FULLSCREEN_PAUSE TRUE
#define DEFAULT_ENABLE_AUTO_RESET       TRUE
#define DEFAULT_AUTO_RESET_THRESHOLD    (15 * 60)

// Ĭ�����Բ���
#define DEFAULT_LANGUAGE                ""

// Ĭ������ѡ�����
#define DEFAULT_ENABLE_LOCK_COMPUTER    FALSE
#define DEFAULT_ENABLE_CLOSE_MONITOR    FALSE
#define DEFAULT_SHOW_FLOATING_WINDOW    FALSE
#define DEFAULT_SHOW_TRAY_ICON          TRUE
#define DEFAULT_ENABLE_LOG              FALSE
#define DEFAULT_LOG_LEVEL               L_MSG
#define DEFAULT_LOG_FILE_SIZE           LOG_FILE_SIZE_256K
#define DEFAULT_AUTO_START              FALSE


//////////////////////////////////////////////////////////////////////////
// ��ʱ��
//////////////////////////////////////////////////////////////////////////
// 1��������ʱ��
#define TIMER_HEART_BEAT_1S             1

// �����ͣ��ⶨʱ��
#define TIMER_MOUSE_HOVER_DETECT        2
#define MOUSE_HOVER_DETECT_LENGTH       (100)


#endif