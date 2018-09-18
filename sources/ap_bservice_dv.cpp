

#include "ap_bservice_dv.h"




void dv_table_block::initialize(uint8_t block_id_) 
{
    block_id = block_id_;

    read_dword_f  = NULL;
    write_dword_f = NULL;
    
    read_word_f  = NULL;
    write_word_f = NULL;
  
    read_byte_f  = NULL;
    write_byte_f = NULL;
        
    next = NULL;       
}
       


dv_table_block_list dv_list;





void dv_table_block_list::add_block(dv_table_block * blk)
{
    blk->next = NULL;
        
    if (first == NULL)
    {
        first = blk;
    }	          
    else
    {
        dv_table_block *p=first;
        while ( p->next !=NULL)
            p = p->next;
    
        p->next = blk;               
    }					      
}



uint8_t dv_table_block_list::read_byte(uint16_t i)
{
    dv_table_block *p=GetBlock(i >> 8   );  
    
    uint8_t rvalue=0;
    
    if (p != NULL)
        rvalue = p->read_byte       (i &  0xFF);
    
    return rvalue;
}

uint16_t dv_table_block_list::read_word(uint16_t i)
{
    dv_table_block *p=GetBlock(i >> 8   );
    
    uint16_t rvalue=0;
    if (p != NULL)
        rvalue = p->read_word       (i &  0xFF);
    
    return rvalue;        
}

uint32_t dv_table_block_list::read_dword(uint16_t i)
{
    dv_table_block *p=GetBlock(i >> 8   );
    
    uint32_t rvalue=0;
    if (p != NULL)
        rvalue = p->read_dword       (i &  0xFF);
    
    return rvalue;        
}

void dv_table_block_list::write_byte(uint16_t i, uint8_t data)
{
    dv_table_block *p=GetBlock(i >> 8   );  
    
    if (p != NULL)
        p->write_byte(i&0xFF, data);
       
}

void dv_table_block_list::write_word(uint16_t i, uint16_t data)
{
    dv_table_block *p=GetBlock(i >> 8   );
    
    if (p != NULL)
        p->write_word(i&0xFF, data);     
}

void dv_table_block_list::write_dword(uint16_t i, uint32_t data)
{
    dv_table_block *p=GetBlock(i >> 8   );
    
    if (p != NULL)
        p->write_dword(i&0xFF, data);     
}

dv_table_block * dv_table_block_list::GetBlock(uint16_t b_id)
{
    dv_table_block *p=first;
    
    while (p != NULL && p->id() != b_id )
        p = p->next;

    return p;      
}







