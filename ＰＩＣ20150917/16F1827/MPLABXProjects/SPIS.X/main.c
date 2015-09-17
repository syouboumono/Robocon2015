#include <xc.h>
#include <pic16f1827.h>
#include "Init.h"
#include "SPI.h"

void Delay(int time){
    int i;
    for(i=0;i<time;i++){
        __delay_ms(1);
    }
}

unsigned char val = 0x01;

void main(void)
{
    OSCCON   = 0x72;  //clkf=8MHz
    MasterInit();
    PORTA    = 0b00000000;  //pin all low
    PORTB    = 0b00000000;  //pin all low
   
    while(1){
        MasterSend(SS_RA2,val);
        if(val == 0x01){
            val = 0x00;
        }else{
            val = 0x01;
        }
        Delay(1000);
    }     
}
