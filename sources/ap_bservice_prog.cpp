
/*
    This module implements the "Bobcat Service" flash programming command set.
*/


#include "ap_bservice.h"
#include "ap_bservice_prog.h"

#include "ap_can.h"
#include "ap_subs.h"
#include "defines.h"
#include "ap_version.h"

#include "global.h"


#include <stdlib.h>

#include "MX_Gtwy_Control_private.h"


unsigned short bservice_seed;

void bservice_prog_initialize(void)
{
    ;
}

#define REQUEST_FOR_PROTOCOL        0x80
#define REQUEST_FOR_PROTOCOL_REPLY  0x81
#define REQUEST_FOR_PROGRAMMING     0x82
#define RESPONSE_COMMAND_REPLY      0x83
#define REQUEST_FOR_ERASE           0x84
#define PROG_ADDRESS                0x85
#define PROG_DATA                   0x86
#define PROG_CHECKSUM               0x87
#define PROG_END                    0x88

enum rstatus_t
{
    SEND_ACK,
    SEND_NAK,
    SEND_NOTHING,     //   ???
    SEND_RESPONSE
};


bservice_prog_mode_t bservice_prog_mode;



uint8_t process_bservice_prog_cmd(const hw_can_msg_t *request,
                                        hw_can_msg_t *response )
{
    response->DLR = 8;
    response->DSR[0] = 0x0B;   // response to a "Program Module" message

    rstatus_t rstatus = SEND_NAK;

    unsigned char cmd = request->DSR[1];

    switch (cmd)
    {
        case REQUEST_FOR_PROTOCOL:
            response->DSR[1] = REQUEST_FOR_PROTOCOL_REPLY;
            response->DSR[2] = bservProg_protocolID;
            response->DSR[3] = bservProg_options;
            response->DSR[4] = bservProg_customerID;
            response->DSR[5] = bservProg_maxDataSize;

            do { bservice_seed = rand(); }
            while (bservice_seed == 0);    // can't send a "seed" of zero.

            response->DSR[6] = bservice_seed >> 8;
            response->DSR[7] = (uint8_t) bservice_seed ;

            break;

        case REQUEST_FOR_PROGRAMMING:
            unsigned short key = request->DSR[6] * 0x100 + request->DSR[7];

            if ( key == ((bservice_seed & 0xFA5F)+1) )
            {
                state_System =  SYS_POWER_DOWN;
                SEND_CAN03_NOW;
 //               SEND_CAN03EXT_NOW;

                eeMirror.recoveryMode = SOFTWARE_UPDATED;

                UpdateEEVariables(NOW);

                // start bootblock in the "captured" mode...
                ap_bservice_pending_reset = TO_BB_SMODE_CAPTURED;
                ap_bservice_pending_reset_countdown = 5;   // wait 5 loops (50mS) unitl reset
                rstatus=SEND_NOTHING;                  // bootblock will send the ACK
            }
            else
            {   // change mode and send NAK
                rstatus=SEND_NAK;
            }

            break;
    }

    if (cmd != REQUEST_FOR_PROTOCOL )
    {
        response->DLR = 6;
        response->DSR[1] = 0x83;
        response->DSR[2] = cmd;
        response->DSR[3] = (rstatus == SEND_ACK)?0:1;

        if (cmd != REQUEST_FOR_PROGRAMMING )
        {

            response->DSR[4] = 0xFF;
            response->DSR[5] = 0xFF;
        }

        response->DSR[6] = 0xFF;
        response->DSR[7] = 0xFF;
    }

    return (rstatus==SEND_NOTHING)?0:1;


}





