#include <pic16f1829.h>
#include <xc.h>
#include "pic16f1829_config.h"
#include "usart.h"
#define MIN_RAD 0.72
#define ONE_COUNT 0.000001


int time = 0;
signed int count = 0;
int rad = 0;



void interrupt check(void){
    
    
    if(IOCAFbits.IOCAF4 == 1){
        if(RA5 == 1){
            count++;
            //sousin(count);
        }else{
            count--;
            //sousin(count);
        }
        IOCAFbits.IOCAF4 = 0;
    }
    
    if(T0IF == 1){
        TMR0 = 156;
        time++;
        T0IF = 0;
    }
}

void main(void)
{
    OSCCON  = 0x7A;
    TRISA   = 0x30;
    TRISB   = 0xA0;
    TRISC   = 0x00;
    PORTA   = 0x00;
    PORTB   = 0x00;
    PORTC   = 0x00;
    ANSELA  = 0x00;
    ANSELB  = 0x00;
    ANSELC  = 0x00;
    WPUA    = 0x30;
    
    //USART設定
    RXDTSEL = 0;
    TXCKSEL = 0;
    TXSTA  = 0b00100100 ;     
    RCSTA  = 0b10010000 ;     
    SPBRG  = 103 ;  
    
    //割り込みの許可
    OPTION_REG  = 0x01; //プリスケール*2,プルアップ抵抗ON
    //timer
    TMR0        = 156;
    T0IF        = 0;
    T0IE        = 1;
    //pin
    IOCAP       = 0x10;
    IOCAF       = 0;
    IOCIE       = 1;
    //周辺、全体
    PEIE        = 1;
    GIE         = 1;
       
    while(1){
        if(time == 500){//50ms
            sousin(count);
            time = 0;
            count = 0;
        }
    }
}