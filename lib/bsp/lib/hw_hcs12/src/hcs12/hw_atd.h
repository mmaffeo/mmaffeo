
// Reference Documents
// 
//  Motorola S12ATD10B8CV2/D (ATD_10B8C Block User Guide V02.10)

#include "hw_mcu.h"


class hw_atd
{
public:
    struct reg_t 
    {
        uint8_t atdctl0;   // reserved 
        uint8_t atdctl1;   // reserved
        uint8_t atdctl2;   // ATD Control Register 2
        uint8_t atdctl3;   // ATD Control Register 3
        uint8_t atdctl4;   // ATD Control Register 4
        uint8_t atdctl5;   // ATD Control Register 5
        uint8_t atdsttat0; // ATD Status  Register 0 
        uint8_t nu1;
        uint8_t atdtest0;
        uint8_t atdtest1;
        uint8_t nu2;
        uint8_t atdstat1;  // ATD Status Register 1  
        uint8_t nu3;
        uint8_t atdien;    // ATD Input Enable Register
        uint8_t nu4;
        uint8_t portad;    // Port Data Register
        uint16_t atddr[8];  // ATD Data Registers
    } ;        
    
    enum ch_t
    {
        CH0, CH1, CH2, CH3, CH4, CH5, CH6, CH7, CH_ALL
    };    
    
    struct cfg_t
    {
        uint8_t initial_ATDCTL4;  
        uint8_t initial_ATDCTL5;  
    };
            
    static const cfg_t DEFAULT_CFG;
    
               
                         
    void initialize(reg_t * reg_, const cfg_t *cfg_=&DEFAULT_CFG  );
    
    void StartMeasurement(ch_t channel);
    
    bool MeasurementDone(ch_t channel);
    
    void GetData(ch_t channel, uint16_t *buffer);
    
  
private:    
    reg_t *reg;
    const cfg_t *cfg;    
    
};
    
 