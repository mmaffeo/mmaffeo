#ifndef af_main_h
#define af_main_h


////////////////////////////////////////////////////////////////////////////////////////////////////
// task definition structure
typedef struct
{
    void (*initialize)(void)   ; // called once on power-up
    void (*    update)(void)   ; // called periodically (every 10mS) by task scheduler.

    unsigned char active_modes;  // 8-bit value incidating the modes this task should executed in.
                   // <<b7:b6:b5:b4:b3:b2:b1:b0>>
                   //   if b0 is set -> execute this task in mode zero.
                   //   if b1 is set -> execute this task in mode one.
                   //   if .... etc...
}af_task_t;


////////////////////////////////////////////////////////////////////////////////////////////////////
// "application" programing interface...
#ifndef HCS12_BSP_EMU
void af_main(unsigned char mode); // 10mS execution loop, never returns and should be called from project startup.
#endif /* HCS12_BSP_EMU */

#endif