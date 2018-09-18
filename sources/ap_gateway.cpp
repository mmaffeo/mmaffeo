
#include "hw_io.h"
#include "nvm_ecuid.h"
#include "ap_gateway.h"
#include <stdlib.h>
#include "ap_can.h"
#include "cdata.h"
#include "defines.h"

#define MAX_NUMBER_GATEWAYS           25
hw_can_msg_filter_t msg_gateways[MAX_NUMBER_GATEWAYS];

///////////////////////////////////////////////////////////////////////////////////////////////////
// CAN message filter class
///////////////////////////////////////////////////////////////////////////////////////////////////

void hw_can_msg_filter_t::initialize(void)
{
    next = NULL;
    // set all mask bits to "don't care"
    id_mask.set_idr(0x00000000);
    data_mask[0] = 0x00;
    data_mask[1] = 0x00;    
}


bool hw_can_msg_filter_t::match(const hw_can_msg_t *msg )const
{
    uint8_t i = 4;    
    
    while(i)
    //for (uint8_t i = 0; i<4; ++i)
    {           
        i--;
        if ( ( (id_value.IDR[i]^msg->id.IDR[i]) & id_mask.IDR[i]) != 0x00 )
        {
            return false;
        }
        
        // don't think we ever want worry about this - AL
        //if (i<2)
        //{
        //    if ( ( (data_value[i]^msg->DSR[i]) & data_mask[i]) != 0x00 )
        //    {
        //        return false;
        //    }
        //}
    }

    return true;
}

void initialize_gateway_filters(void)    
{
  uint8_t i;
 
  for(i = 0; i < MAX_NUMBER_GATEWAYS; i++)
  {
    if((MXGTW_GATEWAY_DIRECTION[i] != 0xFF))
    {
      msg_gateways[i].initialize();
      msg_gateways[i].id_value.set_extID(MXGTW_GATEWAY_J1939_ID[i]);
      msg_gateways[i].id_mask.set_extID(MXGTW_GATEWAY_J1939_MASK[i]);
      
      if(MXGTW_GATEWAY_DIRECTION[i] == DIRECTION_BOTH)
      { 
        msg_gateways[i].route = hw_can_msg_filter_t::RT_CAN0_TO_CAN4 | 
                                hw_can_msg_filter_t::RT_CAN4_TO_CAN0;      
      }
      else if(MXGTW_GATEWAY_DIRECTION[i] == DIRECTION_1_TO_2)
      {
        msg_gateways[i].route = hw_can_msg_filter_t::RT_CAN0_TO_CAN4;  
      }
      else if(MXGTW_GATEWAY_DIRECTION[i] == DIRECTION_2_TO_1)
      {
        msg_gateways[i].route = hw_can_msg_filter_t::RT_CAN4_TO_CAN0;
      }
      
      ap_gateway_routes.add(& msg_gateways[i] );
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// CAN message filter gateway filter list class
///////////////////////////////////////////////////////////////////////////////////////////////////

void hw_can_msg_filter_list::initialize(void) 
{
    first = NULL;
}


void hw_can_msg_filter_list::add(hw_can_msg_filter_t *f)
{					
    if (first==NULL)
    {
        first = f;
    }
    else
    {
        hw_can_msg_filter_t *nf = first;
        
        while (nf->next != NULL)
            nf = nf->next;
        
        EnterCritical();         
        nf->next = f;
        ExitCritical();         
    }					
}


///////////////////////////////////////////////////////////////////////////////////////////////////


hw_can_rxmsg gatway_rx_mbox[HWC_CAN_QTY];


hw_can_msg_filter_list ap_gateway_routes;


static void unpack_gateway_rx_mbox(hw_can_msg_t *msg, uint8_t port)
{
    hw_can_msg_filter_t *fl = ap_gateway_routes.first;
        
    while (fl != NULL)
    {
        if (fl->match(msg))
        {
        
            if      (port==HWC_CAN0 && (fl->route & hw_can_msg_filter_t::RT_CAN0_TO_CAN4 ) )
                hw_can_txq[HWC_CAN4].send_msg(msg);    
            
            else if (port==HWC_CAN4 && (fl->route & hw_can_msg_filter_t::RT_CAN4_TO_CAN0 ) )
                hw_can_txq[HWC_CAN0].send_msg(msg);      
        }  
   
        fl = fl->next;
    }   
}


static void unpack_gateway_rx_mbox_0(hw_can_msg_t *msg) { unpack_gateway_rx_mbox(msg,HWC_CAN0); }
static void unpack_gateway_rx_mbox_1(hw_can_msg_t *msg) { unpack_gateway_rx_mbox(msg,HWC_CAN4); }


void ap_gateway_initialize(void)
{
    for (uint8_t i = 0; i<HWC_CAN_QTY; ++i)
    {
        gatway_rx_mbox[i].rx_id     .set_J1939ID(0, 0x00, 0x00, 0x00); 	 
        gatway_rx_mbox[i].rx_id_mask.set_J1939ID(0, 0x00, 0x00, 0x00); 	         
        gatway_rx_mbox[i].rx_callback = i==0? unpack_gateway_rx_mbox_0:unpack_gateway_rx_mbox_1 ;            
        gatway_rx_mbox[i].initialize();
        
        hw_can_rx_handler[i].add_msg    (&gatway_rx_mbox[i]    );        
    }    
    
    ap_gateway_routes.initialize();	       
}

void ap_gateway_update    (void)
{    

}


