#include <xc.h>
#include <pic16f1827.h>
#include "Init.h"

void main(void)
{
    OSCCON   = 0x72;  //clkf=8MHz
    TRISA    = 0x00;
    TRISB    = 0x00;
    PORTA    = 0x00;
    PORTA    = 0x00;
    ANSELA   = 0x00;
    ANSELB   = 0x00;
    
    while(1){
        
       
    }
}