#ifndef __MYHMI_H
#define __MYHMI_H

#ifdef __cplusplus
extern "C" {
#endif

extern void MyHMI_OnInit(void);
extern void MyHMI_OnTimer10ms(void);
extern void MyHMI_OnTimer1000ms(void);
extern void MyHMI_OnWhileLoop(void);

extern LIGHT g_Light;
extern TESTDEVICE g_TestDevice;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif/*__MYHMI_H*/
