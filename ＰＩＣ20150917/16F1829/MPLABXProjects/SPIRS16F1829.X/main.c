#include <pic16f1829.h>
#include <xc.h>
#include "pic16f1829_config.h"
#include "spi.h"

unsigned char s_data = 0x00;

void interrupt interspi(void)
{
    if(IOCBFbits.IOCBF7 == 1){
        SSP1BUF = s_data;
        IOCBFbits.IOCBF7 = 0;
        s_data++;
    }
    r_data = slaveread();
}

void main(void)
{
    OSCCON  = 0x72;
    TRISA   = 0x00;
    TRISB   = 0xD0;
    TRISC   = 0x40;
    PORTA   = 0x00;
    PORTB   = 0x00;
    PORTC   = 0x00;
    ANSELA  = 0x00;
    ANSELB  = 0x00;
    ANSELC  = 0x00;
    
    //SPI�ݒ�
    SSP1CON1    = 0b00100100;
    SSP1STAT    = 0b00000000;
    
    //�s�����荞�ݐݒ�
    IOCBN   = 0x80; //����������G�b�W�̏�ԕω����荞�݃��W�X�^
    IOCIE   = 1;    //IO�G�b�W���荞�ݗL��
    IOCBF   = 0;
    SSP1IF  = 0;
    SSP1IE  = 1;
    PEIE    = 1;    //���ӑ��u���荞�ݗL��
    GIE     = 1;    
    
    while(1){
        if(r_data == 0x00){
            RA5 = 0;
        }else{
            RA5 = 1;
        }
    }
    
}