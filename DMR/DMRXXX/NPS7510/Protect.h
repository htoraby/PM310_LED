#ifndef PROTECT_H
#define PROTECT_H

enum PROTRCTCODE
{
    PROTECT_DL1 = 0,            // ����I��;         0
    PROTECT_DL2,                // ����II��         1
    PROTECT_GY1,                // ��ѹI��;         2
    PROTECT_GY2,                // ��ѹII��;        3
    PROTECT_QY1,                // ǷѹI��;         4
    PROTECT_QY2,                // ǷѹII��;        5
    PROTECT_MAX1
};

enum PROTECTCODE
{
    PROTECT_IN1 = PROTECT_MAX1,
    PROTECT_IN2,
    PROTECT_IN3,
    PROTECT_IN4,
//     PROTECT_IN5,
//     PROTECT_IN6,
//     PROTECT_IN7,
//     PROTECT_IN8,
    PROTECT_MAX
};

typedef struct _DEVICESETPOINT_iBCU
{
    WORD wDL1_SetI;					// ����I�ε���;
    WORD wDL1_SetT;					// ����I��ʱ��;
//     WORD wDL1_TogTrip;              // ��բ

    WORD wDL2_SetI;					// ����II�ε���;
    WORD wDL2_SetT;					// ����II��ʱ��;
//     WORD wDL2_TogTrip;              // ��բ

    WORD wGY1_SetU;					// ��ѹI��;
    WORD wGY1_SetT;					// ��ѹI��ʱ��;
//     WORD wGY1_TogTrip;              // ��բ

    WORD wGY2_SetU;					// ��ѹII��;
    WORD wGY2_SetT;					// ��ѹII��ʱ��
//     WORD wGY2_TogTrip;              // ��բ

    WORD wQY1_SetU;					// ǷѹI��;
    WORD wQY1_SetT;					// ǷѹI��ʱ��
//     WORD wQY1_TogTrip;              // ��բ

    WORD wQY2_SetU;					// ǷѹII��;
    WORD wQY2_SetT;					// ǷѹII��ʱ��
//     WORD wQY2_TogTrip;              // ��բ
}DEVICESETPOINT_iBCU;

//#define Protect_OnUpdateDevice(pData);

//-----------------------------------------------------------------------------
extern void Protect_DL1_OnInit(void);
extern void Protect_DL1_Run(void);

//-----------------------------------------------------------------------------
extern void Protect_DL2_OnInit(void);
extern void Protect_DL2_Run(void);

//-----------------------------------------------------------------------------
extern void Protect_GY1_OnInit(void);
extern void Protect_GY1_Run(void);

//-----------------------------------------------------------------------------
extern void Protect_GY2_OnInit(void);
extern void Protect_GY2_Run(void);

//-----------------------------------------------------------------------------
extern void Protect_QY1_OnInit(void);
extern void Protect_QY1_Run(void);

//-----------------------------------------------------------------------------
extern void Protect_QY2_OnInit(void);
extern void Protect_QY2_Run(void);

//-----------------------------------------------------------------------------
extern void Protect_OnInit(void);
extern void Protect_OnInitSetpoint(WORD* pSetpoint);
// extern void Protect_OnUpdateDevice(WORD* pData);
// extern WORD Protect_GetProtectPickupInfo(WORD wProtectIndex);
extern void Protect_OnActTripped(WORD wProtectIndex);
extern void Protect_Run(void);

extern const PROTECTACTINFO c_protectActInfo[PROTECT_MAX1];
extern DEVICESETPOINT_iBCU* g_pDeviceSetpoint;
extern WORD g_wCountAfterTripped;

#endif/*CMYPROTECTDMRX01P_H*/

