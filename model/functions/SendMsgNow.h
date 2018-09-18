#ifndef SendMsgNow_h
#define SendMsgNow_h

#ifdef __cplusplus
extern "C" {
#endif


void SendMsg_BICSControl_Now(void);
void SendMsg_03_Now(void);
void matlab_UpdateEEVar(void);
void SendMsg_SOFTRequest_Now(void);
void SendMsg_Derate_Now(void);
void SendMsg_DPM2_Now(void);

#ifdef __cplusplus
}
#endif

#endif
