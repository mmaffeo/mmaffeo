
#ifndef ap_gatwway_h
#define ap_gateway_h






///////////////////////////////////////////////////////////////////////////////////////////////////
// CAN message filter class
///////////////////////////////////////////////////////////////////////////////////////////////////
class hw_can_msg_filter_t
{
public:				   
    hw_can_id id_value;
    hw_can_id id_mask;
    
    uint8_t data_value[2];
    uint8_t data_mask[2];    
    
    void initialize(void);    
    bool match(const hw_can_msg_t *msg )const;   
    
    hw_can_msg_filter_t *next; 
    
    enum 
    {
        RT_CAN0_TO_CAN4 = 0x01,
        RT_CAN4_TO_CAN0 = 0x02
    };
    uint8_t route; 
    
    
private:  
};




class hw_can_msg_filter_list
{
public:
    void initialize(void) ;
    void add(hw_can_msg_filter_t *f);    
    
    hw_can_msg_filter_t *first;		     
};
////////////////////////////////////////////////////////////////////////////////////////////////////

extern hw_can_msg_filter_list ap_gateway_routes;



void ap_gateway_initialize(void);
void ap_gateway_update    (void);
void initialize_gateway_filters(void);

#endif


