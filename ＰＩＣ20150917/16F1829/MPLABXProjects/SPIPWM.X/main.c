#include <pic16f1829.h>
#include <xc.h>
#include "pic16f1829_config.h"
#include "usart.h"
#include "spi.h"
#define MAX_OPE 124

unsigned char ope = 0;

void interrupt inter(void){
    
    ope = slaveread();
    
    if(ope & 0x80){
        CCP1CON = 0xCC;
    }else{
        CCP1CON = 0x4C;
    }
    
    if((ope & 0x7F) <= MAX_OPE){
        CCPR1L = ope & 0x7F;
    }else{
        CCPR1L = MAX_OPE;
    }
}

void main(void)
{
    
    OSCCON  = 0x72;
    TRISA   = 0x30;
    TRISB   = 0x70;
    TRISC   = 0x40;
    PORTA   = 0x00;
    PORTB   = 0x00;
    PORTC   = 0x00;
    ANSELA  = 0x00;
    ANSELB  = 0x00;
    ANSELC  = 0x00;
    WPUA    = 0x30;
    
    //PWM
    CCPTMRS     = 0x00; //Timer2
    CCP1CON     = 0xCC; //other 0x4C
    PSTR1CON    = 0x0A;
    CCPR1L      = 0;    //change the dutty
    P1CSEL      = 0;
    P1DSEL      = 0;
    T2CON       = 0x00; //*1
    PR2         = MAX_OPE;  //PWMf 16kHz
    CCPR1L      = 0;
    CCPR1H      = 0;
    TMR2        = 0;
    TMR2ON      = 1;
    
    //USARTÝ’è
    RXDTSEL = 0;
    TXCKSEL = 0;
    TXSTA   = 0b00100100;     
    RCSTA   = 0b10010000;     
    SPBRG   = 51;  
    
    //SPIÝ’è
    slave_reg();
 
    //timer
    TMR0        = 156;
    T0IF        = 0;
    T0IE        = 1;
    
    //Žü•ÓA‘S‘Ì
    PEIE        = 1;
    GIE         = 1;
    
    
    
    while(1);
}
