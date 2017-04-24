#ifndef PROTECT_H
#define PROTECT_H

enum PROTRCTCODE
{
    PROTECT_DL1 = 0,            // 电流I段;         0
    PROTECT_DL2,                // 电流II段         1
    PROTECT_GY1,                // 过压I段;         2
    PROTECT_GY2,                // 过压II段;        3
    PROTECT_QY1,                // 欠压I段;         4
    PROTECT_QY2,                // 欠压II段;        5
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
    WORD wDL1_SetI;					// 电流I段电流;
    WORD wDL1_SetT;					// 电流I段时间;
//     WORD wDL1_TogTrip;              // 跳闸

    WORD wDL2_SetI;					// 电流II段电流;
    WORD wDL2_SetT;					// 电流II段时间;
//     WORD wDL2_TogTrip;              // 跳闸

    WORD wGY1_SetU;					// 过压I段;
    WORD wGY1_SetT;					// 过压I段时间;
//     WORD wGY1_TogTrip;              // 跳闸

    WORD wGY2_SetU;					// 过压II段;
    WORD wGY2_SetT;					// 过压II段时间
//     WORD wGY2_TogTrip;              // 跳闸

    WORD wQY1_SetU;					// 欠压I段;
    WORD wQY1_SetT;					// 欠压I段时间
//     WORD wQY1_TogTrip;              // 跳闸

    WORD wQY2_SetU;					// 欠压II段;
    WORD wQY2_SetT;					// 欠压II段时间
//     WORD wQY2_TogTrip;              // 跳闸
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

