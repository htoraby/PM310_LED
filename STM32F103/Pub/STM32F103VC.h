
#ifdef __cplusplus
extern "C" {
#endif

extern void DelayOnce(DWORD dwCountUS);
// extern WORD GetFreqXINT1(void);
// extern WORD GetFreqXINT2(void);
extern DWORD g_dwFsam;
extern DWORD g_dwSysTimerUs;
    
extern const tCRC32INFO* g_pCRCInfo;

#ifdef __cplusplus
}
#endif /* extern "C" */
