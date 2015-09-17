#include <xc.h>
#include <pic16f1827.h>
#include "Init.h"

void main()
{
    OSCCON  = 0x72;        //clkf=8MHz
    TRISA   = 0x00;
    PORTA   = 0x00;
    ANSELA  = 0x00;
    TRISB   = 0x00;
    PORTB   = 0x00;
    ANSELB  = 0x00;

    while(1){
        Lchika(RA2);
    }

}



