#include <pic16f1829.h>
#include <xc.h>
#include "pic16f1829_config.h"
#include "spi.h"

void main(void)
{
    unsigned char a = 0x01;
    unsigned char b = 0x02;
    unsigned char c = 0x04;
    unsigned char d = 0x08;
    
    OSCCON  = 0x72;
    master_reg();
    
    while(1){
        
        mastersend(SS_RA0,a);
        __delay_ms(200);
        mastersend(SS_RA0,b);
      __delay_ms(200);
        mastersend(SS_RA0,c);
       __delay_ms(200);
        mastersend(SS_RA0,d);
       __delay_ms(200);
   
    }
}