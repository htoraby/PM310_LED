extern unsigned short g_wLEDX;
extern unsigned short g_wLEDY;
extern unsigned short g_wPageAllCount;

extern void EditRemoveAll(void);
extern void EditAddEnum(unsigned short* pData,char* pszEnum,unsigned short wCountEnum,unsigned short wCountChar);
extern void EditAddToggle(unsigned short* pData);
extern void EditAddInteger(unsigned short* pData,unsigned short wDataMin,unsigned short wDataMax,unsigned short bReserveZero);
extern void EditAddDataWord(unsigned short* pData,unsigned long dwDataMin,unsigned long dwDataMax,
	unsigned short wFormat,unsigned short wScale2XX,unsigned short wDataRunTime);
extern void EditAddPhQh(unsigned long* pData);
extern void EditEnterEdit(void);
extern void EdiQuittEdit(void);
extern unsigned short OnEditKeyMsg(unsigned short wKeyCode);
extern void OnTaskEdit(void);


