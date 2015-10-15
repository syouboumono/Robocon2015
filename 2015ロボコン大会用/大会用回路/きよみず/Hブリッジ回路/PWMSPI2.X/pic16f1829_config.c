#include <pic16f1829.h>
#include <xc.h>
void pic_reg()
{
    
    OSCCON  = 0x72;
    TRISA   = 0x00;
    TRISB   = 0x50;
    TRISC   = 0x40;
    PORTA   = 0x00;
    PORTB   = 0x00;
    PORTC   = 0x00;
    ANSELA  = 0x00;
    ANSELB  = 0x00;
    ANSELC  = 0x00;
    
}