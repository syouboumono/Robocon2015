#include <pic16f1829.h>
#include <xc.h>
#include "Init.h"

void main(void)
{
    OSCCON  = 0x72;
    TRISA   = 0x00;
    PORTA   = 0x00;
    ANSELA  = 0x00;
    TRISB   = 0x00;
    PORTB   = 0x00;
    ANSELB  = 0x00;
    TRISC   = 0x00;
    PORTC   = 0x00;
    ANSELC  = 0x00;
    
    while(1){
        RA0 = 1;
        __delay_ms(100);
        RA0 = 0;
        
        RB4 = 1;
        __delay_ms(100);
        RB4 = 0;
        
        RC0 = 1;
        __delay_ms(100);
        RC0 = 0;
    }
    
    
    
}