#include <pic16f1829.h>
#include <xc.h>
#include "Init.h"

void main(void)
{
    int i = 0;
    
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
    
    //PWM
    CCPTMRS     = 0x00; //Timer2
    CCP1CON     = 0xCC; //other 0x4C
    PSTR1CON    = 0x0A;
    CCPR1L      = 0;    //change the dutty
    P1CSEL      = 0;
    P1DSEL      = 0;
    T2CON       = 0x00; //*1
    PR2         = 124;  //PWMf 16kHz
    CCPR1L      = 0;
    CCPR1H      = 0;
    TMR2        = 0;
    TMR2ON      = 1;
    
    while(1){
        
        if(i == 124){
            i = 0;
        }
     
        CCPR1L = 62;
        __delay_ms(100);
        i++;
    }
           
}
