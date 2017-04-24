#define LINKOUT_ALARMED
#define LINKOUT_TRIPPED
#define LINKOUT_ERRORED

#define DS2_ChargedCHZ		0x2000		//�غ�բ���ָʾ;
#define DS2_ChargedBZT		0x4000		//����Ͷ���ָʾ;
#define DS2_MotorStart		0x8000		//�綯������ָʾ;
#define DS3_GR50			0x4000		//����50%ָʾ;
#define DS3_GR75			0x8000		//����75%ָʾ;


//-----------------------------------------------------------------------------
#undef CLASSNAME_APP
#define CLASSNAME_APP CMyAppDMRX01P
class CMyAppDMRX01P:public CMyAppDMRUnit
{
public:
	void OnInitParams(void);
	void OnTimer10ms(void);
	void OnWaveRecord(WORD wCountAD);
};
