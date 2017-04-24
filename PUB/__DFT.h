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

//˵��:��ָ�����������м������������ʵ��,pData:ָ����������������(24/48/96��),����:����������ʵ��;
extern short DFT_CalculateDFT1R(short* pData);
//˵��:��ָ�����������м�������������鲿,pData:ָ����������������(24/48/96��),����:�����������鲿;
extern short DFT_CalculateDFT1X(short* pData);
//˵��:��ָ�����������м���wTHD��г��������ʵ��,pData:ָ����������������(24/48/96��),wTHD:г������,��3��ʾ3��г��,����:wTHD��г��������ʵ��;
// extern short DFT_CalculateDFTnR(short* pData,WORD wTHD);
//˵��:��ָ�����������м���wTHD��г���������鲿,pData:ָ����������������(24/48/96��),wTHD:г������,��3��ʾ3��г��,����:wTHD��г���������鲿;
// extern short DFT_CalculateDFTnX(short* pData,WORD wTHD);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__DFT_H*/

/******************************************************************************
ģ�鹦��:
��Ҫʵ�ֶ�24/48/96�������������н��е���ɢDFT�任;
�����������з�ΧΪ0-4000,ת������ķ�ֵ(����Чֵ)Ϊ3000;
12λA/Dת�����ֱ�ӿɽ�����ɢDFT�任,�õ������Чֵ3000;
10λA/Dת�������������λ�������ɢDFT�任,�õ������Чֵ3000;
8λA/Dת�������������λ�������ɢDFT�任,�õ������Чֵ3000;
��ɢDFTת����Ľ��(ʵ�����鲿)��ֱ�ӹ�����ʱ����ת��ʸ��,���ϵ���ϵͳ����;
ʹ�ò���:
1.��[Main.h]�ж���ÿ�ܲ���������DFT_DOTXX;
2.һ��ͨ��__Measure.*ģ�����DFT���㺯��,�û�����ɲ�ֱ�ӵ���;
*/
//ThinkBoy,ShenBo,2006/04/30;
