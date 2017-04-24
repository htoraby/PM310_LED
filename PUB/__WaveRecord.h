#ifndef __WAVERECORD_H
#define __WAVERECORD_H

#define MODULE__WAVERECORD_H

#ifndef WAVERECORD_WAVENUM
#define WAVERECORD_WAVENUM      4               //���¼������;
#endif

#ifndef WAVERECORD_DOTNUM
#define WAVERECORD_DOTNUM       2400            //ÿ��¼�������¼������;
#endif

#ifndef WAVERECORD_DATASIZE
#define WAVERECORD_DATASIZE     7               //ÿ��¼�������ݴ�С;
#endif

#define WAVERECORD_ALLWORDS     ((DWORD)WAVERECORD_WAVENUM*(18L+(DWORD)WAVERECORD_DOTNUM*(DWORD)WAVERECORD_DATASIZE))

#define WRS_NULL                0x0000          //����״̬;
#define WRS_RECORDING           0xaaaa          //¼��״̬;
#define WRS_RECORDED            0xffff          //¼�����״̬;

#define WAVEHEAD_SIZE           18              //¼���б���ϢWORD��Ŀ
#define WAVEDATA_SIZE           1680            //¼������WORD��Ŀ
#define WAVEDCHANEL_SIZE        80              //���δ���¼������WORD��Ŀ



//-----------------------------------------------------------------------------
typedef struct
{
    DEVICETIME timeFreeze;                              //¼����¼������ʱ��;
    WORD wRecordStatus;                                 //¼������ǰ¼��״̬;
    WORD wFreezeDotNo;                                  //¼����¼��������;
    WORD wCycleFlag;                                    //¼�����Ƿ�ѭ����־;
    short nK[WAVERECORD_DATASIZE];                      // У��ϵ��
    WORD wOffset;                                       // ֱ������
    WORD wData[WAVERECORD_DOTNUM][WAVERECORD_DATASIZE]; //¼����¼������;
}WAVERECORD;

//-----------------------------------------------------------------------------
extern void WaveRecord_OnInit(void);
extern void WaveRecord_OnTimer1000ms(void);
extern void WaveRecord_StartRecord(void);
extern void WaveRecord_FreezeRecord(void);
extern void WaveRecord_OnRecord(void);
extern WAVERECORD* WaveRecord_GetRecord(WORD wWaveRecordNo);
extern void WaveRecord_ReadRecord(void);
extern void WaveRecord_WriteRecord(void);

extern WORD g_wWRCountNew;                      // ����¼������
extern WORD g_wWRCountOld;                      // ����¼������(���ٸ�����);
extern WORD g_wWRData[WAVERECORD_DATASIZE];     //��ǰ������;

#endif/*__WAVERECORD_H*/
