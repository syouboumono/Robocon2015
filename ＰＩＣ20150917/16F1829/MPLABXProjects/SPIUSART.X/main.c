#include <xc.h>
#include <pic16f1829.h>
#include "pic16f1829_config.h"
#include "spi.h"

void interrupt inter(void){
    r_data = slaveread();
    
    while(TXIF==0);     // ���M�\�ɂȂ�܂ő҂�
    TXREG = r_data;   // ���M��(TXIF == 1)
    TXIF = 0; //���M�I��(���M�\TXIF == 0�ƂȂ�)
//    while(TXIF==0);
//    TXREG = '\n';
//    TXIF = 0;
//    while(TXIF==0);
//    TXREG = '\r';
//    TXIF = 0;
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
    
    
    //USART�ݒ�
    RXDTSEL = 0;
    TXCKSEL = 0;
    TXSTA   = 0b00100100;     
    RCSTA   = 0b10010000;     
    SPBRG   = 51;  
    
    //SPI�ݒ�
    slave_reg();
    
    //���ӁA�S��
    PEIE        = 1;
    GIE         = 1;
    
    while(1){
//        while(TXIF==0);     // ���M�\�ɂȂ�܂ő҂�
//        TXREG = r_data;   // ���M��(TXIF == 1)
//        TXIF = 0; //���M�I��(���M�\TXIF == 0�ƂȂ�)
//        while(TXIF==0);
//        TXREG = '\n';
//        TXIF = 0;
//        while(TXIF==0);
//        TXREG = '\r';
//        TXIF = 0;
    }
}