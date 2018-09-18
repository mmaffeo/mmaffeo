
// Reference Documents
// 
//  Motorola S12SPIV2/D (SPI Block User Guide V02.07)

#ifndef hw_spi_h
#define hw_spi_h

#include "hw_mcu.h"


class hw_spi
{
public:
    struct reg_t 
    {
        uint8_t SPICR1;   // SPI Control Register 1
        uint8_t SPICR2;   // SPI Control Register 2
        uint8_t SPIBR;    // SPI Baud Rate Register
        uint8_t SPISR;    // SPI Status Register
        uint8_t reserved1;
        uint8_t SPIDR;    // SPI data register
        uint8_t reserved2;
        uint8_t reserved3;
    } ;        
    
    struct cfg_t
    {
        uint8_t  initial_SPICR1;  
        uint8_t  initial_SPICR2;
        uint16_t baud_rate_kHz;  
    };
            
    static const cfg_t DEFAULT_CFG;     
               
                         
    void initialize(reg_t * reg_, const cfg_t *cfg_=&DEFAULT_CFG  );
    
    
    bool    TxChar(uint8_t data);
    
    uint8_t RxDataAvailiable(void);
    
    uint8_t RxChar(void);    
    
  
private:    
    reg_t *reg;
    const cfg_t *cfg;    
    
};
    
 
 
#endif 