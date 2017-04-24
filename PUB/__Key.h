#ifndef __KEY_H
#define __KEY_H

#define KEY_NULL			0x0000
#define KEY_UP				0x0001
#define KEY_DOWN			0x0002
#define KEY_LEFT			0x0004
#define KEY_RIGHT			0x0008
#define KEY_OK				0x0010
#define KEY_CANCEL			0x0020
//#define KEY_SETUP			KEY_OK
#define KEY_RESET			0x0040
#define KEY_ADD			    0x0080
#define KEY_SUB			    0x0100

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
//˵��:��ʼ������;
extern void Key_OnInit(void);
//˵��:��ʱ��ⰴ��״̬;
extern void Key_OnTimer10ms(void);
//˵��:�趨���µ�Ӳ����ʽ������;
extern void Key_SetKeyHardCode(WORD wKeyHardCode);
//˵��:�趨��������İ��������,��KEY_UP,KEY_DOWN;
extern void Key_SetKeyRepeatCode(WORD wKeyRepeatCode);
//˵��:��ָ���İ��������밴���뻺�����;
extern void Key_AddKeyQueue(WORD wKeyCode);
//˵��:�Ӱ����뻺�������ȡ������δ����İ�����,Ӧ�ó�����ݰ�����ִ����Ӧ�Ĳ���;
extern WORD Key_GetKeyQueue(void);
//�����������
extern void OnKeyProcess(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__KEY_H*/
/******************************************************************************
ģ�鹦��:
��Ҫʵ�ֶ԰����Ĵ���,���֧��16������,Ӧ�ó������Ӧ�õķ�����,����[Main.h]ʹ��
#define�԰�������������������¶���,��������Ʊ����Ӳ��ʵ�ʶ�Ӧ,��:
ʹ�ò���:
1.����CMyKey��ʵ��,���������:g_key;
2.��g_hmi.OnInit()�е���OnInit();
3.��g_hmi.OnTimer10ms�е���OnTimer10ms();
4.��g_hmi.OnWhileLoop()�е���GetKeyQueue(),���õ��İ�����ִ����Ӧ�Ĳ���;
5.��g_hdif.OnTimer10ms()�и���Ӳ������Ϣִ��SetKeyHardCode();
*/
//ThinkBoy,ShenBo,2006/04/30;
