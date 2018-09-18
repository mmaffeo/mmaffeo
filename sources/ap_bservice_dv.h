////////////////////////////////////////////////////////////////////////////////////////////////////
//  This module has been created in an attempt to modularize the Bobcat "dv_table" concept.
//
//  The "dv_table" is an indirect memory read/write facility that is accessed via some
//  proprietarty CAN messages.
//
//  The "dv_table" has been modularized into "dv_table_block"s
//
//  The "dv_table" is replaced with a "dv_list".
//  The "dv_list" consists of multiple "dv_table_block"s
//
//  The "dv_table" previously had a 16-bit linear address space.
//
//  Each "dv_table_block" has an 8-bit address space and a fixed 8-bit "block_id".
//
//  When converting an old "dv_table" to the new "dv_list".
//    -> the MSByte of the "dv_table" address would map to a "dv_table_block" block_id.
//    -> the LSByte of the "dv_table" address would map to a "dv_table_block"s address space.


// Example usage:
//
//   // create a "dv_table_block" for the a particular module.
//   dv_table_block fan_block;
//
//   // create the fan module's table
//   void * const fan_dv_table[10] =
//   {
//       (void*)&fan_command,
//       (void*)&fan_speed,
//       (void*)&engine_temperature,
//       (void*)&fan_mode
//   };
//
//
//   // somewhere in an initialize function that gets called once on power-up
//   #define FAN_DV_BLOCK_ID 0x01
//
//   fan_block.initialize(FAN_DV_BLOCK_ID,(void **)fan_dv_table);
//   dv_list.add_block(&fan_block);
//
//   // this fan module "dv_table_block" will now be connected to the "dv_table"
//   // read/write can messages.


#ifndef ap_bservice_dv_h
#define ap_bservice_dv_h

#include <stdint.h>
#include <stddef.h>


class dv_table_block
{
public:
    void initialize(uint8_t     block_id_);

    void set_read_byte_f  ( uint8_t  (* read_byte_f_ ) (uint16_t)) { read_byte_f  = read_byte_f_;   }
    void set_read_word_f  ( uint16_t (* read_word_f_ ) (uint16_t)) { read_word_f  = read_word_f_;   }
    void set_read_dword_f ( uint32_t (* read_dword_f_) (uint16_t)) { read_dword_f = read_dword_f_;  }

    uint8_t  read_byte  (uint8_t i ) {  return read_byte_f  ? read_byte_f(i)  : 0;  };
    uint16_t read_word  (uint8_t i ) {  return read_word_f  ? read_word_f(i)  : 0;  };
    uint32_t read_dword (uint8_t i ) {  return read_dword_f ? read_dword_f(i) : 0;  };

    void set_write_byte_f ( void (*write_byte_f_ ) (uint16_t, uint8_t  data)) { write_byte_f  = write_byte_f_;   }
    void set_write_word_f ( void (*write_word_f_ ) (uint16_t, uint16_t data)) { write_word_f  = write_word_f_;   }
    void set_write_dword_f( void (*write_dword_f_) (uint16_t, uint32_t data)) { write_dword_f = write_dword_f_;  }

    void write_byte (uint8_t i, uint8_t  data) { if (write_byte_f ) write_byte_f (i,data); };
    void write_word (uint8_t i, uint16_t data) { if (write_word_f ) write_word_f (i,data); };
    void write_dword(uint8_t i, uint32_t data) { if (write_dword_f) write_dword_f(i,data); };


    uint8_t id(void)                            { return block_id;              }

  dv_table_block *next;
private:
    uint8_t block_id;

    uint8_t  (*read_byte_f)  (uint16_t);
    uint16_t (*read_word_f)  (uint16_t);
    uint32_t (*read_dword_f) (uint16_t);
    void     (*write_byte_f) (uint16_t i, uint8_t  data);
    void     (*write_word_f) (uint16_t i, uint16_t data);
    void     (*write_dword_f)(uint16_t i, uint32_t data);
};



class dv_table_block_list
{
public:
    uint8_t  read_byte (uint16_t i           );
    uint16_t read_word (uint16_t i           );
    uint32_t read_dword(uint16_t i           );

    void write_byte (uint16_t i, uint8_t  data);
    void write_word (uint16_t i, uint16_t data);
    void write_dword(uint16_t i, uint32_t data);

    void add_block(dv_table_block * blk);

private:
    dv_table_block *GetBlock(uint16_t b_id);
    dv_table_block *first;
};


extern dv_table_block_list dv_list;


#endif