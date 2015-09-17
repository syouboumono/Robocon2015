#include <xc.h>
#include <pic16f1827.h>
#include "Init.h"
#include "SPI.h"

void interrupt InterSPI(void)
{
    R_data = SlaveRead();
}

void main(void)
{
    OSCCON   = 0x72;        //clkf=8MHz
    SlaveInit();
    PORTA   = 0b00000000;  //pin all low
    PORTB   = 0b00000000;  //pin all low
    
    while(1){
        if(R_data == 0x01){
            RA2 = 1;
        }else{
            RA2 = 0;
        }
    }
}