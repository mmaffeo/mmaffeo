
/*
    Bobcat service tool programming command interface...
*/

#ifndef ap_bservice_prog_h
#define ap_bservice_prog_h



#include "hw_io.h"



class bservice_prog_mode_t
{
public:
    uint8_t Active(void) const  { return mode == 1; }
    void    Set   (void)        { mode = 1;         }
    void    Clear (void)        { mode = 0;         }

private:
    uint8_t mode;
};
extern bservice_prog_mode_t bservice_prog_mode;


uint8_t process_bservice_prog_cmd(const hw_can_msg_t *request,
                                     hw_can_msg_t *response );





#endif

