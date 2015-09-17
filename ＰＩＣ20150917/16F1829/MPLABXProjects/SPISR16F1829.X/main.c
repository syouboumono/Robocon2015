#include <pic16f1829.h>
#include <xc.h>
#include "pic16f1829_config.h"
#include "spi.h"

void main(void)
{
    unsigned char a = 0x01;
    unsigned char b = 0x00;
    
    
    OSCCON  = 0x72;
    master_reg();
    
    while(1){
        
        r_data = mastersend(SS_RB7,a);
        if(r_data == 0x01){
            RA5 = 1;
            __delay_ms(1000);
            RA5 = 0;
            __delay_ms(1000);
        }else{
            RA5 = 0;
        }
        __delay_ms(1000);
        
        r_data = mastersend(SS_RB7,b);
        if(r_data == 0x01){
            RA5 = 1;
            __delay_ms(1000);
            RA5 = 0;
            __delay_ms(1000);
        }else{
            RA5 = 0;
        }
        __delay_ms(1000);
   
    }
}
