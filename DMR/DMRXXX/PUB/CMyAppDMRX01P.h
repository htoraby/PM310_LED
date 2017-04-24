#define LINKOUT_ALARMED
#define LINKOUT_TRIPPED
#define LINKOUT_ERRORED

#define DS2_ChargedCHZ		0x2000		//重合闸充电指示;
#define DS2_ChargedBZT		0x4000		//备自投充电指示;
#define DS2_MotorStart		0x8000		//电动机启动指示;
#define DS3_GR50			0x4000		//过热50%指示;
#define DS3_GR75			0x8000		//过热75%指示;


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
