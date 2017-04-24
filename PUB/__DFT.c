#include <Main.h>
/*
#ifdef DFT_DOT32
const short c_nTableCosA32[32] = //cos(360/32)
{
	10000,9808,9239,8315,7071,5556,3827,1951,
	0,-1951,-3827,-5556,-7071,-8315,-9239,-9808,
	-10000,-9808,-9239,-8315,-7071,-5556,-3827,-1951,
	0,1951,3827,5556,7071,8315,9239,9808
};
#endif

#ifdef DFT_DOT24
const short c_nTableCosA24[24] = 
{
10000,9659,8660,7071,5000,2588,
0,-2588,-5000,-7071,-8660,-9659,
-10000,-9659,-8660,-7071,-5000,-2588,
0,2588,5000,7071,8660,9659
};
#endif

#ifdef DFT_DOT48
const short c_nTableCosA48[48] = 
{
10000,9914,9659,9239,8660,7934,7071,6088,5000,3827,2588,1305,
0,-1305,-2588,-3827,-5000,-6088,-7071,-7934,-8660,-9239,-9659,-9914,
-10000,-9914,-9659,-9239,-8660,-7934,-7071,-6088,-5000,-3827,-2588,-1305,
0,1305,2588,3827,5000,6088,7071,7934,8660,9239,9659,9914
};
#endif

#ifdef DFT_DOT96
const short c_nTableCosA96[96] = 
{
10000,9979,9914,9808,9659,9469,9239,8969,8660,8315,7934,7518,7071,6593,6088,5556,5000,4423,3827,3214,2588,1951,1305,654,
0,-654,-1305,-1951,-2588,-3214,-3827,-4423,-5000,-5556,-6088,-6593,-7071,-7518,-7934,-8315,-8660,-8969,-9239,-9469,-9659,-9808,-9914,-9979,
-10000,-9979,-9914,-9808,-9659,-9469,-9239,-8969,-8660,-8315,-7934,-7518,-7071,-6593,-6088,-5556,-5000,-4423,-3827,-3214,-2588,-1951,-1305,-654,
0,654,1305,1951,2588,3214,3827,4423,5000,5556,6088,6593,7071,7518,7934,8315,8660,8969,9239,9469,9659,9808,9914,9979
};
#endif
*/
//*********************************
// #ifdef DFT_DOT32
// short DFT_CalculateDFT1R(short* pData)
// {
// 	long lR = 0;
// 	lR += (long)(pData[ 0]-pData[16])*10000L;
// 
// 	lR += (long)(pData[1]+pData[31]-pData[15]-pData[17])*9808L;
// 	lR += (long)(pData[2]+pData[30]-pData[14]-pData[18])*9239L;
// 	lR += (long)(pData[3]+pData[29]-pData[13]-pData[19])*8315L;
// 	lR += (long)(pData[4]+pData[28]-pData[12]-pData[20])*7071L;
// 	lR += (long)(pData[5]+pData[27]-pData[11]-pData[21])*5556L;
// 	lR += (long)(pData[6]+pData[26]-pData[10]-pData[22])*3827L;
// 	lR += (long)(pData[7]+pData[25]-pData[9] -pData[23])*1951L;
// 	lR += (lR>0)?53333L:-53333L;
// 	lR /= 106667L;
// 	return (short)lR;
// }
// 
// short DFT_CalculateDFT1X(short* pData)
// {
// 	long lX = 0;
// 	lX += (long)(pData[ 1]-pData[31]+pData[15]-pData[17])*1951L;
// 	lX += (long)(pData[ 2]-pData[30]+pData[14]-pData[18])*3827L;
// 	lX += (long)(pData[ 3]-pData[29]+pData[13]-pData[19])*5556L;
// 	lX += (long)(pData[ 4]-pData[28]+pData[12]-pData[20])*7071L;
// 	lX += (long)(pData[ 5]-pData[27]+pData[11]-pData[21])*8315L;
// 	lX += (long)(pData[ 6]-pData[26]+pData[10]-pData[22])*9239L;
// 	lX += (long)(pData[ 7]-pData[25]+pData[9]-pData[23])*9808L;
// 	lX += (long)(pData[8]-pData[24])*10000L;
// 	lX += (lX>0)?53333L:-53333L;
// 	lX /= 106667L;
// 	return (short)-lX;
// }
// #endif
/*******************************************************************************/
#ifdef DFT_DOT24
short DFT_CalculateDFT1R(short* pData)
{
	long lR = 0;
	lR += (long)(pData[0]-pData[12])*10000L;
	lR += (long)(pData[1]+pData[23]-pData[11]-pData[13])*9659L;
	lR += (long)(pData[2]+pData[22]-pData[10]-pData[14])*8660L;
	lR += (long)(pData[3]+pData[21]-pData[ 9]-pData[15])*7071L;
	lR += (long)(pData[4]+pData[20]-pData[ 8]-pData[16])*5000L;
	lR += (long)(pData[5]+pData[19]-pData[ 7]-pData[17])*2588L;
	lR += (lR>0)?30000L:-30000L;
	lR /= 60000L;
	return (short)lR;
}

short DFT_CalculateDFT1X(short* pData)
{
	long lX = 0;
	lX += (long)(pData[1]-pData[23]+pData[11]-pData[13])*2588L;
	lX += (long)(pData[2]-pData[22]+pData[10]-pData[14])*5000L;
	lX += (long)(pData[3]-pData[21]+pData[ 9]-pData[15])*7071L;
	lX += (long)(pData[4]-pData[20]+pData[ 8]-pData[16])*8660L;
	lX += (long)(pData[5]-pData[19]+pData[ 7]-pData[17])*9659L;
	lX += (long)(pData[6]-pData[18])*10000L;
	lX += (lX>0)?30000L:-30000L;
	lX /= 60000L;
	return (short)-lX;
}

// short DFT_CalculateDFTnR(short* pData,WORD wTHD)
// {
// 	WORD i;
// 	long lR;
// 	lR = 0;
// 	for(i=0;i<24;i++) lR += (long)pData[i]*(long)c_nTableCosA24[(i*wTHD)%24];
// 	lR += (lR>0)?40000L:-40000L;
// 	lR /= 80000L;
// 	return (short)lR;
// }
// 
// short DFT_CalculateDFTnX(short* pData,WORD wTHD)
// {
// 	WORD i;
// 	long lX;
// 	lX = 0;
// 	for(i=0;i<24;i++) lX += (long)pData[i]*(long)c_nTableCosA24[(i*wTHD+18)%24];
// 	lX += (lX>0)?40000L:-40000L;
// 	lX /= 80000L;
// 	return (short)-lX;
// }
#endif

/*******************************************************************************/
// #ifdef DFT_DOT48
// short DFT_CalculateDFT1R(short* pData)
// {
// 	long lR = 0;
// 	lR += (long)(pData[ 0]-pData[24])*10000L;
// 	lR += (long)(pData[ 1]+pData[47]-pData[23]-pData[25])*9914L;
// 	lR += (long)(pData[ 2]+pData[46]-pData[22]-pData[26])*9659L;
// 	lR += (long)(pData[ 3]+pData[45]-pData[21]-pData[27])*9239L;
// 	lR += (long)(pData[ 4]+pData[44]-pData[20]-pData[28])*8660L;
// 	lR += (long)(pData[ 5]+pData[43]-pData[19]-pData[29])*7934L;
// 	lR += (long)(pData[ 6]+pData[42]-pData[18]-pData[30])*7071L;
// 	lR += (long)(pData[ 7]+pData[41]-pData[17]-pData[31])*6088L;
// 	lR += (long)(pData[ 8]+pData[40]-pData[16]-pData[32])*5000L;
// 	lR += (long)(pData[ 9]+pData[39]-pData[15]-pData[33])*3827L;
// 	lR += (long)(pData[10]+pData[38]-pData[14]-pData[34])*2588L;
// 	lR += (long)(pData[11]+pData[37]-pData[13]-pData[35])*1305L;
// 	lR += (lR>0)?80000L:-80000L;
// 	lR /= 160000L;
// 	return (short)lR;
// }
// 
// short DFT_CalculateDFT1X(short* pData)
// {
// 	long lX = 0;
// 	lX += (long)(pData[ 1]-pData[47]+pData[23]-pData[25])*1305L;
// 	lX += (long)(pData[ 2]-pData[46]+pData[22]-pData[26])*2588L;
// 	lX += (long)(pData[ 3]-pData[45]+pData[21]-pData[27])*3827L;
// 	lX += (long)(pData[ 4]-pData[44]+pData[20]-pData[28])*5000L;
// 	lX += (long)(pData[ 5]-pData[43]+pData[19]-pData[29])*6088L;
// 	lX += (long)(pData[ 6]-pData[42]+pData[18]-pData[30])*7071L;
// 	lX += (long)(pData[ 7]-pData[41]+pData[17]-pData[31])*7934L;
// 	lX += (long)(pData[ 8]-pData[40]+pData[16]-pData[32])*8660L;
// 	lX += (long)(pData[ 9]-pData[39]+pData[15]-pData[33])*9239L;
// 	lX += (long)(pData[10]-pData[38]+pData[14]-pData[34])*9659L;
// 	lX += (long)(pData[11]-pData[37]+pData[13]-pData[35])*9914L;
// 	lX += (long)(pData[12]-pData[36])*10000L;
// 	lX += (lX>0)?80000L:-80000L;
// 	lX /= 160000L;
// 	return (short)-lX;
// }
// 
// short DFT_CalculateDFTnR(short* pData,WORD wTHD)
// {
// 	long lR = 0;
// 	for(WORD i=0;i<48;i++) lR += (long)pData[i]*(long)c_nTableCosA48[(i*wTHD)%48];
// 	lR += (lR>0)?80000L:-80000L;
// 	lR /= 160000L;
// 	return (short)lR;
// }
// 
// short DFT_CalculateDFTnX(short* pData,WORD wTHD)
// {
// 	long lX = 0;
// 	for(WORD i=0;i<48;i++) lX += (long)pData[i]*(long)c_nTableCosA48[(i*wTHD+36)%48];
// 	lX += (lX>0)?80000L:-80000L;
// 	lX /= 160000L;
// 	return (short)-lX;
// }
// #endif
// /*******************************************************************************/
// #ifdef DFT_DOT96
// short DFT_CalculateDFT1R(short* pData)
// {
// 	long lR = 0;
// 	for(WORD i=0;i<96;i++) lR += (long)pData[i]*(long)c_nTableCosA96[i];
// 	lR += (lR>0)?160000L:-160000L;
// 	lR /= 320000L;
// 	return (short)lR;
// }
// 
// short DFT_CalculateDFT1X(short* pData)
// {
// 	long lX = 0;
// 	for(WORD i=0;i<96;i++) lX += (long)pData[i]*(long)c_nTableCosA96[(i+72)%96];
// 	lX += (lX>0)?160000L:-160000L;
// 	lX /= 320000L;
// 	return (short)-lX;
// }
// 
// short DFT_CalculateDFTnR(short* pData,WORD wTHD)
// {
// 	WORD i;
// 	long lR;
// 	lR = 0;
// 	for(i=0;i<96;i++) lR += (long)pData[i]*(long)c_nTableCosA96[(i*wTHD)%96];
// 	lR += (lR>0)?160000L:-160000L;
// 	lR /= 320000L;
// 	return (short)lR;
// }
// 
// short DFT_CalculateDFTnX(short* pData,WORD wTHD)
// {
// 	WORD i;
// 	long lX;
// 	lX = 0;
// 	for(i=0;i<96;i++) lX += (long)pData[i]*(long)c_nTableCosA96[(i*wTHD+72)%96];
// 	lX += (lX>0)?160000L:-160000L;
// 	lX /= 320000L;
// 	return (short)-lX;
// }
// #endif
