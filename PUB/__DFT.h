#ifndef __DFT_H
#define __DFT_H

#ifdef DFT_DOT32
#define DFT_DOTNUM			32
#endif
#ifdef DFT_DOT24
#define DFT_DOTNUM			24
#endif
#ifdef DFT_DOT48
#define DFT_DOTNUM			48
#endif
#ifdef DFT_DOT96
#define DFT_DOTNUM			96
#endif

#ifdef __cplusplus
extern "C" {
#endif

//说明:对指定的数据序列计算基波分量的实部,pData:指向连续的数据序列(24/48/96点),返回:基波分量的实部;
extern short DFT_CalculateDFT1R(short* pData);
//说明:对指定的数据序列计算基波分量的虚部,pData:指向连续的数据序列(24/48/96点),返回:基波分量的虚部;
extern short DFT_CalculateDFT1X(short* pData);
//说明:对指定的数据序列计算wTHD次谐波分量的实部,pData:指向连续的数据序列(24/48/96点),wTHD:谐波次数,如3表示3次谐波,返回:wTHD次谐波分量的实部;
// extern short DFT_CalculateDFTnR(short* pData,WORD wTHD);
//说明:对指定的数据序列计算wTHD次谐波分量的虚部,pData:指向连续的数据序列(24/48/96点),wTHD:谐波次数,如3表示3次谐波,返回:wTHD次谐波分量的虚部;
// extern short DFT_CalculateDFTnX(short* pData,WORD wTHD);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__DFT_H*/

/******************************************************************************
模块功能:
主要实现对24/48/96点连续数据序列进行的离散DFT变换;
输入数据序列范围为0-4000,转换结果的辐值(或有效值)为3000;
12位A/D转换结果直接可进行离散DFT变换,得到最大有效值3000;
10位A/D转换结果须左移两位后进行离散DFT变换,得到最大有效值3000;
8位A/D转换结果须左移四位后进行离散DFT变换,得到最大有效值3000;
离散DFT转换后的结果(实部和虚部)可直接构成逆时针旋转的矢量,符合电力系统规则;
使用步骤:
1.在[Main.h]中定义每周波采样点数DFT_DOTXX;
2.一般通过__Measure.*模块调用DFT计算函数,用户程序可不直接调用;
*/
//ThinkBoy,ShenBo,2006/04/30;
